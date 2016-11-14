/* Modified RJudd March 19, 1998 */
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
/* $Id: vsip_blockbind_i.c,v 1.2 1999/12/04 02:55:47 judd Exp judd $ */
/* vsip_blockbind_i.c */
/* Modified RJudd April 10, 1999 */
/* to allow binding NULL in development mode */
/* vsip_blockbind_d.c Version 0.000 March 28, 1997
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
#include<vsip_blockattributes_i.h>

void (vsip_public_blockinit_i)(vsip_block_i* b,
  vsip_scalar_i* p, size_t N, vsip_memory_hint h) {
  if (NULL != b) {			/* Initialize a public block.	*/
    b->array = p;			/* reference public data array	*/
    b->kind = 1;			/* kind = 1 implies public	*/
    b->admit = 0;
#ifdef VSIP_DEVELOPMENT_MODE
    b->size = N*sizeof(vsip_scalar_i);/* data array size in bytes	*/
    b->bindings = 0;			/* initialize reference counter	*/
    b->markings = vsip_valid_structure_object;
    ++vsip_public_block_total;
#endif /* VSIP_DEVELOPMENT_MODE */
    }
  }

vsip_block_i* (vsip_blockbind_i)(vsip_scalar_i* p,
  size_t N, vsip_memory_hint h) {	/* Bind to a public data array
		with at least N vsip_scalar_i real elements.	*/
  { /* Prevent error checking in vsip_public_blockinit_i.		*/
    VSIP_SET_ERROR_MASK(mask, vsip_bad_public_array_pointer)
    vsip_block_i*
      b = (vsip_block_i*)malloc(sizeof(vsip_block_i));
    vsip_public_blockinit_i(b, p, N, h);
    VSIP_PUT_ERROR_MASK(mask)
    return b;
    }
  }

