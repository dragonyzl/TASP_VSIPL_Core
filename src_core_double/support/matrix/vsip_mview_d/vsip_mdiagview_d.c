/* Modified RJudd December 12, 1998 */
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
/* $Id: vsip_mdiagview_d.c,v 1.1 1999/12/04 06:30:35 judd Exp judd $ */
/* to add index support */
/* Modified RJudd February 15, 1999 */
/* to _d from _f for core profile */
/* vsip_mdiagview_d.c
// 
// This file contains the vsip_mdiagview_d function definition.
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
#include<vsip_mviewattributes_d.h>

extern int (vsip_report_error)(const char*, ...);
extern void (vsip_mcheck_valid_d)(const char*,
  const vsip_mview_d*);

vsip_vview_d* (vsip_mdiagview_d)(
  const vsip_mview_d* M,
  int idiag) {		/* diag{M_ii}	*/
  vsip_index i,j;
  i = (idiag < 0) ? -idiag : 0;
  j = (idiag > 0) ?  idiag : 0;
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_mcheck_valid_d("vsip_mdiagview_d", M);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { /* Prevent error checking in vsip_mgetblock_d,
      vsip_mgetoffset_d,  vsip_mgetrowstride_d,
      vsip_mgetrowlength_d, vsip_mgetcolstride_d,
      vsip_mgetcollength_d and vsip_vbind_d.	*/
    VSIP_SET_ERROR_MASK(mask,
      vsip_invalid_structure_object|vsip_view_outside_data_array)
    vsip_block_d*	b = M->block;
    vsip_offset		o = M->offset + j * M->row_stride + i * M->col_stride;
    vsip_stride		s1 = M->row_stride;
    vsip_stride		s2 = M->col_stride;
    vsip_length		n1 = M->row_length - j;
    vsip_length		n2 = M->col_length - i;
    vsip_vview_d* v = vsip_vbind_d(b, o, s2 + s1, (n1 < n2)? n1: n2);
    VSIP_PUT_ERROR_MASK(mask)
    return v;
    }
  }

