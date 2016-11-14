/* Created By RJudd April 19, 1998 */
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_cholsol_f.c,v 1.2 1999/12/02 18:41:09 judd Exp judd $ */

/* April 21 1,2 to row,col for lusol */
/*
 *  vsip/CORE/src/linalg/vsip_chold_f/vsip_cholsol_f.c
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
 *  -  -   -   -   -   -   -  -  -  -  -  -  -  -  -  -  -  -  -
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
 *  created:          june-25-98 (AP) (modified from r. judds version
 *                    for lud)
 *  last update:      july-13-98 (AP)
 *                    chaned API to fit the VSIP spec...
 *                    Solving system with system matrix solved in either
 *                    upper or lower triangular part of the chol object.
 *
 *                    july-17-98 (AP)
 *                    changed how vsip_chol_attr fits in with chold object
 *                    in choldattributes.h, according to new spec. Accordingly,
 *                    the calling parameters of how the new attributes are
 *                    obtd. are changed, slightly.
 *
 *                    august-24-98 (AP)
 *                    changed the function type from void to int
 *
 *                    august-26-98 (AP)
 *                    changed the algorithm for obtaining each soln matrix
 *                    entry at a time, to getting each row of the soln.
 *                    matrix at a time i.e. from BLAS1 to BLAS2 ops.
 *
 *                    august-31-98  (AP)
 *                    changed the vsip_v(m)get(put)attributes function
 *                    parameters to now include structures passed by reference
 *		      containing the atrributes of the vectors or matrices.
 *
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
 */

#include<vsip.h>
#include<vsip_choldattributes_f.h>

