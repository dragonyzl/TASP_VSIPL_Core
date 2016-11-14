/* Modified RJudd June 28, 1998 */ 
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
/* $Id: vsip_cmdestroy_d.c,v 1.1 1999/12/04 06:32:33 judd Exp judd $ */
/* To add complex block support */
/* Modified RJudd February 15, 1999 */
/* to _d from _f for core profile */
/* vsip_cmdestroy_d.c 
// 
// This file contains the vsip_cmdestroy_d function definition.
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
// Feb. 28, 1997	Added copyright notice.
// Mar. 31, 1997	Modified to conform with VSIP decoder ring.	*/

#include<vsip.h>
#include<vsip_cmviewattributes_d.h>

extern void (vsip_cmcheck_valid_d)(const char*,
  const vsip_cmview_d*);

void (vsip_cmviewterm_d)(vsip_cmview_d* M) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (NULL != M) {			/* Terminate a matrix view.	*/
    if (vsip_check_error(vsip_invalid_structure_object)) {
      vsip_cmcheck_valid_d("vsip_cmviewterm_d", M);
      }
    --M->block->bindings;		/* decrement reference counter	*/
    M->markings = vsip_freed_structure_object;
    --vsip_matrix_object_total;
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  }

vsip_cblock_d* (vsip_cmdestroy_d)(
  vsip_cmview_d* M) {	/* matrix view  destructor	*/
  if (NULL != M) {
#ifdef VSIP_DEVELOPMENT_MODE
    if (vsip_check_error(vsip_invalid_structure_object)) {
      vsip_cmcheck_valid_d("vsip_cmdestroy_d", M);
      }
#endif /* VSIP_DEVELOPMENT_MODE */
    { /* Prevent error checking in vsip_cmgetblock_d and
	vsip_cmviewterm_d.					*/
      VSIP_SET_ERROR_MASK(mask, vsip_invalid_structure_object)
      vsip_cblock_d* b = vsip_cmgetblock_d(M);
      vsip_cmviewterm_d(M);
      VSIP_PUT_ERROR_MASK(mask)
      free((void*)M);
      return b;
      }
    }
  else {				/* Destroying a null pointer is	*/
    return (vsip_cblock_d*)NULL;	/* guaranteed to be harmless.	*/
    }
  }

