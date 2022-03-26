#include <stdio.h>
#include <math.h>
 
#define N 256 

int main(void) {
    FILE *fp;
    char fname[] = "C:\\wknn\\tb\\sample.txt";
    char rname[] = "C:\\wknn\\tb\\test.txt";
    char line[N];
    double RSSI[190];
    double RSSIx[64],RSSIy[64],RSSIz[64];
    double test[52];
    double testx[18],testy[18],testz[18];
    int i,j;
    int k,n;
    double d[64];
    double d1,d2,d3,d4,d5,d6,d7;
    double w,w1,w2,w3,w4,w5,w6,w7;
    double kc,tb=0;;
    double tdx,tdy;
    int m1,m2,m3,m4,m5,m6,m7;
    double samplex[64]={0,   0.6,0.6,0.6,0.6,0.6,0.6,0.6,   1.6,1.6,1.6,1.6,1.6,1.6,1.6,    2.6,2.6,2.6,2.6,2.6,2.6,2.6,    3.6,3.6,3.6,3.6,3.6,3.6,3.6,    4.6,4.6,4.6,4.6,4.6,4.6,4.6,
                            5.6,5.6,5.6,5.6,5.6,5.6,5.6,   6.6,6.6,6.6,6.6,6.6,6.6,6.6,    7.6,7.6,7.6,7.6,7.6,7.6,7.6,    8.6,8.6,8.6,8.6,8.6,8.6,8.6};
    double sampley[64]={0,   1,2,3,4,5,6,7,  1,2,3,4,5,6,7,  1,2,3,4,5,6,7,  1,2,3,4,5,6,7,  1,2,3,4,5,6,7,  1,2,3,4,5,6,7,  1,2,3,4,5,6,7,  1,2,3,4,5,6,7};
    double dx[18]={0, 1.4, 3.8, 3.8, 3, 1.4, 1.4, 2.6, 5.2, 6.2, 4.2, 5.4, 5.6, 7.8, 8.4, 8, 8.4, 7.8};
    double dy[18]={0, 2.4, 1.8, 3.4, 5.6, 4.2, 5.8, 6.4, 6.4, 5.8, 5, 3.8, 1.6, 1, 1.8, 3.4, 5.2, 6.8};



    fp = fopen(fname, "r"); 
    if(fp == NULL) {
        printf("%s file not open!\n", fname);
        return -1;
    }
    

    i=1;
    while(fgets(line, N, fp) != NULL) {
        sscanf(line, "%lf",&RSSI[i]);
        i++;
    }
    fclose(fp);
    for (j=1;j<=63;j++) RSSIx[j]=RSSI[j];
    for (j=64;j<=126;j++) RSSIy[j-63]=RSSI[j];
    for (j=127;j<=189;j++) RSSIz[j-126]=RSSI[j];

    fp = fopen(rname, "r"); 
    if(fp == NULL) {
        printf("%s file not open!\n", fname);
        return -1;
    }
    

    i=1;
    while(fgets(line, N, fp) != NULL) {
        sscanf(line, "%lf",&test[i]);
        i++;
    }
    fclose(fp);
    for (j=1;j<=17;j++) testx[j]=test[j];
    for (j=18;j<=34;j++) testy[j-17]=test[j];
    for (j=35;j<=51;j++) testz[j-34]=test[j];
    //printf("%f",testz[17]);
    for (n=1;n<=17;n++) {
        for (k=1;k<=63;k++) {
            d[k]=sqrt(pow((RSSIx[k]-testx[n]),2)+pow((RSSIy[k]-testy[n]),2)+pow((RSSIz[k]-testz[n]),2));
        }
        d1=d[1];d2=d[1];d3=d[1];d4=d[1];d5=d[1];d6=d[1];d7=d[1];
        for (k=1;k<=63;k++) if (d1>d[k]) { m1=k; d1=d[k];}
        for (k=1;k<=63;k++) if ((d2>d[k]) && (d[k]>d1)) { m2=k; d2=d[k];}
        for (k=1;k<=63;k++) if ((d3>d[k]) && (d[k]>d2)) { m3=k; d3=d[k];}
        for (k=1;k<=63;k++) if ((d4>d[k]) && (d[k]>d3)) { m4=k; d4=d[k];}
        for (k=1;k<=63;k++) if ((d5>d[k]) && (d[k]>d4)) { m5=k; d5=d[k];}
        for (k=1;k<=63;k++) if ((d6>d[k]) && (d[k]>d5)) { m6=k; d6=d[k];}
        for (k=1;k<=63;k++) if ((d7>d[k]) && (d[k]>d6)) { m7=k; d7=d[k];}
        //printf("%d  %d  %d  %d  %d\n",m1,m2,m3,m4,m5);
        w=1/d1+1/d2+1/d3;//+1/d4+1/d5;//+1/d6;
        //w=d1+d2+d3;//+d4;
        tdx=(((1/d1)/(w))*samplex[m1])+(((1/d2)/(w))*samplex[m2])+(((1/d3)/(w))*samplex[m3]);//+(((1/d4)/(w))*samplex[m4])+(((1/d5)/(w))*samplex[m5]);//+(((1/d6)/(w))*samplex[m6])+(((1/d7)/(w))*samplex[m7]);
        tdy=(((1/d1)/(w))*sampley[m1])+(((1/d2)/(w))*sampley[m2])+(((1/d3)/(w))*sampley[m3]);//+(((1/d4)/(w))*sampley[m4])+(((1/d5)/(w))*sampley[m5]);//+(((1/d6)/(w))*sampley[m6])+(((1/d7)/(w))*sampley[m7]);
        //tdx=(((d1)/(w))*samplex[m1])+(((d2)/(w))*samplex[m2])+(((d3)/(w))*samplex[m3]);//+(((d4)/(w))*samplex[m4]);//+(((1/d5)/(w))*samplex[m5]);
        //tdy=(((d1)/(w))*sampley[m1])+(((d2)/(w))*sampley[m2])+(((d3)/(w))*sampley[m3]);//+(((d4)/(w))*sampley[m4]);//+(((1/d5)/(w))*sampley[m5]);
        kc=sqrt(pow((tdx-dx[n]),2)+pow((tdy-dy[n]),2));
        tb=tb+kc;
        printf ("%.10lf\n",kc);
    }
    tb=tb/17;
    printf ("%.10lf",tb);


    return 0;
}
