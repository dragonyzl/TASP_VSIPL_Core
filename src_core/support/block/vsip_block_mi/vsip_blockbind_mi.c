/* Modified RJudd October 10, 1998 */
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
/* $Id: vsip_blockbind_mi.c,v 1.2 1999/12/04 02:51:07 judd Exp judd $ */
/* to make a matrix index block type */
/* Modified RJudd April 10, 1999 */
/* to allow binding NULL in development mode */
/* 
// This file contains the vsip_blockbind_mi function definition.
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
*/

#include<vsip.h>
#include<vsip_blockattributes_mi.h>

void (vsip_public_blockinit_mi)(vsip_block_mi* b,
  vsip_scalar_vi* p, size_t N, vsip_memory_hint h) {
  if (NULL != b) {			/* Initialize a user block.	*/
    b->array = p;			/* reference public data array	*/
    b->kind = 1;			/* kind = 1 implies public	*/
    b->admit = 0;                       /* admit = 0 implies released   */
#ifdef VSIP_DEVELOPMENT_MODE
    b->size = 2 * N * sizeof(vsip_scalar_vi);/* data array size in bytes*/
    b->bindings = 0;			/* initialize reference counter	*/
    b->markings = vsip_valid_structure_object;
    ++vsip_public_block_total;
#endif /* VSIP_DEVELOPMENT_MODE */
    }
  }

vsip_block_mi* (vsip_blockbind_mi)(vsip_scalar_vi* p,
  size_t N, vsip_memory_hint h) {	/* Bind to a public data array
		with at least 2 * N vsip_scalar_vi real elements.	*/
#ifdef VSIP_DEVELOPMENT_MODE
#endif /* VSIP_DEVELOPMENT_MODE */
  { /* Prevent error checking in vsip_public_blockinit_mi.		*/
    VSIP_SET_ERROR_MASK(mask, vsip_bad_public_array_pointer)
    vsip_block_mi *b = (vsip_block_mi*)malloc(sizeof(vsip_block_mi));
    vsip_public_blockinit_mi(b, p, N, h);
    VSIP_PUT_ERROR_MASK(mask)
    return b;
    }
  }

