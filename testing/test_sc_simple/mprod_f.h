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
static void mprod_f(){
   printf("********\nTEST mprod_f\n");
   {
     vsip_scalar_f datal[] = {1, 2.0, 3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_f datar[] = { .1, .2, .3, .4,    
                              1.0, 1.1, 1.2, 1.3,
                              2.1, 2.2, 2.3, 2.4,
                              -1.1, -1.2, -1.3, -1.4,
                              2.1, 2.2, 2.3, 3.4};
     vsip_scalar_f ans_data[] = { 15.9,  16.74, 17.58, 23.42,
                                     0.89,  0.79,  0.69,  0.99,
                                     5.5,   6.3,   7.1,   6.90};
     vsip_block_f *blockl = vsip_blockbind_f(datal,15,0);
     vsip_block_f *blockr = vsip_blockbind_f(datar,20,0);
     vsip_block_f *block_ans = vsip_blockbind_f(ans_data,12,0);
     vsip_block_f *block  = vsip_blockcreate_f(70,0);
     vsip_mview_f *ml = vsip_mbind_f(blockl,0,5,3,1,5);
     vsip_mview_f *mr = vsip_mbind_f(blockr,0,4,5,1,4);
     vsip_mview_f *ans = vsip_mbind_f(block_ans,0,4,3,1,4);
     vsip_mview_f *a = vsip_mbind_f(block,15,-1,3,-3,5);
     vsip_mview_f *b = vsip_mbind_f(block,50,-2,5,-10,4);
     vsip_mview_f *c = vsip_mbind_f(block,49,-8,3,-2,4);
     vsip_mview_f *chk = vsip_mcreate_f(3,4,VSIP_COL,0);
     vsip_blockadmit_f(blockl,VSIP_TRUE);
     vsip_blockadmit_f(blockr,VSIP_TRUE);
     vsip_blockadmit_f(block_ans,VSIP_TRUE);
     vsip_mcopy_f_f(ml,a);
     vsip_mcopy_f_f(mr,b);
     vsip_mprod_f(a,b,c);
     printf("vsip_mprod_f(a,b,c)\n");    
     printf("a\n"); VU_mprintm_f("6.4",a);
     printf("b\n"); VU_mprintm_f("6.4",b);
     printf("c\n"); VU_mprintm_f("6.4",c);
     printf("right answer\n"); VU_mprintm_f("6.4",ans);
     VU_msub_f(c,ans,chk); VU_mmag_f(chk,chk); VU_mclip_f(chk,.0001,.0001,0,1,chk);
     if(VU_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");
     vsip_malldestroy_f(ml);
     vsip_malldestroy_f(mr);
     vsip_mdestroy_f(a);
     vsip_mdestroy_f(b);
     vsip_malldestroy_f(c);
     vsip_malldestroy_f(ans);
     vsip_malldestroy_f(chk);
   }
   return;
}
