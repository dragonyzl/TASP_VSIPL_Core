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
 *  vsip/TASP_VSIPLcore/src_core/linalg/vsip_spclslvrs_f/vsip_covsol_f.c
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
 *  created:          february-1-99 (AP) 
 *
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
 */
/* $Id: vsip_covsol_f.c,v 1.1 1999/12/02 17:38:12 judd Exp judd $ */

#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_vviewattributes_vi.h>


int vsip_covsol_f(
		  const vsip_mview_f *A,
		  const vsip_mview_f *XB)
{
  int retval=0;
  vsip_stride i;
  vsip_mattr_f Mattr;
  vsip_vattr_f Vattr;

  vsip_mview_f mat, *solmat = &mat;
  vsip_vview_f   ddview,  *rdview    = &ddview,
                 qview,   *lqview    = &qview,
                 ccview,  *lviews    = &ccview,
                 xxvec,   *xvec      = &xxvec,
                 ttemp,   *temp      = &ttemp;

  vsip_length M, N, NN, NB;
  vsip_scalar_f sum, scale, sigma, tau, onebytau, beta;
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
     M  = vsip_mgetcollength_f(A);
     N  = vsip_mgetrowlength_f(A);
     NN = vsip_mgetcollength_f(XB);
     NB = vsip_mgetrowlength_f(XB);

       if(N < M)
     NN = N;  /* look at the first n col elemts of soln vec, if N < M */


     /* get attributes */
     vsip_mgetattrib_f(A, &Mattr);

     /* set up views to point to proper block */
     rdview->block     = Mattr.block;
     lqview->block     = Mattr.block;
     lviews->block     = Mattr.block;
     temp->block       = Mattr.block;

     /* Step 1 -- Do QR factorisation first */
     /* set up views with proper attributes */

     Vattr.offset = Mattr.offset;
     Vattr.stride = rst + cst; Vattr.length = N;
     vsip_vputattrib_f(rdview, &Vattr);

     Vattr.stride = cst; Vattr.length = M;
     vsip_vputattrib_f(lqview, &Vattr);

     Vattr.offset = Mattr.offset + rst;
     vsip_vputattrib_f(lviews, &Vattr);

     /* Initialise basic variables */
     sum = sigma = tau = onebytau = 0.0;

     /* main decomposition loop */

     for (k=0; k <((N < M)? N : (N-1)); k++)
     {
       scale = 0.0;
       scale = vsip_vmaxmgval_f(lqview, &where);
       if( scale == 0.0)
       {
         retval++;
         vsip_vput_f(rdview, k, 0.0);
       } else {
         vsip_svmul_f((vsip_scalar_f)1.0/scale, lqview, lqview);

         sum = vsip_vdot_f(lqview, lqview);

	 sigma = (vsip_vget_f(lqview, 0) >= 0.0) ? 
	   (vsip_scalar_f)sqrt(sum) : -(vsip_scalar_f)sqrt(sum);

         vsip_vput_f(lqview,0,vsip_vget_f(lqview,0)+sigma);

	 onebytau = (vsip_scalar_f)1.0/(sigma* vsip_vget_f(lqview, 0));

         for(j=k+1; j<N; j++)
         {
           sum = vsip_vdot_f(lqview, lviews);

	   tau = sum * onebytau;

	   vsip_vsma_f(lqview, -tau, lviews, lviews);

	   lviews->offset += rst;

         } /*end j for loop */

         vsip_vput_f(rdview,k, -scale*sigma);

       } /* end if loop */
       /* update views */
       lqview->offset += rst+cst;
       lqview->length--;       
       lviews->offset = lqview->offset+rst;
       lviews->length = lqview->length;
     }/* end k for loop */
     
     if( N == M)
       vsip_vput_f(rdview, N-1, vsip_vget_f(lqview,0));

     /* end of QR decomp (Householder's) -- only R saved explicitly. */

     /* Solve the system R^T * R X = B */


     /* get\put matrix, vector  attributes */
     vsip_mgetattrib_f(XB, &Mattr);
     solmat->block = Mattr.block;
     xvec->block = Mattr.block;
     vsip_mputattrib_f(solmat, &Mattr);
     

     /* Step 2 --first solve LT system */
     /* get\put row attributes */
     vsip_mgetattrib_f(A, &Mattr);

     Vattr.offset = Mattr.offset+cst;
     Vattr.stride = cst;
     Vattr.length = NB;
     vsip_vputattrib_f(temp,&Vattr);

     Vattr.offset = Mattr.offset + rst;
     Vattr.stride = cst;
     Vattr.length = 1;
     vsip_vputattrib_f(lviews, &Vattr);

     Vattr.offset = XB->offset;
     Vattr.stride = XB->row_stride;
     Vattr.length = XB->row_length;
     vsip_vputattrib_f(xvec, &Vattr);

     solmat->col_length = 1;
    /* do the diagonal scaling */
    beta = 1/vsip_vget_f(rdview,0);
    if(vsip_vget_f(rdview,0) == 0.0)
      retval++;

    vsip_svmul_f(beta, xvec, xvec);
    xvec->offset += XB->col_stride;

    for(i=1; i< (int)NN; i++)
    {
      vsip_vmprod_f(lviews, solmat, temp);
      /* update soln */
      vsip_vsub_f(xvec,temp,xvec);

      beta = 1/vsip_vget_f(rdview,i);

      if(vsip_vget_f(rdview,i) == 0.0)
        retval++;
      vsip_svmul_f(beta, xvec, xvec);
      
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
    vsip_vputattrib_f(lviews, &Vattr); 

    Vattr.offset = XB->offset + (NN-1)*XB->col_stride;
    Vattr.stride = XB->row_stride;
    Vattr.length = XB->row_length;
    vsip_vputattrib_f(xvec, &Vattr);

    solmat->offset = XB->offset + (NN-1) * solmat->col_stride;
    solmat->col_length = 1;

    /* do the diagonal scaling */
    beta = ((vsip_scalar_f)1.0)/vsip_vget_f(rdview,N-1);
    vsip_svmul_f(beta, xvec, xvec);
    xvec->offset -= XB->col_stride;

    for(i = NN-2; i >= 0; i--)
    {
      vsip_vmprod_f(lviews, solmat, temp);

      /* update soln */
      vsip_vsub_f(xvec,temp,xvec);

      beta = (vsip_scalar_f)1.0/vsip_vget_f(rdview,i);

      vsip_svmul_f(beta, xvec, xvec);

      /* update views */
      lviews->offset -= (rst + cst); lviews->length++;
      solmat->offset -= solmat->col_stride;
      solmat->col_length++;
      if(i > 0)
        xvec->offset -= XB->col_stride;
    }
    return(retval);

}
