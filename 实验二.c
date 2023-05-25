#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//�����������ASSCI�룬ͨ��ȡģ6��������ɢ��
int _rank[6] = { 2,1,0,1,3,2 };

const int maxn = 21;

struct Stack1 {         //����ջ
	int ar[21];
	int top;
};

struct Stack2 {        //�ַ�ջ
	char ar[21];       //ջ�ڿռ��ַ����� 
	int top;           //ջ��λ�� 
};

typedef struct Stack1* ps1;
typedef struct Stack2* ps2;

void InitStack1(ps1 st)   //��ʼ�� 
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

void InStack1(ps1 st, int num)   //��ջ
{
	if (st->top > maxn) return;
	st->ar[++st->top] = num;
}

void InStack2(ps2 st, char ch)   //��ջ
{
	if (st->top > maxn) return;
	st->ar[++st->top] = ch;
}

void OutStack1(ps1 st)  //��ջ��ɾ�� 
{
	if (!st->top) return;    //Ϊ��
	st->ar[st->top--] = 0;
}

void OutStack2(ps2 st)   //��ջ 
{
	if (!st->top) return;    //Ϊ��
	st->ar[st->top--] = '\0';
}

int Top1(ps1 st)    //ջ��ֵ 
{
	if (!st->top) return;
	return st->ar[st->top];
}

char Top2(ps2 st)
{
	if (!st->top) return;
	return st->ar[st->top];
}

int compe(const char ch1, const char ch2)	//�Ƚ����ַ�������˳��
{
	//����ɢ��������бȽ�
	int cnt1 = (ch1 - '+' + 43) % 6;	//��һ���ַ���_rank�����е�λ��
	int cnt2 = (ch2 - '+' + 43) % 6;	//�ڶ����ַ�ͬ��
	return _rank[cnt2] <= _rank[cnt1];
}

void cal(ps1 numb,ps2 sbol)
{
	int num1 = Top1(numb);			//��һ����
	OutStack1(numb);
	int num2 = Top1(numb);			//�ڶ�����
	OutStack1(numb);
	char cl = Top2(sbol);            //�����
	OutStack2(sbol);
	int ret = 0;
	switch (cl)                     //���и���������ļ���
	{
		case '+': ret = num2 + num1; break;
		case '-': ret = num2 - num1; break;
		case '*': ret = num2 * num1; break;
		case '/': if( num1==0 ) { printf("��������Ϊ0");exit(0); }
		ret = num2 / num1; break;
		case '^': ret = pow(num2, num1); break;
		default: return;
	}
	//����ֵ����ջ��
	InStack1(numb, ret);
}

void func(ps1 numb,ps2 sbol,char ch)				 //�������ѹ��ջ
{
	if (ch >= '0' && ch <= '9')  //���������
	{
		InStack1(numb, (ch - '0'));
	}
	else
	{
		//�����ǰ�ַ������������ջ���ַ�,һ��ѭ��ֱ�����ڲ�ֹͣ����Ϊ��
		while (sbol->top && compe(Top2(sbol), ch))
		{
			cal(numb,sbol);				//���о������
		}
		InStack2(sbol, ch);				//��ǰ����ѹ��ջ��
	}
}


int main()
{
	//�����ڴ���� 
	ps1 numb=malloc(sizeof(struct Stack1));          //����
	ps2 sbol=malloc(sizeof(struct Stack2));         //�����ַ�	
	
	int ans = 0;
	InitStack1(numb);
	InitStack2(sbol);
	char ch = getchar();
	while(ch!='=')
	{
		func(numb,sbol,ch);
		ch = getchar();
	}
	while (numb->top > 1)           //ֱ����ʣһ�����ŵõ������
		cal(numb,sbol);
	printf("%d",Top1(numb));       //��������
	OutStack1(numb);
	
	free(numb);                     //�ͷ��ڴ� 
	free(sbol);
	
	return 0;
}

