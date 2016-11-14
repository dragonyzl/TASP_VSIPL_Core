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
static void cvsqrt_f(){
   printf("********\nTEST cvsqrt_f\n");
   {
     vsip_scalar_f data_r[] = {.1, .8, 1.3, -4.4, 5.5, 4.6, -10, 2};
     vsip_scalar_f data_i[] = {1, 1.3, 0.9, 10.2, 12.0, -4.6, 0, .5};
     vsip_scalar_f ans_r[] = { 0.7433, 1.0785, 1.2002, 1.8315, 3.0578, 2.3564, 0, 1.4251 };
     vsip_scalar_f ans_i[] = { 0.6727, 0.6027, 0.3749, 2.7847, 1.9622, -0.9761, 3.1623, 0.1754};
     vsip_cblock_f  *block = vsip_cblockbind_f(data_r,data_i,8,0);
     vsip_cblock_f  *ans_block = vsip_cblockbind_f(ans_r,ans_i,8,0);
     vsip_cvview_f  *a = vsip_cvbind_f(block,0,1,8);
     vsip_cvview_f  *ansv = vsip_cvbind_f(ans_block,0,1,8);
     vsip_cvview_f  *b = vsip_cvcreate_f(30,0);
     vsip_cvview_f  *chk = vsip_cvcreate_f(8,0);
     vsip_vview_f  *chk_r = vsip_vrealview_f(chk);
     vsip_cvputlength_f(b,8);
     vsip_cblockadmit_f(block,VSIP_TRUE);
     vsip_cblockadmit_f(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_cvsqrt_f(a,b);
     printf("cvsqrt_f(a,b)\n vector a\n");VU_cvprintm_f("8.6",a);
     printf("vector b\n");VU_cvprintm_f("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_cvprintm_f("8.4",ansv);

     vsip_cvsub_f(b,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,b in place\n");
     vsip_cvputstride_f(b,2);vsip_cvcopy_f_f(a,b);
     vsip_cvsqrt_f(a,a);
     vsip_cvsub_f(a,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\n");
     /* check with a stride 1, b stride 2 */
     printf("vsip_cvsqrt_(a,b) with <a> stride 2, <b> stride 1\n");
     vsip_cvsqrt_f(b,a);
     vsip_cvsub_f(a,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf(" cvsqrt_f in error for in place\n");
     else {
         printf("correct\n");
     }
     vsip_cvalldestroy_f(a);
     vsip_cvalldestroy_f(b);
     vsip_vdestroy_f(chk_r);
     vsip_cvalldestroy_f(chk);
     vsip_cvalldestroy_f(ansv);
   }
   return;
}
