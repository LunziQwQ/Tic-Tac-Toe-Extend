#pragma once
#include "MAX.h"
#include "class_COOR_9.h"

//用COOR_3记录类所需坐标
class COOR_3 {
private:
	int BX = 0;
	int BY = 0;
	int x = 0;
	int y = 0;
public:
	COOR_3();
	COOR_3(int x, int y);
	COOR_3(int bx, int by, int x, int y);
	COOR_3(COOR_9 c9);
	void change_9_to_3(COOR_9 c9);		//9*9坐标转成类所需坐标
	void set_BX(int x);
	int get_BX();
	void set_BY(int y);
	int get_BY();
	void set_x(int x);
	int get_x();
	void set_y(int y);
	int get_y();
};