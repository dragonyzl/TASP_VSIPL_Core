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
/* $Id: vsip_ccholsol_d.c,v 1.1 1999/12/05 16:07:38 judd Exp judd $ */

/*
 *  vsip/CORE/src/linalg/vsip_chold_d/vsip_ccholsol_d.c
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
 *  created:          august-27-98 (AP) (modified from AP's vsip_cholsol_d
 *  last update:      september-1-98 (AP)
 *                    changed v(m)get(put)attrib_d func calls to pass
 *                    attribute structure by reference rather than value.
 *
 *                    january-20-99 (AP)
 *                    conjugated the elements of L, when stored in LT part
 *                    and solving the UT solve. similarly conjugated elts.
 *                    of L^*, when stored in UT part and solving LT solve.
 *    
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
 */

#include<vsip.h>
#include<vsip_ccholdattributes_d.h>

int (vsip_ccholsol_d)(
             const vsip_cchol_d *cchold,
             const vsip_cmview_d *XB)
{
    vsip_cvview_d rrview, *rview     = &rrview,
                  ddview, *dview     = &ddview,
                  xxvec,  *xvec      = &xxvec,
                  ccview, *cview     = &ccview,
                  tmp,    *temp      = &tmp;

    vsip_cmview_d mat, *solmat = &mat;

    int i=0, retval=0;
    vsip_stride rst, cst;
    vsip_cscalar_d beta;
    vsip_scalar_d singular = cchold->singular;

    vsip_length NB = vsip_cmgetrowlength_d(XB);
    vsip_length N;

    vsip_cchol_attr_d attr;
    vsip_cvattr_d Vattr;
    vsip_cmattr_d Mattr;
    vsip_mat_uplo uplo;
#ifdef VSIP_DEVELOPMENT_MODE
       dview->markings  = vsip_valid_structure_object;
       rview->markings  = vsip_valid_structure_object;
       xvec->markings   = vsip_valid_structure_object;
       cview->markings  = vsip_valid_structure_object;
       temp->markings = vsip_valid_structure_object;
       solmat->markings = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */

    cst = cchold->CHOL->col_stride;
    rst = cchold->CHOL->row_stride;

    rview->block    = cchold->CHOL->block;
    dview->block    = cchold->CHOL->block;
    cview->block    = cchold->CHOL->block;

    /*clone XB with vector rowview xvec */
    xvec->block   = XB->block;
    temp->block = XB->block;

    /* get cchol attributes */
    vsip_cchold_getattr_d(cchold, &attr);
    N = attr.n;
    uplo = attr.uplo;

    /* get\put matrix attributes  */
    vsip_cmgetattrib_d(XB, &Mattr);
    solmat->block = XB->block;
    vsip_cmputattrib_d(solmat, &Mattr);

    Vattr.offset = XB->offset + N*XB->col_stride;
    Vattr.stride = XB->row_stride;
    Vattr.length = NB;
    vsip_cvputattrib_d(temp, &Vattr);

    /* This algorithm solves LT first and then upper -- vector operations */
    /* based. The LT part may be stored colwise in L or rowwise in L^t    */

    if(uplo == VSIP_TR_LOW)    /* L (storage)  solve(s) */

    {
	Vattr.offset = cchold->CHOL->offset + cst;
	Vattr.stride = rst; Vattr.length = 1;
        vsip_cvputattrib_d(rview, &Vattr);

	Vattr.offset = cchold->CHOL->offset;
	Vattr.stride = rst + cst; Vattr.length = N;
	vsip_cvputattrib_d(dview, &Vattr);

	Vattr.offset = cchold->CHOL->offset +(N-2)*rst + (N-1)*cst;
	Vattr.stride = cst; Vattr.length = 1;
	vsip_cvputattrib_d(cview, &Vattr);

	Vattr.offset = XB->offset; Vattr.stride = XB-> row_stride;
	Vattr.length = XB->row_length;
	vsip_cvputattrib_d(xvec, &Vattr);

	solmat->col_length = 1;

	 /* do the diagonal scaling */
	 beta = vsip_crecip_d(vsip_cvget_d(dview,0));
	 if(vsip_cmag_d(vsip_cvget_d(dview,0)) <= singular)
	   retval++;

	 vsip_csvmul_d(beta, xvec, xvec);
	 xvec->offset += XB->col_stride;

	 for(i=1; i< (int)N-1; i++)
	 {
	   vsip_cvmprod_d(rview, solmat, temp);

	   /* update soln */
	   vsip_cvsub_d(xvec,temp,xvec);
	   beta = vsip_crecip_d(vsip_cvget_d(dview,i));
	   if(vsip_cmag_d(vsip_cvget_d(dview,i)) <= singular )
	     retval++;
	   vsip_csvmul_d(beta, xvec, xvec);

	   /* update views */
	   rview->offset += cst; rview->length++;
	   solmat->col_length++;
	   xvec->offset += XB->col_stride;
	 }

	 /* i = N-1 case */
	 vsip_cvmprod_d(rview, solmat, temp);
	 vsip_cvsub_d(xvec,temp,xvec);
         beta = vsip_crecip_d(vsip_cvget_d(dview,i));
         if(vsip_cmag_d(vsip_cvget_d(dview,i)) <= singular )
           retval++;
         vsip_csvmul_d(beta, xvec, xvec);

          /*solve Upper */
	  
	  solmat->offset = XB->offset + (N-1) * solmat->col_stride;
	  solmat->col_length = 1;
	  
	  /* do the diagonal scaling */
	  beta = vsip_crecip_d(vsip_cvget_d(dview,N-1));
	  if(vsip_cmag_d(vsip_cvget_d(dview,N-1)) <= singular)
	    retval++;
	  vsip_csvmul_d(beta, xvec, xvec);
	  xvec->offset -= XB->col_stride;

	  vsip_cvconj_d(cview,cview);
	  for(i = N-2; i > 0; i--)
	  {
	    vsip_cvmprod_d(cview, solmat, temp);

	    /* update soln */
	    vsip_cvsub_d(xvec,temp,xvec);
	    beta = vsip_crecip_d(vsip_cvget_d(dview,i));
	    if(vsip_cmag_d(vsip_cvget_d(dview,i)) <= singular)
	      retval++;
	    vsip_csvmul_d(beta, xvec, xvec);

	    /* update views & reconjugated to get original back */
	    cview->offset -= (rst + cst); cview->length++;
	    vsip_cvconj_d(cview,cview);
	    solmat->offset -= solmat->col_stride;
	    solmat->col_length++;
	    xvec->offset -= XB->col_stride;
	  }    
  
	  /* i=0 case */
	  vsip_cvmprod_d(cview, solmat, temp);
	  vsip_cvsub_d(xvec,temp,xvec);
	  beta = vsip_crecip_d(vsip_cvget_d(dview,i));
	  if(vsip_cmag_d(vsip_cvget_d(dview,i)) <= singular)
	    retval++;
	  vsip_csvmul_d(beta, xvec, xvec);

    } else if(uplo == VSIP_TR_UPP) /* L^t (R) (storage) solve(s) */
    { 
      /* put attributes */
      Vattr.offset = cchold->CHOL->offset+rst;
      Vattr.stride = cst; Vattr.length = 1;
      vsip_cvputattrib_d(cview, &Vattr);

      Vattr.offset = cchold->CHOL->offset+(N-2)*cst + (N-1)*rst;
      Vattr.stride = rst; Vattr.length = 1;
      vsip_cvputattrib_d(rview, &Vattr);

      Vattr.offset = XB->offset;
      Vattr.stride = XB->row_stride;
      Vattr.length = XB->row_length;
      vsip_cvputattrib_d(xvec, &Vattr);

      Vattr.offset = cchold->CHOL->offset; 
      Vattr.stride = rst + cst; Vattr.length = N;
      vsip_cvputattrib_d(dview, &Vattr);

         /* solve Lower */
	solmat->col_length = 1;

	 /* do the diagonal scaling */
	 beta = vsip_crecip_d(vsip_cvget_d(dview,0));
	 if(vsip_cmag_d(vsip_cvget_d(dview,0)) <= singular)
	   retval++;

	 vsip_cvconj_d(cview,cview); 
	 vsip_csvmul_d(beta, xvec, xvec);
	 xvec->offset += XB->col_stride;

	 for(i=1; i< (int)N-1; i++)
	 {
	   vsip_cvmprod_d(cview, solmat, temp);

	   /* update soln */
	   vsip_cvsub_d(xvec,temp,xvec);
	   beta = vsip_crecip_d(vsip_cvget_d(dview,i));
	   if(vsip_cmag_d(vsip_cvget_d(dview,i)) <= singular)
	     retval++;
	   vsip_csvmul_d(beta, xvec, xvec);

	   /* update views & reconjugate to get original back */
	   vsip_cvconj_d(cview,cview);
	   cview->offset += rst; cview->length++;
	   vsip_cvconj_d(cview,cview); 
	   solmat->col_length++;
	   xvec->offset += XB->col_stride;
	 }

	 /* i = N-1 case */
	  vsip_cvmprod_d(cview, solmat, temp);
	  vsip_cvsub_d(xvec,temp,xvec);
	  beta = vsip_crecip_d(vsip_cvget_d(dview,i));
          if(vsip_cmag_d(vsip_cvget_d(dview,i)) <= singular)
            retval++;
          vsip_csvmul_d(beta, xvec, xvec);
	  vsip_cvconj_d(cview,cview);

          /*solve Upper */
	  solmat->offset = XB->offset + (N-1) * solmat->col_stride;
	  solmat->col_length = 1;
	  
	  /* do the diagonal scaling */
	  beta = vsip_crecip_d(vsip_cvget_d(dview,N-1));
	  if(vsip_cmag_d(vsip_cvget_d(dview,N-1)) <= singular)
	    retval++;
	  vsip_csvmul_d(beta, xvec, xvec);
	  xvec->offset -= XB->col_stride;

	  for(i = N-2; i > 0; i--)
	  {
	    vsip_cvmprod_d(rview, solmat, temp);

	    /* update soln */
	    vsip_cvsub_d(xvec,temp,xvec);
	    beta = vsip_crecip_d(vsip_cvget_d(dview,i));
	    if(vsip_cmag_d(vsip_cvget_d(dview,i)) <= singular)
	      retval++;
	    vsip_csvmul_d(beta, xvec, xvec);

	    /* update views */
	    rview->offset -= (rst + cst); rview->length++;
	    solmat->offset -= solmat->col_stride;
	    solmat->col_length++;
	    xvec->offset -= XB->col_stride;
	  } 

	  /* i = 0 case */
	  vsip_cvmprod_d(rview, solmat, temp);  
	  vsip_cvsub_d(xvec,temp,xvec);
	  beta = vsip_crecip_d(vsip_cvget_d(dview,i));
          if(vsip_cmag_d(vsip_cvget_d(dview,i)) <= singular)
            retval++;
          vsip_csvmul_d(beta, xvec, xvec);  
 
    } /*end of main if-else-loop */

  return(retval);
}


