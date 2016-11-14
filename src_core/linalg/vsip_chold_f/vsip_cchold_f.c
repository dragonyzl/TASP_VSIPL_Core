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
/* $Id: vsip_cchold_f.c,v 1.2 1999/12/02 18:41:05 judd Exp judd $ */

/*
 *  vsip/CORE/src/linalg/vsip_chold_f/vsip_cchold_f.c
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
 *  created:          august-25-98 (AP) (modified from AP's vsip_chold_f
 *  last update:      september-1-98 (AP)
 *                    changed v(m)get(put)attrib_f func calls to pass
 *                    attribute structure by reference rather than value.
 *
 *                    sept-10-98 (AP)
 *                    made the computation of the last row or col
 *                    separate from the main loop, so as to avoid
 *                    using operations with vector functions with
 *                    vectors of length one. 
 *
 *
 *                    january-20-99 (AP) 
 *                    changed cvdot to cvjdot both in upper/lower
 *                    to account for conjugation, when geting the
 *                    diagonal elements. The vector being viewed
 *                    are rview and cview.
 *
 *                    january-22-99 (AP)
 *                    conjugated individual elements of rview, when 
 *                    storing in LT part and cview in UT part, when 
 *                    updating lcview and arview resply.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
 */

#include<vsip.h>
#include<vsip_ccholdattributes_f.h>

