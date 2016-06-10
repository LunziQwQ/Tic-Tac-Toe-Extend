#include "class_COOR_9.h"
#include "class_COOR_3.h"
COOR_3::COOR_3() = default;
COOR_3::COOR_3(int x, int y) {
	BX = x / MAX;
	BY = y / MAX;
	this->x = x%MAX;
	this->y = y%MAX;
}
COOR_3::COOR_3(int bx, int by, int x, int y) {
	BX = bx;
	BY = by;
	this->x = x;
	this->y = y;
}
COOR_3::COOR_3(COOR_9 c9) {
	BX = c9.x / MAX;
	BY = c9.y / MAX;
	x = c9.x % MAX;
	y = c9.y % MAX;
}
void COOR_3::change_9_to_3(COOR_9 c9) {
	BX = c9.x / MAX;
	BY = c9.y / MAX;
	x = c9.x % MAX;
	y = c9.y % MAX;
}
void COOR_3::set_BX(int x) {
	BX = x;
}
int COOR_3::get_BX() {
	return BX;
}
void COOR_3::set_BY(int y) {
	BY = y;
}
int COOR_3::get_BY() {
	return BY;
}
void COOR_3::set_x(int x) {
	this->x = x;
}
int COOR_3::get_x() {
	return x;
}
void COOR_3::set_y(int y) {
	this->y = y;
}
int COOR_3::get_y() {
	return y;}