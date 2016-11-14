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
/* $Id: vsip_cmsubview_d.c,v 1.1 1999/12/04 06:32:42 judd Exp judd $ */
/* Modified to row, col from 1, 2 */
/* Modified RJudd June 28, 1998 */ 
/* To add complex block support */
/* Modified RJudd to fix row col again Feb 14, 1999 */
/* Modified RJudd February 15, 1999 */
/* to _d from _f for core profile */
/* vsip_cmsubview_d.c 
// 
// This file contains the vsip_cmsubview_d function definition.
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

extern int (vsip_report_error)(const char*, ...);
extern void (vsip_cmcheck_valid_d)(const char*,
  const vsip_cmview_d*);
extern void (vsip_cmcheck_outside_d)(const char*,
  const vsip_cblock_d*, vsip_offset,
  vsip_stride, vsip_length, vsip_stride, vsip_length);

vsip_cmview_d* (vsip_cmsubview_d)(
  const vsip_cmview_d* M,
  vsip_index i, vsip_index j,vsip_length m, vsip_length n) {
						/* submatrix view	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cmcheck_valid_d("vsip_cmsubview_d", M);
    }
  if (vsip_check_error(vsip_view_outside_data_array)) {
    vsip_cblock_d*	b = vsip_cmgetblock_d(M);
    vsip_offset		o = vsip_cmgetoffset_d(M);
    vsip_stride		s1 = vsip_cmgetrowstride_d(M);
    vsip_length		n1 = vsip_cmgetrowlength_d(M);
    vsip_stride		s2 = vsip_cmgetcolstride_d(M);
    vsip_length		n2 = vsip_cmgetcollength_d(M);
    if (n1 < j + n ) {
      vsip_report_error("In function vsip_cmsubview_d,\n"
	"view columns = %lu < %lu + %lu = -1 + subview columns.\n",
	(unsigned long int)n1, (unsigned long int)j, (unsigned long int)n);
      }
    if (n2 < i + m ) {
      vsip_report_error("In function vsip_cmsubview_d,\n"
	"view rows = %lu < %lu + %lu = -1 + subview rows.\n",
	(unsigned long int)n2, (unsigned long int)i, (unsigned long int)m);
      }
    vsip_cmcheck_outside_d("vsip_cmsubview_d",
    b, o + j*s1 + i*s2, s2, m, s1, n);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
    vsip_cmview_d* W = vsip_cmbind_d(
                            M->block, 
                            M->offset + j * M->row_stride + i * M->col_stride, 
                            M->col_stride, 
                            m,
                            M->row_stride, 
                            n); 
    return W;
  }
}

