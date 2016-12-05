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
    printf("vsip_ccorrelate1d_f_para Test3: VSIP_SUPPORT_MIN, VSIP_UNBIASED\n");

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
   vsip_cvview_f *x = vsip_cvcreate_f(Nval,0);
   vsip_cvview_f *h = vsip_cvcreate_f(Mval,0);
   vsip_cvview_f *y = vsip_cvcreate_f(Nval+Mval-1,0); 

   vsip_cvview_f *x2 = vsip_cvcreate_f(Nval,0);
   vsip_cvview_f *h2 = vsip_cvcreate_f(Mval,0);
   vsip_cvview_f *y2 = vsip_cvcreate_f(Nval+Mval-1,0); 

   vsip_vview_f *xr = vsip_vrealview_f(x); vsip_vview_f *xi = vsip_vimagview_f(x);
   vsip_vview_f *hr = vsip_vrealview_f(h); vsip_vview_f *hi = vsip_vimagview_f(h);
   vsip_vramp_f(0,(2 * M_PI * f0)/ fs,xr);

   vsip_vview_f *xr2 = vsip_vrealview_f(x2); vsip_vview_f *xi2 = vsip_vimagview_f(x2);
   vsip_vview_f *hr2 = vsip_vrealview_f(h2); vsip_vview_f *hi2 = vsip_vimagview_f(h2);
   vsip_vramp_f(0,(2 * M_PI * f0)/ fs,xr2);

   vsip_ccorr1d_f *cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
   vsip_ccorr1d_f *cor2 = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);

   vsip_veuler_f(xr,x); /* in-place operation allowed by specification */
   vsip_vputlength_f(xr,Mval); /* Mval >= Nval , required by specification */
   vsip_vputlength_f(xi,Mval);

   vsip_veuler_f(xr2,x2); /* in-place operation allowed by specification */
   vsip_vputlength_f(xr2,Mval); /* Mval >= Nval , required by specification */
   vsip_vputlength_f(xi2,Mval);

   vsip_vadd_f(xi,xr,hr);
   vsip_vmul_f(xr,xi,hi);
   vsip_vadd_f(xi2,xr2,hr2);
   vsip_vmul_f(xr2,xi2,hi2);
   vsip_vdestroy_f(xr); vsip_vdestroy_f(xi);
   vsip_vdestroy_f(hr); vsip_vdestroy_f(hi);
   vsip_vdestroy_f(xr2); vsip_vdestroy_f(xi2);
   vsip_vdestroy_f(hr2); vsip_vdestroy_f(hi2);

mode = 4;

switch (mode)
{
case 2:
    {
        cor2 = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
        clock_t start_t = clock();
        double wall_timer_start = omp_get_wtime();
        vsip_ccorrelate1d_f(cor2,VSIP_UNBIASED,h2,x2,y2);
        double wall_timer_end = omp_get_wtime();
       clock_t end_t = clock();
        printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start); 
        vsip_ccorr1d_destroy_f(cor2);

        cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
        start_t = clock();
        wall_timer_start = omp_get_wtime();
        vsip_ccorrelate1d_f_para(cor,VSIP_UNBIASED,h,x,y);
        wall_timer_end = omp_get_wtime();
        end_t = clock();
        printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);
        vsip_corr1d_destroy_f(cor);
        break;
    }
case 4:
    {
        cor2  = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
           vsip_cvputlength_f(y2,Nval);
        clock_t start_t = clock();
        double wall_timer_start = omp_get_wtime();
        vsip_ccorrelate1d_f(cor2,VSIP_UNBIASED,h2,x2,y2);
        double wall_timer_end = omp_get_wtime();
        clock_t end_t = clock();
        printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);         
        vsip_ccorr1d_destroy_f(cor2);


        cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
           vsip_cvputlength_f(y,Nval);
        start_t = clock();
        wall_timer_start = omp_get_wtime();
        vsip_ccorrelate1d_f_para(cor,VSIP_UNBIASED,h,x,y);
        wall_timer_end = omp_get_wtime();
        end_t = clock();
        printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);
        vsip_ccorr1d_destroy_f(cor);
        break;
    }
case 6:
    {
        cor2 = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
        vsip_cvputlength_f(y2,Nval-Mval+1);
        clock_t start_t = clock();
        double wall_timer_start = omp_get_wtime();
        vsip_ccorrelate1d_f(cor2,VSIP_UNBIASED,h2,x2,y2);
        double wall_timer_end = omp_get_wtime();
        clock_t end_t = clock();
        printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);         
        vsip_ccorr1d_destroy_f(cor2);



        cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
        vsip_cvputlength_f(y,Nval-Mval+1);
        start_t = clock();
        wall_timer_start = omp_get_wtime();
        vsip_ccorrelate1d_f_para(cor,VSIP_UNBIASED,h,x,y);
        wall_timer_end = omp_get_wtime();
        end_t = clock();
        printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);
        vsip_ccorr1d_destroy_f(cor);
        break;
    } 
default:
    break;
}
   vsip_cvalldestroy_f(x);
   vsip_cvalldestroy_f(h);
   vsip_cvalldestroy_f(y);
   vsip_cvalldestroy_f(x2);
   vsip_cvalldestroy_f(h2);
   vsip_cvalldestroy_f(y2);
   } vsip_finalize((void*)0); return 0;
}
