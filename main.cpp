#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");
char a[100][100], sub[100][100];
int n, m, i0, j0, t[100][100], ts[100][100], taux[100][100], pas, okt=0, ai, aj, ia, ja, subi, subj, eti, etj;
float contE=12, timp=0;
int z[8]= {-1,-1,-1,0,1,1, 1, 0};
int y[8]= {-1, 0, 1,1,1,0,-1,-1};
struct inv
{
    int sabie=0;
    int tarnacop=0;
    int subsol=0;
    int etaj=0;
};
inv inventar;
void citire()
{
    fin>>n>>m;
    for(int j=1;j<=m;++j)
        a[0][j]=0;
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
            fin>>a[i][j];
    for(int j=1;j<=m;++j)
        sub[0][j]=-1;
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
            fin>>sub[i][j];
    fin>>i0>>j0;
}
int valid(char x[][100], int T[][100], int ii, int jj)
{
    if(contE<0)return 0;
    if(ii<1 || ii>n || jj<1 || jj>m)return 0;
    if(x[ii][jj]=='1' && inventar.tarnacop!=1)return 0;
    if(T[ii][jj]!=0)return 0;
    return 1;
}
int trans(char x)
{
    return x-64;
}
void Swap()
{
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
            swap(a[i][j],sub[i][j]);
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
            swap(t[i][j],ts[i][j]);
}
void afis(int t[][100], int ts[][100])
{
    fout<<contE<<' '<<timp<<endl;
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=m; ++j)
            fout<<t[i][j]<<' ';
        fout<<endl;
    }
    fout<<endl;
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=m; ++j)
            fout<<ts[i][j]<<' ';
        fout<<endl;
    }
    fout<<endl;
}
void afisCh(char t[][100])
{
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=m; ++j)
            fout<<t[i][j]<<' ';
        fout<<endl;
    }
    fout<<endl;
}
void traseu(char x[][100], int T[][100], int i, int j, int pas)
{
    int ii,jj;
    for(int k=0; k<8; ++k)
    {
        ii=i+z[k];
        jj=j+y[k];
        if(x[ii][jj]=='0' || x[ii][jj]=='s' || x[ii][jj]=='t' || isupper(x[ii][jj]) || x[ii][jj]=='-' || x[ii][jj]=='+')
        {
            if(k%2==1)
            {
                --contE;
                ++timp;
            }
            else if(k%2==0)
            {
                contE-=1.5;
                timp+=1.5;
            }
            if(x[ii][jj]=='s')
            {
                if(inventar.sabie==0)
                {
                    inventar.sabie=1;
                    ai=i;
                    aj=j;
                }
            }
            else if(x[ii][jj]=='t')
            {
                if(inventar.tarnacop==0)
                {
                    inventar.tarnacop=1;
                    ia=i;
                    ja=j;
                }
            }
            else if(isupper(x[ii][jj]))
            {
                contE+=trans(x[ii][jj]);
            }
        }
        else if(x[ii][jj]=='1' && inventar.tarnacop==1)
        {
            if(k%2==1)
            {
                contE-=2;
                timp+=2;
            }
            else if(k%2==0)
            {
                contE-=2.5;
                timp+=2.5;
            }
        }
        else if(x[ii][jj]=='m')
        {
            if(inventar.sabie)
            {
                contE-=3;
                timp+=3;
            }
            else
            {
                contE-=6;
                timp+=6;
            }
        }
        if(valid(x,T,ii,jj))
        {
            T[ii][jj]=pas;
            if(x[ii][jj]=='-')
            {
                pas+=1;
                ts[ii][jj]=pas;
                contE-=0.5;
                timp+=0.5;

                traseu(sub,ts,ii,jj,pas+1);
                contE+=0.5;
                timp-=0.5;
                ts[ii][jj]=0;
            }
            else if(x[ii][jj]=='+')
            {
                pas+=1;
                t[ii][jj]=pas;
                contE-=0.5;
                timp+=0.5;
                traseu(a,t,ii,jj,pas+1);
                contE+=0.5;
                timp-=0.5;
                t[ii][jj]=0;
            }
            if(ii==1 && x[0][jj]==0)
                afis(t,ts);
            else traseu(x,T,ii,jj,pas+1);
            T[ii][jj]=0;
        }
        if(x[ii][jj]=='0' || x[ii][jj]=='s' || x[ii][jj]=='t' || isupper(x[ii][jj]) || x[ii][jj]=='-' || x[ii][jj]=='+')
        {
            if(k%2==1)
            {
                ++contE;
                --timp;
            }
            else if(k%2==0)
            {
                contE+=1.5;
                timp-=1.5;
            }
            if(i==ai && j==aj && x[i][j]!='s')
            {
                ai=0;
                aj=0;
                inventar.sabie=0;
            }
            if(i==ia && j==ja && x[i][j]!='t')
            {
                ia=0;
                ja=0;
                inventar.tarnacop=0;
            }
            if(isupper(x[ii][jj]))
            {
                contE-=trans(x[ii][jj]);
            }
        }
        else if(x[ii][jj]=='1' && inventar.tarnacop==1)
        {
            if(k%2==1)
            {
                contE+=2;
                timp-=2;
            }
            else if(k%2==0)
            {
                contE+=2.5;
                timp-=2.5;
            }
        }
        else if(x[ii][jj]=='m')
        {
            if(inventar.sabie)
            {
                contE+=3;
                timp-=3;
            }
            else
            {
                contE+=6;
                timp-=6;
            }

        }
    }
}
int main()
{
    citire();
    t[i0][j0]=1;
    traseu(a,t,i0,j0,2);
    return 0;
}
