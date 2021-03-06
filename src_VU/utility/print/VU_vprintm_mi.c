/* Produced By Randall Judd */
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
/* $Id$ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
void VU_vprintm_mi(char s[],
    vsip_vview_mi *X)
{
    char format[50];
    vsip_length L = vsip_vgetlength_mi(X);
    vsip_index vi;
    vsip_scalar_mi x;
    strcpy(format,"(%");
    strcat(format,s);
    strcat(format,"ld %");
    strcat(format,s);
    strcat(format,"ld) %s\n");
    printf("[\n");	
    for(vi=0; vi<L; vi++){
      x=vsip_vget_mi(X,vi);
      printf(format,vsip_rowindex(x),
                    vsip_colindex(x),";");
    }  
    printf("];\n");
    return;
}

