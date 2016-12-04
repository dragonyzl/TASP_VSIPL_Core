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
#include<VU.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define f0 2
#define fs 10000
#define Ds 3
#define L  10
#define Nl 42000
#define Ml 420

int main(){vsip_init((void*)0);
{
printf("vsip_convolve1d_f_para Test2: VSIP_SUPPORT_SAME\n");
 int nthreads;
 #pragma omp parallel
   {
     nthreads = omp_get_num_threads();
   }
   printf("Number of threads = %d\n", nthreads);
   vsip_length Yl = Nl + Ml -1;
   vsip_vview_f *h = vsip_vcreate_hanning_f(Ml,0)/*vsip_vcreate_f(1024,0)*/,
                *x = vsip_vcreate_f(Nl,0),
                *y = vsip_vcreate_f(Yl,0),
                *h2 = vsip_vcreate_hanning_f(Ml,0)/*vsip_vcreate_f(1024,0)*/,
                *x2 = vsip_vcreate_f(Nl,0),
                *y2 = vsip_vcreate_f(Yl,0);
/*   FILE *hfile = fopen("hfile.data","r");*/
/*   FILE *xfile = fopen("xfile.data","r");*/
/*   VU_vreadf_f(hfile,h); */
/*   VU_vreadf_f(xfile,x); */
   vsip_symmetry sym = VSIP_NONSYM;
 /*  vsip_length hl = Ml;
     if(hl % 2){
        sym = VSIP_SYM_EVEN_LEN_ODD;
        hl = (hl/2 + 1);
     } else {
        sym = VSIP_SYM_EVEN_LEN_EVEN;
        hl = hl/2;
     } 
   vsip_vputlength_f(h,hl);  */
/*   vsip_vputlength_f(y,37); */
   printf("M = %d;D = %d;N = %d;\n",Ml,Ds,Nl);
   vsip_vramp_f(0,2 * M_PI * f0/fs,x);
   vsip_vramp_f(0,2 * M_PI * f0/fs,x2);
   vsip_vsin_f(x,x);
   vsip_vsin_f(x2,x2);

      vsip_conv1d_f *conv2 = vsip_conv1d_create_f(h2,sym,Nl,Ds,VSIP_SUPPORT_SAME,0,0);
      { vsip_length length2 = (Nl - 1)/Ds + 1;
        vsip_vputlength_f(y2,length2);
      }
int i;
      double wall_timer_start = omp_get_wtime();
       clock_t start_t = clock();
       for(i=0;i<L;i++){
            vsip_convolve1d_f(conv2,x2,y2);
            vsip_valldestroy_f(y2);
            y2 = vsip_vcreate_f(Yl,0),
            vsip_conv1d_destroy_f(conv2);
            conv2 = vsip_conv1d_create_f(h2,sym,Nl,Ds,VSIP_SUPPORT_SAME,0,0);
       }
      double wall_timer_end = omp_get_wtime();
       clock_t end_t = clock();
       printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start); 
      vsip_conv1d_destroy_f(conv2);


/*mode2 VSIP_SUPPORT_SAME*/
      vsip_conv1d_f *conv = vsip_conv1d_create_f(h,sym,Nl,Ds,VSIP_SUPPORT_SAME,0,0);
      { vsip_length length = (Nl - 1)/Ds + 1;
        vsip_vputlength_f(y,length);
      }

       wall_timer_start = omp_get_wtime();
        start_t = clock();
 #pragma omp parallel for
       for(i=0;i<L;i++){
      vsip_convolve1d_f(conv,x,y);
      vsip_valldestroy_f(y);
      y = vsip_vcreate_f(Yl,0),
      vsip_conv1d_destroy_f(conv);
      conv = vsip_conv1d_create_f(h,sym,Nl,Ds,VSIP_SUPPORT_SAME,0,0);
       }
       wall_timer_end = omp_get_wtime();
        end_t = clock();
       printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);
       
      vsip_conv1d_destroy_f(conv);

   vsip_valldestroy_f(h); vsip_valldestroy_f(x); vsip_valldestroy_f(y);
   } vsip_finalize((void*)0); return 0;
}
