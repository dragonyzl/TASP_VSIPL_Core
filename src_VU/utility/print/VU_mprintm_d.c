/* Produced By Randall Judd */
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
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
void VU_mprintm_d(char s[],
    vsip_mview_d *X)
{
    char format[50];
    vsip_length RL = vsip_mgetrowlength_d(X);
    vsip_length CL = vsip_mgetcollength_d(X);
    vsip_length row,col;
    vsip_scalar_d x;
    strcpy(format,"%");
    strcat(format,s);
    strcat(format,"lf %s");
    printf("[\n");	
    for(row=0; row<CL; row++){
      for(col=0; col<RL; col++){
        x=vsip_mget_d(X,row,col);
        printf(format,x,((col==(RL-1)) ? ";" : " "));
      }  
      printf("\n");
    }
    printf("];\n");
    return;
}

