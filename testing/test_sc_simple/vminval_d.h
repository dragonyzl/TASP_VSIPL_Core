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


/* $Id: vminval.t,v 1.2 2000/04/14 12:27:55 judd Exp $ */
static void vminval_d(){
   printf("********\nTEST vminval_d\n");
   {
     vsip_scalar_d data_a[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d ans = -3.3;
     vsip_scalar_d val = 0;
     vsip_index  ans_ind = 5; 
     vsip_index  ind = 9999;
     vsip_block_d  *block_a = vsip_blockbind_d(data_a,6,0);
     vsip_vview_d  *a = vsip_vbind_d(block_a,0,1,6);
     vsip_blockadmit_d(block_a,VSIP_TRUE);
     val = vsip_vminval_d(a,&ind);
     printf("vector |a>\n"),VU_vprintm_d("6.4",a);
     printf("val = vsip_vminval_d(a,&ind)\n");
     printf("val = %f\nexpected answer %f\n",val,ans);
     printf("ind = %u\nexpected index %u\n",ind,ans_ind);

     if(fabs(val - ans) < .0001)
        printf("val correct\n");
     else
        printf("val in error\n");

     if(ind == ans_ind)
        printf("index correct\n");
     else
        printf("index in error\n");

     vsip_valldestroy_d(a);
   }
   return;
}
