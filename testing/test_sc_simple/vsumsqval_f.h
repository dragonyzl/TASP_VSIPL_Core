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

/* $Id: vsumsqval.t,v 1.2 2000/04/14 12:27:55 judd Exp $ */
static void vsumsqval_f(){
   printf("********\nTEST vsumsqval_f\n");
   {
     vsip_scalar_f data[] = {-1,  1, 0,  2, -2 };
     vsip_scalar_f ans = 10.0;
     vsip_scalar_f val=0;
     vsip_block_f  *block = vsip_blockbind_f(data,5,0);
     vsip_vview_f  *a = vsip_vbind_f(block,0,1,5);
     vsip_blockadmit_f(block,VSIP_TRUE);
     val = vsip_vsumsqval_f(a);
     printf("val = vsip_vsumsqval_f(a)\n vector a\n");VU_vprintm_f("8.6",a);
     printf("val = %f\n",val);
     printf("right answer %f\n",ans);
     if(val == ans)
          printf("correct\n");
     else
          printf("error\n");
     vsip_valldestroy_f(a);
   }
   return;
}
