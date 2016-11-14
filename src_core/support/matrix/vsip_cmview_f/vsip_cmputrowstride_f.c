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
/* $Id: vsip_cmputrowstride_f.c,v 1.1 1999/12/04 02:44:17 judd Exp judd $ */
/* change to row * col from 1 & 2 */
/* Modified RJudd June 28, 1998 */ 
/* To add complex block support */
/* Modified RJudd August 3, 1998 */
/* to add attribute structure */
/* vsip_cmputrowstride_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cmputrowstride_f function definition.
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
#include<vsip_cmviewattributes_f.h>
extern void (vsip_cmcheck_valid_f)(const char*,
  const vsip_cmview_f*);
extern void (vsip_cmcheck_outside_f)(const char*,
  const vsip_cblock_f*, vsip_offset,
  vsip_stride, vsip_length, vsip_stride, vsip_length);

vsip_cmview_f* (vsip_cmputrowstride_f)(
  vsip_cmview_f* M, vsip_stride s1) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cmcheck_valid_f("vsip_cmputrowstride_f", M);
    }
  if (vsip_check_error(vsip_view_outside_data_array)) {
    vsip_cmattr_f attr;
    vsip_cmgetattrib_f(M, &attr);
    vsip_cmcheck_outside_f("vsip_cmputrowstride_f",
    attr.block, attr.offset, attr.col_stride, attr.col_length, s1, attr.row_length);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
    M->row_stride = s1;
    return M;
  }
}

