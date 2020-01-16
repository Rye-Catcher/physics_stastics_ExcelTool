#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <cmath>
using namespace std;
const int maxn=17;
int n;


class Poly
{
	
private:
	
	double c_const;
	//����ʽǰ���� 
	int vpower[maxn];
	//��������
	
public:
	
	
	Poly()
	{
		c_const=0;
		memset(vpower,0,sizeof(vpower));
	}	
	Poly(double c, int vp[])
	{
		c_const=c;
		//vpower=vp;
		for(int i=1;i<=maxn-1;i++)vpower[i]=vp[i];
	}
	int get_power(int id)
	{
		return vpower[id];
	}
	void change_power(int id,int val)
	{
		vpower[id]=val;
	}
	double get_const()
	{
		return c_const;
	}
	
	Poly partial_derivative(int id)
	{
		if(vpower[id]==0) return Poly(0, vpower);
		
		double new_c=c_const*vpower[id];
		int new_vpower[15];
		memcpy(new_vpower, vpower, maxn);
		new_vpower[id]--;
		
		return Poly(new_c, new_vpower);
	}
};
class Func
{
private:
	int n,m;
	//����ʽ����  �������� 
	Poly poly[maxn];
	char variable[maxn];
	int is_input[515];
	char posx[maxn][2];
	int posy[maxn][2];
	
	
	
public:

	Func()
	{
		memset(is_input,0,sizeof(is_input));
	}
	
	void print_readme()
	{
		printf("��ӭʹ�����С����\n");
		printf("����Ϊ�˼����physics lab��Excel��������\n");
		printf("����һ����������ע����Ӧ������λ�ã�����������������������������������uncertainty��Excel��ı��ʽ\n"); 
		printf("Ŀǰֻ֧�ֶ���ʽ����");
		printf("�������뷽ʽ���⣬Ĭ�ϵ���ʽ֮��ʹ�üӺ�����;�����������ʹ�ü������ӣ����ں�һ���ĳ�������ϸ���\n");
		printf("��ȷ������������ΪһλӢ����ĸ\n");
		printf("-----------");
	}
	
	void input_func()
	{
		string input_s;
		double c;
		int vpower[maxn];
		
		printf("�����뺯�������ĵ���ʽ����\n>");
		scanf("%d",&n);
		m=0;
		
		for(int i=1;i<=n;i++)
		{
			int t=0;//��ʱ
			c=0;
			memset(vpower,0,sizeof(vpower));
			 
			printf("�������%d������ʽ��ָ����ʹ��������ס����: -3.5x^(-3)y^(2), 2x^(1)y^(-1)\n>", i);
			cin>>input_s;
			
			if(input_s[0]=='-')
			{
				t++;			
				if(input_s[t]>'9'&&input_s[t]<'0') c=-1;
				else
				{
					while(isdigit(input_s[t]))
					{
						c=c*10+input_s[t]-'0';
						t++;
					}
					if(input_s[t]=='.')
					{
						t++;
						
						double power=0.1;
						
						while(isdigit(input_s[t]))
						{
							c=c+(input_s[t]-'0')*power;
							power=power*0.1;
							t++;
						}							
					}
					
					c=-c;
				}
			}
			else if(input_s[0]>'9'||input_s[0]<'0') c=1;
			else
			{
				while(isdigit(input_s[t]))
				{
					c=c*10+input_s[t]-'0';
					t++;
				}
				
				if(input_s[t]=='.')
				{
					t++;
						
					double power=0.1;
						
					while(isdigit(input_s[t]))
					{
						c=c+(input_s[t]-'0')*power;
						power=power*0.1;
						t++;
					}							
				}
			}
			//read constant
			
		
			#ifdef debug
			puts("ssss");
			#endif
			
			while(t<input_s.length())
			{
				int power=0;
				char now_var;
				
				if(is_input[input_s[t]])
				{
					;
				}
				else
				{
					is_input[input_s[t]]=++m;
					variable[m]=input_s[t];
				}
				
				now_var=input_s[t];
				

				
				t++;
				
				if(input_s[t]=='^')
				{
					t++;//(
					t++;
					
					if(input_s[t]=='-')
					{
						t++;
						while(input_s[t]!=')')
						{
							power=power*10+input_s[t]-'0';
							t++;
						}
						power=-power;
					}
					else
					{
						while(input_s[t]!=')')
						{
							power=power*10+input_s[t]-'0';
							t++;
						}
					}
					vpower[is_input[now_var]]=power;
					
					
					#ifdef debug
					printf("--%d--\n",power);
					#endif
						
					t++;//)
				}
				else
				{
					power=1;
					vpower[is_input[now_var]]=power;
					
					continue;
				}
			}
			//read variable;
			

			
			poly[i]=Poly(c, vpower);
		} 
		//���뵥��ʽ
		
			
		printf("̫���ˣ��������Ӧ������ 1.����ֵ��Excel������λ��(��:B5)  2.uncertainty��λ��. ��һ���ո����\n");	
		
		getchar();
		for(int i=1;i<=m;i++)
		{
			printf("%c   ",variable[i]);
			scanf("%c%d %c%d",&posx[i][0],&posy[i][0],&posx[i][1],&posy[i][1]); 
			getchar();
		}
	}
	
	void output()
	{
		printf("----\n");
		printf("SQRT(");
		for(int i=1;i<=m;i++)
		{
			printf("(");
			printf("(");
			
			for(int j=1;j<=n;j++)
			{	
				Poly result=poly[j].partial_derivative(i);
				
				if(result.get_const()==0)
				{
					printf("0");
					if(j!=n) putchar('+');
					continue;
				}
				
				printf("%lf*",result.get_const());
				
				//�ɸĽ�  --ָ��Ϊ0ʱ 
				for(int k=1;k<=m;k++)
				{
					printf("%c%d^",posx[k][0],posy[k][0]);
					printf("(%d)",result.get_power(k));
					
					if(k!=m) printf("*");
				}
				
				if(j!=n)printf("+");
			}
			
			printf(")*%c%d",posx[i][1],posy[i][1]);
			printf(")^2");
			
			if(i!=m)printf("+");
		}
		printf(")");
	}		
};

int main()
{
	Func f;
	f.print_readme();
	f.input_func();
	f.output();	
	return 0;
}
