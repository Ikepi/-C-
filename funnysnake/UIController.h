#ifndef __UICONTROLLER__
#define __UICONTROLLER__

#include<vector>
#include "Box.h"

class Snake
{
public:
	int _r;
	int _c;
public:
	Snake(int r,int c):_r(r),_c(c) {}
};

//class Box;
class BlackBoard; 

class UIController
{
public:
	// 整个区域容纳的方块数量
	const static int ROWS = 25; 
	const static int COLS = 20;
	int _boxes[ROWS][COLS]; //创建一个相应的数组,并约定0:empty;1:snake;2:food;
	std::vector<Snake> snake;

	// 初始掉落位置
	const static int INITIAL_COL = COLS / 2; 
	const static int BOX_SIZE = 20; 
public:
	// UIController采用单子模式，整个软件中唯一
	static UIController &handle()
	{
		static UIController instance; 
		return instance; 
	}

	// 掉落速度，单位毫秒，即每X毫秒掉落一格
	int GameSpeed() { return 400; }

	// 定时器处理逻辑，此处主要用于驱动方块自动掉落
	void OnTimer(int code); 

	// 绘图逻辑，包括边框绘制，方块绘制
	void OnDraw(BlackBoard &board); 

	// 按键逻辑，主要处理用户左、右、下三个方向的操作
	void OnKey(unsigned char key, int x, int y); 

	//生成食物
	void create_food();

	// 判断方块是否触碰左边界、右边界、下边界、及已有固定方块
	bool HitLeft(Box &box);
	bool HitRight(Box &box);
	bool HitBottom(Box &box);
	bool HitTop(Box &box);
	bool HitBody(Box &box);
	bool HitFood(Box &box);

	~UIController();

private:
	UIController(); //单子模式，外界无法使用构造函数

	// 活动方块控制逻辑
	void MoveBoxLeft(); 
	void MoveBoxRight(); 
	void MoveBoxDown(); 
	void MoveBoxup();
		
private:
	
	int _left,  _bottom; //用于构造游戏框的大小，不是命令窗口
	int _right, _top; 
	
	Box snakehead;
	
	int CurrentDirection;

}; 


#endif // #ifndef __UICONTROLLER__