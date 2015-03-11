//--------------------------------------------------------------------------//
//                 简单五子棋（控制台版）代码[Ver2.1]
//     修复了AI越界的问题，简化评分函数，修复输赢判断函数的BUG。
//     AI评分函数规则有部分改变，代码也更加简练。
//     新增悔棋功能，仅与AI对战时可用，新增重新开始功能。
//     修复悔棋的一个小BUG，修复AI随机落子部分的定义错误。
//                 作者：落叶化尘     QQ：775904764
//--------------------------------------------------------------------------//
#include "五子棋.h"
#include <time.h>                                                  
#include <iostream>
using namespace std;                                                   
static const char ch[11][4]={"┌","┬","┐","├","┼","┤","└","┴","┘","○","●"};  //可供选用的字符，输出棋盘或者棋子用
static int Record[15][15]={0};             //记录棋子
static int Score[15][15]={0};              //评分
static int Sum=0,Renum=0;                 
int main()                                
{
    int Default[15][15]={ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,  //空棋盘
						  3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
						  3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
						  3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5, 
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
                          6,7,7,7,7,7,7,7,7,7,7,7,7,7,8 };
	int value[15][15]={0};      
	FiveChess Start;
	do
	{
	    Start.StartGame(value,Default);   //开始游戏
	}
	while (Start.Continue);        //若是要退出就修改这个值
	return 0;                       
}
//------------------------------开始游戏------------------------------------------//
void FiveChess::StartGame(int value[][15],int Default[][15])
{
	Empty(value,Default);         //初始化棋盘ad
	ExWhile=true;
	while(ExWhile)
	{
		Choice=MainMenu();        //调用主菜单，并把用户选择的值储存在Choice里                 
		switch(Choice)                       
	    {
	        case 1:flag=1;ExWhile=false;break;    //把标志设置为1，与AI对战
	    	case 2:flag=2;ExWhile=false;break;    //把标志设置为2，双人对战
			case 3:Select=Introduce();ExWhile=Select;Continue=false;break;     //游戏说明函数
	    	case 4:Select=Coder();ExWhile=Select;Continue=false;break;         //作者介绍函数
	    	case 5:Exit();ExWhile=false;Continue=false;break;                  //退出游戏函数
	    	default:cin.fail();cin.clear();cin.sync();cout<<"输出错误，请重新输入！\n";system("pause>nul 2>nul");ExWhile=true;break;  //其它
	    }
   	}
	if (flag==1)             //如果标志等于1，说明为单人游戏
	{
		Single(value);        
	}
   	else if (flag==2)		  //如果标志等于2，说明为双人游戏
	{
		Double(value);
	}
	flag=0;
}
//------------------------清空棋盘或初始化棋盘-----------------------------------//
void FiveChess::Empty(int value[][15],int Default[][15])       //清空棋盘
{
	for (int i=0;i<15;i++)             
	{
		for (int j=0;j<15;j++)
		{
		     value[i][j]=Default[i][j];
		}
	}
}
void FiveChess::Exit()             //退出游戏
{
	system("cls");
	cout<<"┌—————————————————————————┐\n";
	cout<<"│          感谢您使用：简单五子棋 Ver2.1           │\n";
	cout<<"│                                                  │\n";
	cout<<"│[游戏制作]：落叶化尘                              │\n";
	cout<<"│[联系Q Q ]: 775904764                             │\n";
	cout<<"│[联系邮箱]：lxhdjwg@126.com                       │\n";
	cout<<"│[简单说明]：游戏结束界面，谢谢您的使用！          │\n";
	cout<<"└—————————————————————————┘\n";
	cout<<"感谢您的使用，谢谢！按任意键退出游戏...\n";
	system("pause>nul 2>nul");          
}
bool FiveChess::Introduce()              //游戏介绍
{
	system("cls");
	cout<<"┌—————————————————————————┐\n";
	cout<<"│          简单五子棋 Ver2.1[游戏介绍界面]         │\n";
	cout<<"│                                                  │\n";
	cout<<"│[单人游戏]：玩家和AI（人工智能）对战，AI智商不高。│\n";
	cout<<"│                                                  │\n";
	cout<<"│[双人游戏]: 可以两个玩家一起对战，可能不是很方便。│\n";
	cout<<"│                                                  │\n";
	cout<<"│[游戏方法]：输入X Y坐标落子，输入双-1悔棋。       │\n";
	cout<<"│                                                  │\n";
	cout<<"│[特别提示]：若游戏中想突然退出，按Ctrl+C即可中断。│\n";
	cout<<"│                                                  │\n";
	cout<<"└—————————————————————————┘\n";
	cout<<"是否返回？[Y-返回 N-退出]：";
	char choice;
	cin>>choice;
	if (choice=='N'||choice=='n')
	{
		cout<<"感谢您的使用，谢谢！按任意键退出游戏...\n";
	    system("pause>nul 2>nul");      
		return false;
	}
	else
	{
		return true;
	}
}
bool FiveChess::Coder()                     //作者介绍              
{
	system("cls");
	cout<<"┌—————————————————————————┐\n";
	cout<<"│          简单五子棋 Ver2.1[作者介绍界面]         │\n";
	cout<<"│                                                  │\n";
	cout<<"│[游戏制作]：落叶化尘                              │\n";
	cout<<"│[联系Q Q ]: 775904764                             │\n";
	cout<<"│[联系邮箱]：lxhdjwg@126.com                       │\n";
	cout<<"│[简单介绍]：游戏制作简陋，还请见谅^_^！           │\n";
    cout<<"│[附加说明]：作者正在努力学习C++中，嘿嘿~          │\n";
  	cout<<"└—————————————————————————┘\n";
	cout<<"是否返回？[Y-返回 N-退出]：";
	char choice;
	cin>>choice;
	if (choice=='N'||choice=='n')
	{
		cout<<"感谢您的使用，谢谢！按任意键退出游戏...\n";
	    system("pause>nul 2>nul");             
		return false;                       
	}
	else
	{
		return true;
	}
}

