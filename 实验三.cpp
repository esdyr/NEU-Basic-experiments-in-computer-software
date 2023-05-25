/*
 *ģ���ļ�����
 */
#include<iostream>
#include<malloc.h>
#include<string.h>
using namespace std ;

/*
 *�����ļ����ݽṹ
 */
typedef struct file
{
	char file_name[20] ;
	bool file_protect[3] ;
	bool open_file_protect[3] ; //�����ļ���ʱ��Ч
	int  read , write ; //����Ϊ��дָ��
	int  file_length ;
	struct file *next ;
} File ;

/*
 *�û����ļ���ӳ��
 */
typedef struct x_map
{
	char userName[20] ;
	File *file ;
	struct x_map *next ;
} Map ;

/*
 *�������ļ�Ŀ¼
 */
typedef struct mfd
{
	Map *head , *tail ;
} MFD ;

/*
 *���ļ�Ŀ¼
 */
typedef struct afd
{
	File *head , *tail ;
	int max_open ;
	int current_open ;
} AFD ;

/*
 *�����û��ĳ�ʼ��
 */
void initUser(MFD *mfd) ;

/*
 *����ϵͳ�û������
 */
void displayUser(MFD *mfd) ;

/*
 *�����û��Ĳ��ң��ҵ��򷵻��û�ӳ��ָ��
 */
Map * queryUser(char userName[] , MFD *mfd) ;

/*
 *�����ļ��Ĵ�������
 *�ɹ��򷵻�true �� ���򷵻�false
 */
bool createFile(Map *user , char file_name[] , bool file_protect[3] , int file_length) ;

/*
 *�����ļ�ɾ������
 */
bool deleteFile(Map *user , char file_name[] , AFD *afd) ;

/*
 *�����ļ��򿪲���
 */
bool openFile(Map *user , char file_name[] , AFD *afd , bool open_file_protect[]) ;

/*
 *���ж�����
 */
bool readFile(AFD *afd , char file_name[]) ;

/*
 *�����ļ���д����
 */
bool writeFile(AFD *afd , char file_name[]) ;

/*
 *�ر��ļ�
 */
bool closeFile(AFD *afd , char file_name[]) ;

/*
 *�����û��ļ�����ʾ
 */
void displayUserFile(Map *user) ;

/*
 *��ʾ�򿪵��ļ�
 */
void displayOpenFile(AFD *afd , Map *user) ;

/*
 *����������
 */
int main()
{
	MFD *mfd ;
	mfd = (MFD*)malloc(sizeof(MFD)) ;
	if(mfd == NULL)
	{
		exit(0) ;
	}
	mfd->head = mfd->tail = NULL ;
	initUser(mfd) ;
	displayUser(mfd) ;
	
	char userName[20] ;
	while(true)
	{
		cout<<"Please choose user to login : " ;
		cin>>userName ;
		Map *user ;
		user = queryUser(userName , mfd) ;
		if(user == NULL)
		{
			cout<<"No such user ! "<<endl;
		}
		else
		{
			//Ϊ�û���ʼ�����ļ�Ŀ¼
			AFD *afd ;
			afd = (AFD*)malloc(sizeof(AFD)) ;
			if(afd == NULL)
			{
				cout<<"The memory is not enough ! "<<endl ;
				exit(0) ;
			}
			afd->head = afd->tail = NULL ;
			afd->max_open = 5 ;
			afd->current_open = 0 ;
			
			char command[20] ;
			char file_name[20] ;
			bool file_protect[3] ;
			bool open_file_protect[3] ;
			int file_length ;
			while(true)
			{
				cout<<userName<<">>" ;
				cin>>command ;
				//����������в���
				if(strcmp(command , "create") == 0)
				{
					cout<<"Please file (file_name file_protect file_length) : " ;
					cin>>file_name>>file_protect[0]>>file_protect[1]>>file_protect[2]>>file_length ;
					createFile(user , file_name , file_protect , file_length) ;
					displayUserFile(user) ;
				}
				else if(strcmp(command , "delete") == 0)
				{
					cout<<"Please input the file's name you want to delete : " ;
					cin>>file_name ;
					deleteFile(user , file_name , afd) ;
					displayUserFile(user) ;
				}
				else if(strcmp(command , "open") == 0)
				{
					cout<<"Please input the file name you want to open : " ;
					cin>>file_name>>open_file_protect[0]>>open_file_protect[1]>>open_file_protect[2] ;
					openFile(user , file_name , afd , open_file_protect) ;
					displayOpenFile(afd , user) ;
				}
				else if(strcmp(command , "close") == 0)
				{
					cout<<"Please input the file you want to close : " ;
					cin>>file_name ;
					closeFile(afd , file_name) ;
					displayOpenFile(afd , user) ;
				}
				else if(strcmp(command , "read") == 0)
				{
					cout<<"Please input the file you want to read : " ;
					cin>>file_name ;
					readFile(afd , file_name) ;
					displayOpenFile(afd , user) ;
				}
				else if(strcmp(command , "write") == 0)
				{
					cout<<"Please input the file you want to write : " ;
					cin>>file_name ;
					writeFile(afd , file_name) ;
					displayOpenFile(afd , user) ;
				}
				else if(strcmp(command , "exit") == 0)
				{
					break ;
				}
				else
				{
					cout<<"No such command \""<< command <<"\""<<endl ;
				}
			}
		}
	}
	return 0 ;
}

