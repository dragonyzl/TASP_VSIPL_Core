/* Modified RJudd July 13, 1998 */
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
/* $Id: vsip_vputoffset_mi.c,v 1.1 1999/12/02 19:23:04 judd Exp judd $ */
/* to add viewattributes support */
/* Modified RJudd August 3, 1998 */
/* to add attribute structure */
/* vsip_vputoffset_mi.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vputoffset_mi function definition.
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
#include<vsip_vviewattributes_mi.h>

extern void (vsip_vcheck_valid_mi)(const char*,
  const vsip_vview_mi*);
extern void (vsip_vcheck_outside_mi)(const char*,
  const vsip_block_mi*, vsip_offset, vsip_stride, vsip_length);

vsip_vview_mi* (vsip_vputoffset_mi)(
  vsip_vview_mi* v, vsip_offset o) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_mi("vsip_vputlength_mi", v);
    }
  if (vsip_check_error(vsip_view_outside_data_array)) {
    vsip_vattr_mi attr;
    vsip_vgetattrib_mi(v, &attr);
    vsip_vcheck_outside_mi("vsip_vputoffset_mi",
    attr.block, o, attr.stride, attr.length);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    v->offset = o;
    return v;
  }
}

