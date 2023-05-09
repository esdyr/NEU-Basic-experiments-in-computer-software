/*
	������������ʵ��1�������Ա�����������

	by������ 20215068

*/

#include<stdio.h>
#define ElemType int
#define maxsize 15 //���Ա�϶��ﵽ�����
#define OK 1
#define ERROR 0
typedef struct //�ṹ��
{
	ElemType elem[maxsize];
	int length;
}SeqList;
SeqList L;
int  Locate(SeqList L,ElemType x)//����
{
	int i = 1;
	while((i<=L.length)&&(L.elem[i]!=x))
		i++;
	if(i<=L.length)   return(i);
	else              return(-1);
}
int InsList(SeqList*L,int i,ElemType x)//����
{
	int k;
	if ((i < 1) || (i>L->length+1))
	{
		printf("����λ�ô���");
		return(ERROR);
	}
	if(L->length>=maxsize-1)
	{
		printf("�������޷�����");
		return(ERROR);
	}
	for(k=L->length;k>=i;k--)//�����һ����ǰ��
		L->elem[k+1]=L->elem[k];
	L->elem[i]=x;
	L->length++;
	return(OK);
}
int DelList(SeqList *L,int i,ElemType *e)
{
	int k;
	if((i<1)||(i>L->length))
	{
		printf("ɾ��λ�ò��Ϸ���");
		return(ERROR);
	}
	*e=L->elem[i];
	for(k=i;k<=L->length-1;k++)
		L->elem[k]=L->elem[k+1];
	L->length--;
	return(OK);
}
void Bubble(int num[],int n){   //ð������
	int flag=1;
	int a=0;
	for(int i = 0;i < n-1;i++){
		flag=0;
		for(int j = 0;j<n-1;j++){
			if(num[j]>num[j+1]){
				a = num[j];
				num[j]=num[j+1];    //�������������û�
				num[j+1]=a;
				flag = 1;
			}
		}
		if(flag==0)
			break;
	}
	for(int i=0;i<n;i++)
		printf("%d  ",num[i]);
	for(int i=0;i<L.length;i++)
		L.elem[i]=num[i];
}
void output_L(){
	for(int i=0;i<L.length;i++)
		printf("%d  ",L.elem[i]);
}
int main(){
	L.length=10;
	int input=0;
	printf("��������\n������%d���������ڳ�ʼ�����Ա�\n",L.length);
	for(int i=0;i < L.length;i++){
		scanf("%d",&L.elem[i]);
		if(!(L.length-i-1==0)){
		printf("��������ʣ%d������\n",L.length-i-1);
		}else if(L.length-i-1==0){
		printf("��ʼ�����\n");
		}
	}
	printf("����������\n");
	Bubble(L.elem,L.length);
	printf("\n����Ҫ�����һ������\n");
	scanf("%d",&input);
	InsList(&L,1,input);
	Bubble(L.elem,L.length);
	output_L();
	printf("\n����Ҫɾ����һ������\n");
	scanf("%d",&input);
	DelList(&L,Locate(L,input),&input);
	output_L();
	printf("ȫ���������");
	return 0;
}