//-------------------------------选择主菜单-----------------------------//
int FiveChess::MainMenu()                         
{
	system("cls");                                 //清屏
	system("title 五子棋游戏   By--落叶化尘   QQ:775904764");     //修改窗口标题
	system("color 3f");                            //定义窗口颜色
	system ("mode con cols=56 lines=20");          //设置窗口大小
	cout<<"┌—————————————————————————┐\n";
	cout<<"│                  简单五子棋 Ver2.1               │\n";
	cout<<"│[1]、单人游戏                                     │\n";
	cout<<"│                                                  │\n";
	cout<<"│[2]、双人游戏                                     │\n";
	cout<<"│                                                  │\n";
	cout<<"│[3]、游戏介绍                                     │\n";
	cout<<"│                                                  │\n";
	cout<<"│[4]、关于作者                                     │\n";
	cout<<"│                                                  │\n";
	cout<<"│[5]、退出                                         │\n";
	cout<<"└—————————————————————————┘\n";
	cout<<"请选择：";
	int select;
	cin>>select;
    return select;      //返回用户选择的值
}

//--------------------------------胜利界面--------------------------------//
void FiveChess::Victory(int Num)
{
	system ("mode con cols=56 lines=20");          //设置窗口大小
	system("cls");
	if (Num==1)
	{
		system("color 1f");
	    cout<<"┌—————————————————————————┐\n";
	    cout<<"│          恭喜玩家1[黑棋]获得胜利！               │\n";
		cout<<"│                                                  │\n";
		cout<<"│[胜利玩家]：玩家1                                 │\n";
		cout<<"│[所属棋子]: 黑色                                  │\n";
		cout<<"│[祝福话语]：不错哦^_^！恭喜您获得了胜利！         │\n";
		cout<<"│                                                  │\n";
		cout<<"└—————————————————————————┘\n";
	}
	else if (Num==2)
	{
		system("color 2f");
		cout<<"┌—————————————————————————┐\n";
		cout<<"│          恭喜玩家2[白棋]获得胜利！               │\n";
		cout<<"│                                                  │\n";
		cout<<"│[胜利玩家]：玩家2                                 │\n";
		cout<<"│[所属棋子]: 白色                                  │\n";
		cout<<"│[祝福话语]：恭喜您获得了胜利，再接再厉哈^_^！     │\n";
		cout<<"│                                                  │\n";
		cout<<"└—————————————————————————┘\n";
	}
	else if(Num==3)
	{
		system("color 3f");
		cout<<"┌—————————————————————————┐\n";
		cout<<"│                  恭喜您，获得了胜利              │\n";
		cout<<"│                                                  │\n";
		cout<<"│[胜利玩家]：自己                                  │\n";
		cout<<"│[所属棋子]: 黑色                                  │\n";
		cout<<"│[祝福话语]：不错哦，打败了AI，恭喜！              │\n";
		cout<<"│                                                  │\n";
		cout<<"└—————————————————————————┘\n";
	}
	else if(Num==4)
	{
		system("color 5f");
		cout<<"┌—————————————————————————┐\n";
		cout<<"│                  非常遗憾，您输了!               │\n";
		cout<<"│                                                  │\n";
		cout<<"│[胜利玩家]：AI（电脑）                            │\n";
		cout<<"│[所属棋子]: 白色                                  │\n";
		cout<<"│[祝福话语]：加油吧，下次一定要把AI打败哦!         │\n";
		cout<<"│                                                  │\n";
		cout<<"└—————————————————————————┘\n";
	}
	else
	{
		system("color 5f");
		cout<<"┌—————————————————————————┐\n";
		cout<<"│                  势均力敌——平局                │\n";
		cout<<"│                                                  │\n";
		cout<<"│[胜利玩家]：无[平局]                              │\n";
		cout<<"│[所属棋子]: 黑色或白色                            │\n";
		cout<<"│[祝福话语]：棋盘居然被走满了，不错不错~！         │\n";
		cout<<"│                                                  │\n";
		cout<<"└—————————————————————————┘\n";
	}
	cout<<"是否返回主界面？[Y-返回 N-退出]：";
	char choice;
	cin>>choice;
	if (choice=='N'||choice=='n')
	{
		cout<<"感谢您的使用，谢谢！按任意键退出游戏...\n";
	    system("pause>nul 2>nul");              
		Continue=false;
	}
	else
	{
		Continue=true;
	}
}

