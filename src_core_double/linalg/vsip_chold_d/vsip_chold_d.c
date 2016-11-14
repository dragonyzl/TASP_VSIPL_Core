
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
/* $Id: vsip_chold_d.c,v 1.1 1999/12/05 16:07:40 judd Exp judd $ */
/* April 21 1,2 to row,col for lud */
/*
 *  vsip/CORE/src/linalg/vsip_chold_d/vsip_chold_d.c
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
#include<vsip_choldattributes_d.h>

int (vsip_chold_d)(
             vsip_chol_d *chold,
             const vsip_mview_d *A) 
{
  int retval=0;
     /*******************************************************/
     /* finish creating chold object */
    vsip_chol_attr_d attr;
    vsip_mattr_d     Mattr;
    vsip_vattr_d     Vattr;

    vsip_vview_d   ddview,  *dview  = &ddview,
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
       lcview->markings = vsip_valid_structure_object;
       cview->markings  = vsip_valid_structure_object;
       arview->markings = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */

     /* get attributes of A */
     vsip_mgetattrib_d(A, &Mattr);

     /* set up views to point to proper block */
     dview->block     = Mattr.block;
     arview->block    = Mattr.block;
     rview->block     = Mattr.block;
     lcview->block    = Mattr.block;
     cview->block     = Mattr.block;

     /* get attributes of cholesky object */
     vsip_chold_getattr_d(chold, &attr);
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
     /* } else {
        chold->singular  = singular;
     } */
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
     vsip_vputattrib_d(dview, &Vattr);

     Vattr.offset = Mattr.offset + cst;
     Vattr.length = 1; Vattr.stride = rst;
     vsip_vputattrib_d(rview, &Vattr);

     Vattr.stride = cst; Vattr.length = N-1;
     vsip_vputattrib_d(lcview, &Vattr);

     vsip_vputattrib_d(cview, &Vattr);

       /* main decomposition loop */
       /* i = 0 case -- first col(row) */
       i = 0;

    /*vsip_vput_d(dview,i,sqrt(vsip_vget_d(dview,i))); --inlined below */

    {vsip_scalar_d *dv = (dview->block->array) + dview->offset + 
	                  (dview->stride) * i;
      *dv = sqrt(*dv);
      if(fabs(*(dv)) < chold->singular) retval++;
     }  /* inlining ended */

    /*vsip_svmul_d(1/vsip_vget_d(dview,i), arview,lcview); -- inlined below*/

    {vsip_scalar_d *dv = (dview->block->array) + dview->offset + 
	                  (dview->stride) * i;
     vsip_scalar_d onebydv = 1.0/(*dv);

     vsip_svmul_d(onebydv,lcview,lcview);
    }  /* inlining ended */


    /*update the lcview and cview*/

    lcview->offset += rst+cst;
    lcview->length--;
    cview->offset += cst;
    cview->length--;

    /* Compute cols(rows) 2 - N-1 of L(L^t) */
    for(i=1; i< (vsip_scalar_vi) N-1; i++)
    {

      /*vsip_vput_d(dview,i,sqrt(vsip_vget_d(dview,i)-
	vsip_vdot_d(rview,rview))); --inlined below*/

       {vsip_scalar_d *dv = (dview->block->array) + dview->offset + 
	                  (dview->stride) * i;
       *dv = sqrt(*dv - vsip_vdot_d(rview,rview));
       if(fabs(*(dv)) < chold->singular) retval++;
       }   /* inlining ended */

      for(j=0; j<i; j++)
      {
        /*vsip_vsma_d(cview,-vsip_vget_d(rview,j),lcview,lcview);
	 -- inlined get call */

	{vsip_scalar_d *rv = (rview->block->array) + rview->offset + 
	                     (rview->stride) * j;

	vsip_vsma_d(cview,-(*rv),lcview,lcview);
	} 

	cview->offset += rst;
      }

     /*vsip_svmul_d(1/vsip_vget_d(dview,i),lcview,lcview); 
       --inlined the get call below*/

      {vsip_scalar_d *dv = (dview->block->array) + dview->offset + 
	                  (dview->stride) * i;
       vsip_scalar_d onebydv = 1.0/(*dv);

       vsip_svmul_d(onebydv,lcview,lcview);
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
    vsip_vput_d(dview,N-1,sqrt(vsip_vget_d(dview,N-1) -
	vsip_vdot_d(rview,rview)));

  }else if(uplo == VSIP_TR_UPP)
  { /*do all in Upper part */
     /* set up views with proper attributes */

    Vattr.offset   = Mattr.offset;
    Vattr.stride   = rst + cst; Vattr.length = N;
    vsip_vputattrib_d(dview, &Vattr);

    Vattr.offset   = Mattr.offset + rst;
    Vattr.stride = rst; Vattr.length = N-1;
    vsip_vputattrib_d(arview, &Vattr);

    vsip_vputattrib_d(rview, &Vattr);

    Vattr.stride = cst; Vattr.length = 1;
    vsip_vputattrib_d(cview, &Vattr);
       /* main decomposition loop */
       /* i = 0 case -- first col(row) */
       i = 0;

    /*vsip_vput_d(dview,i,sqrt(vsip_vget_d(dview,i))); --inlined below */

    {vsip_scalar_d *dv = (dview->block->array) + dview->offset + 
	                  (dview->stride) * i;
      *dv = sqrt(*dv);
      if(fabs(*(dv)) < chold->singular) retval++;
     }  /* inlining ended */

    /*vsip_svmul_d(1/vsip_vget_d(dview,i), arview,arview); -- inlined below*/

    {vsip_scalar_d *dv = (dview->block->array) + dview->offset + 
	                  (dview->stride) * i;
     vsip_scalar_d onebydv = 1.0/(*dv);

     vsip_svmul_d(onebydv,arview,arview);
    }  /* inlining ended */


    /*update the arview and rview */

    arview->offset += rst+cst;
    arview->length--;
    rview->offset += rst;
    rview->length--;

    /* Compute cols(rows) 2 - N-1  of L(L^t) */
    for(i=1; i< (vsip_scalar_vi) N-1; i++) 
    {

      /*vsip_vput_d(dview,i,sqrt(vsip_vget_d(dview,i)-
	vsip_vdot_d(cview,cview))); --inlined below*/

       {vsip_scalar_d *dv = (dview->block->array) + dview->offset + 
	                  (dview->stride) * i;
       *dv = sqrt(*dv - vsip_vdot_d(cview,cview));
       if(fabs(*(dv)) < chold->singular) retval++;
       }   /* inlining ended */

      for(j=0; j<i; j++)
      {
        /*vsip_vsma_d(rview,-vsip_vget_d(cview,j),arview,arview);
	 -- inlined get call */

	{vsip_scalar_d *cv = (cview->block->array) + cview->offset + 
	                     (cview->stride) * j;

	vsip_vsma_d(rview,-(*cv),arview,arview);
	} 

	rview->offset += cst;
      }

     /*vsip_svmul_d(1/vsip_vget_d(dview,i),arview,arview); 
       --inlined the get call below*/

      {vsip_scalar_d *dv = (dview->block->array) + dview->offset + 
	                  (dview->stride) * i;
       vsip_scalar_d onebydv = 1.0/(*dv);

       vsip_svmul_d(onebydv,arview,arview);
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
      vsip_vput_d(dview,N-1,sqrt(vsip_vget_d(dview,N-1) -
        vsip_vdot_d(cview,cview)));


  } /* end of main if loop */
  return(retval);
}