int (vsip_cholsol_f)(
             const vsip_chol_f *chold,
             const vsip_mview_f *XB)
{
    vsip_vview_f rrview, *rview  = &rrview,
                 ddview, *dview  = &ddview,
                 xxvec,  *xvec   = &xxvec,
                 ccview,*cview   = &ccview,
                 tmp, *temp      = &tmp;

    vsip_mview_f mat, *solmat = &mat;

    int i=0, retval=0;
    vsip_stride rst, cst;
    vsip_scalar_f beta;

    vsip_length NB = vsip_mgetrowlength_f(XB);
    vsip_length N;

    vsip_chol_attr_f attr;
    vsip_vattr_f Vattr;
    vsip_mattr_f Mattr;
    vsip_mat_uplo uplo;
#ifdef VSIP_DEVELOPMENT_MODE
       dview->markings  = vsip_valid_structure_object;
       rview->markings  = vsip_valid_structure_object;
       xvec->markings   = vsip_valid_structure_object;
       cview->markings  = vsip_valid_structure_object;
       temp->markings = vsip_valid_structure_object;
       solmat->markings = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */

    cst = chold->CHOL->col_stride;
    rst = chold->CHOL->row_stride;

    rview->block    = chold->CHOL->block;
    dview->block    = chold->CHOL->block;
    cview->block    = chold->CHOL->block;

    /*clone XB with vector rowview xvec */
    xvec->block   = XB->block;
    temp->block = XB->block;

    /* get chol attributes */
    vsip_chold_getattr_f(chold, &attr);
    N = attr.n;
    uplo = attr.uplo;

  /* get\put matrix attributes  */
    vsip_mgetattrib_f(XB, &Mattr);
    solmat->block = XB->block;
    vsip_mputattrib_f(solmat, &Mattr);

    Vattr.offset = XB->offset + N*XB->col_stride;
    Vattr.stride = XB->row_stride;
    Vattr.length = NB;
    vsip_vputattrib_f(temp, &Vattr);

    /* This algorithm solves LT first and then upper -- vector operations */
    /* based. The LT part may be stored colwise in L or rowwise in L^t    */

    if(uplo == VSIP_TR_LOW)    /* L (storage)  solve(s) */

    {
	Vattr.offset = chold->CHOL->offset + cst;
	Vattr.stride = rst; Vattr.length = 1;
        vsip_vputattrib_f(rview, &Vattr);

	Vattr.offset = chold->CHOL->offset;
	Vattr.stride = rst + cst; Vattr.length = N;
	vsip_vputattrib_f(dview, &Vattr);

	Vattr.offset = chold->CHOL->offset +(N-2)*rst + (N-1)*cst;
	Vattr.stride = cst; Vattr.length = 1;
	vsip_vputattrib_f(cview, &Vattr);

	Vattr.offset = XB->offset; Vattr.stride = XB-> row_stride;
	Vattr.length = XB->row_length;
	vsip_vputattrib_f(xvec, &Vattr);

	solmat->col_length = 1;

	 /* do the diagonal scaling */
	 beta = 1/vsip_vget_f(dview,0);
	 if(vsip_vget_f(dview,0) <= chold->singular)
	   retval++;

	 vsip_svmul_f(beta, xvec, xvec);
	 xvec->offset += XB->col_stride;

	 for(i=1; i< (int)N; i++)
	 {
	   vsip_vmprod_f(rview, solmat, temp);

	   /* update soln */
	   vsip_vsub_f(xvec,temp,xvec);
	   beta = (vsip_scalar_f)1.0/vsip_vget_f(dview,i);
	   if(vsip_vget_f(dview,i) <= chold->singular)
	     retval++;
	   vsip_svmul_f(beta, xvec, xvec);

	   /* update views */
	   rview->offset += cst; rview->length++;
	   solmat->col_length++;
	   if(i < (int)N - 1)
	     xvec->offset += XB->col_stride;
	 }

          /*solve Upper */
	  
	  solmat->offset = XB->offset + (N-1) * solmat->col_stride;
	  solmat->col_length = 1;
	  
	  /* do the diagonal scaling */
	  beta = ((vsip_scalar_f)1.0)/vsip_vget_f(dview,N-1);
	  if(vsip_vget_f(dview,N-1) <= chold->singular)
	    retval++;
	  vsip_svmul_f(beta, xvec, xvec);
	  xvec->offset -= XB->col_stride;

	  for(i = N-2; i >= 0; i--)
	  {
	    vsip_vmprod_f(cview, solmat, temp);

	    /* update soln */
	    vsip_vsub_f(xvec,temp,xvec);
	    beta = (vsip_scalar_f)1.0/vsip_vget_f(dview,i);
	    if(vsip_vget_f(dview,i)<= chold->singular)
	      retval++;
	    vsip_svmul_f(beta, xvec, xvec);

	    /* update views */
	    cview->offset -= (rst + cst); cview->length++;
	    solmat->offset -= solmat->col_stride;
	    solmat->col_length++;
	    if(i > 0)
	      xvec->offset -= XB->col_stride;
	  }      

    } else if(uplo == VSIP_TR_UPP) /* L^t (R) (storage) solve(s) */
    { 
      /* put attributes */
      Vattr.offset = chold->CHOL->offset+rst;
      Vattr.stride = cst; Vattr.length = 1;
      vsip_vputattrib_f(cview, &Vattr);

      Vattr.offset = chold->CHOL->offset+(N-2)*cst + (N-1)*rst;
      Vattr.stride = rst; Vattr.length = 1;
      vsip_vputattrib_f(rview, &Vattr);

      Vattr.offset = XB->offset;
      Vattr.stride = XB->row_stride;
      Vattr.length = XB->row_length;
      vsip_vputattrib_f(xvec, &Vattr);

      Vattr.offset = chold->CHOL->offset; 
      Vattr.stride = rst + cst; Vattr.length = N;
      vsip_vputattrib_f(dview, &Vattr);

         /* solve Lower */
	solmat->col_length = 1;

	 /* do the diagonal scaling */
	 beta = 1/vsip_vget_f(dview,0);
	 if(vsip_vget_f(dview,0) <= chold->singular)
	   retval++;

	 vsip_svmul_f(beta, xvec, xvec);
	 xvec->offset += XB->col_stride;

	 for(i=1; i< (int)N; i++)
	 {
	   vsip_vmprod_f(cview, solmat, temp);

	   /* update soln */
	   vsip_vsub_f(xvec,temp,xvec);
	   beta = (vsip_scalar_f)1.0/vsip_vget_f(dview,i);
	   if(vsip_vget_f(dview,i) <= chold->singular)
	     retval++;
	   vsip_svmul_f(beta, xvec, xvec);

	   /* update views */
	   cview->offset += rst; cview->length++;
	   solmat->col_length++;
	   if(i < (int)N - 1)
	     xvec->offset += XB->col_stride;
	 }


          /*solve Upper */
	  solmat->offset = XB->offset + (N-1) * solmat->col_stride;
	  solmat->col_length = 1;
	  
	  /* do the diagonal scaling */
	  beta = ((vsip_scalar_f)1.0)/vsip_vget_f(dview,N-1);
	  if(vsip_vget_f(dview,N-1) <= chold->singular)
	    retval++;
	  vsip_svmul_f(beta, xvec, xvec);
	  xvec->offset -= XB->col_stride;

	  for(i = N-2; i >= 0; i--)
	  {
	    vsip_vmprod_f(rview, solmat, temp);

	    /* update soln */
	    vsip_vsub_f(xvec,temp,xvec);
	    beta = (vsip_scalar_f)1.0/vsip_vget_f(dview,i);
	    if(vsip_vget_f(dview,i) <= chold->singular)
	      retval++;
	    vsip_svmul_f(beta, xvec, xvec);

	    /* update views */
	    rview->offset -= (rst + cst); rview->length++;
	    solmat->offset -= solmat->col_stride;
	    solmat->col_length++;
	    if(i > 0)
	      xvec->offset -= XB->col_stride;
	  }      
 
    } /*end of main if-else-loop */

  return(retval);
}