//----------------------------悔棋-------------------------------//
void FiveChess::Retract(int &x1,int &y1,int &x2,int &y2,int value[][15])
{
	if (Sum>=1)
	{
	    Sum--;
	}
	if ((x1==-1)&&(y1==-1)&&(x2==-1)&&(y2==-1))
	{
		cout<<"当前无法悔棋，棋盘上没有棋子!";
		system("pause>nul");
	}
	else if (Renum>=6)
	{
		cout<<"悔棋超过6次，为了公平，您不能再次悔棋!";
		system("pause>nul");
	}
	else
    {
		Renum++;
		if (x1==0&&y1==0){value[x1][y1]=0;Record[x1][y1]=0;}
		else if (x1==0&&y1==14){value[x1][y1]=2;Record[x1][y1]=0;}
		else if (x1==14&&y1==0){value[x1][y1]=6;Record[x1][y1]=0;}
		else if (x1==14&&y1==14){value[x1][y1]=8;Record[x1][y1]=0;}
		else if (x1==14&&(y1>0&&y1<14)){value[x1][y1]=7;Record[x1][y1]=0;}
		else if (y1==14&&(x1>0&&x1<14)){value[x1][y1]=5;Record[x1][y1]=0;}
		else if (x1==0&&(y1>0&&y1<14)){value[x1][y1]=1;Record[x1][y1]=0;}
		else if (y1==0&&(x1>0&&x1<14)){value[x1][y1]=3;Record[x1][y1]=0;}
		else {value[x1][y1]=4;Record[x1][y1]=0;}

		if (x2==0&&y2==0){value[x2][y2]=0;Record[x2][y2]=0;}
		else if (x2==0&&y2==14){value[x2][y2]=2;Record[x2][y2]=0;}
		else if (x2==14&&y2==0){value[x2][y2]=6;Record[x2][y2]=0;}
		else if (x2==14&&y2==14){value[x2][y2]=8;Record[x2][y2]=0;}
		else if (x2==14&&(y2>0&&y2<14)){value[x2][y2]=7;Record[x2][y2]=0;}
		else if (y2==14&&(x2>0&&x2<14)){value[x1][y2]=5;Record[x2][y2]=0;}
		else if (x2==0&&(y2>0&&y2<14)){value[x2][y2]=1;Record[x2][y2]=0;}
		else if (y2==0&&(x2>0&&x2<14)){value[x2][y2]=3;Record[x2][y2]=0;}
		else {value[x2][y2]=4;Record[x2][y2]=0;}
		cout<<"每盘最多允许悔棋6次,且最多只能回到上一步!";
		system("pause>nul");
	}
}
//-----------------------------判断用户输入的坐标合法性-------------------------//
int FiveChess::Position(int *x,int *y,int value[][15])            
{              
	if (cin.fail()||*x<0||*x>=15||*y<0||*y>=15)  
	{
		cin.clear();   
                cin.sync();   
		return 1;      //返回1表示不在范围内或者输入的不是数字
	}
    	else if (value[*x][*y]==9||value[*x][*y]==10)
	{
		return 2;           //存在棋子
	}
	else
	{
	    return 0;           //返回 0 表示 坐标正常
    }
}

