#pragma once
#include "class_coor_3.h"
//用coor_9记录9*9坐标
class  coor_9 {
private:
	int x = 0;
	int y = 0;
public:
	coor_9() = default;
	coor_9(int x, int y){
		this->x = x;
		this->y = y;
	}
	coor_9(int BX, int BY, int x, int y) {
		this->x = BX * 3 + x;
		this->y = BY * 3 + y;
	}
	/*
	//将类所需坐标转成9×9坐标
	void changeTo9(coor_3 c3) {
		x = c3.get_BX() * 3 + x;
		y = c3.get_BY() * 3 + y;
	}
	//传递坐标类
	coor_9 sent_coor_9(coor_3 c3) {
		coor_9 XY;
		XY.changeTo9(c3);
		return XY;
	}
	coor_9 sent_coor_9(int x, int y) {
		coor_9 XY;
		XY.x = x;
		XY.y = y;
		return XY;
	}
	*/
	//获取坐标类的xy
	int get_coor_9(int n) {
		if (n == 1) {
			return x;
		} else if (n == 2) {
			return y;
		}
	}
	//修改坐标
	void set_coor_9(int x, int y) {
		this->x = x;
		this->y = y;
	}
};