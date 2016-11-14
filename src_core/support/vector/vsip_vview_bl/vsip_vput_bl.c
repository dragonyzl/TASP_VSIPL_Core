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
/* $Id: vsip_vput_bl.c,v 1.1 1999/12/04 02:40:38 judd Exp judd $ */
/* Modify to use vviewattributes */
/* vsip_vput_bl.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vput_bl function definition.
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
#include<vsip_vviewattributes_bl.h>

extern void (vsip_vcheck_valid_bl)(const char*,
  const vsip_vview_bl*);
extern int (vsip_report_error)(const char*, ...);

void (vsip_vput_bl)(const vsip_vview_bl *v,
  vsip_index j, vsip_scalar_bl zeta) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_bl("vsip_vput_bl", v);
    }
  if (vsip_check_error(vsip_view_index_exceeds_length)) {
    vsip_length	n = vsip_vgetlength_bl(v);
    if (n <= j) {
      vsip_report_error("In function vsip_vput_bl,\n"
	"length = %lu <= %lu = -1.\n",
	(unsigned long int)n, (unsigned long int)j);
      exit(EXIT_FAILURE);
      }
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
    vsip_offset	offset = v->offset + j * v->stride;
    vsip_block_bl*   b = v->block;
    b->array[offset]   = zeta;
  }
}
