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
	// �����������ɵķ�������
	const static int ROWS = 25; 
	const static int COLS = 20;
	int _boxes[ROWS][COLS]; //����һ����Ӧ������,��Լ��0:empty;1:snake;2:food;
	std::vector<Snake> snake;

	// ��ʼ����λ��
	const static int INITIAL_COL = COLS / 2; 
	const static int BOX_SIZE = 20; 
public:
	// UIController���õ���ģʽ�����������Ψһ
	static UIController &handle()
	{
		static UIController instance; 
		return instance; 
	}

	// �����ٶȣ���λ���룬��ÿX�������һ��
	int GameSpeed() { return 400; }

	// ��ʱ�������߼����˴���Ҫ�������������Զ�����
	void OnTimer(int code); 

	// ��ͼ�߼��������߿���ƣ��������
	void OnDraw(BlackBoard &board); 

	// �����߼�����Ҫ�����û����ҡ�����������Ĳ���
	void OnKey(unsigned char key, int x, int y); 

	//����ʳ��
	void create_food();

	// �жϷ����Ƿ�����߽硢�ұ߽硢�±߽硢�����й̶�����
	bool HitLeft(Box &box);
	bool HitRight(Box &box);
	bool HitBottom(Box &box);
	bool HitTop(Box &box);
	bool HitBody(Box &box);
	bool HitFood(Box &box);

	~UIController();

private:
	UIController(); //����ģʽ������޷�ʹ�ù��캯��

	// ���������߼�
	void MoveBoxLeft(); 
	void MoveBoxRight(); 
	void MoveBoxDown(); 
	void MoveBoxup();
		
private:
	
	int _left,  _bottom; //���ڹ�����Ϸ��Ĵ�С�����������
	int _right, _top; 
	
	Box snakehead;
	
	int CurrentDirection;

}; 


#endif // #ifndef __UICONTROLLER__