#include "stdafx.h"

#include <iostream>
#include <time.h>

#include "UIController.h"
#include "BlackBoard.h"


extern BlackBoard board; //����һ��ȫ�ֱ���

UIController::UIController() : _left(-(COLS * Box::BOX_SIZE / 2)), _bottom(-ROWS * Box::BOX_SIZE / 2), \
	_right(COLS * Box::BOX_SIZE / 2), _top(ROWS * Box::BOX_SIZE / 2), snakehead(_left, _top, rand()%ROWS, rand()%COLS), CurrentDirection(0)
{
	snake.push_back(Snake(snakehead.getRow(),snakehead.getCol()));//save snake's option
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			// ��ʼû�й̶�����
			_boxes[r][c] = 0; 
		}
	}
	_boxes[snakehead.getRow()][snakehead.getCol()] = 1;
	create_food();//create first food
}

UIController::~UIController()//��������
{
}

void UIController::create_food()
{
	int r,c;
	while(1)
	{
		srand((int)time(0));
		r = rand()%ROWS;
		c = rand()%COLS;
		if(_boxes[r][c] == 0)  //���ܳ���������ռ�е�λ��,0�����
		{   
			_boxes[r][c] = 2;
			break;  
		} 
	}
}

void UIController::OnDraw(BlackBoard &board) 
{
	//������Ϸ�Ŀ�򣬿����������
	board.SetColor(1, 0, 1); 
	board.DrawLine(_left,  _top,   _left,  _bottom);
	board.DrawLine(_left,  _top,   _right, _top);
	board.DrawLine(_left,  _bottom,_right, _bottom);
	board.DrawLine(_right, _top,   _right, _bottom);
//	snakehead.OnDraw(board);
	//���ɵ��µ��ߣ��Լ���һ��ʳ��
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			if (_boxes[r][c] != 0)
			{
				if(_boxes[r][c] == 1){// ����Box�������
					Box box(_left, _top, r, c);
					box.OnDraw(board); 
				}
				else{//����ʳ��
					board.SetColor(1, 1, 0); 
					board.DrawCircle(_left + c * BOX_SIZE + 9,_top  - r * BOX_SIZE - 9,10);
				}
			}
		}
	}

}

void UIController::OnTimer(int code)
{
	switch (CurrentDirection)
	{
	case 1:
		MoveBoxDown(); //�����ƶ�����
		break;
	case 2:
		MoveBoxLeft(); //�����ƶ�����
		break;
	case 3:
		MoveBoxRight(); //�����ƶ�����
		break;
	case 4:
		MoveBoxup();//�����ƶ�����
		break;
	default:
		break;
	}
}

void UIController::OnKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		std::cout<<"see you"<<std::endl;
		exit(0);//��q�˳�
		break; 
	case 's':
		MoveBoxDown(); //�����ƶ�����
		CurrentDirection = 1;
		break; 
	case 'a':
		MoveBoxLeft(); //�����ƶ�����
		CurrentDirection = 2;
		break; 
	case 'd':
		MoveBoxRight(); //�����ƶ�����
		CurrentDirection = 3;
		break; 
	case 'w':
		MoveBoxup();//�����ƶ�����
		CurrentDirection = 4;
		break;

	}
}

bool UIController::HitLeft(Box &box)
{
	return box.LeftTo(_left); 
}

bool UIController::HitRight(Box &box)
{
	return box.RightTo(_right); 
}

bool UIController::HitBottom(Box &box)
{
	return box.LowerTo(_bottom); 
}

bool UIController::HitTop(Box &box){
	return box.HigherTo(_top);
}

bool UIController::HitBody(Box &box)
{
	return box.HitBody();
}

bool UIController::HitFood(Box &box)
{
	return box.HitFood();
}

void UIController::MoveBoxLeft()
{
	if (snakehead.CanMove(0, -1))
	{
		snakehead.Move(0, -1); 
		board.Update(); 
	}
	else{
		std::cout<<"game over"<<std::endl;
		exit(0);
	}
}

void UIController::MoveBoxRight()
{
	if (snakehead.CanMove(0, 1))
	{
		snakehead.Move(0, 1);
		board.Update();
	}
	else{
		std::cout<<"game over"<<std::endl;
		exit(0);
	}
}

void UIController::MoveBoxup()
{
	if (snakehead.CanMove(-1, 0))
	{
		snakehead.Move(-1, 0); 
		board.Update();
	}
	else{
		std::cout<<"game over"<<std::endl;
		exit(0);
	}
}

void UIController::MoveBoxDown()
{
	if (snakehead.CanMove(1, 0))
	{
		snakehead.Move(1, 0); 
		board.Update(); 
	}
	else{
		std::cout<<"game over"<<std::endl;
		exit(0);
	}
}

