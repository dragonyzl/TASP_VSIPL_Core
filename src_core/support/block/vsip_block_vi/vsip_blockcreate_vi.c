/* Modified RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_blockcreate_vi.c,v 1.3 1999/12/04 02:57:04 judd Exp judd $ */
/* vsip_blockcreate_vi.c Version 0.000 March 28, 1997
// 
// This file contains the vsip_blockcreate_vi function definition.
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
#include<vsip_blockattributes_vi.h>

static void (vsip_privateblockinit_vi)(vsip_block_vi* b,
  size_t N, vsip_memory_hint h) {	/* Create a private data array with at least N
				  vsip_scalar_vi real    elements.	*/
  if (NULL != b) {			/* Initialize a private block.	*/
    size_t	size = N*sizeof(vsip_scalar_vi);
    b->array = (vsip_scalar_vi*)malloc(size);
					/* allocate private data array	*/
    b->kind = 0;			/* kind = 0 implies private	*/
    b->admit = 1;                       /* admit = 1 implies admited    */
#ifdef VSIP_DEVELOPMENT_MODE
    b->size = size;			/* data array size in bytes	*/
    b->bindings = 0;			/* reference counter		*/
    b->markings = vsip_valid_structure_object;
    if (vsip_check_error(vsip_bad_private_array_storage)) {
      if(NULL == b->array) {
        vsip_report_error("In function vsip_privateblockinit_vi,\n"
	  "the private data array memory allocation failed.\n");
	}
      }
    if (vsip_check_error(vsip_invalid_structure_object)) {
      size_t	j = 0;			/* Initialize the data array	*/
      for (j = 0; j < N; j++) {		/* with some obnoxious value.	*/
	b->array[j] = VSIP_MAX_SCALAR_VI;
      }
    }
    ++vsip_privateblock_total;
#endif /* VSIP_DEVELOPMENT_MODE */
  }
}

vsip_block_vi* (vsip_blockcreate_vi)(size_t N, vsip_memory_hint h) {
			/* Create a private data array with at least N
			  vsip_scalar_vi real scalar elements.	*/
  vsip_block_vi* b = (vsip_block_vi*)malloc(sizeof(vsip_block_vi));
  if(b != NULL){
      vsip_privateblockinit_vi(b, N, h);
      if(b->array == NULL){
          free((void*)b);
          b = NULL;
      }
  }
  return b;
}