//---------------------------判断该哪个玩家先走----------------------------//
int FiveChess::NextPlayer(int value[][15])    
{
	int i,j;
	int player1=0,player2=0;           
	for (i=0;i<15;i++)
	{
		for (j=0;j<15;j++)
		{
			if (value[i][j]==10)
			{
				player1++;               //统计棋盘上面黑子的个数
			}
			else if (value[i][j]==9)
			{
				player2++;               //统计棋盘上白子的个数
			}
		}
	}
	if (player1>player2||player1<player2) 
	{
		return 2;                          //该玩家2走了(白子)
	}
	else                                   
	{
		return 1;                          //该玩家1走了（黑子）
	}
}

//---------------------------判断棋子落在这点，是否胜利或者平局-----------------------------------------//
int FiveChess::Win(int *x,int *y,int ChessNum,int value[][15])   
{                                       
	int i,j,k;             //返回-1：平局     返回0：没有谁胜利     返回1：传递过来ChessNum号的那一方胜利
    int number=0;
	Sumchess=0;            
	for (i=-1;i<=1;i++)
	{
		for (j=-1;j<=1;j++)      //循环8次，分别计算这个点的8个方向是否构成5连
		{
			if (i!=0 || j!=0)    //i或者j等于0，不就代表的是ChessNum的值嘛
			{
				for (k=1;k<5;k++)  //循环4次
				{                              //这是不越界判断                                     //存在棋子数目+1
				    if(*x+k*i>=0 &&*x+k*i<=14 && *y+k*j>=0 &&*y+k*j<=14 && value[*x+k*i][*y+k*j]==ChessNum){number++;}   //如果这个点有棋子
                    else {break;}      //没有棋子就跳出
				}
				for (k=-1;k>-5;k--)  //与上面相对的方向的判断
				{                         
					if(*x+k*i>=0 &&*x+k*i<=14 && *y+k*j>=0 &&*y+k*j<=14 && value[*x+k*i][*y+k*j]==ChessNum){number++;}   
                    else {break;}      //没有棋子就跳出
				}
				if(number>=4)          //如果>=4就说明5连了，返回ChessNum表示传递过来的这个玩家得下子点能构成5个，胜利了 
                {
                     return 1;  
                }
                else
                {
                     number=0;          //清空统计 
                }

			}
		}
	}
	for (i=0;i<15;i++)                   //棋盘是否满了
	{
		for(j=0;j<15;j++)
		{
			if (value[i][j]==9||value[i][j]==10)
			{
				Sumchess++;   //统计黑子和白子的总个数
			}
		}
	}
	if (Sumchess>=225)
	{
	   return -1;                 //棋盘满了
	}
	else
	{
        return  0;               //没胜利也没和棋
	}
}

