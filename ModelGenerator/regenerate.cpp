/*************************************************************************
 * regenerate for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Description : Calculate normal-vector, volumes and so on.
 ************************************************************************/
#include <bits/stdc++.h>

using namespace std;

struct ppp{
    float x;float y;float z;
};

struct cmp{
    bool operator()(ppp a,ppp b){
        return a.x<b.x || (a.x==b.x && a.y<b.y) || (a.x==b.x && a.y==b.y && a.z<b.z);
    }
};

const int N=10000;

FILE* input;
FILE* output;
int n,m;
float vol,elas,dens;
float x[N][3],y[N][3],z[N][3],vx[N],vy[N],vz[N];
set<ppp,cmp> a;

// calculate normal vector
void normv(int loca,float x,float y,float z,float xx,float yy,float zz){
    vx[loca]=y*zz-z*yy;
    vy[loca]=-x*zz+z*xx;
    vz[loca]=x*yy-y*xx;
}

// dot calculate
float dot(float x,float y,float z,int loca){
    return x*vx[loca]+y*vy[loca]+z*vz[loca];
}

// square calculate
double sqr(float a){return a*a;}

// dist calculate
double dist(float a,float b,float c,float x,float y,float z){
    return sqrt(sqr(a-x)+sqr(b-y)+sqr(c-z));
}

void prt(int i,int j){
    fprintf(output,"%.10f %.10f %.10f ",x[i][j],y[i][j],z[i][j]);
}

void trans(){
    double maxdist=0;

    fscanf(input,"%d",&n);
    for (int i=0;i<n;++i){
        for (int j=0;j<3;++j){
            fscanf(input,"%f%f%f",x[i]+j,y[i]+j,z[i]+j);
            maxdist=max(maxdist,dist(x[i][j],y[i][j],z[i][j],0,0,0));
        }
        normv(i,x[i][1]-x[i][0],y[i][1]-y[i][0],z[i][1]-z[i][0],
                x[i][2]-x[i][1],y[i][2]-y[i][1],z[i][2]-z[i][1]);
        vol+=dot(x[i][0],y[i][0],z[i][0],i)/6;
    }

    fprintf(output,"%d %.10f %.10f %.10f %.10lf\n",n,vol,(rand()%100)/100.0,(rand()%100)/100.0,maxdist);
    for (int i=0;i<n;++i){
        for (int j=0;j<3;++j){
            prt(i,j);

            // check whether it has ocurred
            ppp now={x[i][j],y[i][j],z[i][j]};
            if (a.find(now)==a.end()) {a.insert(now); fprintf(output,"1 ");}
                else fprintf(output,"0 ");
        }
        fprintf(output,"%.10f %.10f %.10f\n",vx[i],vy[i],vz[i]);
    }
}

int main(){
    srand(time(0));
    char st[N],tst[N];
    scanf("%s",st);
    n=strlen(st);
    st[n++]='.'; st[n++]='t'; st[n++]='x'; st[n++]='t';
    st[n]='\0';
    tst[0]='M'; tst[1]='o'; tst[2]='d'; tst[3]='e'; tst[4]='l';
    for (int i=0;i<=n;++i) tst[5+i]=st[i];

    input=fopen(st,"r");
    if (!input) {printf("error\n"); return 0;}
    output=fopen(tst,"w");

    trans();

    fclose(input);
    fclose(output);
}