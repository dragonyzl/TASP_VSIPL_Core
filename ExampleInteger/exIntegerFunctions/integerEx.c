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

/* Example of integer negate */
 
#include<stdio.h>
#include<vsip.h>

#define L 7                   /*length*/

int main(){vsip_init((void*)0);
{

    int i;

    vsip_vview_i *a  = vsip_vcreate_i(L,0),
                 *b  = vsip_vcreate_i(L,0);

    vsip_vramp_i(1, 1 , a);
    vsip_vramp_i(1, 2, b);
    printf("a = ramp(1,1)\n");
    for(i=0; i<L; i++)
        printf("%i ",vsip_vget_i(a,i));
    printf("\n");
    printf("b = ramp(1,2)\n");
    for(i=0; i<L; i++)
        printf("%i ",vsip_vget_i(b,i));
    printf("\n");
    vsip_vadd_i(a,b,b);
    printf("b = vadd(a,b,b)\n");
    for(i=0; i<L; i++)
        printf("%i ",vsip_vget_i(b,i));
    printf("\n");
    printf("sumval(a) = %i\n",vsip_vsumval_i(a));
    vsip_vneg_i(a, a);
    printf("a = neg(a)\n");
    for(i=0; i<L; i++)
        printf("%i ",vsip_vget_i(a,i));
    printf("\n");
    vsip_vfill_i(5,a);
    printf("a = fill(5,a)\n");
    for(i=0; i<L; i++)
        printf("%i ",vsip_vget_i(a,i));
    printf("\n");
    vsip_svadd_i(5,b,a);
    printf("svadd(5,b,a) => a =");
    for(i=0; i<L; i++)
        printf("%i ",vsip_vget_i(a,i));
    printf("\n");
    vsip_vmul_i(a,b,b);
    printf("vmul(a,b,b) => b =");
    for(i=0; i<L; i++)
        printf("%i ",vsip_vget_i(b,i));
    printf("\n");
    vsip_vsub_i(b,a,a);
    printf("vsub(b,a,a) => a =");
    for(i=0; i<L; i++)
        printf("%i ",vsip_vget_i(a,i));
    printf("\n");
    vsip_svsub_i(2,a,a);
    printf("svsub(2,a,a) => a =");
    for(i=0; i<L; i++)
        printf("%i ",vsip_vget_i(a,i));
    printf("\n");
    printf("TEST Integer Logical \n");
    { 
         vsip_vview_bl *bool = vsip_vcreate_bl(L,0);
         vsip_vramp_i((int)(L-L/2),-1,a);
         vsip_vramp_i(- (int)(L-L/2),1,b);
         printf("      a ="); for(i=0; i<L; i++) printf("%4i ",vsip_vget_i(a,i)); printf("\n");
         printf("      b ="); for(i=0; i<L; i++) printf("%4i ",vsip_vget_i(b,i)); printf("\n");
         vsip_vleq_i(a,b,bool); printf("vleq(a,b)");
           for(i=0; i<L; i++) printf("%4s ",(vsip_vget_bl(bool,i)) ? "T":"F"); printf("\n");
         vsip_vlge_i(a,b,bool); printf("vlge(a,b)");
           for(i=0; i<L; i++) printf("%4s ",(vsip_vget_bl(bool,i)) ? "T":"F"); printf("\n");
         vsip_vlgt_i(a,b,bool); printf("vlgt(a,b)");
           for(i=0; i<L; i++) printf("%4s ",(vsip_vget_bl(bool,i)) ? "T":"F"); printf("\n");
         vsip_vlle_i(a,b,bool); printf("vlle(a,b)");
           for(i=0; i<L; i++) printf("%4s ",(vsip_vget_bl(bool,i)) ? "T":"F"); printf("\n");
         vsip_vllt_i(a,b,bool); printf("vllt(a,b)");
           for(i=0; i<L; i++) printf("%4s ",(vsip_vget_bl(bool,i)) ? "T":"F"); printf("\n");
         vsip_vlne_i(a,b,bool); printf("vlne(a,b)");
           for(i=0; i<L; i++) printf("%4s ",(vsip_vget_bl(bool,i)) ? "T":"F"); printf("\n");
         vsip_valldestroy_bl(bool);
     }
     {
         printf("TEST swap\n");
         printf("a = "); for(i=0; i<L; i++) printf(" %6i ",vsip_vget_i(a,i)); printf("\n");
         printf("b = "); for(i=0; i<L; i++) printf(" %6i ",vsip_vget_i(b,i)); printf("\n");
         vsip_vswap_i(a,b); printf("swap(a,b)\n");
         printf("a = "); for(i=0; i<L; i++) printf(" %6i ",vsip_vget_i(a,i)); printf("\n");
         printf("b = "); for(i=0; i<L; i++) printf(" %6i ",vsip_vget_i(b,i)); printf("\n");
     }
     vsip_vswap_i(a,b);
     printf("TEST Bitwise Logical (printed as unsigned int)\n");
     {
         vsip_vview_i *c = vsip_vcreate_i(L,0);
         printf("      a ="); for(i=0; i<L; i++) printf(" %10u ",vsip_vget_i(a,i)); printf("\n");
         printf("      b ="); for(i=0; i<L; i++) printf(" %10u ",vsip_vget_i(b,i)); printf("\n");
         vsip_vnot_i(a,c); printf("  vnot(a)");
           for(i=0; i<L; i++) printf(" %10u ",vsip_vget_i(c,i)); printf("\n");
         vsip_vand_i(a,b,c); printf("vand(a,b)");
           for(i=0; i<L; i++) printf(" %10u ",vsip_vget_i(c,i)); printf("\n");
         vsip_vor_i(a,b,c); printf(" vor(a,b)");
           for(i=0; i<L; i++) printf(" %10u ",vsip_vget_i(c,i)); printf("\n");
         vsip_vxor_i(a,b,c); printf("vxor(a,b)");
           for(i=0; i<L; i++) printf(" %10u ",vsip_vget_i(c,i)); printf("\n");
         vsip_valldestroy_i(c);
      }
      printf("TEST Clip and Inverse Clip\n");
      {
	vsip_vview_f *wave = vsip_vcreate_f(L,0);
        vsip_vramp_f(0,(2 * M_PI)/(L-1),wave);
	vsip_vsin_f(wave,wave);
	vsip_svmul_f(10000,wave,wave);
	vsip_vcopy_f_i(wave,a);
	vsip_vclip_i(a,-500,500,10000,-10000,b);
	printf("                                 a = "); 
           for(i=0; i<L; i++) printf(" %6i ",vsip_vget_i(a,i)); printf("\n");
	printf("     clip(a,-500,500,10000,-10000) = "); 
           for(i=0; i<L; i++) printf(" %6i ",vsip_vget_i(b,i)); printf("\n");
	vsip_vinvclip_i(a,-500,0,500,10000,-10000,b);
	printf("invclip(a,-500,0,500,10000,-10000) = "); 
           for(i=0; i<L; i++) printf(" %6i ",vsip_vget_i(b,i)); printf("\n");
      }
    vsip_valldestroy_i(a);
    vsip_valldestroy_i(b);
    }vsip_finalize((void*)0);return 0;
}
