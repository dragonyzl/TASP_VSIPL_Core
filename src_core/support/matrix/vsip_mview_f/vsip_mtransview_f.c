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
/* $Id: vsip_mtransview_f.c,v 1.1 1999/12/04 02:42:47 judd Exp judd $ */
/* 1,2 to row,col */
/* Modified RJudd January 1, 1999 */
/* to add attribute support */
/* Modified RJudd to fix row col again Feb 14, 1999 */
/* vsip_mtransview_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_mtransview_f function definition.
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

extern int (vsip_report_error)(const char*, ...);
extern void (vsip_mcheck_valid_f)(const char*,
  const vsip_mview_f*);
extern void (vsip_mcheck_outside_f)(const char*,
  const vsip_block_f*, vsip_offset,
  vsip_stride, vsip_length, vsip_stride, vsip_length);

vsip_mview_f* (vsip_mtransview_f)(
  const vsip_mview_f* M) {/* transpose matrix view	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_mcheck_valid_f("vsip_mtransview_f", M);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { /* Prevent error checking in vsip_mgetblock_f,
      vsip_mgetoffset_f,  vsip_mgetrowstride_f,
      vsip_mgetrowlength_f, vsip_mgetcolstride_f,
      vsip_mgetcollength_f and vsip_mbind_f.	*/
    VSIP_SET_ERROR_MASK(mask,
      vsip_invalid_structure_object|vsip_view_outside_data_array)
    vsip_block_f*	b = M->block;
    vsip_offset		o = M->offset;
    vsip_stride		s1 = M->row_stride;
    vsip_stride		n1 = M->row_length;
    vsip_stride		s2 = M->col_stride;
    vsip_stride		n2 = M->col_length;
    vsip_mview_f* R = vsip_mbind_f(b, o, s1, n1, s2, n2);
    VSIP_PUT_ERROR_MASK(mask)
    return R;
    }
  }

vsip_mview_f *VI_mtransview_f(const vsip_mview_f* M, vsip_mview_f * Mt)
{
   *Mt = *M;
   Mt->row_stride = M->col_stride;
   Mt->col_stride = M->row_stride;
   Mt->row_length = M->col_length;
   Mt->col_length = M->row_length;
   return Mt;
}

