/* Created by RJudd */
/* SPAWARSYSCEN D881 */
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

#include <stdio.h>
#include<vsip.h>

#define M  3
#define N  4
#define P  5

int main(){vsip_init((void*)0);
{
   vsip_cmview_d *A = vsip_cmcreate_d(M,P,VSIP_ROW,0),
                 *B = vsip_cmcreate_d(P,N,VSIP_ROW,0),
                 *R = vsip_cmcreate_d(M,N,VSIP_ROW,0);
   int i, j;
   for(i=0;i<M;i++) for(j=0;j<P;j++)
        vsip_cmput_d(A,i,j,vsip_cmplx_d(i,1 + sqrt(i*j)));
   
   for(i=0;i<P;i++) for(j=0;j<N;j++)
        vsip_cmput_d(B,i,j,vsip_cmplx_d(1 , i * j));
   
   printf("\n A input \n");
   vsip_cmprodj_d(A,B,R);
   {for(i=0;i<M;i++) {for(j=0;j<P;j++){
           printf("%5.2f + %5.2fi%s ",
             vsip_real_d(vsip_cmget_d(A,i,j)),
             vsip_imag_d(vsip_cmget_d(A,i,j)),
             (j == P-1) ? ";":",");
           }
       printf("\n");
       }
   }
   printf("\n B input \n");
   {for(i=0;i<P;i++) {for(j=0;j<N;j++){
           printf("%5.2f + %5.2fi%s ",
             vsip_real_d(vsip_cmget_d(B,i,j)),
             vsip_imag_d(vsip_cmget_d(B,i,j)),
             (j == N-1) ? ";":",");
           }
       printf("\n");
       }
   }
   printf("\n R output = A * conj(B)\n");
   {for(i=0;i<M;i++) {for(j=0;j<N;j++){
           printf("%5.2f + %5.2fi%s ",
             vsip_real_d(vsip_cmget_d(R,i,j)),
             vsip_imag_d(vsip_cmget_d(R,i,j)),
             (j == N-1) ? ";":",");
           }
       printf("\n");
       }
   }
   vsip_cmalldestroy_d(A);
   vsip_cmalldestroy_d(B);
   vsip_cmalldestroy_d(R);
   }vsip_finalize((void*)0);return 0;
}
