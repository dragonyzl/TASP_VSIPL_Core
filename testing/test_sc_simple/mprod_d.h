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

/* $Id: mprod.t,v 1.3 2000/04/14 12:27:55 judd Exp $ */
static void mprod_d(){
   printf("********\nTEST mprod_d\n");
   {
     vsip_scalar_d datal[] = {1, 2.0, 3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_d datar[] = { .1, .2, .3, .4,    
                              1.0, 1.1, 1.2, 1.3,
                              2.1, 2.2, 2.3, 2.4,
                              -1.1, -1.2, -1.3, -1.4,
                              2.1, 2.2, 2.3, 3.4};
     vsip_scalar_d ans_data[] = { 15.9,  16.74, 17.58, 23.42,
                                     0.89,  0.79,  0.69,  0.99,
                                     5.5,   6.3,   7.1,   6.90};
     vsip_block_d *blockl = vsip_blockbind_d(datal,15,0);
     vsip_block_d *blockr = vsip_blockbind_d(datar,20,0);
     vsip_block_d *block_ans = vsip_blockbind_d(ans_data,12,0);
     vsip_block_d *block  = vsip_blockcreate_d(70,0);
     vsip_mview_d *ml = vsip_mbind_d(blockl,0,5,3,1,5);
     vsip_mview_d *mr = vsip_mbind_d(blockr,0,4,5,1,4);
     vsip_mview_d *ans = vsip_mbind_d(block_ans,0,4,3,1,4);
     vsip_mview_d *a = vsip_mbind_d(block,15,-1,3,-3,5);
     vsip_mview_d *b = vsip_mbind_d(block,50,-2,5,-10,4);
     vsip_mview_d *c = vsip_mbind_d(block,49,-8,3,-2,4);
     vsip_mview_d *chk = vsip_mcreate_d(3,4,VSIP_COL,0);
     vsip_blockadmit_d(blockl,VSIP_TRUE);
     vsip_blockadmit_d(blockr,VSIP_TRUE);
     vsip_blockadmit_d(block_ans,VSIP_TRUE);
     vsip_mcopy_d_d(ml,a);
     vsip_mcopy_d_d(mr,b);
     vsip_mprod_d(a,b,c);
     printf("vsip_mprod_d(a,b,c)\n");    
     printf("a\n"); VU_mprintm_d("6.4",a);
     printf("b\n"); VU_mprintm_d("6.4",b);
     printf("c\n"); VU_mprintm_d("6.4",c);
     printf("right answer\n"); VU_mprintm_d("6.4",ans);
     VU_msub_d(c,ans,chk); VU_mmag_d(chk,chk); VU_mclip_d(chk,.0001,.0001,0,1,chk);
     if(VU_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");
     vsip_malldestroy_d(ml);
     vsip_malldestroy_d(mr);
     vsip_mdestroy_d(a);
     vsip_mdestroy_d(b);
     vsip_malldestroy_d(c);
     vsip_malldestroy_d(ans);
     vsip_malldestroy_d(chk);
   }
   return;
}
