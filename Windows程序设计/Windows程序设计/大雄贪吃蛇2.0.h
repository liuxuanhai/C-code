#include "dxList.h"		// 添加ADT链表
#include "dxDigit.h"	// 添加ADT数字显示

class Snake
{
private: 
	List snake;
	RECT rcFood;
public:
	Snake(int wid = 20, int len = 3, int x = 20 * 3, int y = 20 * 5);
	void Draw(HDC hdc);
	enum MoveDir { UP, DOWN, LEFT, RIGHT };
	bool Move(HWND, MoveDir);
	void RandomFood(HWND);
	void ShowFood(HWND);
	BOOL IsEat();
	BOOL IsDead(HWND);
	void Add() { snake.AddTail(snake.GetTail()->item); }
	void Resert(int wid = 20, int len = 3, int x = 20 * 3, int y = 20 * 5); 
};