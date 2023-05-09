/*
	计算机软件基础实验1——线性表的排序与查找

	by张世杰 20215068

*/

#include<stdio.h>
#define ElemType int
#define maxsize 15 //线性表肯定达到的最大长
#define OK 1
#define ERROR 0
typedef struct //结构体
{
	ElemType elem[maxsize];
	int length;
}SeqList;
SeqList L;
int  Locate(SeqList L,ElemType x)//查找
{
	int i = 1;
	while((i<=L.length)&&(L.elem[i]!=x))
		i++;
	if(i<=L.length)   return(i);
	else              return(-1);
}
int InsList(SeqList*L,int i,ElemType x)//插入
{
	int k;
	if ((i < 1) || (i>L->length+1))
	{
		printf("插入位置错误");
		return(ERROR);
	}
	if(L->length>=maxsize-1)
	{
		printf("表已满无法插入");
		return(ERROR);
	}
	for(k=L->length;k>=i;k--)//从最后一个往前移
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
		printf("删除位置不合法！");
		return(ERROR);
	}
	*e=L->elem[i];
	for(k=i;k<=L->length-1;k++)
		L->elem[k]=L->elem[k+1];
	L->length--;
	return(OK);
}
void Bubble(int num[],int n){   //冒泡排序
	int flag=1;
	int a=0;
	for(int i = 0;i < n-1;i++){
		flag=0;
		for(int j = 0;j<n-1;j++){
			if(num[j]>num[j+1]){
				a = num[j];
				num[j]=num[j+1];    //与更大的数进行置换
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
	printf("程序启动\n请输入%d个整数用于初始化线性表\n",L.length);
	for(int i=0;i < L.length;i++){
		scanf("%d",&L.elem[i]);
		if(!(L.length-i-1==0)){
		printf("继续，还剩%d个整数\n",L.length-i-1);
		}else if(L.length-i-1==0){
		printf("初始化完成\n");
		}
	}
	printf("排序结果如下\n");
	Bubble(L.elem,L.length);
	printf("\n输入要插入的一个整数\n");
	scanf("%d",&input);
	InsList(&L,1,input);
	Bubble(L.elem,L.length);
	output_L();
	printf("\n输入要删除的一个整数\n");
	scanf("%d",&input);
	DelList(&L,Locate(L,input),&input);
	output_L();
	printf("全部任务完成");
	return 0;
}
