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

/* $Id: vclip.t,v 1.3 2000/04/14 12:27:55 judd Exp $ */
static void vclip_d(){
   printf("********\nTEST vclip_d\n");
   {
        vsip_scalar_d min_lim = -.6;
        vsip_scalar_d max_lim = .9;
        vsip_scalar_d min     = -5;
        vsip_scalar_d max     = 1;
        vsip_scalar_d data[]={0, 0.5878, 0.9511, 0.9511, 0.5878, 0.0, 
                                0.5878, -0.9511, -0.9511, -0.5878, -0.0};
        vsip_scalar_d data_ans[]={0, 0.5878, 1.0, 1.0, 0.5878, 0.0, 
                                0.5878, -5.0, -5.0, -0.5878, -0.0};
        vsip_block_d *block = vsip_blockbind_d(data,10,0);
        vsip_block_d *block_ans = vsip_blockbind_d(data_ans,10,0);
        vsip_vview_d *a = vsip_vbind_d(block,0,1,10);
        vsip_vview_d *ans = vsip_vbind_d(block_ans,0,1,10);
        vsip_vview_d *b = vsip_vcreate_d(10,0);
        vsip_vview_d *chk = vsip_vcreate_d(10,0);
        printf("vsip_vclip_d(a,min_lim,max_lim,min,max,b)\n");
        vsip_vclip_d(a,min_lim,max_lim,min,max,b);
        printf("a = "); VU_vprintm_d("8.6",a);
        printf("min_lim = %4.2f\nmax_lim = %4.2f\nmin = %4.2f\nmax = %4.2\n",
                min_lim,max_lim,min,max);
        printf("b = "); VU_vprintm_d("8.6",b);
        printf("right answer = "); VU_vprintm_d("8.6",ans);
        vsip_vsub_d(b,ans,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
        if(vsip_vsumval_d(chk) > .5)
            printf("error\n");
        else
            printf("correct\n");
        
        printf("a,b in place \n");
        vsip_vcopy_d_d(a,b);
        vsip_vclip_d(b,min_lim,max_lim,min,max,b);
        vsip_vsub_d(b,ans,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
        if(vsip_vsumval_d(chk) > .5)
            printf("error\n");
        else
            printf("correct\n");
   }
   return;
}
