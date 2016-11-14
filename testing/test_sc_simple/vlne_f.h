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

/* $Id: vlne.t,v 1.2 2000/04/14 12:27:55 judd Exp $ */
static void vlne_f(){
   printf("********\nTEST vlne_f\n");
   {
      vsip_scalar_f data1[] = { 0.0, 1.2, 3.0, 4.2, 3.3, -2.2, 5.2};
      vsip_scalar_f data2[] = { 1.0, 1.2, 2.0, 4.2, 2.3, -2.2, 3.2};
      vsip_scalar_f ans_data[]   = { 1.0, 0.0, 1.0, 0.0, 1.0,  0.0, 1.0};
      vsip_block_f  *block_a = vsip_blockbind_f(data1,7,0);
      vsip_block_f  *block_b = vsip_blockbind_f(data2,7,0);
      vsip_block_f  *block_ans = vsip_blockbind_f(ans_data,7,0);
      vsip_vview_f *a = vsip_vbind_f(block_a,0,1,7);
      vsip_vview_f *b = vsip_vbind_f(block_b,0,1,7);
      vsip_vview_f *ans = vsip_vbind_f(block_ans,0,1,7);
      vsip_vview_bl *c = vsip_vcreate_bl(7,0);
      vsip_vview_f  *d = vsip_vcreate_f(7,0);
      vsip_vview_f  *chk = vsip_vcreate_f(7,0);
      vsip_blockadmit_f(block_a,VSIP_TRUE);
      vsip_blockadmit_f(block_b,VSIP_TRUE);
      vsip_blockadmit_f(block_ans,VSIP_TRUE);
      
      vsip_vlne_f(a,b,c);
      vsip_vcopy_bl_f(c,d);
      printf("vsip_vlne_f(a,b,c)");
      printf("vector a\n");VU_vprintm_f("8.6",a);
      printf("vector b\n");VU_vprintm_f("8.6",b);
      printf("vector c\n");VU_vprintm_f("1.0",d);
      printf("right answer\n");VU_vprintm_f("1.0",ans);

      vsip_vsub_f(d,ans,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
      if(vsip_vsumval_f(chk) > .5)
         printf("error\n");
      else
         printf("correct\n");

   }
   return;
}