/* Modified RJudd April 20, 1998 */
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
/* $Id: vsip_mbind_f.c,v 1.1 1999/12/04 02:42:30 judd Exp judd $ */
/* 1,2 to row,col */
/* Modified RJudd to fix row col again Feb 14, 1999 */
/* vsip_mbind_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_mbind_f function definition.
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
#include<vsip_mviewattributes_f.h>

extern void (vsip_blockcheck_valid_f)(const char*,
  const vsip_block_f*);
extern void (vsip_mcheck_outside_f)(const char*,
  const vsip_block_f*,
  vsip_offset, vsip_stride, vsip_length, vsip_stride, vsip_length);

void (vsip_mviewinit_f)(vsip_mview_f* M,
  const vsip_block_f* b, vsip_offset o,
  vsip_stride s1, vsip_length n1, vsip_stride s2, vsip_length n2) {
  if (NULL != M) {			/* Initialize a matrix view.	*/
    M->block   = (vsip_block_f*)b;
    M->offset  = o;
    M->row_stride = s1;
    M->row_length = n1;
    M->col_stride = s2;
    M->col_length = n2;
#ifdef VSIP_DEVELOPMENT_MODE
    M->markings = vsip_valid_structure_object;
    if (vsip_check_error(vsip_invalid_structure_object)) {
      vsip_blockcheck_valid_f("vsip_mviewinit_f", b);
      }
    if (vsip_check_error(vsip_view_outside_data_array)) {
      vsip_mcheck_outside_f("vsip_mviewinit_f",
      b, o, s1, n1, s2, n2);
      }
    /* ++b->bindings; */		/* increment reference counter	*/
    { /* Prevent compilers from complaining about const b->bindings.	*/
      int*	p = (int*)(&(b->bindings));
      ++(*p);
      }
    ++vsip_matrix_object_total;
#endif /* VSIP_DEVELOPMENT_MODE */
    }
  }

vsip_mview_f* (vsip_mbind_f)(
  const vsip_block_f* b, vsip_offset o,
  vsip_stride s2, vsip_length n2, vsip_stride s1, vsip_length n1) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_blockcheck_valid_f("vsip_mbind_f", b);
    }
  if (vsip_check_error(vsip_view_outside_data_array)) {
    vsip_mcheck_outside_f("vsip_mbind_f",
    b, o, s1, n1, s2, n2);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { /* Prevent error checking in vsip_mviewinit_f.	*/
    VSIP_SET_ERROR_MASK(mask,
      vsip_invalid_structure_object|vsip_view_outside_data_array)
    vsip_mview_f* M =
      (vsip_mview_f*)malloc(sizeof(vsip_mview_f));
    vsip_mviewinit_f(M, b, o, s1, n1, s2, n2);
    VSIP_PUT_ERROR_MASK(mask)
    return M;
    }
  }

