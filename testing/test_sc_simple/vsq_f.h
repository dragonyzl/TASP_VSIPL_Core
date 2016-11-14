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

/* $Id: vsq.t,v 1.3 2000/04/14 12:27:55 judd Exp $ */
static void vsq_f(){
   printf("********\nTEST vsq_f\n");
   {
     vsip_scalar_f data[] = {.1, .8, 1.3, 4.4, 5.5, 4.6, 10, 5};
     vsip_scalar_f ans[] = { 0.01, 0.64, 1.69, 19.36, 30.25, 21.16, 100.0, 25.0 };
     vsip_block_f  *block = vsip_blockbind_f(data,8,0);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,8,0);
     vsip_vview_f  *a = vsip_vbind_f(block,0,1,8);
     vsip_vview_f  *ansv = vsip_vbind_f(ans_block,0,1,8);
     vsip_vview_f  *b = vsip_vcreate_f(30,0);
     vsip_vview_f  *chk = vsip_vcreate_f(8,0);
     vsip_vputlength_f(b,8);
     vsip_blockadmit_f(block,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_vsq_f(a,b);
     printf("vsq_f(a,b)\n vector a\n");VU_vprintm_f("8.6",a);
     printf("vector b\n");VU_vprintm_f("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_vprintm_f("8.4",ansv);

     vsip_vsub_f(b,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,b in place\n");
     vsip_vputstride_f(b,2);vsip_vcopy_f_f(a,b);
     vsip_vsq_f(a,a);
     vsip_vsub_f(a,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\n");
     /* check with a stride 1, b stride 2 */
     printf("vsip_vsq_(a,b) with <a> stride 2, <b> stride 1\n");
     vsip_vsq_f(b,a);
     vsip_vsub_f(a,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf(" vsq_f in error for in place\n");
     else {
         printf("correct\n");
     }
     vsip_valldestroy_f(a);
     vsip_valldestroy_f(b);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ansv);
   }
   return;
}
