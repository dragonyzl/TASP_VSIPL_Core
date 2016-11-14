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
static void cvmodulate_d(){
   printf("********\nTEST cvmodulate_d\n");
   {
      vsip_scalar_d nu = .5;
      vsip_scalar_d phi = M_PI * .25;
      vsip_scalar_d phi1 = 5 + M_PI * .25;
      vsip_scalar_d ans1_r[] ={  1.8385, 1.4778, 0.7553, -0.1521, -1.0223, 
                                  -1.6422, -1.8600, -1.6224, -0.9877, -0.1111 };
      vsip_scalar_d ans1_i[] ={0.2828, 1.1296, 1.6998, 1.8539, 1.5540, 0.8737, 
                                -0.0206, -0.9098, -1.5762, -1.8568};
      vsip_scalar_d ans2_r[] ={ 0.7927, 1.5024, 1.8443, 1.7346, 1.2002, 
                                  0.3720, -0.5473, -1.3326, -1.7917, -1.8120};
      vsip_scalar_d ans2_i[] ={  -1.6827, -1.0967, -0.2421, 0.6717, 1.4211,
                                    1.8225, 1.7778, 1.2977, 0.5000, -0.4202 };
      vsip_cblock_d *ans1_block = vsip_cblockbind_d(ans1_r,ans1_i,10,0);
      vsip_cblock_d *ans2_block = vsip_cblockbind_d(ans2_r,ans2_i,10,0);
      vsip_cvview_d *ans1 = vsip_cvbind_d(ans1_block,0,1,10);
      vsip_cvview_d *ans2 = vsip_cvbind_d(ans2_block,0,1,10);
      vsip_cvview_d *a  = vsip_cvcreate_d(20,0);
      vsip_cvview_d *a1 = vsip_cvsubview_d(a,0,10);
      vsip_cvview_d *a2 = vsip_cvsubview_d(a,10,10);
      vsip_cvview_d *r1 = vsip_cvcreate_d(10,0);
      vsip_cvview_d *r2 = vsip_cvcreate_d(10,0);
      vsip_cvview_d *chk = vsip_cvcreate_d(10,0);
      vsip_vview_d *chk_r = vsip_vrealview_d(chk);

      vsip_cblockadmit_d(ans1_block,VSIP_TRUE);
      vsip_cblockadmit_d(ans2_block,VSIP_TRUE);
      vsip_cvfill_d(vsip_cmplx_d(1.5,-1.1),a);
      printf("phi = vsip_cvmodulate_d(a1,nu,phi,r1)\n");
      printf("a1 = ");VU_cvprintm_d("8.6",a1); 
      printf("nu = %4.2f\n",nu);
      printf("input phi = %6.4f\n",phi);
      phi = vsip_cvmodulate_d(a1,nu,phi,r1);
      printf("output phi = %6.4f\n",phi);
      printf("expected output phi = %6.4f\n",phi1);
      if(fabs(phi - phi1) > .0001)
           printf("error\n");
      else
           printf("correct\n");
      printf("r1 = ");VU_cvprintm_d("8.6",r1); 
      printf("expected r1 =");VU_cvprintm_d("8.6",ans1); 
      vsip_cvsub_d(r1,ans1,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_d(chk_r) > .5)
         printf("error\n");
      else
         printf("correct\n");


      printf("vsip_cvmodulate_d(a2,nu,phi,r2)\n");
      vsip_cvmodulate_d(a2,nu,phi,r2);
      printf("a2 = ");VU_cvprintm_d("8.6",a2);
      printf("r2 = ");VU_cvprintm_d("8.6",r2);
      printf("expected r2 =");VU_cvprintm_d("8.6",ans2);
      vsip_cvsub_d(r2,ans2,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_d(chk_r) > .5)
         printf("error\n");
      else
         printf("correct\n");
     
      vsip_vdestroy_d(chk_r);
      vsip_cvalldestroy_d(chk);
      vsip_cvalldestroy_d(ans1);vsip_cvalldestroy_d(ans2);
      vsip_cvdestroy_d(a1);vsip_cvdestroy_d(a2);
      vsip_cvalldestroy_d(a);
      vsip_cvalldestroy_d(r1);vsip_cvalldestroy_d(r2);

   }
   return;
}
