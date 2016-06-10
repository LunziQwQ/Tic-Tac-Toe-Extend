#pragma once
#include <stdio.h>
#include "class_BIGBOX.h"
#include "class_COOR_9.h"
#include "class_COOR_3.h"
#include "function.h"
//当前玩家
//玩家交换

COOR_9 get_COOR_9(COOR_3 temp_3) {
	COOR_9 temp_9(temp_3.get_BX(), temp_3.get_BY(), temp_3.get_x(), temp_3.get_y());
	return temp_9;
}

COOR_3 get_COOR_3(COOR_9 temp_9) {
	COOR_3 temp_3(temp_9.x, temp_9.y);
	return temp_3;
}