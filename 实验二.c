#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//根据运算符的ASSCI码，通过取模6进行数组散列
int _rank[6] = { 2,1,0,1,3,2 };

const int maxn = 21;

struct Stack1 {         //数字栈
	int ar[21];
	int top;
};

struct Stack2 {        //字符栈
	char ar[21];       //栈内空间字符数组 
	int top;           //栈顶位置 
};

typedef struct Stack1* ps1;
typedef struct Stack2* ps2;

void InitStack1(ps1 st)   //初始化 
{
	int i;
	for ( i = 0; i < maxn; i++)
		st->ar[i] = 0;
	st->top = 0;
}

void InitStack2(ps2 st)
{
	int i;
	for ( i = 0; i < maxn; i++)
		st->ar[i] = '\0';
	st->top = 0;
}

void InStack1(ps1 st, int num)   //入栈
{
	if (st->top > maxn) return;
	st->ar[++st->top] = num;
}

void InStack2(ps2 st, char ch)   //入栈
{
	if (st->top > maxn) return;
	st->ar[++st->top] = ch;
}

void OutStack1(ps1 st)  //出栈即删除 
{
	if (!st->top) return;    //为空
	st->ar[st->top--] = 0;
}

void OutStack2(ps2 st)   //出栈 
{
	if (!st->top) return;    //为空
	st->ar[st->top--] = '\0';
}

int Top1(ps1 st)    //栈顶值 
{
	if (!st->top) return;
	return st->ar[st->top];
}

char Top2(ps2 st)
{
	if (!st->top) return;
	return st->ar[st->top];
}

int compe(const char ch1, const char ch2)	//比较两字符的运算顺序
{
	//根据散列数组进行比较
	int cnt1 = (ch1 - '+' + 43) % 6;	//第一个字符在_rank数组中的位置
	int cnt2 = (ch2 - '+' + 43) % 6;	//第二个字符同理
	return _rank[cnt2] <= _rank[cnt1];
}

void cal(ps1 numb,ps2 sbol)
{
	int num1 = Top1(numb);			//第一个数
	OutStack1(numb);
	int num2 = Top1(numb);			//第二个数
	OutStack1(numb);
	char cl = Top2(sbol);            //运算符
	OutStack2(sbol);
	int ret = 0;
	switch (cl)                     //进行各种运算符的计算
	{
		case '+': ret = num2 + num1; break;
		case '-': ret = num2 - num1; break;
		case '*': ret = num2 * num1; break;
		case '/': if( num1==0 ) { printf("除数不能为0");exit(0); }
		ret = num2 / num1; break;
		case '^': ret = pow(num2, num1); break;
		default: return;
	}
	//将新值放入栈中
	InStack1(numb, ret);
}

void func(ps1 numb,ps2 sbol,char ch)				 //计算或者压入栈
{
	if (ch >= '0' && ch <= '9')  //如果是数字
	{
		InStack1(numb, (ch - '0'));
	}
	else
	{
		//如果当前字符运算符不大于栈顶字符,一个循环直到大于才停止或者为空
		while (sbol->top && compe(Top2(sbol), ch))
		{
			cal(numb,sbol);				//进行具体计算
		}
		InStack2(sbol, ch);				//当前运算压入栈中
	}
}


int main()
{
	//申请内存分配 
	ps1 numb=malloc(sizeof(struct Stack1));          //数字
	ps2 sbol=malloc(sizeof(struct Stack2));         //运算字符	
	
	int ans = 0;
	InitStack1(numb);
	InitStack2(sbol);
	char ch = getchar();
	while(ch!='=')
	{
		func(numb,sbol,ch);
		ch = getchar();
	}
	while (numb->top > 1)           //直到还剩一个数才得到最后结果
		cal(numb,sbol);
	printf("%d",Top1(numb));       //输出最后结果
	OutStack1(numb);
	
	free(numb);                     //释放内存 
	free(sbol);
	
	return 0;
}

