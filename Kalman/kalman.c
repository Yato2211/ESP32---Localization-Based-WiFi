#include <stdio.h>
#include <math.h>
 
#define N 256 

int main(void) {
    FILE *fp;
    char fname[] = "C:\\tach\\test\\5.txt";
    char rname[] = "C:\\Kalman\\test\\5.txt";
    char line[N];
    float RSSI[151];
    float RSSIx[51],RSSIy[51],RSSIz[51];
    int i,j,k;
    float varx[51],vary[51],varz[51];
    float error=0.01,sumx,sumy,sumz;
    float kx,ky,kz;
    float x[51],y[51],z[51];


    for (j=0;j<50;j++) {
        varx[j]=0;
        vary[j]=0;
        varz[j]=0;
    }


    fp = fopen(fname, "r"); 
    if(fp == NULL) {
        printf("%s file not open!\n", fname);
        return -1;
    }
    

    i=1;
    while(fgets(line, N, fp) != NULL) {
        sscanf(line, "%f",&RSSI[i]);
        i++;
    }
    fclose(fp);


    k=1;
    sumx=0;sumy=0; sumz=0;
    for (j=1;j<=150;j=j+3) {
        RSSIx[k]=RSSI[j];
        sumx=sumx+RSSIx[k];
        k++;
        }
    k=1;
    for (j=2;j<=150;j=j+3) {
        RSSIy[k]=RSSI[j];
        sumy=sumy+RSSIy[k];
        k++;
        }
    k=1;
    for (j=3;j<=150;j=j+3) {
        RSSIz[k]=RSSI[j];
        sumz=sumz+RSSIz[k];
        k++;
        }
    sumx=sumx/50;
    sumy=sumy/50;
    sumz=sumz/50;


    varx[0]=0;
    for (j=1;j<=50;j++) varx[0]=(sumx-RSSIx[j])*(sumx-RSSIx[j])+varx[0];
    varx[0]=varx[0]/50;
    varx[0]=varx[0]*varx[0];

    vary[0]=0;
    for (j=1;j<=50;j++) vary[0]=(sumy-RSSIy[j])*(sumy-RSSIy[j])+vary[0];
    vary[0]=vary[0]/50;
    vary[0]=vary[0]*vary[0];

    varz[0]=0;
    for (j=1;j<=50;j++) varz[0]=(sumz-RSSIz[j])*(sumz-RSSIz[j])+varz[0];
    varz[0]=varz[0]/50;
    varz[0]=varz[0]*varz[0];

    x[0]=RSSIx[1];
    x[1]=RSSIx[1];
    varx[1]=varx[0];
    kx=varx[1]/(varx[1]+error);
    x[1]=x[1]+kx*(x[1]-x[1]);
    varx[1]=(1-kx)*varx[1];

    y[0]=RSSIy[1];
    y[1]=RSSIy[1];
    vary[1]=vary[0];
    ky=vary[1]/(vary[1]+error);
    y[1]=y[1]+ky*(y[1]-y[1]);
    vary[1]=(1-ky)*vary[1];

    z[0]=RSSIz[1];
    z[1]=RSSIz[1];
    varz[1]=varz[0];
    kz=varz[1]/(varz[1]+error);
    z[1]=z[1]+kz*(z[1]-z[1]);
    varz[1]=(1-kz)*varz[1];


    for (j=2;j<=50;j++){
        x[j]=x[j-1];
        varx[j]=varx[j-1];
        kx=varx[j]/(varx[j]+error);
        x[j]=x[j]+kx*(RSSIx[j]-x[j]);
        varx[j]=(1-kx)*varx[j];

        y[j]=y[j-1];
        vary[j]=vary[j-1];
        ky=vary[j]/(vary[j]+error);
        y[j]=y[j]+ky*(RSSIy[j]-y[j]);
        vary[j]=(1-ky)*vary[j];

        z[j]=z[j-1];
        varz[j]=varz[j-1];
        kz=varz[j]/(varz[j]+error);
        z[j]=z[j]+kz*(RSSIz[j]-z[j]);
        varz[j]=(1-kz)*varz[j];
    }
    printf("-%f\n",x[50]);
    printf("-%f\n",y[50]);
    printf("-%f\n",z[50]);
    fp = fopen(rname, "w"); 
    fprintf(fp,"-%f\n",x[50]);
    fprintf(fp,"-%f\n",y[50]);
    fprintf(fp,"-%f\n",z[50]);
    fclose(fp);
    return 0;
}