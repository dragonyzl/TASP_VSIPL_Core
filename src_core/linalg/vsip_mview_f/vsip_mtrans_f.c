/* Modified R Judd March 18, 1998 */
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
/* $Id: vsip_mtrans_f.c,v 1.2 1999/12/02 18:43:17 judd Exp judd $ */
/* April 21, 1998 1,2 to row,col */
/* vsip_mtrans_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_mtrans_f function definition.
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

extern void (vsip_mcheck_valid_f)(const char*,
  const vsip_mview_f*);
extern void (vsip_mcheck_lengths_f)(const char*,
  int, const vsip_mview_f*,
  int, const vsip_mview_f*);

void (vsip_mtrans_f)(
  const vsip_mview_f* A,
  const vsip_mview_f* R) {	/* transpose matrix	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_mcheck_valid_f("vsip_mtrans_f", A);
    vsip_mcheck_valid_f("vsip_mtrans_f", R);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_mview_f*	T = vsip_mtransview_f(A);
    vsip_mcheck_lengths_f("vsip_mtrans_f",
      1, T, 2, R);
    vsip_mdestroy_f(T);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    vsip_length  lx = A->row_length,
                 ly = A->col_length;
    vsip_scalar_f tmp;
    vsip_scalar_f *a_p = A->block->array + A->offset * A->block->rstride,
                  *r_p = R->block->array + R->offset * R->block->rstride;
    vsip_length i, j;
    int stAx = A->row_stride * A->block->rstride, stAy = A->col_stride * A->block->rstride;
    int stRx = R->row_stride * R->block->rstride, stRy = R->col_stride * R->block->rstride;
    if((lx == ly) && (a_p == r_p)){
      for(i=1; i<lx; i++){
        for(j=0; j<i; j++){ 
           tmp = *(a_p + j * stAy + i * stAx);
           *(a_p + j * stAy + i * stAx) = *(a_p + j * stAx + i * stAy);
           *(a_p + j * stAx + i * stAy) = tmp; 
        }
      }
    } else {
       for(i=0; i<ly; i++){
         r_p = R->block->array + R->offset * R->block->rstride + i * stRx;
         a_p = A->block->array + A->offset * A->block->rstride + i * stAy;
         for(j=0; j<lx; j++){
            *r_p = *a_p;
            r_p += stRy; a_p += stAx;
         }
      }
    }
  }
}