void initUser(MFD *mfd)
{
	//��ʼ��ʮ����ͬ�û�
	for(int i = 1 ; i <= 10 ; i++)
	{
		Map *m ;
		m = (Map*)malloc(sizeof(Map)) ;
		if(m == NULL)
		{
			exit(0) ;
		}
		cout<<"Please input init user name : " ;
		cin>>m->userName ;
		m->file = NULL ;
		m->next = NULL ;
		if(mfd->head == NULL)
		{
			mfd->head = mfd->tail = m ;
		}
		else
		{
			mfd->tail->next = m ;
			mfd->tail = m ;
		}
	}
}

void displayUser(MFD *mfd)
{
	Map *m = NULL ;
	m = mfd->head;
	cout<<"user : " ;
	while(m)
	{
		cout<<m->userName<<" " ;
		m = m->next ;
	}
	cout<<endl ;
}

Map * queryUser(char userName[] , MFD *mfd)
{
	Map *m = NULL ;
	m = mfd->head ;
	while(m)
	{
		if(strcmp(userName , m->userName) == 0)
		{
			return m ;
		}
		m = m->next ;
	}
	return NULL ;
}

bool createFile(Map *user , char file_name[] , bool file_protect[3] , int file_length)
{
	File *file ;
	file = (File*)malloc(sizeof(File)) ;
	if(file == NULL)
	{
		return false ;
	}
	
	//�����ļ��ĳ�ʼ��
	strcpy(file->file_name , file_name) ;
	file->file_protect[0] = file_protect[0] ;
	file->file_protect[1] = file_protect[1] ;
	file->file_protect[2] = file_protect[2] ;
	file->file_length = file_length ;
	file->read = file->write = 0 ;
	file->next = NULL ;
	
	if(user->file == NULL)
	{
		user->file = file ;
	}
	else
	{
		File *op  , *preOp = NULL ;
		op = user->file ;
		//�����Ƿ����ͬ���ļ�
		while(op)
		{
			if(strcmp(op->file_name , file->file_name) == 0)
			{
				cout<<"The file name "<<file->file_name<<" is already exit ! "<<endl ;
				return false ;
			}
			preOp = op ;
			op = op->next ;
		}
		preOp->next = file ;
	}
}

void displayUserFile(Map *user)
{
	cout<<"The fileList of "<<user->userName<<endl ;
	File *file = NULL ;
	file = user->file ;
	while(file)
	{
		cout<<file->file_name<<" "<<file->file_protect[0]<<" "<<file->file_protect[1]<<" "<<file->file_protect[2]<<" "<<file->file_length<<endl ;
		file = file->next ;
	}
}

bool deleteFile(Map *user , char file_name[] , AFD *afd)
{
	File *file = NULL , *prefile = NULL , *temp ;
	file = afd->head ;
	//�ڴ��ļ��в���
	while(file)
	{
		if(strcmp(file_name , file->file_name) == 0)
		{
			cout<<"\""<<file_name<<"\" is open , please close it before ! \n" ;
			return false ;
		}
		file = file->next ;
	}
	file = user->file ;
	//���ļ��н��в���
	while(file)
	{
		if(strcmp(file_name , file->file_name) == 0)
		{
			if(file == user->file)
			{
				temp = file ;
				user->file = file->next ;
			}
			else
			{
				temp = file ;
				prefile->next = file->next ;
			}
			delete temp ;
			return true ;
		}
		prefile = file ;
		file = file->next ;
	}
	if(prefile->next == NULL)
	{
		cout<<"user "<<user->userName<<" has not the file \""<<file_name<<"\""<<endl;
	}
	return false ;
}

