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
   vsip_mview_d *A = vsip_mcreate_d(M,P,VSIP_ROW,0),
                *B = vsip_mcreate_d(P,N,VSIP_ROW,0),
                *R = vsip_mcreate_d(M,N,VSIP_ROW,0);
   int i, j;
   for(i=0;i<M;i++) for(j=0;j<P;j++)
        vsip_mput_d(A,i,j,1 + sqrt(i*j));
   
   for(i=0;i<P;i++) for(j=0;j<N;j++)
        vsip_mput_d(B,i,j,1 + i * j);
   
   printf("\n A input \n");
   vsip_mprod_d(A,B,R);
   {for(i=0;i<M;i++) {for(j=0;j<P;j++){
           printf(": %6.2f  ",vsip_mget_d(A,i,j));
           }
       printf(":\n");
       }
   }
   printf("\n B input \n");
   {for(i=0;i<P;i++) {for(j=0;j<N;j++){
           printf(": %6.2f  ",vsip_mget_d(B,i,j));
           }
       printf(":\n");
       }
   }
   printf("\n R output \n");
   {for(i=0;i<M;i++) {for(j=0;j<N;j++){
           printf(": %6.2f  ",vsip_mget_d(R,i,j));
           }
       printf(":\n");
       }
   }
   vsip_malldestroy_d(A);
   vsip_malldestroy_d(B);
   vsip_malldestroy_d(R);
   }vsip_finalize((void*)0);return 0;
}