//---------------------------------绘制棋盘、落子函数-----------------------------------------//
void FiveChess::PrintBord(int *x,int *y,int value[][15],int player)    
{
	system("cls");  
	int i,j;
	if (player==1)                   
	{
	    value[*x][*y]=9;              //黑棋
	}
	else if (player==2)              
	{
	    value[*x][*y]=10;           //白棋
	}
	cout<<"     0 1 2 3 4 5 6 7 8 9 10 1 2 3 4\n";     //输出参考坐标
	for (i=0;i<15;i++)              
	{
		if(i!=0)
		{
        		cout<<"    "<<i%10;         
		}
		else
		{
			cout<<"    0";
		}
		for (j=0;j<15;j++)           
		{
           		cout<<ch[value[i][j]];    
		}
		cout<<"\n";                  
	 }
}

//------------------------------------双人对战-----------------------------//
void FiveChess::Double(int value[][15])   
{
	cout<<"您选择了双人对战模式，请按任意键继续！";
	system("pause>nul 2>nul");        
	system("cls");
	system ("mode con cols=43 lines=20");   
	system("color 3f");
	system("title 五子棋-双人对战模式");
	PrintBord(&x,&y,value,-1);  //先绘制个空棋盘
	ExWhile=true;        //退出循环用的
	memset(Record,0,sizeof(Record));   //先把记录落子的数组清0
	while(ExWhile)
	{
		int play=NextPlayer(value); //先得到该哪个玩家走棋了
		cout<<"请(玩家"<<play<<")输入坐标[用空格隔开]：";
		cin>>x>>y;
		Check=Position(&x,&y,value);   //检测坐标合法性
		if (Check==0)                  //坐标没问题
		{ 
		    PrintBord(&x,&y,value,play); //再绘制落子棋盘
			Record[x][y]=play;           //记录这个点，1表示黑子,2表示白子
			cout<<"玩家["<<play<<"]的棋子落在了：[X:"<<x<<"]  [Y:"<<y<<"]\n";
			Check1=Win(&x,&y,play,Record);  //检测是否有一方胜利或者和棋
            if (Check1==-1)          //和棋
		    {
				cout<<"游戏棋盘满啦，还没分出胜负，都很厉害哈!\n";
				cout<<"本次游戏结束，按任意键继续...";
			    system("pause>nul 2>nul");  
				Victory(5);                //跳转胜利界面
				ExWhile=false;             
			}
			else if(Check1==1)       //当前玩家paly胜利
			{
				cout<<"恭喜[玩家"<<play<<"]获得胜利！\n";
				cout<<"本次游戏结束，按任意键继续...";
			    system("pause>nul 2>nul");
				Victory(play);           //跳转胜利界面
				ExWhile=false;       
			}
			else                     //没谁胜利
			{
				ExWhile=true;            //不退出循环
			}
		}
		else if(Check==1)
		{
			cout<<"输入范围错误，请重新输入！\n";
			ExWhile=true;
		}
		else
		{
			cout<<"您输入的坐标已经存在棋子，请重新输入！\n";
			ExWhile=true;
		}
	}
}

