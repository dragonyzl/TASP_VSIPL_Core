/* Modified RJudd June 20, 1998 */
/* for Complex Block Addition */
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
/* $Id: vsip_cblockcreate_f.c,v 1.3 1999/11/14 18:15:40 judd Exp judd $ */
/* Modified RJudd July 11 */
/* to modify complex block */
/* vsip_cblockcreate_f.c Version 0.000 March 28, 1997
// 
// This file contains the vsip_cblockcreate_f function definition.
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
#include<vsip_cblockattributes_f.h>

static void (vsip_cprivateblockinit_f)(vsip_cblock_f* b,
  size_t N, vsip_memory_hint h) {	/* Create a private data array with at least N
				  vsip_scalar_f complex elements.	*/
  if (NULL != b) {			/* Initialize a private block.	*/
    size_t	size = 2*N*sizeof(vsip_scalar_f);

    /* initialize real block */
    b->R->array = (vsip_scalar_f*)malloc(size);
    b->R->kind  = 2;
    b->R->admit = 1;
    b->R->rstride = 2; /*default block is interleaved */

    /* initialize imaginary block */
    b->I->array = b->R->array + 1;
    b->I->kind  = 2; 
    b->I->admit = 1; 
    b->I->rstride = 2; /*default block is interleaved */

    b->kind = 0;			/* kind = 0 implies private	*/
    b->admit = 1;                       /* admit = 1 implies admited    */
    b->cstride = 2;                     /* interleaved                  */
#ifdef VSIP_DEVELOPMENT_MODE
    b->R->size = size;
    b->R->bindings = 0;
    b->R->markings = vsip_valid_structure_object;
    b->I->size = size - sizeof(vsip_scalar_f);
    b->I->bindings = 0; 
    b->I->markings = vsip_valid_structure_object; 
    b->size = size;			/* data array size in bytes	*/
    b->bindings = 0;			/* reference counter		*/
    b->markings = vsip_valid_structure_object;
    if (vsip_check_error(vsip_bad_private_array_storage)) {
      if(NULL == b->R->array) {
	vsip_report_error("In function vsip_cprivateblockinit_f,\n"
	  "the private data array memory allocation failed.\n");
	}
      }
    if (vsip_check_error(vsip_invalid_structure_object)) {
      size_t	j = 0;			/* Initialize the data array	*/
      for (j = 0; j < 2*N; j++) {	/* with some obnoxious value.	*/
	b->R->array[j] = VSIP_MAX_SCALAR_F;
	}
      }
    ++vsip_privateblock_total;
#endif /* VSIP_DEVELOPMENT_MODE */
    }
  }

vsip_cblock_f* (vsip_cblockcreate_f)(size_t N, vsip_memory_hint h) {
				/* Create a private data array with at least N
				  vsip_scalar_f complex elements.	*/
  vsip_cblock_f* b = (vsip_cblock_f*)malloc(sizeof(vsip_cblock_f));
  if(b != NULL){
      b->R = (vsip_block_f*)malloc(sizeof(vsip_cblock_f));
      b->I = (vsip_block_f*)malloc(sizeof(vsip_cblock_f));
      if((b->R == NULL) || (b->I == NULL)){
          free((void *)b->R);
          free((void *)b->I);
          free((void *)b);
          b = (vsip_cblock_f*)NULL;
      }
      if(b != NULL){
         vsip_cprivateblockinit_f(b, N, h);
         if(b->R->array == NULL){
           free((void *)b->R);
           free((void *)b->I);
           free((void *)b);
           b = (vsip_cblock_f*)NULL;
         }
      }
  }    
  return b;
}
