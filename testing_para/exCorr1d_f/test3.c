/* Created RJudd March 17, 1999 */
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

/* to do a feel good test on correlate function */

#include<vsip.h>
#include<VU.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define f0 25
#define fs 128

int main(int argc, char *argv[]){vsip_init((void*)0);
{
    printf("vsip_correlate1d_f_para Test3: VSIP_SUPPORT_MIN, VSIP_UNBIASED\n");

      vsip_length Mval,Nval;

if(argc < 2){
      printf("usage\nqrdex Nval Mval\n");
      printf("defaule Nval75000000 Mval50000000\n");
      Nval = 75000000;
      Mval = 50000000;
   }
 else {
                  Nval    = (vsip_length)atoi(argv[1]);
                  Mval    = (vsip_length)atoi(argv[2]);
 }



 int nthreads;
 #pragma omp parallel
   {
     nthreads = omp_get_num_threads();
   }
printf("Number of threads = %d\n", nthreads);
printf("N = %d, M = %d\n", Nval, Mval);
    int mode;
   vsip_vview_f *x = vsip_vcreate_f(Nval,0);
/*   vsip_vview_f *h = vsip_vcreate_hanning_f(Mval,0); */
   vsip_vview_f *h = vsip_vcreate_f(Mval,0);
   vsip_vview_f *y = vsip_vcreate_f(Nval+Mval-1,0); 

   vsip_vview_f *x2 = vsip_vcreate_f(Nval,0);
/*   vsip_vview_f *h = vsip_vcreate_hanning_f(Mval,0); */
   vsip_vview_f *h2 = vsip_vcreate_f(Mval,0);
   vsip_vview_f *y2 = vsip_vcreate_f(Nval+Mval-1,0); 

   vsip_corr1d_f *cor = vsip_corr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
   vsip_corr1d_f *cor2 = vsip_corr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);

   vsip_vramp_f(0,(2 * M_PI * f0)/ fs,x);
   vsip_vramp_f(0,(2 * M_PI * f0)/ fs,x2);
   vsip_vputlength_f(x,Mval);
   vsip_vputlength_f(x2,Mval);
   vsip_vsin_f(x,h);
   vsip_vsin_f(x2,h2);
   vsip_vputlength_f(x,Nval);
   vsip_vputlength_f(x2,Nval);
   vsip_vsin_f(x,x);
   vsip_vsin_f(x2,x2);

mode = 6;

switch (mode)
{
case 2:
    {
        cor2 = vsip_corr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
        clock_t start_t = clock();
        double wall_timer_start = omp_get_wtime();
        vsip_correlate1d_f(cor2,VSIP_UNBIASED,h2,x2,y2);
        double wall_timer_end = omp_get_wtime();
       clock_t end_t = clock();
        printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start); 
        vsip_corr1d_destroy_f(cor2);

        cor = vsip_corr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
        start_t = clock();
        wall_timer_start = omp_get_wtime();
        vsip_correlate1d_f_para(cor,VSIP_UNBIASED,h,x,y);
        wall_timer_end = omp_get_wtime();
        end_t = clock();
        printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);
        vsip_corr1d_destroy_f(cor);
        break;
    }
case 4:
    {
        cor2 = vsip_corr1d_create_f(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
        vsip_vputlength_f(y2,Nval);
        clock_t start_t = clock();
        double wall_timer_start = omp_get_wtime();
        vsip_correlate1d_f(cor2,VSIP_UNBIASED,h2,x2,y2);
        double wall_timer_end = omp_get_wtime();
        clock_t end_t = clock();
        printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);         
        vsip_corr1d_destroy_f(cor2);


        cor = vsip_corr1d_create_f(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
        vsip_vputlength_f(y,Nval);
        start_t = clock();
        wall_timer_start = omp_get_wtime();
        vsip_correlate1d_f_para(cor,VSIP_UNBIASED,h,x,y);
        wall_timer_end = omp_get_wtime();
        end_t = clock();
        printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);
        vsip_corr1d_destroy_f(cor);
        break;
    }
case 6:
    {
        cor2 = vsip_corr1d_create_f(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
        vsip_vputlength_f(y2,Nval-Mval+1);
        clock_t start_t = clock();
        double wall_timer_start = omp_get_wtime();
        vsip_correlate1d_f(cor2,VSIP_UNBIASED,h2,x2,y2);
        double wall_timer_end = omp_get_wtime();
        clock_t end_t = clock();
        printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);         
        vsip_corr1d_destroy_f(cor2);



        cor = vsip_corr1d_create_f(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
        vsip_vputlength_f(y,Nval-Mval+1);
        start_t = clock();
        wall_timer_start = omp_get_wtime();
        vsip_correlate1d_f_para(cor,VSIP_UNBIASED,h,x,y);
        wall_timer_end = omp_get_wtime();
        end_t = clock();
        printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);
        vsip_corr1d_destroy_f(cor);
        break;
    } 
default:
    break;
}
   vsip_valldestroy_f(x);
   vsip_valldestroy_f(h);
   vsip_valldestroy_f(y);
   } vsip_finalize((void*)0); return 0;
}
