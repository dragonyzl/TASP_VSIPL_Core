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

/* $Id: svdiv.t,v 1.2 2000/04/14 12:27:55 judd Exp $ */
static void svdiv_f(){
   printf("********\nTEST svdiv_f\n");
   {
     vsip_scalar_f alpha     = 1.5;
     vsip_scalar_f data_b[] = {10.1, 11.2, 22.1, 12.2, -13.1, -0.3};
     vsip_scalar_f ans[]    = { 0.1485, 0.1339, 0.0679, 0.123, -0.1145, -5.0 };

     vsip_block_f  *block_b = vsip_blockbind_f(data_b,6,0);
     vsip_block_f  *block_c = vsip_blockcreate_f(30,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,0);

     vsip_vview_f  *b = vsip_vbind_f(block_b,0,1,6);
     vsip_vview_f  *c = vsip_vbind_f(block_c,18,-2,6);

     vsip_vview_f  *ansv = vsip_vbind_f(ans_block,0,1,6);
     vsip_vview_f  *chk = vsip_vcreate_f(6,0);

     vsip_blockadmit_f(block_b,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);

     printf("vsip_svdiv_f(alpha,b,c)\n");
     vsip_svdiv_f(alpha,b,c);
     printf("alpha = %f\n",alpha);
     printf("vector b\n");VU_vprintm_f("8.6",b);
     printf("vector c\n");VU_vprintm_f("8.6",c);
     printf("right answer\n");VU_vprintm_f("8.4",ansv);

     vsip_vsub_f(c,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nb,c in place\n");
     vsip_vcopy_f_f(b,c);
     vsip_svdiv_f(alpha,c,c);
     vsip_vsub_f(c,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_f(b);
     vsip_valldestroy_f(c);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ansv);
   }
   return;
}
