/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/

/*
 *  vsip/TASP_VSIPLcore/src_core/linalg/vsip_spclslvrs_f/vsip_cllsqsol_f.c
 *  Vsip Library Component
 *
 *  Avijit Purkayastha
 *  High Performance Computing Laboratory
 *  Department of Computer Science and NSF Engineering Research Center
 *  Mississippi State University, Mississippi State, MS 39762
 *                             and
 *  Department of Mathematics
 *  University of Puerto Rico, Mayaguez, PR 00681.
 *
 *  Contact Information:
 *  Phone: (601) 325-2565; Fax: (601) 325-7692
 *  avijit@erc.msstate.edu; avijit@cs.upr.clu.edu
 *
 * -  -   -   -   -   -   -  -  -  -  -  -  -  -  -  -  -  -  -
 *
 * Copyright (C) Mississippi State University, 1998.
 *
 * Permission is hereby granted for using this software to all persons to
 * copy, modify, distribute and produce derivative works for any purpose
 * and without any restrictions, provided that this copyright notice and the
 * following disclaimer appear on all copies. This computer code also does
 * not make any warranty, express or implied, or assumes any legal liability
 * or  responsibility for  the accuracy, completeness or usefulness of any
 * of any information, apparatus, product or  process  disclosed, or
 * represents that its  use would not infringe privately owned rights.
 *
 * Work supported under contract from DARPA (TASP) through the US Air Force
 * Rome Laboratory, under contracts F30602-95-1-0036 and F30602-96-1-0329.
 * Any opinions, findings and conclusions or recommendations expressed
 * in this material are those of the author(s) and do not necessarily
 * reflect the views of U.S. Department of Energy or Mississippi State
 * University or University of Puerto Rico.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
 *
 *  Author: A. Purkayastha
 *
 *  created:          april-22-99 (AP)
 *
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
 */
/* $Id: vsip_cllsqsol_f.c,v 1.1 1999/12/02 17:38:11 judd Exp judd $ */

#include<vsip.h>
#include<vsip_cmviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_vviewattributes_vi.h>


