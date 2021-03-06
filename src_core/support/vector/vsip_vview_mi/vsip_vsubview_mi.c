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
/* $Id: vsip_vsubview_mi.c,v 1.1 1999/12/02 19:23:05 judd Exp judd $ */
/* to include attributes information */
/* vsip_vsubview_mi.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vsubview_mi function definition.
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
// Feb. 28, 1997   Added copyright notice.
// Mar. 31, 1997   Modified to conform with VSIP decoder ring.   */

#include<vsip.h>
#include<vsip_vviewattributes_mi.h>

extern int (vsip_report_error)(const char*, ...);
extern void (vsip_vcheck_valid_mi)(const char*,
  const vsip_vview_mi*);
extern void (vsip_vcheck_outside_mi)(const char*,
  const vsip_block_mi*, vsip_offset, vsip_stride, vsip_length);

vsip_vview_mi* (vsip_vsubview_mi)(
  const vsip_vview_mi* v, vsip_index j, vsip_length n) {
                  /* subvector view   */
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_mi("vsip_vsubview_mi", v);
    }
  if (vsip_check_error(vsip_view_outside_data_array)) {
    vsip_block_mi*   b = vsip_vgetblock_mi(v);
    vsip_offset      o = vsip_vgetoffset_mi(v);
    vsip_stride      s = vsip_vgetstride_mi(v);
    vsip_length      l = vsip_vgetlength_mi(v);
    if (l < j + n ) {
      vsip_report_error("In function vsip_vsubview_mi,\n"
   "view length = %lu < %lu + %lu = -1 + subview length.\n",
   (unsigned long int)l, (unsigned long int)j, (unsigned long int)n);
      }
    vsip_vcheck_outside_mi("vsip_vsubview_mi",
    b, o + j*s, s, n);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { /* Prevent error checking in vsip_vgetblock_mi,
      vsip_vgetoffset_mi, vsip_vgetstride_mi
      and vsip_vbind_mi.               */
    VSIP_SET_ERROR_MASK(mask,
      vsip_invalid_structure_object|vsip_view_outside_data_array)
    vsip_block_mi*   b = v->block;
    vsip_offset      o = v->offset;
    vsip_stride      s = v->stride;
    vsip_vview_mi*   t = vsip_vbind_mi(b, o + j*s, s, n);
    VSIP_PUT_ERROR_MASK(mask)
    return t;
    }
  }

