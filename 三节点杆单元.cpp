#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX 100
double K_A[MAX][MAX],K[MAX][MAX],K_B[MAX][MAX],K_C[MAX][MAX];		//K����ܸնȾ���K_A���һ��Ϊ����������Ԫ�նȾ���K_B���ȥ��Լ����ת�ú�ĸնȾ���,
double W[MAX],F[MAX];												//K_C���ȥ��Լ����ȥ��1��5���У��ĸնȾ��� ,W���λ������,F�����������ڵ������� 
void K_e()
{
	double L,l,E,Iy,a;
	int i; 
	cout<<"������˳�������ģ��������漫���Ծأ�"<<endl;
	cin>>L>>E>>Iy;
	l=L/2; 
	a=E*Iy/(l*l*l);
	K_A[1][1]=K_A[3][3]=12*a;
	K_A[1][2]=K_A[1][4]=K_A[2][1]=K_A[4][1]=6*l*a;
	K_A[1][3]=K_A[3][1]=-12*a;
	K_A[2][2]=K_A[4][4]=4*l*l*a;
	K_A[2][3]=K_A[3][2]=K_A[3][4]=-6*l*a;
	K_A[2][4]=K_A[4][2]=2*l*l*a;
	cout<<"����Ԫ�նȾ��� K1=K2:"<<endl;
	for(i=1;i<=4;i++)
		cout<<K_A[i][1]<<"		"<<K_A[i][2]<<"		"<<K_A[i][3]<<"		"<<K_A[i][4]<<endl;
	for(i=1;i<=6;i++)
		K[i][i]=0;
	K[5][1]=K[6][2]=K[1][5]=K[2][6]=0;
	K[1][1]=K[5][5]=12;
	K[1][2]=K[1][4]=K[2][1]=K[3][6]=K[4][1]=K[6][3]=6*l;
	K[1][3]=K[3][1]=K[3][5]=K[5][3]=-12;
	K[2][2]=K[6][6]=4*l*l;
	K[2][3]=K[3][2]=K[4][5]=K[5][4]=K[5][6]=K[6][5]=-6*l;
	K[2][4]=K[4][2]=K[4][6]=K[6][4]=2*l*l;
	K[3][3]=24;
	K[4][4]=8*l*l;
	cout<<"�ܸնȾ���"<<endl;
	for(i=1;i<=6;i++)
		cout<<K[i][1]<<"		"<<K[i][2]<<"		"<<K[i][3]<<"		"<<K[i][4]<<"		"<<K[i][5]<<"		"<<K[i][6]<<endl;
} 
/***�ܸ�ת��***/ 
void tanl()
{
	int i,j;
	for(i=2;i<=4;i++)							//��ת�� 
		for(j=1;j<=6;j++)
			K_C[i-1][j]=K[i][j];
	for(i=1;i<=6;i++)
		K_C[4][i]=K[6][i];
	for(i=2;i<=4;i++)
		for(j=1;j<=4;j++)						//��ת�� 
			K_C[j][i-1]=K[j][i];
	for(i=1;i<=4;i++)
		K_C[i][4]=K[i][6];
	cout<<"ȥ��Լ�������ĸնȾ���:"<<endl;
	for(i=1;i<=4;i++)							
		cout<<K_C[i][1]<<"		"<<K_C[i][2]<<"		"<<K_C[i][3]<<"		"<<K_C[i][4]<<endl;
	
}

void F_e()
{
	int i;
	cout<<"���������ڵ�������(�ĸ�)��"<<endl;
	cin>>F[1]>>F[2]>>F[3]>>F[4];
}

//����һ��չ������|A|
double getA(double arcs[MAX][MAX],int n)
{
    if(n==1)
    {
        return arcs[1][1];
    }
    double ans = 0;
    double temp[MAX][MAX]={0.0};
    int i,j,k;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n-1;j++)
        {
            for(k=1;k<=n-1;k++)
            {
                temp[j][k] = arcs[j+1][(k>=i)?k+1:k];

            }
        }
        double t = getA(temp,n-1);
        if(i%2==0)
        {
            ans += arcs[1][i]*t;
        }
        else
        {
            ans -=  arcs[1][i]*t;
        }
    }
    return ans;
}

//����ÿһ��ÿһ�е�ÿ��Ԫ������Ӧ������ʽ�����A*
void  getAStart(double arcs[MAX][MAX],int n,double ans[MAX][MAX])
{
    if(n==1)
    {
        ans[1][1] = 1;
        return;
    }
    int i,j,k,t;
    double temp[MAX][MAX];
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            for(k=1;k<=n-1;k++)
            {
                for(t=1;t<=n-1;t++)
                {
                    temp[k][t] = arcs[k>=i?k+1:k][t>=j?t+1:t];
                }
            }


            ans[j][i]=getA(temp,n-1);
            if((i+j)%2 == 1)
            {
                ans[j][i] =-ans[j][i];
            }
        }
    }
}


//�õ���������src������󱣴浽des�С�
void GetMatrixInverse(double src[MAX][MAX],int n)
{
	int i;
    double flag=getA(src,n);
    double t[MAX][MAX];
	getAStart(src,n,t);
    for(int i=1;i<=4;i++)
    {
        for(int j=1;j<=4;j++)
        {
       		K_B[i][j]=t[i][j]/flag;
        }
    }
	cout<<"�նȾ���������"<<endl;
	for(i=1;i<=4;i++)							
		cout<<K_B[i][1]<<"		"<<K_B[i][2]<<"		"<<K_B[i][3]<<"		"<<K_B[i][4]<<endl;
}

/***���Ψһ����***/ 
void W_e()
{
	int i,j;
	double a;
	for(i=1;i<=4;i++)
	{
		a=0;						
		for(j=1;j<=4;j++)
			a+=K_B[i][j]*F[j];
		W[i]=a;
	}
}

void display()
{
	cout<<"��Ԫλ������"<<endl; 						
	cout<<0<<endl;
	cout<<W[1]<<endl;
	cout<<W[2]<<endl;
	cout<<W[3]<<endl;
	cout<<0<<endl;
	cout<<W[1]<<endl; 
}

int main()
{
	K_e();
	tanl();
	GetMatrixInverse(K,4);				//�õ��նȾ��������� 
	F_e();
	W_e();
	display();
	return 0;
}