//-------------------------------与AI对战------------------------------//
void FiveChess::Single(int value[][15])                        
{
	cout<<"您选择了与AI对战的模式，请按任意键继续！";
	system("pause>nul 2>nul");       
	system("cls");
	system ("mode con cols=43 lines=20");   
	system("color 3f");
	system("title 五子棋-与AI的对战模式");
	PrintBord(&x,&y,value,-1);                     //先绘制个空棋盘
	ExWhile=true;                                  //退出循环用的
	Sum=0,Renum=0;                                    
	memset(Record,0,sizeof(Record));               //先把记录落子的数组清0
	int x1=-1,y1=-1,x2=-1,y2=-1;
	while(ExWhile)
	{
		    ExWhile1=true;
			cout<<"请[玩家]输入坐标[双(-1)为悔棋]：";
		    cin>>x>>y;
			Check=Position(&x,&y,value);
			if ((x==-1)&&(y==-1))
			{
				Retract(x1,y1,x2,y2,value);
				PrintBord(&x,&y,value,-1);   //绘制落子棋盘
				ExWhile=true;
			}
		    else if (Check==0)          //坐标没问题
		    {
				value[x][y]=9;
				Record[x][y]=1;                 //记录这个点，1表示黑子,2表示白子
				x1=x;y1=y;                      //记录当前坐标悔棋用
				Sum++;
				if (Win(&x,&y,1,Record)==0)
			    { 
					Robot(&x,&y,&Sum,value);    //调用AI函数
					PrintBord(&x,&y,value,2);   //绘制落子棋盘
					x2=x;y2=y;                  //记录当前坐标悔棋用
					cout<<"玩家棋子数:"<<Sum<<" 电脑的棋子落在了[X:"<<x<<"] [Y:"<<y<<"]\n";
					//cout<<"玩家坐标："<<x1<<" "<<y1<<"电脑坐标:"<<x2<<"  "<<y2<<endl;
					if (Win(&x,&y,2,Record)==1)
					{
						cout<<"非常遗憾，您输了，AI获得了胜利！\n";
						cout<<"本次游戏结束，按任意键继续...";
						system("pause>nul 2>nul");
						Victory(4);                   //跳转胜利界面
						ExWhile=false;
					}
					else if(Win(&x,&y,2,Record)==-1)
					{
						cout<<"游戏棋盘满啦，还没分出胜负，都很厉害哈!\n";
						cout<<"本次游戏结束，按任意键继续...";
						system("pause>nul 2>nul");
						Victory(5);                    //跳转平局界面
						ExWhile=false;
					}
					else {ExWhile=true;}
				}
				else if(Win(&x,&y,1,Record)==1)
				{
					PrintBord(&x,&y,value,-1);       //绘制棋盘
					cout<<"恭喜[玩家]获得胜利！\n";
				    cout<<"本次游戏结束，按任意键继续...";
			        system("pause>nul 2>nul");
				    Victory(3);              //跳转胜利界面
					ExWhile=false;
				}
				else if(Win(&x,&y,1,Record)==-1)
				{
					PrintBord(&x,&y,value,-1);       //绘制棋盘
					cout<<"游戏棋盘满啦，还没分出胜负，都很厉害哈!\n";
				    cout<<"本次游戏结束，按任意键继续...";
			        system("pause>nul 2>nul");
				    Victory(5);                    //跳转平局界面
					ExWhile=false;
				}
		    }
		    else if(Check==1)
		    {
			    cout<<"输入范围错误，请重新输入！\n";
		    }
		    else
		    {
			    cout<<"您输入的坐标已经存在棋子，请重新输入！\n";
		    }
	}
}

