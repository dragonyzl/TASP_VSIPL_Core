/* Created by RJudd */
/* SPAWARSYSCEN D857 */
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

/* $Id: cvsqrt.t,v 1.3 2000/04/14 12:30:15 judd Exp judd $ */
static void cvsqrt_d(){
   printf("********\nTEST cvsqrt_d\n");
   {
     vsip_scalar_d data_r[] = {.1, .8, 1.3, -4.4, 5.5, 4.6, -10, 2};
     vsip_scalar_d data_i[] = {1, 1.3, 0.9, 10.2, 12.0, -4.6, 0, .5};
     vsip_scalar_d ans_r[] = { 0.7433, 1.0785, 1.2002, 1.8315, 3.0578, 2.3564, 0, 1.4251 };
     vsip_scalar_d ans_i[] = { 0.6727, 0.6027, 0.3749, 2.7847, 1.9622, -0.9761, 3.1623, 0.1754};
     vsip_cblock_d  *block = vsip_cblockbind_d(data_r,data_i,8,0);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,8,0);
     vsip_cvview_d  *a = vsip_cvbind_d(block,0,1,8);
     vsip_cvview_d  *ansv = vsip_cvbind_d(ans_block,0,1,8);
     vsip_cvview_d  *b = vsip_cvcreate_d(30,0);
     vsip_cvview_d  *chk = vsip_cvcreate_d(8,0);
     vsip_vview_d  *chk_r = vsip_vrealview_d(chk);
     vsip_cvputlength_d(b,8);
     vsip_cblockadmit_d(block,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_cvsqrt_d(a,b);
     printf("cvsqrt_d(a,b)\n vector a\n");VU_cvprintm_d("8.6",a);
     printf("vector b\n");VU_cvprintm_d("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_cvprintm_d("8.4",ansv);

     vsip_cvsub_d(b,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,b in place\n");
     vsip_cvputstride_d(b,2);vsip_cvcopy_d_d(a,b);
     vsip_cvsqrt_d(a,a);
     vsip_cvsub_d(a,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\n");
     /* check with a stride 1, b stride 2 */
     printf("vsip_cvsqrt_(a,b) with <a> stride 2, <b> stride 1\n");
     vsip_cvsqrt_d(b,a);
     vsip_cvsub_d(a,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf(" cvsqrt_d in error for in place\n");
     else {
         printf("correct\n");
     }
     vsip_cvalldestroy_d(a);
     vsip_cvalldestroy_d(b);
     vsip_vdestroy_d(chk_r);
     vsip_cvalldestroy_d(chk);
     vsip_cvalldestroy_d(ansv);
   }
   return;
}
