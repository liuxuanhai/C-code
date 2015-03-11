//---------------------------------------------------------------------
//文件修改时间：2013年1月10号   系统：Win7 32位旗舰版 IDE：VS2010
//   作者：落叶化尘                     QQ：775904764
//   头文件名：五子棋类.h
//   主要功能：声明五子棋所用到的一些函数及变量，并初始化。
//   特殊说明：类的声明一般储存在头文件中，这是一种习惯。
//---------------------------------------------------------------------
class FiveChess
{
public:
	FiveChess():x(0),y(0),flag(0),Choice(0),Check(0),Check1(0),Select(true),ExWhile(true),ExWhile1(true),Continue(true){}  //构造函数初始化成员变量的值
	~FiveChess(){}                         
	void StartGame(int [][15],int [][15]);			//游戏开始
	void PrintBord(int *,int *,int [][15],int);     //落子函数，绘制棋盘
	void Empty(int [][15],int [][15]);				//清空棋盘
	void Retract(int &,int &,int &,int &,int [][15]); //悔棋
	int Position(int *,int *,int [][15]);			//判断坐标合法性
	int Win(int *,int *,int,int [][15]);			//判断胜利或者和棋
	int NextPlayer(int [][15]);						//判断该哪个玩家走了
	void Single(int [][15]);						//与AI对战
	void Double(int [][15]);						//双人对战
	void Robot(int *,int *,int *,int [][15]);		//AI落子主函数
	void Findscore(int &,int &);                    //寻找最高评分
	void ChessScore();                              //AI评分函数
	void ChessOne(int &,int &,int [][15]);          //电脑第一步随机落子
	void Victory(int);					            //胜利界面
	int  MainMenu();								//选择界面
	bool Introduce();								//游戏介绍
	bool Coder();								    //关于作者
	void Exit();								    //退出界面
	bool Continue;                                  //是否继续游戏
private:
	int x;                             //坐标
	int y;
	int flag;                          //标志
	int Sumchess;                      //棋子数统计
	bool Select;
	bool ExWhile;                      //退出循环条件
	bool ExWhile1;
	int Choice;
	int Check;                         //检测返回值用的
	int Check1;
};