//-----------------------------电脑落子函数-------------------------------//
void FiveChess::Robot(int *x,int *y,int *Sum,int value[][15])  
{
	ExWhile1=true;
	if (*Sum==1)                
	{
		while(ExWhile1)
		{
		   ChessOne(*x,*y,value);
		   if (Position(x,y,value)==0){ExWhile1=false;}
		}
		Record[*x][*y]=2;          //记录这个点
	}
	else                             //从第2步开始，使用评分系统
	{
	    Findscore(*x,*y);             
	}
}

//-----------------------------查找评分最高的坐标-------------------------//
void FiveChess::Findscore(int &x,int &y)           
{
	srand( (unsigned)time( NULL ) );         
	int i,j,x1,x2,y1,y2,lx;
	int Max=0;
	ChessScore();                   //调用评分函数
	for (i=0;i<15;i++)
	{
		for (j=0;j<15;j++)
		{
			if(Score[i][j]>Max)
			{
				Max=Score[i][j];          //获取所有点中，评分最高的
				x1=i;
				y1=j;
			}
		}
	}
	x2=x1;y2=y1;
	for (i=0;i<15;i++)                   //可能的话，有评分相同的多个点
	{
		for (j=0;j<15;j++)
		{
	        if(Score[i][j]==Max&&i!=x2&&j!=y2)    //在这么多个相同分数的点中，随机找一个
			{
				lx=rand()%10;
				if (lx<5)
				{
			        x2=i,y2=j;
					break;
				}
			}
		}
	}
	if (x2!=x1 || y2!=y1)    //棋盘上有2个最高分
	{
		lx=rand()%10;            //随机一个^_^
		if (lx>6)
		{
			x=x1,y=y1;
		}
		else
		{
			x=x2,y=y2;
		}
	}
	else                  //棋盘上只有一个最高分
	{
	   x=x1,y=y1;
	}
	Max=0;                 //清空最大值
	Record[x][y]=2;          //记录这个点
}

