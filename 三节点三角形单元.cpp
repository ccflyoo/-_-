#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX 100
double a[MAX],b[MAX],c[MAX];												//ai,bi,ci 
double A1,E1,U1,t; 															//面积,杨氏模量，泊松比 
double NX[4];																//形函数中间量													 
double N[MAX][MAX],B[MAX][MAX],S[MAX][MAX],A[MAX][MAX],C[MAX];				//N为形函数矩阵，B为单元几何转换矩阵，S为单元应力转换矩阵，A数组为坐标矩阵，C数组为位移矩阵	
double D[3],B1[MAX][MAX],K[MAX][MAX],F[MAX];								//D为应力列阵 ,B1单元几何转置矩阵，K刚度矩阵 ,F单元结点位移所等效的力矩阵 

void input()
{
	int i,j;
	cout<<"三节点三角形单元有限元计算"<<endl;
	cout<<"请输入三节点坐标(按逆时针输入):"<<endl;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=2;j++)
			cin>>A[i][j];
	}
	cout<<"请输入三节点位移(与坐标输入对应):"<<endl;
	for(i=1;i<=6;i++)
	{
		cin>>C[i];	
	}
	cout<<"请输入E,u,t(杨氏模量，泊松比,板厚):"<<endl;
	cin>>E1>>U1>>t; 
}

void N_e()																	//计算形函数 
{
	int i,x;
	double m,n,p;																//面积中间变量 
	a[1]=A[2][1]*A[3][2]-A[3][1]*A[2][2];
	b[1]=A[2][2]-A[3][2];
	c[1]=A[3][1]-A[2][1];
	
	a[2]=A[3][1]*A[1][2]-A[1][1]*A[3][2];
	b[2]=A[1][2]-A[1][2];
	c[2]=A[1][1]-A[3][1];
	
	a[3]=A[1][1]*A[2][2]-A[2][1]*A[1][2];
	b[3]=A[1][2]-A[2][2];
	c[3]=A[2][1]-A[1][1];
	
	m=A[1][1]*A[2][2]-A[2][1]*A[1][2];
	n=A[2][1]*A[3][2]-A[3][1]*A[2][2];
	p=A[3][1]*A[1][2]-A[1][1]*A[3][2];
	A1=(m+n+p)/2;															//三角形面积计算 
	
	for(i=1;i<=3;i++)														//形函数中间量计算 
		NX[i]=(a[i]+b[i]*A[i][1]+c[i]*A[i][2])/(2*A1);
	for(i=1;i<=5;i+=2)														//生成形函数矩阵 
	{
		x=i-2;
		if(i==1)
			x=1;
		N[1][i]=NX[x];
		N[2][i+1]=NX[x];
		N[1][i+1]=0;
		N[2][i]=0;		
	}
		
} 

void B_e()										//计算单元几何矩阵 
{
	int x=1;
	int i,j;
	for(i=1;i<=5;i+=2)							//将bi,ci输入到单元几何矩阵 
	{								
		if(i==3)								//将x变为1，2，3 
			x=2;									
		if(i==5)
			x=3;
		
		B[1][i]=b[x]/(2*A1);					//将bi输入 
		B[3][i+1]=b[x]/(2*A1);
		
		B[2][i+1]=c[x]/(2*A1);					//将ci输入 
		B[3][i]=c[x]/(2*A1);
		
		B[1][2]=0;
		B[2][1]=0;
	}
	
}

void S_e()										//生成单元应力转换矩阵 
{
	int i,j;
	int x=1;
	for(i=1;i<=3;i++)
		for(j=1;j<=6;j++)
			S[i][j]=E1/(1-U1*U1)*B[i][j];
	for(i=1;i<=5;i+=2)										
	{
		if(i==3)								//将x变为1，2，3
			x=2;							 
		if(i==5)
			x=3;
		
		S[1][i+1]=c[x]*U1;					
		S[2][i]=b[x]*U1;
		
		S[3][i]=S[3][i]*(1-U1)/2;					
		S[3][i+1]=S[3][i+1]*(1-U1)/2;
	}
	
	
	
}

void D_e()
{
	int i,j;
	int a;
	for(i=1;i<=3;i++)
	{
		a=0;
		for(j=1;j<=6;j++)	
			a+=S[i][j]*C[j];
		D[i]=a;
	}
} 

void K_e()
{
	int i,j,m;
	int a;
	for(i=1;i<=3;i++)									//转置B矩阵，得到B1 
		for(j=1;j<=6;j++)
			B1[j][i]=B[i][j];
	for(i=1;i<=6;i++)									//得到刚度矩阵 
	{
		for(m=1;m<=6;m++)
		{
			a=0;										
			for(j=1;j<=3;j++)			
				a+=A1*t*B1[i][j]*S[j][m];
			K[i][m]=a;
		}
	}
}

void F_e()
{
	int i,j;
	int a;
	for(i=1;i<=6;i++)									//得到单元节点所受力矩阵 
	{
		a=0;
		for(j=1;j<=6;j++)
			a+=K[i][j]*C[j];
		F[i]=a;
	}
}

void output()
{
	int i,j;
	cout<<"三节点坐标:"<<endl;
	for(i=1;i<=3;i++)
	{
		cout<<A[i][1]<<"	"<<A[i][2]<<endl;
	}
	
	cout<<"三角形面积:"<<A1<<endl;	
		
	cout<<"三节点位移:"<<endl;
	for(i=1;i<=6;i++)
	{
		cout<<C[i]<<endl;
	}
	
	cout<<"ai,bi,ci:"<<endl;								//输出ai,bi,ci 
	for(i=1;i<=3;i++)
	{
		cout<<a[i]<<"	"<<b[i]<<"	"<<c[i]<<endl;
	}
	
	cout<<"形函数:"<<endl;									//输出形函数2X6矩阵 
	for(i=1;i<=2;i++)
		cout<<N[i][1]<<"	"<<N[i][2]<<"	"<<N[i][3]<<"	"<<N[i][4]<<"	"<<N[i][5]<<"	"<<N[i][6]<<endl;
		
	cout<<"单元几何矩阵:"<<endl;							//输出应变转换3X6矩阵 	
	for(i=1;i<=3;i++)
		cout<<B[i][1]<<"	"<<B[i][2]<<"	"<<B[i][3]<<"	"<<B[i][4]<<"	"<<B[i][5]<<"	"<<B[i][6]<<endl;	
		
	cout<<"单元应力转换矩阵:"<<endl;						//输出应力转换3X6矩阵 	
	for(i=1;i<=3;i++)
		cout<<S[i][1]<<"	"<<S[i][2]<<"	"<<S[i][3]<<"	"<<S[i][4]<<"	"<<S[i][5]<<"	"<<S[i][6]<<endl;
	
	cout<<"单元应力列阵:"<<endl;							//输出应力3X6矩阵 	
	for(i=1;i<=3;i++)
		cout<<D[i]<<endl;
			
	cout<<"单元刚度矩阵:"<<endl;							//输出单元刚度6X6矩阵 	
	for(i=1;i<=6;i++)
		cout<<K[i][1]<<"	"<<K[i][2]<<"	"<<K[i][3]<<"	"<<K[i][4]<<"	"<<K[i][5]<<"	"<<K[i][6]<<endl;
	
	cout<<"单元位移等效力列阵:"<<endl;							//输出应力3X6矩阵 	
	for(i=1;i<=6;i++)
		cout<<F[i]<<endl;
}



int main()
{

	input();
	N_e();
	B_e();
	S_e();
	D_e();
	K_e();
	F_e();
	output();
	return 0;
	
} 
