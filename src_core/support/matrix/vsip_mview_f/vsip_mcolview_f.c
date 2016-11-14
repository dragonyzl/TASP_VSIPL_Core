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
/* $Id: vsip_mcolview_f.c,v 1.1 1999/12/04 02:42:31 judd Exp judd $ */
/* 1,2 to row,col */
/* Modified RJudd January 1, 1998 */
/* to add attributes support */
/* vsip_mcolview_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_mcolview_f function definition.
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
// Feb. 28, 1997    Added copyright notice.
// Mar. 31, 1997    Modified to conform with VSIP decoder ring.    */

#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>

extern int (vsip_report_error)(const char*, ...);
extern void (vsip_mcheck_valid_f)(const char*,
  const vsip_mview_f*);

vsip_vview_f* (vsip_mcolview_f)(
  const vsip_mview_f* M, vsip_index j) {    /* column M_j    */
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_mcheck_valid_f("vsip_mcolview_f", M);
    }
  if (vsip_check_error(vsip_view_outside_data_array)) {
    vsip_length        n1 = vsip_mgetrowlength_f(M);
    if (n1 <= j) {
      vsip_report_error("In function vsip_mcolview_f,\n"
    "columns = %lu <= %lu = column -1.\n",
    (unsigned long int)n1, (unsigned long int)j);
      }
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { /* Prevent error checking in vsip_mgetblock_f,
      vsip_mgetoffset_f,  vsip_mgetrowstride_f,
      vsip_mgetcolstride_f, vsip_mgetcollength_f
      and vsip_vbind_f.                    */
    VSIP_SET_ERROR_MASK(mask,
      vsip_invalid_structure_object|vsip_view_outside_data_array)
    vsip_block_f*      b  = M->block;
    vsip_offset        o  = M->offset;
    vsip_stride        s1 = M->row_stride;
    vsip_stride        s2 = M->col_stride;
    vsip_length        n2 = M->col_length;
    vsip_vview_f* v = vsip_vbind_f(b, o + j*s1, s2, n2);
    VSIP_PUT_ERROR_MASK(mask)
    return v;
    }
  }

vsip_vview_f* (VI_mcolview_f)(
      const vsip_mview_f* M,
      vsip_index i,
      vsip_vview_f *a) {
      a->block = M->block;
      a->offset = M->offset + i * M->row_stride;
      a->stride = M->col_stride;
      a->length = M->col_length;
#ifdef VSIP_DEVELOPMENT_MODE
      a->markings = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */
      return a;
}
