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
/* $Id: vsip_llsqsol_d.c,v 1.1 1999/12/05 16:08:16 judd Exp judd $ */

/*
 *  vsip/TASP_VSIPLcore/src_core_double/linalg/vsip_spclslvrs_d/vsip_llsqsol_d.c
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
 *  created:          february-3-99 (AP)
 *
 *  last update:      april-9-99 (AP)
 *                    changed the algorithm from MGS based to Householder
 *                    based, to avoid extra creation/deletion of O(N^2)
 *                    workspace.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
 */

#include<vsip.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_vviewattributes_vi.h>


int vsip_llsqsol_d(
                  const vsip_mview_d *A,
                  const vsip_mview_d *XB)
{
  int retval=0;
  int i;
  vsip_mattr_d Mattr;
  vsip_vattr_d Vattr; 

  vsip_mview_d   mat, *solmat = &mat;
  vsip_vview_d   ddview,  *rdview  = &ddview,
                 rrview,  *rview   = &rrview,
                 llcview, *lqview  = &llcview,
                 qqview,  *qview   = &qqview,
                 xxb,     *xb      = &xxb,
                 tmp,     *temp    = &tmp,
                 ccview,  *lviews  = &ccview;

  vsip_length M, N, NN, NB;
  vsip_scalar_d alpha, sum, sigma, r11, tau, beta, scale;
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
     M  = vsip_mgetcollength_d(A);
     N  = vsip_mgetrowlength_d(A);
     NN = vsip_mgetcollength_d(XB);
     NB = vsip_mgetrowlength_d(XB);

       if(N < M)
     NN = N;  /* look at the first n col elemts of soln vec, if N < M */


     /* get attributes */
     vsip_mgetattrib_d(A, &Mattr);

     /* set up views to point to proper block */
     lqview->block     = Mattr.block;
     qview->block     = Mattr.block;
     lviews->block     = Mattr.block;
     rdview->block     = Mattr.block;
     rview->block      = Mattr.block;
     temp->block       = Mattr.block;
    /*clone XB and xb */
     vsip_mgetattrib_d(XB, &Mattr);
     solmat->block = XB->block;
     xb->block  = XB->block;
     Vattr.offset = Mattr.offset;
     Vattr.stride = Mattr.col_stride;
     Vattr.length = Mattr.col_length;
     vsip_vputattrib_d(xb, &Vattr);
     vsip_mputattrib_d(solmat, &Mattr);

     /* Start QR using Householder's alg. */
     /* Step 1 -- QR decomp and updating rhs on the fly*/
     /* set up views with proper attributes */
     Vattr.offset = A->offset;
     Vattr.stride = cst + rst; Vattr.length = N;
     vsip_vputattrib_d(rdview, &Vattr);

     Vattr.offset = A->offset;
     Vattr.stride = cst; Vattr.length = M;
     vsip_vputattrib_d(lqview, &Vattr);

     Vattr.offset = A->offset + rst;
     Vattr.stride = cst; Vattr.length = M;
     vsip_vputattrib_d(lviews, &Vattr);

     Vattr.offset = A->offset;
     Vattr.stride = cst; Vattr.length = M;
     vsip_vputattrib_d(qview,  &Vattr);
     
     k=0;
     scale = vsip_vmaxmgval_d(lqview, &where);
       if( scale == 0.0)
       {
         retval++;
         r11 = 0.0;
         tau=0.0;

       } else {
         vsip_svmul_d(1.0/scale, lqview, lqview);
	 r11 = vsip_vget_d(lqview,k);
	 sum = vsip_vdot_d(qview, qview);

         sigma = (vsip_vget_d(qview, 0) >= 0.0) ? 
	   (vsip_scalar_d)sqrt(sum) : -(vsip_scalar_d)sqrt(sum);

	 vsip_vput_d(qview,0,vsip_vget_d(qview,0)+sigma);

	 tau = sigma* vsip_vget_d(qview, 0);

	 for(j=k+1; j<N; j++)
         {
           sum = vsip_vdot_d(qview, lviews);
           beta = sum/tau;
           vsip_vsma_d(qview, -beta, lviews, lviews);
           lviews->offset += rst;

         } /*end j for loop */
         r11 =  -scale*sigma;
       } /* end if loop */
       /* update rhs w/qview */
       for(i=0; i < (int)NB; i++)
       {
	 alpha = vsip_vdot_d(qview,xb);
	 beta = alpha/tau;
	 vsip_vsma_d(qview,-beta,xb,xb);
	 xb->offset += XB->row_stride;
       }

       /* update views */
       lqview->offset += rst+cst; lqview->length--; 
       qview->offset += cst; qview->length--;   
       lviews->offset = lqview->offset+rst;
       lviews->length = lqview->length;
       xb->offset = XB->offset + XB->col_stride;
       xb->length--;
       vsip_vput_d(rdview,0,r11);

     /* Get remaining cols of Q, one at a time and overlap updating rhs*/
     for (k=1; k <((N < M)? N : (N-1)); k++)
     {
       scale = 0.0;
       scale = vsip_vmaxmgval_d(lqview, &where);
       if( scale == 0.0)
       {
         retval++;
         vsip_vput_d(rdview, k, 0.0);
         tau=0.0;

       } else {
         vsip_svmul_d(1.0/scale, lqview,qview);

         sum = vsip_vdot_d(qview, qview);
         sigma = (vsip_vget_d(qview, 0) >= 0.0) ? 
	   (vsip_scalar_d)sqrt(sum) : -(vsip_scalar_d)sqrt(sum);

         vsip_vput_d(qview,0,vsip_vget_d(qview,0)+sigma);

         tau= sigma* vsip_vget_d(qview, 0);

         for(j=k+1; j<N; j++)
         {
           sum = vsip_vdot_d(qview, lviews);
           beta = sum/tau;
           vsip_vsma_d(qview, -beta, lviews, lviews);
           lviews->offset += rst;

         } /*end j for loop */
         vsip_vput_d(rdview,k, -scale*sigma);
       } /* end if loop */ 
       /* update rhs w/qview */
       for(i=0; i < (int)NB; i++)
       {
	 alpha = vsip_vdot_d(qview,xb);
	 beta = alpha/tau;
	 vsip_vsma_d(qview,-beta,xb,xb);
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
    vsip_vputattrib_d(rview, &Vattr); 

    Vattr.offset = XB->offset + (NN-1)*XB->col_stride;
    Vattr.stride = XB->row_stride;
    Vattr.length = XB->row_length;
    vsip_vputattrib_d(xb, &Vattr);

    solmat->offset = XB->offset + (NN-1) * solmat->col_stride;
    solmat->col_length = 1;

    Vattr.offset = A->offset + cst;
    Vattr.stride = cst;
    Vattr.length = NB;
    vsip_vputattrib_d(temp, &Vattr);

    /* do the diagonal scaling */
    alpha = (1.0)/vsip_vget_d(rdview,N-1);
    if(vsip_vget_d(rdview,N-1) == 0.0)
      retval++;

    vsip_svmul_d(alpha, xb, xb);
    xb->offset -= XB->col_stride;

    for(i = NN-2; i >= 0; i--)
    {
      vsip_vmprod_d(rview, solmat, temp);

      /* update soln */
      vsip_vsub_d(xb,temp,xb);

      alpha = 1.0/vsip_vget_d(rdview,i);

      if(vsip_vget_d(rdview,i) == 0.0)
        retval++;

      vsip_svmul_d(alpha, xb, xb);

      /* update views */
      rview->offset -= (rst + cst); rview->length++;
      solmat->offset -= solmat->col_stride;
      solmat->col_length++;
      if(i > 0)
        xb->offset -= XB->col_stride;
    }

    return(retval);
}

