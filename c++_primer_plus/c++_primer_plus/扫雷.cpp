#include <graphics.h> 
#include <stdlib.h> 
#include <dos.h> 
#define LEFTPRESS 0xff01 
#define LEFTCLICK 0xff10 
#define LEFTDRAG 0xff19 
#define MOUSEMOVE 0xff08 
int num[10][10];/*范围*/ 
int p[10][10];/*统计雷的数组*/ 
int loop;/*重新来的标志*/ 
int again=0;/*是否重来的变量*/ 
int scorenum;/*一开始统计有几个雷*/ 
char score[3];/*输出一共有几个地雷*/ 
int Keystate; 
int MouseExist; 
int MouseButton; 
int MouseX; 
int MouseY; 
/*鼠标光标形状定义*/ 
typedef struct 
  { 
   unsigned int shape[32]; 
   char hotx; 
   char hoty; 
  }SHAPE; 

/*箭头型*/ 
SHAPE ARROW={ 
      { 
       0x3fff,0x1fff,0x0fff,0x07ff, 
       0x03ff,0x01ff,0x00ff,0x007f, 
       0x003f,0x00ff,0x01ff,0x10ff, 
       0x30ff,0xf87f,0xf87f,0xfc3f, 
       0x0000,0x7c00,0x6000,0x7000, 
       0x7800,0x7c00,0x7e00,0x7f00, 
       0x7f80,0x7e00,0x7c00,0x4600, 
       0x0600,0x0300,0x0300,0x0180 
      }, 
      0,0, 
     }; 

/*鼠标光标显示*/ 
void MouseOn() 
  { 
   _AX=0x01; 
   geninterrupt(0x33); 
  } 

/*鼠标光标掩示*/ 
void MouseOff()/*鼠标光标隐藏*/ 
  { 
   _AX=0x02; 
   geninterrupt(0x33); 
  } 
void MouseSetXY(int x,int y)/*设置当前位置*/ 
  { 
   _CX=x; 
   _DX=y; 
   _AX=0x04; 
   geninterrupt(0x33); 
  } 
int LeftPress()/*左键按下*/ 
  { 
   _AX=0x03; 
   geninterrupt(0x33); 
   return(_BX&1); 
  } 
void MouseGetXY()/*得到当前位置*/ 
  { 
   _AX=0x03; 
   geninterrupt(0x33); 
   MouseX=_CX; 
   MouseY=_DX; 
  } 
 begain()/*游戏开始画面*/ 
{ 
 int i,j; 
 loop: cleardevice(); 
 MouseOn(); 
 MouseSetXY(180,30); 
 MouseX=180; 
 MouseY=30; 
 scorenum=0; 
 setfillstyle(SOLID_FILL,7); 
 bar(190,60,390,290); 
 setfillstyle(SOLID_FILL,8); 
 for(i=100;i<300;i+=20)/*画格子*/ 
  for(j=200;j<400;j+=20) 
   bar(j-8,i+8,j+8,i-8); 
 setcolor(7); 
 setfillstyle(SOLID_FILL,YELLOW);/*画脸*/ 
 fillellipse(290,75,10,10); 
 setcolor(YELLOW); 
 setfillstyle(SOLID_FILL,0); 
  fillellipse(285,75,2,2); 
  fillellipse(295,75,2,2); 
 setcolor(0); 
  bar(287,80,293,81); 
 randomize(); 
 for(i=0;i<10;i++) 
  for(j=0;j<10;j++) 
   { 
   num[i][j]=random(7)+10;/*用10代表地雷算了*/ 
   if(num[i][j]==10) 
    scorenum++; 
   } 
 sprintf(score,"%d",scorenum); 
 setcolor(1); 
 settextstyle(0,0,2); 
 outtextxy(210,70,score); 
 scorenum=100-scorenum;/*为了后面判断胜利*/ 
} 
gameove()/*游戏结束画面*/ 
{ 
 int i,j; 
 setcolor(0); 
 for(i=0;i<10;i++) 
  for(j=0;j<10;j++) 
   if(num[i][j]==10)/*是地雷的就显示出来*/ 
    { 
     setfillstyle(SOLID_FILL,RED); 
      bar(200+j*20-8,100+i*20-8,200+j*20+8,100+i*20+8); 
      setfillstyle(SOLID_FILL,0); 
      fillellipse(200+j*20,100+i*20,7,7); 
    } 
} 
int tongji(int i,int j)/*计算有几个雷*/ 
{ 
 int x=0;/*10代表地雷*/ 
 if(i==0&&j==0) 
  { 
  if(num[0][1]==10) 
  x++; 
  if(num[1][0]==10) 
  x++; 
  if(num[1][1]==10) 
  x++; 
  } 
 else if(i==0&&j==9) 
 { 
  if(num[0][8]==10) 
  x++; 
  if(num[1][9]==10) 
  x++; 
  if(num[1][8]==10)  
  x++; 
 } 
 else if(i==9&&j==0) 
 { 
  if(num[8][0]==10) 
  x++; 
  if(num[9][1]==10) 
  x++; 
  if(num[8][1]==10) 
  x++; 
 } 
 else if(i==9&&j==9) 
 { 
  if(num[9][8]==10) 
  x++; 
  if(num[8][9]==10) 
  x++; 
  if(num[8][8]==10) 
  x++; 
 } 
 else if(j==0) 
 { 
  if(num[i][j+1]==10) 
  x++; 
  if(num[i+1][j]==10) 
  x++; 
  if(num[i-1][j]==10) 
  x++; 
  if(num[i-1][j+1]==10) 
  x++; 
  if(num[i+1][j+1]==10) 
  x++; 
 } 
 else if(j==9) 
 { 
  if(num[i][j-1]==10) 
  x++; 
  if(num[i+1][j]==10) 
  x++; 
  if(num[i-1][j]==10) 
  x++; 
  if(num[i-1][j-1]==10) 
  x++; 
  if(num[i+1][j-1]==10) 
  x++; 
 } 
 else if(i==0) 
 { 
  if(num[i+1][j]==10) 
  x++; 
  if(num[i][j-1]==10) 
  x++; 
  if(num[i][j+1]==10) 
  x++; 
  if(num[i+1][j-1]==10) 
  x++; 
  if(num[i+1][j+1]==10) 
  x++; 
 } 
 else if(i==9) 
 { 
  if(num[i-1][j]==10) 
  x++; 
  if(num[i][j-1]==10) 
  x++; 
  if(num[i][j+1]==10) 
  x++; 
  if(num[i-1][j-1]==10) 
  x++; 
  if(num[i-1][j+1]==10) 
  x++; 
 } 
 else 
 { 
  if(num[i-1][j]==10) 
  x++; 
  if(num[i-1][j+1]==10) 
  x++; 
  if(num[i][j+1]==10) 
  x++; 
  if(num[i+1][j+1]==10) 
  x++; 
  if(num[i+1][j]==10) 
  x++; 
  if(num[i+1][j-1]==10) 
  x++; 
  if(num[i][j-1]==10) 
  x++; 
  if(num[i-1][j-1]==10) 
  x++; 
 } 
 return(x); 
} 
funcheck(int i,int j)/*开始找无雷*/ 
{ 
 scorenum--; 
 if(p[i][j]==0&&num[i][j]!=10) 
   { 
    setfillstyle(SOLID_FILL,7);/*显示无雷区*/ 
     bar(200+j*20-7,100+i*20-7,200+j*20+7,100+i*20+7); 
    num[i][j]=-1; 
   } 
 else if(p[i][j]!=0) 
  { 
  sprintf(score,"%d",p[i][j]);/*输出雷数*/ 
   setcolor(RED); 
   outtextxy(195+j*20,95+i*20,score); 
   num[i][j]=-1; 
   return ; 
  } 
 if(i!=0&&num[i-1][j]!=-1&&num[i-1][j]!=10)/*第归开始*/ 
   funcheck(i-1,j); 
 if(i!=0&&j!=9&&num[i-1][j+1]!=-1&&num[i-1][j+1]!=10) 
   funcheck(i-1,j+1); 
 if(j!=9&&num[i][j+1]!=-1&&num[i][j+1]!=10) 
   funcheck(i,j+1); 
 if(j!=9&&i!=9&&num[i+1][j+1]!=-1&&num[i+1][j+1]!=10) 
   funcheck(i+1,j+1); 
 if(i!=9&&num[i+1][j]!=-1&&num[i+1][j]!=10) 
   funcheck(i+1,j); 
 if(i!=9&&j!=0&&num[i+1][j-1]!=-1&&num[i+1][j-1]!=10) 
   funcheck(i+1,j-1); 
 if(j!=0&&num[i][j-1]!=-1&&num[i][j-1]!=10) 
   funcheck(i,j-1); 
 if(i!=0&&j!=0&&num[i-1][j-1]!=-1&&num[i-1][j-1]!=10) 
   funcheck(i-1,j-1); 
} 

