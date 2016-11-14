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
 *  vsip/TASP_VSIPLcore/src_core/linalg/vsip_spclslvrs_f/vsip_ccovsol_f.c
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
/* $Id: vsip_ccovsol_f.c,v 1.1 1999/12/02 17:38:09 judd Exp judd $ */

#include<vsip.h>
#include<vsip_cmviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_vviewattributes_vi.h>


int vsip_ccovsol_f(
		  const vsip_cmview_f *A,
		  const vsip_cmview_f *XB)
{
  int retval=0;
  vsip_stride i;
  vsip_cmattr_f Mattr;
  vsip_cvattr_f Vattr;

  vsip_cmview_f mat, *solmat = &mat;
  vsip_cvview_f   ddview,  *rdview    = &ddview,
                 qview,   *lqview    = &qview,
                 ccview,  *lviews    = &ccview,
                 xxvec,   *xvec      = &xxvec,
                 ttemp,   *temp      = &ttemp;

  vsip_length M, N, NN, NB;
  vsip_cscalar_f sum, scale, sigma, tau, onebytau, beta;
  vsip_cscalar_f val_where;
  vsip_scalar_vi where;
  vsip_scalar_vi j, k;
  vsip_scalar_vi rst = A->row_stride;
  vsip_scalar_vi cst = A->col_stride;

#ifdef VSIP_DEVELOPMENT_MODE
    rdview->markings  = vsip_valid_structure_object;
    lqview->markings  = vsip_valid_structure_object;
    lviews->markings  = vsip_valid_structure_object;
    xvec->markings    = vsip_valid_structure_object;
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
     rdview->block     = Mattr.block;
     lqview->block     = Mattr.block;
     lviews->block     = Mattr.block;
     temp->block       = Mattr.block;

     /* Step 1 -- Do QR factorisation first */
     /* set up views with proper attributes */

     Vattr.offset = Mattr.offset;
     Vattr.stride = rst + cst; Vattr.length = N;
     vsip_cvputattrib_f(rdview, &Vattr);

     Vattr.stride = cst; Vattr.length = M;
     vsip_cvputattrib_f(lqview, &Vattr);

     Vattr.offset = Mattr.offset + rst;
     vsip_cvputattrib_f(lviews, &Vattr);

     /* main decomposition loop */

     for (k=0; k <((N < M)? N : (N-1)); k++)
     {
       scale = vsip_cmplx_f(0,0);
       scale = vsip_cmplx_f((vsip_scalar_f)sqrt(vsip_vcmaxmgsqval_f(lqview, &where)),0);
       if( vsip_cmag_f(scale) == 0.0)
       {
         retval++;
         vsip_cvput_f(rdview, k, vsip_cmplx_f(0,0));
       } else {
	 val_where = vsip_cvget_f(lqview,where);

         vsip_csvmul_f(vsip_crecip_f(val_where), 
		       lqview, lqview);

         sum = vsip_cvjdot_f(lqview, lqview);

	 sigma = (vsip_cmag_f(vsip_cvget_f(lqview, 0)) >= 0.0) ? 
	   vsip_csqrt_f(sum) : vsip_cneg_f(vsip_csqrt_f(sum));

         vsip_cvput_f(lqview,0,vsip_cadd_f(vsip_cvget_f(lqview,0),sigma));

	 onebytau = vsip_crecip_f(vsip_cmul_f(sigma, vsip_cvget_f(lqview, 0)));

         for(j=k+1; j<N; j++)
         {
           sum = vsip_cvjdot_f(lqview, lviews);

	   tau = vsip_cmul_f(sum,onebytau);

	   vsip_cvsma_f(lqview, vsip_cneg_f(vsip_conj_f(tau)), lviews, lviews);

	   lviews->offset += rst;

         } /*end j for loop */

         vsip_cvput_f(rdview,k,
		      vsip_cmul_f(vsip_cneg_f(val_where),sigma));

       } /* end if loop */
       /* update views */
       lqview->offset += rst+cst;
       lqview->length--;       
       lviews->offset = lqview->offset+rst;
       lviews->length = lqview->length;
     }/* end k for loop */
     
     if( N == M)
       vsip_cvput_f(rdview, N-1, vsip_cvget_f(lqview,0));

     /* end of QR decomp (Householder's) -- only R saved explicitly. */

     /* Solve the system R^T * R X = B */


     /* get\put matrix, vector  attributes */
     vsip_cmgetattrib_f(XB, &Mattr);
     solmat->block = Mattr.block;
     xvec->block = Mattr.block;
     vsip_cmputattrib_f(solmat, &Mattr);
     

     /* Step 2 --first solve LT system */
     /* get\put row attributes */
     vsip_cmgetattrib_f(A, &Mattr);

     Vattr.offset = Mattr.offset+cst;
     Vattr.stride = cst;
     Vattr.length = NB;
     vsip_cvputattrib_f(temp,&Vattr);

     Vattr.offset = Mattr.offset + rst;
     Vattr.stride = cst;
     Vattr.length = 1;
     vsip_cvputattrib_f(lviews, &Vattr);

     Vattr.offset = XB->offset;
     Vattr.stride = XB->row_stride;
     Vattr.length = XB->row_length;
     vsip_cvputattrib_f(xvec, &Vattr);

     solmat->col_length = 1;
    /* do the diagonal scaling */
    beta = vsip_crecip_f(vsip_conj_f(vsip_cvget_f(rdview,0)));
    if(vsip_cmag_f(vsip_cvget_f(rdview,0)) == 0.0)
      retval++;

    vsip_csvmul_f(beta, xvec, xvec);
    xvec->offset += XB->col_stride;

    for(i=1; i< (int)NN; i++)
    {
      vsip_cvconj_f(lviews,lviews);
      vsip_cvmprod_f(lviews, solmat, temp);
      /* update soln */
      vsip_cvsub_f(xvec,temp,xvec);

      beta = vsip_crecip_f(vsip_conj_f(vsip_cvget_f(rdview,i)));

      if(vsip_cmag_f(vsip_cvget_f(rdview,i)) == 0.0)
        retval++;
      vsip_csvmul_f(beta, xvec, xvec);
      
      /* reconjugate back */
      vsip_cvconj_f(lviews,lviews);

      /* update views */
      lviews->offset += rst; lviews->length++;
      solmat->col_length++;
      if(i < (int)NN - 1)
        xvec->offset += XB->col_stride;
    }

    /* end of LT solve */
    /* Step 3 -- UT solve */
    /* get\put vector attributes */
    
    Vattr.offset = Mattr.offset + (N-2)* cst + (N-1)*rst;
    Vattr.stride = rst;
    Vattr.length = 1;
    vsip_cvputattrib_f(lviews, &Vattr); 

    Vattr.offset = XB->offset + (NN-1)*XB->col_stride;
    Vattr.stride = XB->row_stride;
    Vattr.length = XB->row_length;
    vsip_cvputattrib_f(xvec, &Vattr);

    solmat->offset = XB->offset + (NN-1) * solmat->col_stride;
    solmat->col_length = 1;

    /* do the diagonal scaling */
    beta = vsip_crecip_f(vsip_cvget_f(rdview,N-1));
    if(vsip_cmag_f(vsip_cvget_f(rdview,N-1)) == 0)
      retval++;
    vsip_csvmul_f(beta, xvec, xvec);
    xvec->offset -= XB->col_stride;

    for(i = NN-2; i >= 0; i--)
    {
      vsip_cvmprod_f(lviews, solmat, temp);

      /* update soln */
      vsip_cvsub_f(xvec,temp,xvec);

      beta = vsip_crecip_f(vsip_cvget_f(rdview,i));

      vsip_csvmul_f(beta, xvec, xvec);

      /* update views */
      lviews->offset -= (rst + cst); lviews->length++;
      solmat->offset -= solmat->col_stride;
      solmat->col_length++;
      if(i > 0)
        xvec->offset -= XB->col_stride;
    }
    return(retval);

}
