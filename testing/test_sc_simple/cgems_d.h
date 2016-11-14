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

/* $Id: cgems.t,v 1.5 2000/04/14 12:27:55 judd Exp $ */
static void cgems_d(){
   printf("********\nTEST cgems_d\n");
   {
     vsip_cscalar_d alpha = vsip_cmplx_d(1.5,.25);
     vsip_cscalar_d beta  = vsip_cmplx_d(-.5,2.0);
     vsip_scalar_d data_ar[] = {1, 2.0, -3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                -4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_d data_ai[] = {.1, 2.1, -2.0,  3,  5.0,
                                3,  1.1,  1.2, -5.3,   1.4,
                                -2, 2.2, 2.2,  0.5,  1.1};
     vsip_scalar_d ans_n_data_r[] = {
   -0.025,  0.975, -5.5,    3.750,  4.75,
    5.250, -1.625, -1.5,    0.275, -1.25,
   -7.0,    2.45,   0.95,  -1.625, -3.275};
     vsip_scalar_d ans_n_data_i[] = {
    2.15,   5.4,   -2.0,    7.25, 10.50,
    7.5,    3.425,  3.6,   -6.125, 3.95,
   -2.25,   5.8,    5.55,   2.5,   3.15};
     vsip_scalar_d ans_c_data_r[] = {
   -2.7625, -7.7625,  1.7500, -9.6250, -14.6250,
   -9.3750, -5.6125, -5.8500, 11.2375, -6.3250,
    1.5000, -7.7750, -8.0250, -4.0625, -5.8875 };
     vsip_scalar_d ans_c_data_i[] = {
   -1.025, -3.40,   -7.75,   0.375,  -2.0,
    3.500, -6.5875, -6.55,  11.6375, -6.475,
  -10.875, -0.55,   -3.675, -5.25,  -10.025};
     vsip_scalar_d ans_t_data_r[] = { 
    2.475,  7.75,  -4.5,
    3.475,  0.875,  4.950,
   -3.000,  1.000,  3.450,
    6.250,  2.775,  0.875,
    7.250,  1.250, -0.775};
     vsip_scalar_d ans_t_data_i[] = { 
    4.90,  10.250,  0.50,
    8.15,   6.175,  8.55,
    0.75,   6.350,  8.30,
   10.00,  -3.375,  5.25,
   13.25,   6.700,  5.90};
     vsip_cblock_d *block_a = vsip_cblockbind_d(data_ar,data_ai,15,0);
     vsip_cblock_d *block_ans_n = vsip_cblockbind_d(ans_n_data_r,ans_n_data_i,15,0);
     vsip_cblock_d *block_ans_c = vsip_cblockbind_d(ans_c_data_r,ans_c_data_i,15,0);
     vsip_cblock_d *block_ans_t = vsip_cblockbind_d(ans_t_data_r,ans_t_data_i,15,0);
     vsip_cblock_d *block  = vsip_cblockcreate_d(400,0);
     vsip_cmview_d *au = vsip_cmbind_d(block_a,0,5,3,1,5);
     vsip_cmview_d *ans_n = vsip_cmbind_d(block_ans_n,0,5,3,1,5);
     vsip_cmview_d *ans_c = vsip_cmbind_d(block_ans_c,0,5,3,1,5);
     vsip_cmview_d *ans_t = vsip_cmbind_d(block_ans_t,0,3,5,1,3);
     vsip_cmview_d *a = vsip_cmbind_d(block,15,-1,3,-3,5);
     vsip_cmview_d *cn = vsip_cmbind_d(block,200,-10,3,-2,5);
     vsip_cmview_d *ct = vsip_cmbind_d(block,300,2,5,15,3);
     vsip_cmview_d *chk_n = vsip_cmcreate_d(3,5,VSIP_COL,0);
     vsip_cmview_d *chk_t = vsip_cmcreate_d(5,3,VSIP_ROW,0);
     vsip_mview_d *chk_n_r = vsip_mrealview_d(chk_n);
     vsip_mview_d *chk_t_r = vsip_mrealview_d(chk_t);
     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_cblockadmit_d(block_ans_n,VSIP_TRUE);
     vsip_cblockadmit_d(block_ans_c,VSIP_TRUE);
     vsip_cblockadmit_d(block_ans_t,VSIP_TRUE);
     vsip_cmcopy_d_d(au,a);
     VU_cmfill_d(vsip_cmplx_d(1.0,.5),cn);
     VU_cmfill_d(vsip_cmplx_d(2.0,-1),ct);

     /* test n */
     printf("\nvsip_cgems_d(alpha,a,VSIP_MAT_NTRANS,beta,c)\n");
     printf("alpha = (%f %+fi)\n",vsip_real_d(alpha),vsip_imag_d(alpha));
     printf("matrix a = ");VU_cmprintm_d("6.4",a);
     printf("beta = (%f %+fi)\n",vsip_real_d(beta),vsip_imag_d(beta));
     printf("on input matrix c = ");VU_cmprintm_d("6.4",cn);
     vsip_cgems_d(alpha,a,VSIP_MAT_NTRANS,beta,cn);
     printf("on output matrix c = ");VU_cmprintm_d("6.4",cn);
     printf("right answer = ");VU_cmprintm_d("6.4",ans_n);
     VU_cmsub_d(cn,ans_n,chk_n); VU_cmmag_d(chk_n,chk_n_r); VU_mclip_d(chk_n_r,.0001,.0001,0,1,chk_n_r);
     if(VU_msumval_d(chk_n_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     /* test c */
     printf("\nvsip_cgems_d(alpha,a,VSIP_MAT_CONJ,beta,c)\n");
     printf("alpha = (%f %+fi)\n",vsip_real_d(alpha),vsip_imag_d(alpha));
     printf("matrix a = ");VU_cmprintm_d("6.4",a);
     printf("beta = (%f %+fi)\n",vsip_real_d(beta),vsip_imag_d(beta));
     printf("on input matrix c = ");VU_cmprintm_d("6.4",cn);
     vsip_cgems_d(alpha,a,VSIP_MAT_CONJ,beta,cn);
     printf("on output matrix c = ");VU_cmprintm_d("6.4",cn);
     printf("right answer = ");VU_cmprintm_d("6.4",ans_c);
     VU_cmsub_d(cn,ans_c,chk_n); VU_cmmag_d(chk_n,chk_n_r); VU_mclip_d(chk_n_r,.0001,.0001,0,1,chk_n_r);
     if(VU_msumval_d(chk_n_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     /* test t */
     printf("\nvsip_cgems_d(alpha,a,VSIP_MAT_TRANS,beta,c)\n");
     printf("alpha = (%f %+fi)\n",vsip_real_d(alpha),vsip_imag_d(alpha));
     printf("matrix a = ");VU_cmprintm_d("6.4",a);
     printf("beta = (%f %+fi)\n",vsip_real_d(beta),vsip_imag_d(beta));
     printf("on input matrix c = ");VU_cmprintm_d("6.4",ct);
     vsip_cgems_d(alpha,a,VSIP_MAT_TRANS,beta,ct);
     printf("on output matrix c = ");VU_cmprintm_d("6.4",ct);
     printf("right answer = ");VU_cmprintm_d("6.4",ans_t);
     VU_cmsub_d(ct,ans_t,chk_t); VU_cmmag_d(chk_t,chk_t_r); VU_mclip_d(chk_t_r,.0001,.0001,0,1,chk_t_r);
     if(VU_msumval_d(chk_t_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_cmalldestroy_d(au);

     vsip_cmdestroy_d(a); vsip_cmdestroy_d(cn);
     vsip_cmalldestroy_d(ct);

     vsip_cmalldestroy_d(ans_t); 
     vsip_cmalldestroy_d(ans_n);
     vsip_cmalldestroy_d(ans_c);

     vsip_mdestroy_d(chk_t_r); vsip_mdestroy_d(chk_n_r);
     vsip_cmalldestroy_d(chk_t); vsip_cmalldestroy_d(chk_n);
   }
   return;
}
