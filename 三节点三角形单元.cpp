#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX 100
double a[MAX],b[MAX],c[MAX];												//ai,bi,ci 
double A1,E1,U1,t; 															//���,����ģ�������ɱ� 
double NX[4];																//�κ����м���													 
double N[MAX][MAX],B[MAX][MAX],S[MAX][MAX],A[MAX][MAX],C[MAX];				//NΪ�κ�������BΪ��Ԫ����ת������SΪ��ԪӦ��ת������A����Ϊ�������C����Ϊλ�ƾ���	
double D[3],B1[MAX][MAX],K[MAX][MAX],F[MAX];								//DΪӦ������ ,B1��Ԫ����ת�þ���K�նȾ��� ,F��Ԫ���λ������Ч�������� 

void input()
{
	int i,j;
	cout<<"���ڵ������ε�Ԫ����Ԫ����"<<endl;
	cout<<"���������ڵ�����(����ʱ������):"<<endl;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=2;j++)
			cin>>A[i][j];
	}
	cout<<"���������ڵ�λ��(�����������Ӧ):"<<endl;
	for(i=1;i<=6;i++)
	{
		cin>>C[i];	
	}
	cout<<"������E,u,t(����ģ�������ɱ�,���):"<<endl;
	cin>>E1>>U1>>t; 
}

void N_e()																	//�����κ��� 
{
	int i,x;
	double m,n,p;																//����м���� 
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
	A1=(m+n+p)/2;															//������������� 
	
	for(i=1;i<=3;i++)														//�κ����м������� 
		NX[i]=(a[i]+b[i]*A[i][1]+c[i]*A[i][2])/(2*A1);
	for(i=1;i<=5;i+=2)														//�����κ������� 
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

void B_e()										//���㵥Ԫ���ξ��� 
{
	int x=1;
	int i,j;
	for(i=1;i<=5;i+=2)							//��bi,ci���뵽��Ԫ���ξ��� 
	{								
		if(i==3)								//��x��Ϊ1��2��3 
			x=2;									
		if(i==5)
			x=3;
		
		B[1][i]=b[x]/(2*A1);					//��bi���� 
		B[3][i+1]=b[x]/(2*A1);
		
		B[2][i+1]=c[x]/(2*A1);					//��ci���� 
		B[3][i]=c[x]/(2*A1);
		
		B[1][2]=0;
		B[2][1]=0;
	}
	
}

void S_e()										//���ɵ�ԪӦ��ת������ 
{
	int i,j;
	int x=1;
	for(i=1;i<=3;i++)
		for(j=1;j<=6;j++)
			S[i][j]=E1/(1-U1*U1)*B[i][j];
	for(i=1;i<=5;i+=2)										
	{
		if(i==3)								//��x��Ϊ1��2��3
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
	for(i=1;i<=3;i++)									//ת��B���󣬵õ�B1 
		for(j=1;j<=6;j++)
			B1[j][i]=B[i][j];
	for(i=1;i<=6;i++)									//�õ��նȾ��� 
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
	for(i=1;i<=6;i++)									//�õ���Ԫ�ڵ����������� 
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
	cout<<"���ڵ�����:"<<endl;
	for(i=1;i<=3;i++)
	{
		cout<<A[i][1]<<"	"<<A[i][2]<<endl;
	}
	
	cout<<"���������:"<<A1<<endl;	
		
	cout<<"���ڵ�λ��:"<<endl;
	for(i=1;i<=6;i++)
	{
		cout<<C[i]<<endl;
	}
	
	cout<<"ai,bi,ci:"<<endl;								//���ai,bi,ci 
	for(i=1;i<=3;i++)
	{
		cout<<a[i]<<"	"<<b[i]<<"	"<<c[i]<<endl;
	}
	
	cout<<"�κ���:"<<endl;									//����κ���2X6���� 
	for(i=1;i<=2;i++)
		cout<<N[i][1]<<"	"<<N[i][2]<<"	"<<N[i][3]<<"	"<<N[i][4]<<"	"<<N[i][5]<<"	"<<N[i][6]<<endl;
		
	cout<<"��Ԫ���ξ���:"<<endl;							//���Ӧ��ת��3X6���� 	
	for(i=1;i<=3;i++)
		cout<<B[i][1]<<"	"<<B[i][2]<<"	"<<B[i][3]<<"	"<<B[i][4]<<"	"<<B[i][5]<<"	"<<B[i][6]<<endl;	
		
	cout<<"��ԪӦ��ת������:"<<endl;						//���Ӧ��ת��3X6���� 	
	for(i=1;i<=3;i++)
		cout<<S[i][1]<<"	"<<S[i][2]<<"	"<<S[i][3]<<"	"<<S[i][4]<<"	"<<S[i][5]<<"	"<<S[i][6]<<endl;
	
	cout<<"��ԪӦ������:"<<endl;							//���Ӧ��3X6���� 	
	for(i=1;i<=3;i++)
		cout<<D[i]<<endl;
			
	cout<<"��Ԫ�նȾ���:"<<endl;							//�����Ԫ�ն�6X6���� 	
	for(i=1;i<=6;i++)
		cout<<K[i][1]<<"	"<<K[i][2]<<"	"<<K[i][3]<<"	"<<K[i][4]<<"	"<<K[i][5]<<"	"<<K[i][6]<<endl;
	
	cout<<"��Ԫλ�Ƶ�Ч������:"<<endl;							//���Ӧ��3X6���� 	
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
