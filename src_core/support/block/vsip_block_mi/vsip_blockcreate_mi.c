/* Modified RJudd January 1, 1999 */
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
/* $Id: vsip_blockcreate_mi.c,v 1.3 1999/12/04 02:51:08 judd Exp judd $ */
/* to handle block of type vsip_block_mi */
/*
// 
//
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
// Mar. 28, 1997    Added copyright notice.                */

#include<vsip.h>
#include<vsip_blockattributes_mi.h>

static void (vsip_privateblockinit_mi)(vsip_block_mi* b,
  size_t N, vsip_memory_hint h) {    
   /* Create a private data array with at least 2 * N vsip_scalar_vi real elements. */
  if (NULL != b) {           /* Initialize a private block. */
    size_t size = 2 * N * sizeof(vsip_scalar_vi);
                            /* allocate private data array  */
    b->array  = (vsip_scalar_vi*) malloc(size);
    b->kind = 0;            /* kind = 0 implies private     */
    b->admit = 1;           /* admit = 1 implies admited    */
#ifdef VSIP_DEVELOPMENT_MODE
    b->size = size;            /* data array size in bytes  */
    b->bindings = 0;           /* reference counter         */
    b->markings = vsip_valid_structure_object;
    if (vsip_check_error(vsip_bad_private_array_storage)) {
      if(NULL == b->array) {
        vsip_report_error("In function vsip_privateblockinit_mi,\n"
      "the private data array memory allocation failed.\n");
    }
      }
    if (vsip_check_error(vsip_invalid_structure_object)) {
      size_t    j = 0;            /* Initialize the data array    */
      for (j = 0; j < 2 * N; j++) {        /* with some obnoxious value.    */
         b->array[j] = VSIP_MAX_SCALAR_VI;
      }
    }
    ++vsip_privateblock_total;
#endif /* VSIP_DEVELOPMENT_MODE */
  }
}

vsip_block_mi* (vsip_blockcreate_mi)(size_t N, vsip_memory_hint h) {
            /* Create a private data array with at least 2 * N
              vsip_scalar_vi real scalar elements.    */
  vsip_block_mi* b = (vsip_block_mi*)malloc(sizeof(vsip_block_mi));
  if(b != NULL){
      vsip_privateblockinit_mi(b, N, h);
      if(b->array == NULL){
          free((void*)b);
          b = NULL;
      }
  }
  return b;
}

