/* Modified RJudd June 28, 1998 */ 
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
/* $Id: vsip_mimagview_d.c,v 1.1 1999/12/04 06:32:43 judd Exp judd $ */
/* To add complex block support */
/* Modified RJudd July 11, 1998 */
/* to modify complex blocks */
/* Modified RJudd February 15, 1999 */
/* to _d from _f for core profile */
/* vsip_mimagview_d.c 
// 
// This file contains the vsip_mimagview_d function definition.
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
#include<vsip_mviewattributes_d.h>

extern void (vsip_cmcheck_valid_d)(const char*,
  const vsip_cmview_d*);

vsip_mview_d* (vsip_mimagview_d)(
  const vsip_cmview_d* M) {		/* imaginary part only	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cmcheck_valid_d("vsip_mimagview_d", M);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
      vsip_mview_d *MI = (vsip_mview_d*)malloc(sizeof(vsip_mview_d));
      if( MI == NULL){
         vsip_mdestroy_d(MI);
         return (vsip_mview_d*)NULL;
      } 
      MI->block = M->block->I;
      MI->offset = M->offset;
      MI->row_length = M->row_length;
      MI->col_length = M->col_length;
      MI->row_stride = M->row_stride;
      MI->col_stride = M->col_stride;
      #ifdef VSIP_DEVELOPMENT_MODE
          MI->block->bindings += 1;
          MI->markings = vsip_valid_structure_object; 
      #endif
      return MI;
  }
}

vsip_mview_d* VI_mimagview_d(
      const vsip_cmview_d* X,
      vsip_mview_d* Y)
{
     Y->block = X->block->I;
     Y->offset = X->offset;
     Y->row_length = X->row_length;
     Y->col_length = X->col_length;
     Y->row_stride = X->row_stride;
     Y->col_stride = X->col_stride;
     #ifdef VSIP_DEVELOPMENT_MODE
         Y->markings = vsip_valid_structure_object;
     #endif
     return Y;
}