playgame()/*游戏过程*/ 
{int i,j,numx; 
 for(i=0;i<10;i++) 
   for(j=0;j<10;j++) 
     p[i][j]=tongji(i,j);/*把标记有几个雷的数字都存放起来*/ 
 while(!kbhit()) 
 { 
  if(LeftPress())/*左键盘按下*/ 
   { 
    MouseGetXY(); 
    if(MouseX>280&&MouseX<300&&MouseY>65&&MouseY<85)/*重新来*/ 
    { 
    MouseOff(); 
    again=1; 
    break; 
    } 
    if(MouseX>190&&MouseX<390&&MouseY>90&&MouseY<290)/*是否在游戏范围内*/ 
    { 
    j=(MouseX-190)/20;/*x坐标*/ 
    i=(MouseY-90)/20;/*y坐标*/ 
      if(num[i][j]!=-1) 
     { 
      if(num[i][j]==10)/*中雷*/ 
      { 
      MouseOff(); 
      gameove();/*失败*/ 
      break; 
      } 
      else/*非中雷*/ 
      { 
      MouseOff(); 
      numx=tongji(i,j); 
      if(numx==0)/*周围没地雷*/ 
         funcheck(i,j);/*开始找无雷*/ 
      else/*有地雷*/ 
        { 
        sprintf(score,"%d",numx);/*输出雷数*/ 
        setcolor(RED); 
 outtextxy(195+j*20,95+i*20,score); 
 scorenum--; 
        } 
      MouseOn(); 
      num[i][j]=-1; 
      if(scorenum<1)/*胜利了*/ 
       { 
       setcolor(11); 
       settextstyle(0,0,2); 
       outtextxy(230,30,"YOU WIN!"); 
       break; 
       } 
      } 
     } 
    } 
   } 
 } 
} 
 main() 
{int gd=DETECT,gr; 
 registerbgidriver(EGAVGA_driver); 
 initgraph(&gd,&gr,"c:\\tc"); 
 loop: begain(); 
 playgame();/*具体游戏*/ 
 if(again)/*游戏中重新开始*/ 
{ 
 again=0; 
 goto loop; 
} 
 MouseOn(); 
 while(!kbhit())/*重新来*/ 
 { 
  if(LeftPress()) 
   { 
   MouseGetXY();/*失败后重新来*/ 
   if(MouseX>280&&MouseX<300&&MouseY>65&&MouseY<85) 
   goto loop; 
   } 
 } 
 MouseOff(); 
 closegraph(); 
} 