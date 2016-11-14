/* Created RJudd February 16, 1999 */
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
/* $Id: vsip_vmmul_d.c,v 1.1 1999/12/05 01:43:24 judd Exp judd $ */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<VI_functions_d.h>

void (vsip_vmmul_d)(
  const vsip_vview_d *a,
  const vsip_mview_d *B,
  vsip_major major,
  const vsip_mview_d *R) {
  vsip_vview_d bb,*b,rr,*r;
  vsip_stride sb,sr;
  vsip_length L;
  if(major == VSIP_ROW){
     sb = B->col_stride;
     sr = R->col_stride;
     L  = B->col_length;
     b = VI_mrowview_d(B,0,&bb);
     r = VI_mrowview_d(R,0,&rr);
  } else {
     sb = B->row_stride; 
     sr = R->row_stride; 
     L  = B->row_length;;
     b = VI_mcolview_d(B,0,&bb); 
     r = VI_mcolview_d(R,0,&rr);
  }
  while(L-- >0){
     { 
         /*define variables*/
         /* register */ vsip_length n = r->length;
         /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                    bst = b->stride * b->block->rstride,
                                    rst = r->stride * r->block->rstride;
         vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                       *bp = (b->block->array) + b->offset * b->block->rstride,
                       *rp = (r->block->array) + r->offset * r->block->rstride;
         /*end define*/
         ap -= ast; bp -= bst; rp -= rst;
         while(n-- > 0)
              *(rp+=rst) = *(ap+=ast) * *(bp+=bst);
      }
      b->offset += sb;
      r->offset += sr;
   }
   return;
}
