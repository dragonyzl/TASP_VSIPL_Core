/* Created by RJudd */
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
/* $Id: atest.c,v 1.1 2000/04/14 12:47:23 judd Exp judd $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
#define NDPTR_f ((vsip_scalar_f*)NULL)
#define NDPTR_d ((vsip_scalar_d*)NULL)

#include"utility_f.h"
#include"utility_d.h"

#include"cvscatter_f.h"

int main(int argc, char* argv[]){
     vsip_init((void*)0);
     cvscatter_f();
     vsip_finalize((void*)0);
     return 0;
}
