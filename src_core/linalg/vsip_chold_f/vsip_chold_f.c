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
/* $Id: vsip_chold_f.c,v 1.2 1999/12/02 18:41:07 judd Exp judd $ */

/* April 21 1,2 to row,col for lud */
/*
 *  vsip/CORE/src/linalg/vsip_chold_f/vsip_chold_f.c
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
 *  created:          june-25-98 (AP) (modified from r. judds version
 *                    for lud)
 *  last update:      july-13-98 (AP)
 *                    chaned API to fit the VSIP spec...
 *                    changed referencing and touching either upper
 *                    or lower part of symmetric matrix i.e 
 *                    A = LL^(T) or A = U^(T)U
 *
 *                    july-17-98 (AP)
 *                    changed how vsip_chol_attr fits in with chold object
 *                    in choldattributes.h, according to new spec. Accordingly,
 *                    the calling parameters of how the new attributes are
 *                    obtd. are changed, slightly.
 *
 *                    august-31-98  (AP)
 *                    changed the vsip_v(m)get(put)attributes function 
 *                    parameters to now include structures by reference 
 *		      containing the atrributes of the vectors or matrices.
 *
 *                    sept-10-98 (AP)
 *                    made the computation of the last row or col
 *                    separate from the main loop, to avoid using
 *                    vector functions with vectors of length one.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
 */

#include<vsip.h>
#include<vsip_choldattributes_f.h>

