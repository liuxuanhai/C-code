#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
int GameOver=0;

struct Body//蛇身（链表结构）
{
	int x,y;//蛇身结点坐标
	Body *next;//下一个结点
};

void SetPos(int i,int j)//设定光标位置
{
	COORD pos={i-1,j-1};//坐标变量
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);//获取输出句柄
    SetConsoleCursorPosition(Out,pos);//设定光标位置
}

class Sneak//贪吃蛇类
{
    private:
		Body *head;//蛇头指针
		int Direction;//移动方向。1,2,3,4对应上左下右
		int Count;//蛇长
        int Speed;//速度（等级）
		int FoodExist;//食物存在标记
		int Food_x;//食物X坐标
		int Food_y;//食物Y坐标
    public:
		Sneak(int a=3,int b=4,int c=1,int d=0)//构造函数
		{ 
			  FoodExist=d;//起始不存在食物
			  Body *temp1,*temp2;
              head=new(Body);//申请起始蛇身3节
			  head->x=4;
			  head->y=2;
			  
			  temp1=new(Body);
			  temp1->x=3;
			  temp1->y=2;
			  
			  temp2=new(Body);
			  temp2->x=2;
			  temp2->y=2;

			  head->next=temp1;
			  temp1->next=temp2;
			  temp2->next=NULL;

			  Direction=b;//方向为右
			  Count=a;//长为3
			  Speed=c;//等级1
		}
		void Map();//画界面函数
		void Paint();//画蛇身函数
		void Food();//生成食物
		int Over();//判断游戏是否结束
		void Gaming();//游戏进程函数
		void Move();//移动
};

void Sneak::Map()//使用
{
	int i;
	for(i=1;i<=50;i++)
	{
		SetPos(i,1);
		cout<<"-";
	}
	for(i=2;i<=25;i++)
	{
		SetPos(1,i);
		cout<<"|";
		SetPos(50,i);
		cout<<"|";
	}
	for(i=1;i<=50;i++)
	{
		SetPos(i,25);
		cout<<"-";
	}
	SetPos(54,3);
	cout<<"贪吃蛇";
	SetPos(54,5);
	cout<<"长度:"<<Count;
	SetPos(54,7);
	cout<<"LEVEL:"<<Speed;
}

void Sneak::Food()
{
	Body *p;
	int InBody=0;	//判断食物是否产生在蛇体内
	srand((int)time(0));//用系统时间来做随机数种子
	while(1)
	{
	    Food_x=rand()%48+2;//随机出食物的坐标
	    Food_y=rand()%23+2;
	    p=head;
	    while(p!=NULL)//判断食物是否产生在蛇体内
	    {
		    if(p->x==Food_x&&p->y==Food_y)
			{
				InBody=1;
				break;
			}
			p=p->next;
		}
		if(InBody==0)//食物不在蛇身。生成成功
			break;
		InBody=0;
	}
}

int Sneak::Over()
{
	Body *p;
	p=head;
	if((head->x)>=50||(head->x)<=1||(head->y)<=1||(head->y)>=25)//是否撞到边缘
		return 1;
	p=head->next;
	while(p!=NULL)//是否撞到蛇身
	{
		if((head->x==p->x)&&(head->y==p->y))
			return 1;
		p=p->next;
	}
	return 0;
}

void Sneak::Paint()
{
	Body *p;
	p=head;
	while(p!=NULL)
	{
		SetPos(p->x,p->y);
		cout<<"*";
		p=p->next;
	}
	SetPos(Food_x,Food_y);
	cout<<"*";
}

void Sneak::Move()
{
    Body *New;
	New=new(Body);//新的蛇身结点
	if(Direction==1)//确定新蛇头的坐标	
	{
         New->x=head->x;
		 New->y=head->y-1;
		 New->next=head;
		 head=New;
	}
	if(Direction==2)
	{
         New->x=head->x-1;
		 New->y=head->y;
		 New->next=head;
		 head=New;
	}
	if(Direction==3)
	{
         New->x=head->x;
		 New->y=head->y+1;
		 New->next=head;
		 head=New;
	}
	if(Direction==4)
	{
         New->x=head->x+1;
		 New->y=head->y;
		 New->next=head;
		 head=New;
	}
}

void Sneak::Gaming()
{
	system("cls");//刷新屏幕
	char x;
	Body *p;
    Map();//画界面的先
    Paint();//再画蛇身
    while(1)
	{
		if(_kbhit())//_kbhit()判断是否有键盘操作
		{
			x=_getch();//重缓冲区读出一个字符赋给x
			if((x=='W'||x=='w')&&Direction!=3)//改变蛇的方向（不可以是反方向）
				Direction=1;
			if((x=='S'||x=='s')&&Direction!=1)
				Direction=3;
			if((x=='A'||x=='a')&&Direction!=4)
				Direction=2;
			if((x=='D'||x=='d')&&Direction!=2)
				Direction=4;
			while(_kbhit())//读掉这之后所有的键盘输入
				_getch();
		}
		if(FoodExist==0)//如果食物被吃了或刚开始游戏，要生成新的食物
		{
		     Food();
			 FoodExist=1;
		}
		Move();//移动蛇
		if(head->x==Food_x&&head->y==Food_y)//如果蛇吃到了食物
		{
		   FoodExist=0;
		   Count++;//蛇身+1
		   SetPos(54,5);
	       cout<<"长度:"<<Count;//改变界面信息
		   if(Count%10==0)//每十个蛇身升一级
		   {
			  Speed++;
			  SetPos(54,7);
	          cout<<"LEVEL:"<<Speed;
		   }
		   if(Speed==10)//最高等级达成。退出游戏
			   break;
		}
		Paint();//画新的蛇身
		if(FoodExist==1)//如果没有吃到食物，需要删除蛇尾。
		{
			p=head;
			while((p->next)->next!=NULL)
		       p=p->next;
			SetPos(p->next->x,p->next->y);
            cout<<" ";
			delete(p->next);
            p->next=NULL;
		}
		if(Over())//判断是否游戏结束
			break;
		Sleep(500-Speed*50);//等待，具体时间和等级有关
	}
	system("cls");
	if(Speed==10)//通关
	{
		SetPos(25,25);
		cout<<"碉堡-_-||你通关了"<<endl;
		system("pause");
	}
	else//失败
	{
		SetPos(25,10);
		cout<<"-0- ~~你挂了，最终长度为 "<<Count<<endl;
		system("pause");
	}
}
int main()
{
	Sneak game;
	system("cls");
	cout<<"*****************************************************"<<endl;
	cout<<"*                        贪吃蛇                     *"<<endl;
	cout<<"*****************************************************"<<endl;
	cout<<"*                说明                               *"<<endl;
	cout<<"*            W,A,S,D控制移动                        *"<<endl;
	cout<<"*       每10节蛇身升一级，并提高速度，10级通关      *"<<endl;
	cout<<"*****************************************************"<<endl;
	cout<<"*      何某人制作，百度ID：HapHapYear               *"<<endl;
	cout<<"*********         任意键开始   **********************"<<endl;
    _getch();
	game.Gaming();
	return 0;
}