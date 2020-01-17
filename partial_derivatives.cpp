#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
const int maxn=17;
const int MAX_DIGIT = 10;
int n;


class Poly
{
	
private:
	
	double c_const;
	//单项式前常数 
	int vpower[maxn];
	//变量的幂
	
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
	//单项式个数  变量个数 
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
		printf("欢迎使用这个小程序！\n");
		printf("它是为了简化完成physics lab的Excel而开发的\n");
		printf("给定一个函数，标注出对应变量的位置，它可以生成求出这个函数所代表物理量的uncertainty在Excel里的表达式\n"); 
		printf("目前只支持多项式函数");
		printf("由于输入方式特殊，默认单项式之间使用加号连接;如果函数中是使用减号连接，请在后一个的常数项加上负号\n");
		printf("请确保函数变量名为一位英文字母\n");
		printf("-----------");
	}
	
	void input_func()
	{
		string input_s;
		double c;
		int vpower[maxn];
		
		printf("请输入函数包含的单项式个数\n>");
		scanf("%d",&n);
		m=0;
		
		for(int i=1;i<=n;i++)
		{
			int t=0;//临时
			c=0;
			memset(vpower,0,sizeof(vpower));
			 
			printf("请输入第%d个单项式，指数请使用括号括住，如: -3.5x^(-3)y^(2), 2x^(1)y^(-1)\n>", i);
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
		//输入单项式
		
			
		printf("太棒了，请输入对应变量的 1.测量值在Excel表格里的位置(如:B5)  2.uncertainty的位置. 用一个空格隔开\n");	
		
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
				
				//printf("%lf*",result.get_const());
				int CurrentDigit;
				char tempstr[MAX_DIGIT];
				snprintf(tempstr[0], MAX_DIGIT, "%lf", result.get_const());
				for (CurrentDigit = MAX_DIGIT; (tempstr[i] <= '0' || tempstr[i] > '9') && tempstr[i] != '.'; CurrentDigit--)
    				;
				if (tempstr[i] == '.')
    				tempstr[i] = '\0';
				else
    				tempstr[i][CurrentDigit + 1] = '\0';
				printf("%s*", tempstr);
				
				//可改进  --指数为0时 
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
