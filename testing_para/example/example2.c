
#include <stdio.h>
#include<vsip.h>
#include <omp.h>

/*Testing vsip_gems_f_para()*/

#define M  4
#define N  5
#define L  1
#define alpha 2.0
#define beta  3.5

int main(){vsip_init((void*)0);
{
   void VU_mprint_f(vsip_mview_f*);
   void VU_mfill_f(vsip_mview_f*, vsip_scalar_f);
   vsip_mview_f *A = vsip_mcreate_f(M,N,VSIP_ROW,0),
                *C = vsip_mcreate_f(N,M,VSIP_ROW,0),
                *D = vsip_mcreate_f(N,M,VSIP_ROW,0);
   int row, col,i;
   for(row=0;row<M;row++) for(col=0;col<N;col++)
        vsip_mput_f(A,row,col,1 + sqrt(col*row));
   
   printf("\n A input \n");
   VU_mprint_f(A);
   VU_mfill_f(C,0);
   VU_mfill_f(D,0);
   printf("\n C input \n");
   VU_mprint_f(C);
   printf("alpha= %f, beta= %f,\n",alpha,beta);
   {
      vsip_mat_op OpA = VSIP_MAT_TRANS;
      /*vsip_mat_op OpA = VSIP_MAT_NTRANS;*/
     
      printf("OpA %i\n",OpA);
      for(i=0; i<L; i++){
         vsip_gems_f(alpha,A,OpA,beta,C);
         printf("before para C number %i\n",i); VU_mprint_f(C); 
      }

      for(i=0; i<L; i++){
         vsip_gems_f_para(alpha,A,OpA,beta,D);
         printf("\n\nafter para C number %i\n",i); VU_mprint_f(D); 
      }

   }
   vsip_malldestroy_f(A);
   vsip_malldestroy_f(C);
   vsip_malldestroy_f(D);
   } vsip_finalize((void*)0); return 0;
}
void VU_mprint_f(vsip_mview_f *X)
{
    vsip_length RL = vsip_mgetrowlength_f(X);
    vsip_length CL = vsip_mgetcollength_f(X);
    vsip_length row,col;
    vsip_scalar_f x;
    printf("[\n");
    for(row=0; row<CL; row++){
      for(col=0; col<RL; col++){
        x=vsip_mget_f(X,row,col);
        printf("%6.4f %s",x,((col==(RL-1)) ? ";" : " "));
      }  
      printf("\n");
    }
    printf("];\n");
    return;
}
void VU_mfill_f(vsip_mview_f *X, vsip_scalar_f a)
{
    vsip_length RL = vsip_mgetrowlength_f(X);
    vsip_length CL = vsip_mgetcollength_f(X);
    vsip_length row,col;
    for(row=0; row<CL; row++)
      for(col=0; col<RL; col++)
        vsip_mput_f(X,row,col,a);
    return;
}
     
/* expected output */
