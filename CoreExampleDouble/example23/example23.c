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
/* $Id$ */

#include<vsip.h>

void VU_mprintm_d(char format[],vsip_mview_d *X)
{ vsip_length RL = vsip_mgetrowlength_d(X),
              CL = vsip_mgetcollength_d(X),
              row,col;
  vsip_scalar_d x;
  printf("[\n");
  for(row=0; row<CL; row++){
    for(col=0; col<RL; col++){
      x=vsip_mget_d(X,row,col);
      printf(format,x,((col==(RL-1)) ? ";" : " "));
    } printf("\n");
  }printf("];\n");
  return;
}

/* A simple QRD example */
int main(){vsip_init((void*)0);
{
   vsip_mview_d *A =
        vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE),
        *B = vsip_mcreate_d(3,2,VSIP_COL,VSIP_MEM_NONE);
   vsip_qr_d *qrd = vsip_qrd_create_d(3,3,VSIP_QRD_SAVEQ1);
   vsip_mput_d(A,0,0,1);vsip_mput_d(A,0,1,2);
   vsip_mput_d(A,0,2,3);
   vsip_mput_d(A,1,0,-1);vsip_mput_d(A,1,1,1);
   vsip_mput_d(A,1,2,-2);
   vsip_mput_d(A,2,0,1);vsip_mput_d(A,2,1,1);
   vsip_mput_d(A,2,2,-3);
   vsip_mput_d(B,0,0,1); vsip_mput_d(B,0,1,1);
   vsip_mput_d(B,1,0,-1); vsip_mput_d(B,1,1,1);
   vsip_mput_d(B,2,0,-2); vsip_mput_d(B,2,1,3);
   printf("A = "); VU_mprintm_d("%4.2f ",A);
   printf("B = "); VU_mprintm_d("%4.2f ",B);
   if(0 != vsip_qrd_d(qrd,A)) {vsip_finalize((void*)0);return 1;}
   vsip_qrsol_d(qrd,VSIP_LLS,B);
   printf("X = "); VU_mprintm_d("%6.3f",B);
   vsip_malldestroy_d(A); vsip_malldestroy_d(B);
   vsip_qrd_destroy_d(qrd);
   }vsip_finalize((void*)0);return 0;
}
