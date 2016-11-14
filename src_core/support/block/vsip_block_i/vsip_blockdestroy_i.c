/* Modified RJudd June 27, 1998 */
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
/* $Id: vsip_blockdestroy_i.c,v 1.1 1999/12/04 02:55:48 judd Exp judd $ */
/* Modified to make API agree with cblockdestroy */
/* vsip_blockdestroy_i.c Version 0.000 March 28, 1997
// 
// This file contains the vsip_blockdestroy_i function definition.
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

void (vsip_public_blockterm_i)(vsip_block_i* b) {
  if (NULL != b) {			/* Terminate a public  block.	*/
#ifdef VSIP_DEVELOPMENT_MODE
    if (vsip_check_error(vsip_invalid_structure_object)) {
      vsip_blockcheck_valid_i("vsip_public_blockterm_i", b);
      }
    if (vsip_check_error(vsip_non_zero_binding_counter)) {
      if (0 != b->bindings) {
	vsip_report_error("In function vsip_public_blockterm_i,\n"
	  "%i view objects are still bound to the block object.\n",
	  b->bindings);
	}
      }
    --vsip_public_block_total;
    b->markings = vsip_freed_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */
    }
  }

void (vsip_privateblockterm_i)(vsip_block_i* b) {
  if (NULL != b) {			/* Terminate a private block.	*/
#ifdef VSIP_DEVELOPMENT_MODE
    if (vsip_check_error(vsip_invalid_structure_object)) {
      vsip_blockcheck_valid_i("vsip_privateblockterm_i", b);
      }
    if (vsip_check_error(vsip_non_zero_binding_counter)) {
      if (0 != b->bindings) {
	vsip_report_error("In function vsip_privateblockterm_i,\n"
	  "%i view objects are still bound to the block object.\n",
	  b->bindings);
	}
      }
    --vsip_privateblock_total;
    b->markings = vsip_freed_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */
    free((void*)b->array);
    }
  }

void (vsip_blockdestroy_i)(vsip_block_i* b) {
  /* Destroy *b and return a pointer to the public data array
     if vsip_block_i *b was public, otherwise return a null pointer. */
  vsip_scalar_i *p; 
  if (NULL != b) {
#ifdef VSIP_DEVELOPMENT_MODE
    if (vsip_check_error(vsip_invalid_structure_object)) {
      vsip_blockcheck_valid_i("vsip_blockdestroy_i", b);
      }
    if (vsip_check_error(vsip_non_zero_binding_counter)) {
      if (0 != b->bindings) {
	vsip_report_error("In function vsip_blockdestroy_i,\n"
	  "%i view objects are still bound to the block object.\n",
	  b->bindings);
	}
      }
#endif /* VSIP_DEVELOPMENT_MODE */
    { /* Prevent error checking in vsip_public_blockterm_i or
	vsip_public_blockterm_i.					*/
      VSIP_SET_ERROR_MASK(mask,
	vsip_invalid_structure_object|vsip_non_zero_binding_counter)
      p = vsip_blockfind_i(b);
      if (b->kind == 0) {			/* free the private data array	*/
	vsip_privateblockterm_i(b);
	}
      else {
	vsip_public_blockterm_i(b);
	}
      free((void*)b);			/* destroy the block *b itself	*/
      VSIP_PUT_ERROR_MASK(mask)
      return;
      }
    }
  else {				/* Destroying a null pointer is	*/
    p = NULL;			/* guaranteed to be harmless.	*/
    return;
    }
  }

