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
/* $Id: vsip_cmrowview_f.c,v 1.1 1999/12/04 02:44:17 judd Exp judd $ */
/* change to row * col from 1 & 2 */
/* Modified RJudd June 28, 1998 */ 
/* To add complex block support */
/* Modified RJudd January 9, 1999 */
/* to add VI_cmrowview_f.c */
/* vsip_cmrowview_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cmrowview_f function definition.
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
#include<vsip_cvviewattributes_f.h>
#include<VI_functions_f.h>

extern int (vsip_report_error)(const char*, ...);
extern void (vsip_cmcheck_valid_f)(const char*,
  const vsip_cmview_f*);

vsip_cvview_f* (vsip_cmrowview_f)(
  const vsip_cmview_f* M, vsip_index i) {	/* row M_i	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cmcheck_valid_f("vsip_cmrowview_f", M);
    }
  if (vsip_check_error(vsip_view_outside_data_array)) {
    vsip_length		n2 = vsip_cmgetcollength_f(M);
    if (n2 <= i) {
      vsip_report_error("In function vsip_cmrowview_f,\n"
	"rows = %lu <= %lu = row -1.\n",
	(unsigned long int)n2, (unsigned long int)i);
      }
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    VSIP_SET_ERROR_MASK(mask,
      vsip_invalid_structure_object|vsip_view_outside_data_array)
    vsip_cvview_f* v = vsip_cvbind_f(
                            M->block, 
                            M->offset + i * M->col_stride, 
                            M->row_stride, 
                            M->row_length);
    VSIP_PUT_ERROR_MASK(mask)
    return v;
  }
}
vsip_cvview_f* (VI_cmrowview_f)(
      const vsip_cmview_f* M, 
      vsip_index i, 
      vsip_cvview_f *a) {
      a->block = M->block;
      a->offset = M->offset + i * M->col_stride;
      a->stride = M->row_stride;
      a->length = M->row_length;
#ifdef VSIP_DEVELOPMENT_MODE
      a->markings = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */
      return a;
}
