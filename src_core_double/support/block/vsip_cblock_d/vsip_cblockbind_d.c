/* Modified by RJudd June 20, 1998 */
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
/* $Id: vsip_cblockbind_d.c,v 1.1 1999/11/14 18:06:16 judd Exp judd $ */
/* to vsip_cblockbind_d.c */
/* Modified RJudd April 10, 1999 */
/* to allow binding NULL in development mode */
/* vsip_blockbind_d.c
// 
// This file contains the vsip_blockbind_d function definition.
//
// Copyright (c) Hughes Research Laboratories, Inc. 1997 
// A non-exclusive, non-royalty bearing license is hereby granted to all 
// persons to copy, modify, distribute and produce derivative works for 
// any purpose, provided that this copyright notice and following disclaimer 
// appear on all copies.  
// 
// THIS LICENSE INCLUDES NO WARRANTEES, EXPRESSED OR IMPLIED, WHETHER ORAL 
// OR WRITTEN, WITH RESPECT TO THE SOFTWARE OR OTHER MATERIAL, INCLUDING 
// BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OF MERCHANTABILITY, OR FITNESS 
// FOR A PARTICULAR PURPOSE, OR ARISING FROM A COURSE OF PERFORMANCE, OR 
// DEALING, OR FROM USAGE OR TRADE, OR OF NON-INFRINGEMENT OF ANY PATENTS 
// OF THIRD PARTIES.
//
// This material is based upon work supported by Ft. Huachuca/DARPA under
// Contract No.  DABT63-96-C-0060.  Any opinions, findings and conclusions
// or recommendations expressed in this material are those of the author(s)
// and do not necessarily reflect the views of Ft. Huachuca/DARPA.
//
// Author: E. Robert Tisdale
//
// Revision History:
// Mar. 28, 1997	Added copyright notice.				*/

#include<vsip.h>
#include<vsip_cblockattributes_d.h>

static void (vsip_public_cblockinit_d)(vsip_cblock_d* b,
  vsip_scalar_d* Rp, vsip_scalar_d* Ip, size_t N, vsip_memory_hint h) {
  if (NULL != b) {			/* Initialize a public block.	*/
    /* init c block attributes for public block*/
    b->kind = 1;	                     /* kind = 1 implies public */
    b->admit = 0;                            /* Not admitted */
    b->cstride = ((Ip == NULL) ? 2 : 1);

    /* init real vsip_block_d b->R */
    b->R->array = Rp;			/* reference public data array	*/
    b->R->kind  = 2;
    b->R->admit = 0;
    b->R->rstride = b->cstride;

    /* init imag vsip_block_d b->I */ 
    b->I->array = ((Ip == NULL) ? Rp + 1 : Ip);                   /* reference public data array  */
    b->I->kind  = 2; 
    b->I->admit = 0; 
    b->I->rstride = b->cstride;
#ifdef VSIP_DEVELOPMENT_MODE
    b->R->size = b->cstride * N * sizeof(vsip_scalar_d);
    b->R->bindings = 0;
    b->R->markings = vsip_valid_structure_object;
    b->I->size = b->R->size - (b->cstride - 1) * sizeof(vsip_scalar_d);
    b->I->bindings = 0; 
    b->I->markings = vsip_valid_structure_object; 
    b->size = 2 * N*sizeof(vsip_scalar_d);   /* data array size in bytes */
    b->bindings = 0;                         /* initialize reference counter */
    b->markings = vsip_valid_structure_object;
    /* Binding to Null is allowed now
    /  if (vsip_check_error(vsip_bad_public_array_pointer)) {
      /  if(NULL == Rp) {
	/  vsip_report_error("In function vsip_public_cblockinit_d,\n"
	  /  "the public data array was referenced through a null pointer.\n");
	/  }
      /  } */
    ++vsip_public_block_total;
#endif /* VSIP_DEVELOPMENT_MODE */
    }
  }

vsip_cblock_d* (vsip_cblockbind_d)(vsip_scalar_d* Rp,vsip_scalar_d* Ip,
  size_t N, vsip_memory_hint h) {	/* Bind to a public data array
		with at least 2 * N vsip_scalar_d real elements.	*/
#ifdef VSIP_DEVELOPMENT_MODE
    if (vsip_check_error(vsip_bad_public_array_pointer)) {
      if(NULL == Rp) {
	vsip_report_error("In function vsip_blockbind_d,\n"
	  "the public data array was referenced through a null pointer.\n");
	}
      }
#endif /* VSIP_DEVELOPMENT_MODE */
  { /* Prevent error checking in vsip_public_cblockinit_d.		*/
    VSIP_SET_ERROR_MASK(mask, vsip_bad_public_array_pointer)
    vsip_cblock_d* b = (vsip_cblock_d*)malloc(sizeof(vsip_cblock_d));
    if(b != NULL){
        b->R = (vsip_block_d*)malloc(sizeof(vsip_cblock_d));
        b->I = (vsip_block_d*)malloc(sizeof(vsip_cblock_d));
        if((b->R == NULL) || (b->I == NULL)){
            free((void *)b->R); 
            free((void *)b->I);
            free((void *)b);
            b = (vsip_cblock_d*)NULL;
        }
    }
    vsip_public_cblockinit_d(b, Rp, Ip, N, h);
    VSIP_PUT_ERROR_MASK(mask)
    return b;
    }
  }

