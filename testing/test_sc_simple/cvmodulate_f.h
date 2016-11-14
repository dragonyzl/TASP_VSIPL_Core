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

/* $Id: cvmodulate.t,v 1.3 2000/04/14 12:27:55 judd Exp $ */
static void cvmodulate_f(){
   printf("********\nTEST cvmodulate_f\n");
   {
      vsip_scalar_f nu = .5;
      vsip_scalar_f phi = M_PI * .25;
      vsip_scalar_f phi1 = 5 + M_PI * .25;
      vsip_scalar_f ans1_r[] ={  1.8385, 1.4778, 0.7553, -0.1521, -1.0223, 
                                  -1.6422, -1.8600, -1.6224, -0.9877, -0.1111 };
      vsip_scalar_f ans1_i[] ={0.2828, 1.1296, 1.6998, 1.8539, 1.5540, 0.8737, 
                                -0.0206, -0.9098, -1.5762, -1.8568};
      vsip_scalar_f ans2_r[] ={ 0.7927, 1.5024, 1.8443, 1.7346, 1.2002, 
                                  0.3720, -0.5473, -1.3326, -1.7917, -1.8120};
      vsip_scalar_f ans2_i[] ={  -1.6827, -1.0967, -0.2421, 0.6717, 1.4211,
                                    1.8225, 1.7778, 1.2977, 0.5000, -0.4202 };
      vsip_cblock_f *ans1_block = vsip_cblockbind_f(ans1_r,ans1_i,10,0);
      vsip_cblock_f *ans2_block = vsip_cblockbind_f(ans2_r,ans2_i,10,0);
      vsip_cvview_f *ans1 = vsip_cvbind_f(ans1_block,0,1,10);
      vsip_cvview_f *ans2 = vsip_cvbind_f(ans2_block,0,1,10);
      vsip_cvview_f *a  = vsip_cvcreate_f(20,0);
      vsip_cvview_f *a1 = vsip_cvsubview_f(a,0,10);
      vsip_cvview_f *a2 = vsip_cvsubview_f(a,10,10);
      vsip_cvview_f *r1 = vsip_cvcreate_f(10,0);
      vsip_cvview_f *r2 = vsip_cvcreate_f(10,0);
      vsip_cvview_f *chk = vsip_cvcreate_f(10,0);
      vsip_vview_f *chk_r = vsip_vrealview_f(chk);

      vsip_cblockadmit_f(ans1_block,VSIP_TRUE);
      vsip_cblockadmit_f(ans2_block,VSIP_TRUE);
      vsip_cvfill_f(vsip_cmplx_f(1.5,-1.1),a);
      printf("phi = vsip_cvmodulate_f(a1,nu,phi,r1)\n");
      printf("a1 = ");VU_cvprintm_f("8.6",a1); 
      printf("nu = %4.2f\n",nu);
      printf("input phi = %6.4f\n",phi);
      phi = vsip_cvmodulate_f(a1,nu,phi,r1);
      printf("output phi = %6.4f\n",phi);
      printf("expected output phi = %6.4f\n",phi1);
      if(fabs(phi - phi1) > .0001)
           printf("error\n");
      else
           printf("correct\n");
      printf("r1 = ");VU_cvprintm_f("8.6",r1); 
      printf("expected r1 =");VU_cvprintm_f("8.6",ans1); 
      vsip_cvsub_f(r1,ans1,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_f(chk_r) > .5)
         printf("error\n");
      else
         printf("correct\n");


      printf("vsip_cvmodulate_f(a2,nu,phi,r2)\n");
      vsip_cvmodulate_f(a2,nu,phi,r2);
      printf("a2 = ");VU_cvprintm_f("8.6",a2);
      printf("r2 = ");VU_cvprintm_f("8.6",r2);
      printf("expected r2 =");VU_cvprintm_f("8.6",ans2);
      vsip_cvsub_f(r2,ans2,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_f(chk_r) > .5)
         printf("error\n");
      else
         printf("correct\n");
     
      vsip_vdestroy_f(chk_r);
      vsip_cvalldestroy_f(chk);
      vsip_cvalldestroy_f(ans1);vsip_cvalldestroy_f(ans2);
      vsip_cvdestroy_f(a1);vsip_cvdestroy_f(a2);
      vsip_cvalldestroy_f(a);
      vsip_cvalldestroy_f(r1);vsip_cvalldestroy_f(r2);

   }
   return;
}