//------------------------------玩家走第1步时的落子-------------------------------// 
inline void FiveChess::ChessOne(int &x,int &y,int value[][15])     
{
	int i,j;
	srand( (unsigned)time( NULL ) );            //随机数随着时间的改变而改变
	for (i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			    if (value[i][j]==9)             //如果找到了玩家的棋子，在它的8个方的任意一点落子
			    {
				        int lx=rand()%7;       
				        if(lx==0)                
				        {
							x=i+1;y=j+1;
							if (Position(&x,&y,value)==0){break;}
				        }
				        else if(lx==1)
				        {
							x=i+1;y=j-1;
							if (Position(&x,&y,value)==0){break;}
				        }
				        else if(lx==2)
				        {
							x=i-1;y=j-1;
							if (Position(&x,&y,value)==0){break;}
				        }
				        else if(lx==3)
				        {
							x=i-1;y=j+1;
							if (Position(&x,&y,value)==0){break;}
				        }
						else if(lx==4)
				        {
							x=i-1;y=j;                             //上
							if (Position(&x,&y,value)==0){break;}
				        }
						else if(lx==5)
				        {
							x=i;y=j-1;                             //左
							if (Position(&x,&y,value)==0){break;}
				        }
						else if(lx==6)
				        {
							x=i;y=j+1;                            //右
							if (Position(&x,&y,value)==0){break;}
				        }
						else
				        {
							x=i+1;y=j;                            //下
							if (Position(&x,&y,value)==0){break;}
				        }
                 }
		   }
	  }
}
//-----------------------------------AI评分函数---------------------------------------//
void FiveChess::ChessScore()    
{
      int x,y,i,j,k;				    //循环变量
	  int number1=0,number2=0;			//number用来统计玩家或电脑棋子连成个数
	  int empty=0;				        //empty用来统计空点个数
      memset(Score,0,sizeof(Score));    //把评分数组先清零
      for(x=0;x<15;x++)
	  {
          for(y=0;y<15;y++)      
		  {
              if(Record[x][y]==0)   //如果这个点为空 
			  {
                  for(i=-1;i<=1;i++)
				  {
					  for(j=-1;j<=1;j++)  //判断8个方向 
					 {
						 if(i!=0 || j!=0)  //若是都为0的话，那不就是原坐标嘛
						 {
							 //-------------------------------------对玩家落点评分---------------------------------------//
						      for(k=1;i<=4;k++)          //循环4次
							  {              //这点没越界                              //且这点存在黑子（玩家）
                                  if(x+k*i>=0 && x+k*i<=14 && y+k*j>=0 && y+k*j<=14 && Record[x+k*i][y+k*j]==1 ){number1++;}
								  else if(Record[x+k*i][y+k*j]==0){empty++;break;}     //这点是个空点，+1后退出
								  else {break;}         //否则是墙或者对方的棋子了 
							  }                    
							  for(k=-1;k>=-4;k--)      //向它的相反方向判断 
							  {            //这点没越界                              //且这点存在黑子（玩家）
							      if(x+k*i>=0 && x+k*i<=14 && y+k*j>=0 && y+k*j<=14 && Record[x+k*i][y+k*j]==1 ){number1++;}
								  else if(Record[x+k*i][y+k*j]==0){empty++;break;}    //同上条
								  else {break;}           
                              } 
							  if(number2==1)     {Score[x][y]+=1;}  //2个棋子   
                              else if(number1==2)                   //3个棋子 
                              {
                                    if(empty==1)       {Score[x][y]+=5;}   //有一个空点+5分     //死3       
                                    else if(empty==2)  {Score[x][y]+=10;}  //有两个空点+10分    //活3
                              }
                              else if(number1==3)   //4个棋子 
                              {
                                    if(empty==1)      {Score[x][y]+=20;}    //有一个空点+20分   //死4 
                                    else if(empty==2) {Score[x][y]+=100;}   //有2个空点+100分   //活4
                              }
							  else if(number1>=4)     {Score[x][y]+=1000;}   //对方有5个棋子，分数要高点，先堵

                              empty=0;        //统计空点个数的变量清零 

                             //---------------------------------------对电脑落点评分---------------------------------------//
							 for(k=1;i<=4;k++)  //循环4次
							 {         //这点没越界                              //且这点存在白子（电脑）
                                  if(x+k*i>=0 && x+k*i<=14 && y+k*j>=0 && y+k*j<=14 && Record[x+k*i][y+k*j]==2 ){number2++;}
								  else if(Record[x+k*i][y+k*j]==0){empty++;break;}  //空点
								  else {break;}        
							 }                    
							 for(k=-1;k>=-4;k--)      //向它的相反方向判断 
							 {
							      if(x+k*i>=0 && x+k*i<=14 && y+k*j>=0 && y+k*j<=14 && Record[x+k*i][y+k*j]==2 ){number2++;}
								  else if(Record[x+k*i][y+k*j]==0){empty++;break;}  
								  else {break;}           //这里顶上判断玩家的都做解释了，不再介绍
                             }
							 if (number2==0)         {Score[x][y]+=1;}  //1个棋子
							 else if(number2==1)     {Score[x][y]+=2;}  //2个棋子    
							 else if(number2==2)       //3个棋子
							 {
								  if(empty==1)       {Score[x][y]+=8;}   //死3
								  else if(empty==2)  {Score[x][y]+=30;}  //活3 
							 }
							 else if(number2==3)       //4个棋子
							 {
								  if(empty==1)       {Score[x][y]+=50;}    //死4
								  else if(empty==2)  {Score[x][y]+=200;}   //活4
						     }
							 else if(number2>=4)     {Score[x][y]+=10000;}  //自己落在这点能形成5个，也就能胜利了，分数最高
							 number1=0;         
						     number2=0;          //清零，以便下次重新统计
                             empty=0;
					     }
				     }
                 }
             }
		 }
     } 
}