bool openFile(Map *user , char file_name[] , AFD *afd , bool open_file_protect[])
{
	File *file = NULL ;
	file = user->file ;
	while(file)
	{
		if(strcmp(file->file_name , file_name) == 0)
		{
			break ;
		}
		file = file->next ;
	}
	if(file)
	{
		File *xfile ;
		xfile = (File*)malloc(sizeof(File)) ;
		if(xfile == NULL)
		{
			return false ;
		}
		*xfile = *file ;
		//�����ļ���Ȩ�޽��д�Ȩ�޵ĸ�ֵ
		if(xfile->file_protect[0] >= open_file_protect[0])
		{
			xfile->open_file_protect[0] = open_file_protect[0] ;
		}
		else
		{
			cout<<"no read priority ! "<<endl;
			return false ;
		}
		if(xfile->file_protect[1] >= open_file_protect[1])
		{
			xfile->open_file_protect[1] = open_file_protect[1] ;
		}
		else
		{
			cout<<"no write priority ! "<<endl;
			return false ;
		}
		if(xfile->file_protect[2] >= open_file_protect[2])
		{
			xfile->open_file_protect[2] = open_file_protect[2] ;
		}
		else
		{
			cout<<"no excute priority ! "<<endl;
			return false ;
		}
		xfile->next = NULL ;
		if(afd->head == NULL)
		{
			afd->head = afd->tail = xfile ;
			afd->current_open += 1 ;
		}
		else if(afd->current_open < afd->max_open)
		{
			afd->tail->next = xfile ;
			afd->tail = xfile ;
			afd->current_open += 1 ;
		}
		else
		{
			cout<<"The open file is too many ! " <<endl ;
			return false ;
		}
	}
	else
	{
		cout<<"the "<<file_name<<" is not exit !"<<endl ;
		return false ;
	}
}

bool closeFile(AFD *afd , char file_name[])
{
	File *file = NULL  , *preFile = NULL  , *temp = NULL ;
	//�ڴ��ļ������н��в���
	file = afd->head ;
	while(file)
	{
		if(strcmp(file->file_name , file_name) == 0)
		{
			if(file == afd->head)
			{
				if(file == afd->tail)
				{
					temp = file ;
					afd->head = afd->tail = NULL ;
				}
				else
				{
					temp = file ;
					afd->head = file->next ;
				}
			}
			else if(file == afd->tail)
			{
				temp = file ;
				preFile->next = NULL ;
				afd->tail = preFile ;
			}
			else
			{
				temp =file ;
				preFile->next = file->next ;
			}
			delete temp ;
			return true ;
		}
		preFile = file ;
		file = file->next ;
	}
	cout<<"The file is not exit ! "<<endl ;
	return false ;
}

bool readFile(AFD *afd , char file_name[])
{
	File *file = NULL ;
	file = afd->head ;
	while(file)
	{
		if(strcmp(file->file_name , file_name) == 0)
		{
			if(file->open_file_protect[0])
			{
				file->read++ ;
				return true ;
			}
			else
			{
				cout<<"no read priority ! \n"<<endl ;
				return false ;
			}
		}
		file = file->next ;
	}
	cout<<"no such file ! "<<endl ;
	return false ;
}

bool writeFile(AFD *afd , char file_name[])
{
	File *file = NULL ;
	file = afd->head ;
	while(file)
	{
		if(strcmp(file->file_name , file_name) == 0)
		{
			if(file->open_file_protect[1])
			{
				file->write++ ;
				return true ;
			}
			else
			{
				cout<<"no write priority ! \n"<<endl ;
				return false ;
			}
		}
		file = file->next ;
	}
	cout<<"no such file ! "<<endl ;
	return false ;
}

void displayOpenFile(AFD *afd , Map *user)
{
	cout<<"The open file of "<<user->userName<<" : "<<endl ;
	File *file ;
	file = afd->head ;
	while(file)
	{
		cout<<file->file_name<<" "<<file->file_protect[0]<<" "<<file->file_protect[1]<<" "<<file->file_protect[2]<<" "<<file->file_length<<" " ;
		cout<<"readcout : "<<file->read<<" writecout : "<<file->write<<endl ;
		file = file->next ;
	}
}
