#pragma once
#include "class_coor_9.h"

//用coor_3记录类所需坐标
class coor_3 {
private:
	int BX = 0;
	int BY = 0;
	int x = 0;
	int y = 0;
public:
	coor_3() = default;
	coor_3(int x, int y) {
		BX = x / MAX;
		BY = y / MAX;
		this->x = x%MAX;
		this->y = y%MAX;
	}
	coor_3(int bx, int by, int x, int y) {
		BX = bx;
		BY = by;
		this->x = x;
		this->y = y;
	}

	//9*9坐标转成类所需坐标
	void change_9_to_3(coor_9 c9) {
		BX = c9.get_coor_9(1) / MAX;
		BY = c9.get_coor_9(2) / MAX;
		x = c9.get_coor_9(1) % MAX;
		y = c9.get_coor_9(2) % MAX;
	}

	void set_BX(int x) {
		BX = x;
	}
	int get_BX() {
		return BX;
	}
	void set_BY(int y) {
		BY = y;
	}
	int get_BY() {
		return BY;
	}
	void set_x(int x) {
		this->x = x;
	}
	int get_x() {
		return x;
	}
	void set_y(int y) {
		this->y = y;
	}
	int get_y() {
		return y;
	}
	
};