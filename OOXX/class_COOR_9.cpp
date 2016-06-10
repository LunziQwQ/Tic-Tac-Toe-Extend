#include "MAX.h"
#include "class_COOR_3.h"
#include "class_COOR_9.h"
COOR_9::COOR_9() = default;
COOR_9::COOR_9(int x, int y) {
	this->x = x;
	this->y = y;
}
COOR_9::COOR_9(int BX, int BY, int x, int y) {
	this->x = BX * MAX + x;
	this->y = BY * MAX + y;
}
