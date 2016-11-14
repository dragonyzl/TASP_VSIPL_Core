/* Created RJudd August 29, 1999 */
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
/* $Id: vsip_qrdsolr_f.c,v 1.1 1999/12/02 17:35:46 judd Exp $ */

#include<vsip.h>
#include<vsip_qrdattributes_f.h>
#include<VI_functions_f.h>

static void VI_vsubvmprodIP_f(
             vsip_vview_f *a,
             vsip_mview_f *B,
             vsip_vview_f *r)
{
   vsip_scalar_f temp;
   vsip_length nx = 0, mx = 0;
   vsip_scalar_f  *ap = a->block->array + a->offset * a->block->rstride,
                  *ap0 = ap,
                  *rp = r->block->array + r->offset * a->block->rstride,
                 *Byp = B->block->array + B->offset * a->block->rstride,
                 *Bxp = Byp;
   vsip_stride BCst = B->col_stride * B->block->rstride,
               BRst = B->row_stride * B->block->rstride,
               rst  = r->stride * r->block->rstride;
   while(nx++ < B->row_length){
       temp = 0;
       mx = 0;
       while(mx++ < B->col_length){
           temp += (*ap * *Byp);
           ap += a->stride; Byp += BCst;
       }
       *rp -= temp;
       ap = ap0;
       Byp = (Bxp += BRst);
       rp += rst;
   }
}

static void VI_solve_ut_f(
              vsip_mview_f *R,
              vsip_scalar_f alpha,
              vsip_mview_f *B)
{
   vsip_length N = R->row_length;
   vsip_mview_f XX = *B;
   vsip_mview_f *X = &XX;
   vsip_vview_f xx, rr;
   vsip_vview_f *x = VI_mrowview_f(X,(vsip_index) (N-1),&xx);
   vsip_vview_f *r_d = VI_mrowview_f(R,(vsip_index) 0,&rr);
   vsip_vview_f rr_m = rr;
   vsip_vview_f *r_m = &rr_m; 
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->length = 1; r_d->offset += ((N-1) * d_s);
   r_m->length = 0; r_m->offset = r_d->offset + R->row_stride;
   X->col_length = 1; X->offset = x->offset;
   if(alpha == 0) return;
   vsip_svmul_f(alpha,x,x);
   vsip_svmul_f((vsip_scalar_f) 1.0/(vsip_vget_f(r_d,0)),x,x);
   N--;
   while(N-- >0){
      r_d->offset -= d_s;
      r_m->length++; r_m->offset -= d_s;
      x->offset -= X->col_stride;
      vsip_svmul_f(alpha,x,x);
      VI_vsubvmprodIP_f(r_m,X,x);
      vsip_svmul_f((vsip_scalar_f) 1.0/(vsip_vget_f(r_d,0)),x,x);
      X->col_length++; X->offset = x->offset;
   }
   return;
}

static void VI_solve_lt_f(
              vsip_mview_f *R,
              vsip_scalar_f alpha,
              vsip_mview_f *B)
{
   vsip_length N = R->row_length;
   vsip_mview_f XX = *B;
   vsip_mview_f *X = &XX;
   vsip_vview_f xx, rr;
   vsip_vview_f *x = VI_mrowview_f(X,(vsip_index)0,&xx);
   vsip_vview_f *r_d = VI_mrowview_f(R,(vsip_index) 0,&rr);
   vsip_vview_f rr_m = rr;
   vsip_vview_f *r_m = &rr_m; 
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->length = 1; 
   r_m->length = 0;
   X->col_length = 1;
   if(alpha == 0) return;
   vsip_svmul_f(alpha,x,x);
   vsip_svmul_f((vsip_scalar_f) 1.0/(vsip_vget_f(r_d,0)),x,x);
   N--;  
   while(N-- >0){
      r_d->offset += d_s;
      r_m->length++; r_m->offset += R->col_stride; 
      x->offset += X->col_stride; 
      vsip_svmul_f(alpha,x,x);
      VI_vsubvmprodIP_f(r_m,X,x);
      vsip_svmul_f((vsip_scalar_f) 1.0/(vsip_vget_f(r_d,0)),x,x);
      X->col_length++; 
   }
   return;
}

int vsip_qrdsolr_f(
         const vsip_qr_f *qr,
         vsip_mat_op OpR,
         vsip_scalar_f alpha,
         const vsip_mview_f *XB)
{
      int retval = 0;
      vsip_mview_f RR = *(qr->A);
      vsip_mview_f *R = &RR;
      vsip_mview_f XX = *XB;
      vsip_mview_f *X = &XX;
      R->row_length = qr->N;
      R->col_length = qr->N;
      if(OpR == VSIP_MAT_NTRANS){
           VI_solve_ut_f(R,alpha,X);
      } else if(OpR == VSIP_MAT_TRANS){
           R->row_stride = qr->A->col_stride;
           R->col_stride = qr->A->row_stride;
           VI_solve_lt_f(R,alpha,X);
      } else{
           retval = 1;
      }
      return retval;
}