int (vsip_cchold_f)(
             vsip_cchol_f *cchold,
             const vsip_cmview_f *A)
{
  int retval=0;
     /*******************************************************/
     /* finish creating chold object */
    vsip_cchol_attr_f attr;
    vsip_cmattr_f     Mattr;
    vsip_cvattr_f     Vattr;

    vsip_cvview_f   ddview,  *dview  = &ddview,
                    aarview, *arview = &aarview,
                    rrview,  *rview  = &rrview,
                    llcview, *lcview = &llcview,
                    ccview,  *cview  = &ccview;

    vsip_length N;
    vsip_mat_uplo uplo;
    vsip_scalar_vi i, j;
    vsip_scalar_vi rst = A->row_stride;
    vsip_scalar_vi cst = A->col_stride;
#ifdef VSIP_DEVELOPMENT_MODE
       dview->markings  = vsip_valid_structure_object;
       rview->markings  = vsip_valid_structure_object;
       lcview->markings   = vsip_valid_structure_object;
       cview->markings  = vsip_valid_structure_object;
       arview->markings = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */

     /* get attributes of A */
     vsip_cmgetattrib_f(A, &Mattr);

     /* set up views to point to proper block */
     dview->block     = Mattr.block;
     arview->block    = Mattr.block;
     rview->block     = Mattr.block;
     lcview->block    = Mattr.block;
     cview->block     = Mattr.block;

     /* get attributes of cholesky object */
     vsip_cchold_getattr_f(cchold, &attr);
     N = attr.n;
     uplo = attr.uplo;

     /*in place, set A attibutes  to CHOL */
     cchold->CHOL->block      = Mattr.block;
     cchold->CHOL->row_stride = Mattr.row_stride;
     cchold->CHOL->col_stride = Mattr.col_stride;
     cchold->CHOL->row_length = Mattr.row_length;
     cchold->CHOL->col_length = Mattr.col_length;
     cchold->CHOL->offset     = Mattr.offset; 

     /* check and set singular */
     cchold->singular = VSIP_MIN_SCALAR_F;
/*        cchold->singular = VSIP_MIN_SCALAR_F;
     } else {
        cchold->singular  = singular;
     }*/
     /*******************************************************/
     /* do decomposition -- the alg is vector based approach to compute */
     /* each col of L (or each row of L^t) - one vector at a time       */ 
    
     /* check which part of A to reference and touch */
   if (uplo == VSIP_TR_LOW) /* do all in Lower part */
   { 

     /* set up views with proper attributes */
     Vattr.offset = Mattr.offset;
     Vattr.length = Mattr.row_length;
     Vattr.stride = rst + cst;
     vsip_cvputattrib_f(dview, &Vattr);

     Vattr.offset = Mattr.offset + cst;
     Vattr.length = 1; Vattr.stride = rst;
     vsip_cvputattrib_f(rview, &Vattr);

     Vattr.stride = cst; Vattr.length = N-1;
     vsip_cvputattrib_f(lcview, &Vattr);

     vsip_cvputattrib_f(cview, &Vattr);

       /* main decomposition loop */
       i = 0; /* compute first col(row) */

    vsip_cvput_f(dview,i,vsip_csqrt_f(vsip_cvget_f(dview,i))); 

    vsip_csvmul_f(vsip_crecip_f(vsip_cvget_f(dview,i)), lcview,lcview);

    /*update the lcview and cview*/

    lcview->offset += rst+cst;
    lcview->length--;
    cview->offset += cst;
    cview->length--;

    /* Compute cols(rows) 2 - N-1  of L(L^T) */
    for(i=1; i< (vsip_scalar_vi) N-1; i++)
    {

      vsip_cvput_f(dview,i,vsip_csqrt_f(vsip_csub_f(
			  vsip_cvget_f(dview,i),
	vsip_cvjdot_f(rview,rview)))); 

      for(j=0; j<i; j++)
      {
        vsip_cvsma_f(cview,vsip_cneg_f(vsip_conj_f(
			       vsip_cvget_f(rview,j))),lcview,lcview);
	 
	cview->offset += rst;
      }

     vsip_csvmul_f(vsip_crecip_f(vsip_cvget_f(dview,i)),lcview,lcview); 

      /*update all view offsets */
      lcview->offset += rst+cst;
      lcview->length--;
      cview->offset = cview->offset -rst*i + cst;
      cview->length--;
      rview->offset += cst;
      rview->length++;
      
    }
      /* compute last col(row) of L(L^t)  */
      vsip_cvput_f(dview,N-1,vsip_csqrt_f(vsip_csub_f(
         vsip_cvget_f(dview,N-1), vsip_cvjdot_f(rview,rview))));

  }else if(uplo == VSIP_TR_UPP)
  { /*do all in Upper part */
     /* set up views with proper attributes */

    Vattr.offset   = Mattr.offset;
    Vattr.stride   = rst + cst; Vattr.length = N;
    vsip_cvputattrib_f(dview, &Vattr);

    Vattr.offset   = Mattr.offset + rst;
    Vattr.stride = rst; Vattr.length = N-1;
    vsip_cvputattrib_f(arview, &Vattr);

    vsip_cvputattrib_f(rview, &Vattr);

    Vattr.stride = cst; Vattr.length = 1;
    vsip_cvputattrib_f(cview, &Vattr);
       /* main decomposition loop */
       i = 0; /* compute first col(row) of L(L^t)  */

    vsip_cvput_f(dview,i,vsip_csqrt_f(vsip_cvget_f(dview,i)));

    vsip_csvmul_f(vsip_crecip_f(vsip_cvget_f(dview,i)), arview,arview);

    /*update the arview and rview */

    arview->offset += rst+cst;
    arview->length--;
    rview->offset += rst;
    rview->length--;

    /* Compute cols(rows) 2 - N-1 of L(L^t) */
    for(i=1; i< (vsip_scalar_vi) N-1; i++)
    /*for(i=1; i< (vsip_scalar_vi) N; i++) */
    {

      vsip_cvput_f(dview,i,vsip_csqrt_f(
		       vsip_csub_f(vsip_cvget_f(dview,i),
	               vsip_cvjdot_f(cview,cview))));

      for(j=0; j<i; j++)
      {
        vsip_cvsma_f(rview,vsip_cneg_f(vsip_conj_f(
			  vsip_cvget_f(cview,j))),arview,arview);

	rview->offset += cst;
      }

     vsip_csvmul_f(vsip_crecip_f(vsip_cvget_f(dview,i)),arview,arview); 
      

      /*update all view offsets */

      arview->offset += rst+cst;
      arview->length--;
      rview->offset = rview->offset -cst*i + rst;
      rview->length--;
      cview->offset += rst;
      cview->length++;
      
    }
      vsip_cvput_f(dview,N-1,vsip_csqrt_f(
       vsip_csub_f(vsip_cvget_f(dview,N-1), vsip_cvjdot_f(cview,cview))));

  } /* end of main if loop */
  return(retval);
}