int (vsip_chold_f)(
             vsip_chol_f *chold,
             const vsip_mview_f *A)
{
  int retval=0;
     /*******************************************************/
     /* finish creating chold object */
    vsip_chol_attr_f attr;
    vsip_mattr_f     Mattr;
    vsip_vattr_f     Vattr;

    vsip_vview_f   ddview,  *dview  = &ddview,
                   aarview, *arview = &aarview,
                   rrview,  *rview  = &rrview,
                   llcview, *lcview = &llcview,
                   ccview,  *cview  = &ccview;

    vsip_length N;
    vsip_mat_uplo uplo;
    vsip_scalar_vi i, j;
    vsip_stride rst  = A->row_stride;
    vsip_stride cst  = A->col_stride;
#ifdef VSIP_DEVELOPMENT_MODE
       dview->markings  = vsip_valid_structure_object;
       rview->markings  = vsip_valid_structure_object;
       lcview->markings = vsip_valid_structure_object;
       cview->markings  = vsip_valid_structure_object;
       arview->markings = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */

     /* get attributes of A */
     vsip_mgetattrib_f(A, &Mattr);

     /* set up views to point to proper block */
     dview->block     = Mattr.block;
     arview->block    = Mattr.block;
     rview->block     = Mattr.block;
     lcview->block    = Mattr.block;
     cview->block     = Mattr.block;

     /* get attributes of cholesky object */
     vsip_chold_getattr_f(chold, &attr);
     N = attr.n;
     uplo = attr.uplo;

     /*in place, set A attibutes  to CHOL */
     chold->CHOL->block      = Mattr.block;
     chold->CHOL->row_stride = Mattr.row_stride;
     chold->CHOL->col_stride = Mattr.col_stride;
     chold->CHOL->row_length = Mattr.row_length;
     chold->CHOL->col_length = Mattr.col_length;
     chold->CHOL->offset     = Mattr.offset; 

     /* check and set singular */
     chold->singular = VSIP_MIN_SCALAR_F;
/*        chold->singular = VSIP_MIN_SCALAR_F;
     } else {
        chold->singular  = singular;
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
     vsip_vputattrib_f(dview, &Vattr);

     Vattr.offset = Mattr.offset + cst;
     Vattr.length = 1; Vattr.stride = rst;
     vsip_vputattrib_f(rview, &Vattr);

     Vattr.stride = cst; Vattr.length = N-1;
     vsip_vputattrib_f(lcview, &Vattr);

     vsip_vputattrib_f(cview, &Vattr);

       /* main decomposition loop */
       /* i = 0 case -- first col(row) */
       i = 0;

    /*vsip_vput_f(dview,i,(vsip_scalar_f)sqrt(vsip_vget_f(dview,i))); --inlined below */

    {vsip_scalar_f *dv = (dview->block->array) + dview->offset * dview->block->rstride + 
	                  (dview->stride) * dview->block->rstride * i;
      *dv = (vsip_scalar_f)sqrt(*dv);
      if((vsip_scalar_f)fabs(*(dv)) < chold->singular) retval++;
     }  /* inlining ended */

    /*vsip_svmul_f(1/vsip_vget_f(dview,i), arview,lcview); -- inlined below*/

    {vsip_scalar_f *dv = (dview->block->array) + dview->offset * dview->block->rstride + 
	                  (dview->stride * dview->block->rstride) * i;
     vsip_scalar_f onebydv = (vsip_scalar_f)1.0/(*dv);

     vsip_svmul_f(onebydv,lcview,lcview);
    }  /* inlining ended */


    /*update the lcview and cview*/

    lcview->offset += rst+cst;
    lcview->length--;
    cview->offset += cst;
    cview->length--;

    /* Compute cols(rows) 2 - N-1 of L(L^t) */
    for(i=1; i< (vsip_scalar_vi) N-1; i++)
    {

      /*vsip_vput_f(dview,i,(vsip_scalar_f)sqrt(vsip_vget_f(dview,i)-
	vsip_vdot_f(rview,rview))); --inlined below*/

       {vsip_scalar_f *dv = (dview->block->array) + dview->offset * dview->block->rstride + 
	                  (dview->stride * dview->block->rstride) * i;
       *dv = (vsip_scalar_f)sqrt(*dv - vsip_vdot_f(rview,rview));
       if((vsip_scalar_f)fabs(*(dv)) < chold->singular) retval++;
       }   /* inlining ended */

      for(j=0; j<i; j++)
      {
        /*vsip_vsma_f(cview,-vsip_vget_f(rview,j),lcview,lcview);
	 -- inlined get call */

	{vsip_scalar_f *rv = (rview->block->array) + rview->offset * rview->block->rstride + 
	                     (rview->stride * rview->block->rstride) * j;

	vsip_vsma_f(cview,-(*rv),lcview,lcview);
	} 

	cview->offset += rst;
      }

     /*vsip_svmul_f(1/vsip_vget_f(dview,i),lcview,lcview); 
       --inlined the get call below*/

      {vsip_scalar_f *dv = (dview->block->array) + dview->offset * dview->block->rstride + 
	                  (dview->stride * dview->block->rstride) * i;
       vsip_scalar_f onebydv = (vsip_scalar_f)1.0/(*dv);

       vsip_svmul_f(onebydv,lcview,lcview);
      }  /* inlining ended */

      /*update all view offsets */
      lcview->offset += rst+cst;
      lcview->length--;
      cview->offset = cview->offset -rst*i + cst;
      cview->length--;
      rview->offset += cst;
      rview->length++;
      
    }
     /* compute last remaining col (row)  */
    vsip_vput_f(dview,N-1,(vsip_scalar_f)sqrt(vsip_vget_f(dview,N-1) -
	vsip_vdot_f(rview,rview)));

  }else if(uplo == VSIP_TR_UPP)
  { /*do all in Upper part */
     /* set up views with proper attributes */

    Vattr.offset   = Mattr.offset;
    Vattr.stride   = rst + cst; Vattr.length = N;
    vsip_vputattrib_f(dview, &Vattr);

    Vattr.offset   = Mattr.offset + rst;
    Vattr.stride = rst; Vattr.length = N-1;
    vsip_vputattrib_f(arview, &Vattr);

    vsip_vputattrib_f(rview, &Vattr);

    Vattr.stride = cst; Vattr.length = 1;
    vsip_vputattrib_f(cview, &Vattr);
       /* main decomposition loop */
       /* i = 0 case -- first col(row) */
       i = 0;

    /*vsip_vput_f(dview,i,(vsip_scalar_f)sqrt(vsip_vget_f(dview,i))); --inlined below */

    {vsip_scalar_f *dv = (dview->block->array) + dview->offset * dview->block->rstride + 
	                  (dview->stride * dview->block->rstride) * i;
      *dv = (vsip_scalar_f)sqrt(*dv);
      if((vsip_scalar_f)fabs(*(dv)) < chold->singular) retval++;
     }  /* inlining ended */

    /*vsip_svmul_f(1/vsip_vget_f(dview,i), arview,arview); -- inlined below*/

    {vsip_scalar_f *dv = (dview->block->array) + dview->offset * dview->block->rstride + 
	                  (dview->stride * dview->block->rstride) * i;
     vsip_scalar_f onebydv = (vsip_scalar_f)1.0/(*dv);

     vsip_svmul_f(onebydv,arview,arview);
    }  /* inlining ended */


    /*update the arview and rview */

    arview->offset += rst+cst;
    arview->length--;
    rview->offset += rst;
    rview->length--;

    /* Compute cols(rows) 2 - N-1  of L(L^t) */
    for(i=1; i< (vsip_scalar_vi) N-1; i++) 
    {

      /*vsip_vput_f(dview,i,(vsip_scalar_f)sqrt(vsip_vget_f(dview,i)-
	vsip_vdot_f(cview,cview))); --inlined below*/

       {vsip_scalar_f *dv = (dview->block->array) + dview->offset * dview->block->rstride + 
	                  (dview->stride * dview->block->rstride) * i;
       *dv = (vsip_scalar_f)sqrt(*dv - vsip_vdot_f(cview,cview));
       if((vsip_scalar_f)fabs(*(dv)) < chold->singular) retval++;
       }   /* inlining ended */

      for(j=0; j<i; j++)
      {
        /*vsip_vsma_f(rview,-vsip_vget_f(cview,j),arview,arview);
	 -- inlined get call */

	{vsip_scalar_f *cv = (cview->block->array) + cview->offset * cview->block->rstride + 
	                     (cview->stride * cview->block->rstride) * j;

	vsip_vsma_f(rview,-(*cv),arview,arview);
	} 

	rview->offset += cst;
      }

     /*vsip_svmul_f(1/vsip_vget_f(dview,i),arview,arview); 
       --inlined the get call below*/

      {vsip_scalar_f *dv = (dview->block->array) + dview->offset * dview->block->rstride + 
	                  (dview->stride * dview->block->rstride) * i;
       vsip_scalar_f onebydv = (vsip_scalar_f)1.0/(*dv);

       vsip_svmul_f(onebydv,arview,arview);
      }  /* inlining ended */

      /*update all view offsets */

      arview->offset += rst+cst;
      arview->length--;
      rview->offset = rview->offset -cst*i + rst;
      rview->length--;
      cview->offset += rst;
      cview->length++;
      
    }
      /* compute last col(row)  */
      vsip_vput_f(dview,N-1,(vsip_scalar_f)sqrt(vsip_vget_f(dview,N-1) -
        vsip_vdot_f(cview,cview)));


  } /* end of main if loop */
  return(retval);
}