int vsip_cllsqsol_f(
                  const vsip_cmview_f *A,
                  const vsip_cmview_f *XB)
{
  int retval=0;
  int i;
  vsip_cmattr_f Mattr;
  vsip_cvattr_f Vattr; 

  vsip_cmview_f   mat, *solmat = &mat;
  vsip_cvview_f   ddview,  *rdview  = &ddview,
                 rrview,  *rview   = &rrview,
                 llcview, *lqview  = &llcview,
                 qqview,  *qview   = &qqview,
                 xxb,     *xb      = &xxb,
                 tmp,     *temp    = &tmp,
                 ccview,  *lviews  = &ccview;

  vsip_length M, N, NN, NB;
  vsip_cscalar_f alpha, sum, sigma, r11, tau, beta; 
  vsip_cscalar_f scale, scale_val;
  vsip_scalar_vi j,k, where;
  vsip_scalar_vi rst = A->row_stride;
  vsip_scalar_vi cst = A->col_stride;


#ifdef VSIP_DEVELOPMENT_MODE
    rview->markings   = vsip_valid_structure_object;
    rdview->markings  = vsip_valid_structure_object;
    lqview->markings  = vsip_valid_structure_object;
    qview->markings  = vsip_valid_structure_object;
    lviews->markings  = vsip_valid_structure_object;
    xb->markings      = vsip_valid_structure_object;
    temp->markings    = vsip_valid_structure_object;
    solmat->markings  = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */

     /*get lengths */
     M  = vsip_cmgetcollength_f(A);
     N  = vsip_cmgetrowlength_f(A);
     NN = vsip_cmgetcollength_f(XB);
     NB = vsip_cmgetrowlength_f(XB);

       if(N < M)
     NN = N;  /* look at the first n col elemts of soln vec, if N < M */


     /* get attributes */
     vsip_cmgetattrib_f(A, &Mattr);

     /* set up views to point to proper block */
     lqview->block     = Mattr.block;
     qview->block     = Mattr.block;
     lviews->block     = Mattr.block;
     rdview->block     = Mattr.block;
     rview->block      = Mattr.block;
     temp->block       = Mattr.block;
    /*clone XB and xb */
     vsip_cmgetattrib_f(XB, &Mattr);
     solmat->block = XB->block;
     xb->block  = XB->block;
     Vattr.offset = Mattr.offset;
     Vattr.stride = Mattr.col_stride;
     Vattr.length = Mattr.col_length;
     vsip_cvputattrib_f(xb, &Vattr);
     vsip_cmputattrib_f(solmat, &Mattr);

     /* Start QR using Householder's alg. */
     /* Step 1 -- QR decomp and updating rhs on the fly*/
     /* set up views with proper attributes */
     Vattr.offset = A->offset;
     Vattr.stride = cst + rst; Vattr.length = N;
     vsip_cvputattrib_f(rdview, &Vattr);

     Vattr.offset = A->offset;
     Vattr.stride = cst; Vattr.length = M;
     vsip_cvputattrib_f(lqview, &Vattr);

     Vattr.offset = A->offset + rst;
     Vattr.stride = cst; Vattr.length = M;
     vsip_cvputattrib_f(lviews, &Vattr);

     Vattr.offset = A->offset;
     Vattr.stride = cst; Vattr.length = M;
     vsip_cvputattrib_f(qview,  &Vattr);
     
     k=0;
     scale = vsip_cmplx_f((vsip_scalar_f)sqrt(vsip_vcmaxmgsqval_f(lqview, &where)),0);
     scale_val = vsip_cvget_f(lqview, where);
       if( vsip_cmag_f(scale) == 0.0)
       {
         retval++;
         r11 = vsip_cmplx_f(0,0);

       } else {
         vsip_csvmul_f(vsip_crecip_f(scale_val), 
		       lqview, lqview);
	 r11 = vsip_cvget_f(lqview,0);
	 sum = vsip_cvjdot_f(qview, qview);

         sigma = (vsip_cmag_f(vsip_cvget_f(qview, 0)) >= 0.0) ? 
	   vsip_csqrt_f(sum) : vsip_cneg_f(vsip_csqrt_f(sum));
	
	 vsip_cvput_f(qview,0,vsip_cadd_f(vsip_cvget_f(qview,0),sigma));

	 tau = vsip_cmul_f(sigma,vsip_cvget_f(qview, 0));

	 for(j=k+1; j<N; j++)
         {
           sum = vsip_cvjdot_f(qview, lviews);
           beta = vsip_cdiv_f(sum,tau);
           vsip_cvsma_f(qview, vsip_cneg_f(vsip_conj_f(beta)), 
					   lviews, lviews);
           lviews->offset += rst;

         } /*end j for loop */
         r11 =  vsip_cmul_f(vsip_cneg_f(scale_val),sigma);
       } /* end if loop */
       /* update rhs w/qview */
       for(i=0; i < (int)NB; i++)
       {
	 alpha = vsip_cvjdot_f(qview,xb);
	 beta = vsip_cdiv_f(alpha,tau);
	 vsip_cvsma_f(qview,vsip_cneg_f(vsip_conj_f(beta)),xb,xb);
 	 xb->offset += XB->row_stride;
       }

       /* update views */
       lqview->offset += rst+cst; lqview->length--; 
       qview->offset += cst; qview->length--;   
       lviews->offset = lqview->offset+rst;
       lviews->length = lqview->length;
       xb->offset = XB->offset + XB->col_stride;
       xb->length--;
       vsip_cvput_f(rdview,0,r11);

     /* Get remaining cols of Q, one at a time and overlap updating rhs*/
     for (k=1; k <((N < M)? N : (N-1)); k++)
     {
       scale = vsip_cmplx_f((vsip_scalar_f)sqrt(vsip_vcmaxmgsqval_f(lqview, &where)),0);
       scale_val = vsip_cvget_f(lqview, where);
       if( vsip_cmag_f(scale) == 0.0)
       {
         retval++;
         vsip_cvput_f(rdview, k, vsip_cmplx_f(0,0));

       } else {
         vsip_csvmul_f(vsip_crecip_f(scale_val), 
				     lqview,qview);

         sum = vsip_cvjdot_f(qview, qview);
        
	 sigma = (vsip_cmag_f(vsip_cvget_f(qview, 0)) >= 0.0) ? 
	   vsip_csqrt_f(sum) : vsip_cneg_f(vsip_csqrt_f(sum));

         vsip_cvput_f(qview,0,vsip_cadd_f(vsip_cvget_f(qview,0),sigma));

         tau= vsip_cmul_f(sigma,vsip_cvget_f(qview, 0));

         for(j=k+1; j<N; j++)
         {
           sum = vsip_cvjdot_f(qview, lviews);
           beta = vsip_cdiv_f(sum,tau);
           vsip_cvsma_f(qview, vsip_cneg_f(vsip_conj_f(beta)), 
			lviews, lviews);
           lviews->offset += rst;

         } /*end j for loop */
         vsip_cvput_f(rdview, k, 
		      vsip_cmul_f(vsip_cneg_f(scale_val),
                                  sigma));
       } /* end if loop */ 
       /* update rhs w/qview */
       for(i=0; i < (int)NB; i++)
       {
	 alpha = vsip_cvjdot_f(qview,xb);
	 beta = vsip_cdiv_f(alpha,tau);
	 vsip_cvsma_f(qview,vsip_cneg_f(vsip_conj_f(beta)),xb,xb);
	 xb->offset += XB->row_stride;
       }
       /* update views */
       lqview->offset += rst+cst;
       lqview->length--;       
       qview->length--;
       lviews->offset = lqview->offset+rst;
       lviews->length = lqview->length;
       xb->offset = XB->offset + (k+1)*XB->col_stride;
       xb->length--;
     }/* end k for loop */

     /* Step 2 -- Solve UT system */
    Vattr.offset = A->offset + (N-2)* cst + (N-1)* rst;
    Vattr.stride = rst;
    Vattr.length = 1;
    vsip_cvputattrib_f(rview, &Vattr); 

    Vattr.offset = XB->offset + (NN-1)*XB->col_stride;
    Vattr.stride = XB->row_stride;
    Vattr.length = XB->row_length;
    vsip_cvputattrib_f(xb, &Vattr);

    solmat->offset = XB->offset + (NN-1) * solmat->col_stride;
    solmat->col_length = 1;

    Vattr.offset = A->offset + cst;
    Vattr.stride = cst;
    Vattr.length = NB;
    vsip_cvputattrib_f(temp, &Vattr);

    /* do the diagonal scaling */
    alpha = vsip_crecip_f(vsip_cvget_f(rdview,N-1));
    if(vsip_cmag_f(vsip_cvget_f(rdview,N-1)) == 0.0)
      retval++;

    vsip_csvmul_f(alpha, xb, xb);
    xb->offset -= XB->col_stride;

    for(i = NN-2; i >= 0; i--)
    {
      vsip_cvmprod_f(rview, solmat, temp);

      /* update soln */
      vsip_cvsub_f(xb,temp,xb);

      alpha = vsip_crecip_f(vsip_cvget_f(rdview,i));

      vsip_csvmul_f(alpha, xb, xb);

      /* update views */
      rview->offset -= (rst + cst); rview->length++;
      solmat->offset -= solmat->col_stride;
      solmat->col_length++;
      if(i > 0)
        xb->offset -= XB->col_stride;
    }

    return(retval);
}

