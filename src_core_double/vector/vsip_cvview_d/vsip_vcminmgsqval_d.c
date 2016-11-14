/* Modified RJudd January 4, 1998 */
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
/* $Id: vsip_vcminmgsqval_d.c,v 1.1 1999/12/05 01:46:30 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified RJudd January 3, 1999 */
/* To incorporate rstride */
/* vsip_vcminmgsqval_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vcminmgsqval_d function definition.
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
#include<vsip_cvviewattributes_d.h>

extern void (vsip_cvcheck_valid_d)(const char*,
  const vsip_cvview_d*);

vsip_scalar_d (vsip_vcminmgsqval_d)(
   const vsip_cvview_d* a, 
   vsip_index *j) {
	/* j such that |a_j|^2 = min{|a_0|^2, |a_1|^2, ..., |a_n-1|^2}	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_d("vsip_vcminmgsqval_d", a);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
      /* register */ vsip_length n  = a->length, n0 ;
      vsip_stride cast = a->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset);
      vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset);
      vsip_scalar_d  r     = 0, magsq = 0;
      /* register */ vsip_stride ast = (cast * a->stride);
      n0 = n - 1;
      r = *apr * *apr + *api * *api;
      if(j != NULL) *j = (vsip_index) 0;
      while(n-- > 0){
         magsq = *apr * *apr + *api * *api;
         if(r > magsq){
               r = magsq;
               if(j != NULL) *j = (vsip_index) ( n0 - n);
          }
          apr += ast; api += ast;
      }
      return r;
  }
}

