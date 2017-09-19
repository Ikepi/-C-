#include "stdafx.h"

#include "Box.h"
#include "BlackBoard.h"
#include "UIController.h"



Box::Box(int left, int top, int r, int c) : _left(left), _top(top), _row(r), _col(c)
{
}


void Box::OnDraw(BlackBoard &board)
{
	board.SetColor(0, 1, 1); 
	int x1 = _left + _col * BOX_SIZE, x2 = x1 + BOX_SIZE - 1; 
	int y1 = _top  - _row * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 

	board.DrawLine(x1, y1, x1, y2); 
	board.DrawLine(x1, y1, x2, y1); 
	board.DrawLine(x1, y2, x2, y2); 
	board.DrawLine(x2, y1, x2, y2); 
}

void Box::Move(int dx, int dy)
{
	_row += dx; 
	_col += dy; 
	//UIController::handle()._boxes[snake[snake.size()-1]._r][snake[snake.size()-1]._c] = 0;
	for(unsigned int i = 0; i < UIController::handle().snake.size(); ++i){
			UIController::handle()._boxes[UIController::handle().snake[i]._r][UIController::handle().snake[i]._c] = 1;
		}
}

bool Box::CanMove(int dx, int dy)
{
	// 借助一个临时方块的移动，来判断移动后是否触发各种条件
	Box temp = *this;

	temp._row += dx; 
	temp._col += dy;
//	temp.Move(dx, dy); 
	if (UIController::handle().HitLeft(temp))
	{
		return false; 
	}

	if (UIController::handle().HitRight(temp))
	{
		return false; 
	}

	if (UIController::handle().HitBottom(temp))
	{
		return false; 
	}

	if (UIController::handle().HitTop(temp))
	{
		return false; 
	}

	if (UIController::handle().HitBody(temp))
	{
		return false; 
	}

	if (UIController::handle().HitFood(temp))
	{
		EatFood(temp._row,temp._col);
		UIController::handle()._boxes[temp._row][temp._col] = 1;
		UIController::handle().create_food();
		return true;
	}

	UIController::handle()._boxes[UIController::handle().snake[0]._r][UIController::handle().snake[0]._c] = 0;
	for(unsigned int i = 0; i < UIController::handle().snake.size()-1; ++i){
			UIController::handle().snake[i] = UIController::handle().snake[i+1];
		}
	UIController::handle().snake[UIController::handle().snake.size()-1] = Snake(temp._row,temp._col);
	return true; 
}

void Box::EatFood(int x,int y)
{
	UIController::handle().snake.push_back(Snake(x,y));
}

bool Box::HitBody()
{
	return UIController::handle()._boxes[_row][_col]==1;
}

bool Box::HitFood()
{
	return UIController::handle()._boxes[_row][_col]==2;
}