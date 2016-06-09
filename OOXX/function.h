#pragma once
#include <stdio.h>
#include "class_BigBox.h"
#include "class_coor_9.h"
#include "class_coor_3.h"

//限制对方落子位置
void ban(int BX, int BY);

//当前落子坐标是否已经有棋
bool haveChess(int BX, int BY, int x, int y);

//落子，成功返回true，不成功返回false
bool fill(int x, int y);

//判断大棋盘的胜利者
int checkBigWinner();

//更新大棋盘战况
void upgradeBig();


//当前玩家
int currentplayer = 1;
//玩家交换
void changeplayer(int &currentplayer) {
	if (currentplayer == 1) {
		currentplayer = 2;
	} else if (currentplayer == 2) {
		currentplayer = 1;
	}
}
//限制对方落子位置
void ban(int BX, int BY) {
	if (Box[BX][BY].get_winner() != 0 || Box[BX][BY].get_isFull()) {			//不可落子的位置
		for (int i = 0;i < MAX;i++) {
			for (int j = 0;j < MAX;j++) {
				if (Box[i][j].get_winner() == 0 && !Box[i][j].get_isFull()) {
					Box[i][j].set_canFill(true);
				}
			}
		}
		//printf("ban can't\n");
	} else if (Box[BX][BY].get_winner() == 0 && !Box[BX][BY].get_isFull()) {		//可以落子的位置
		for (int i = 0;i < MAX;i++) {
			for (int j = 0;j < MAX;j++) {
				if (i == BX && j == BY) {
					Box[i][j].set_canFill(true);
				} else {
					Box[i][j].set_canFill(false);
				}
			}
		}
		//printf("ban can\n");
	}
}

//当前落子坐标是否已经有棋
bool haveChess(int BX, int BY, int x, int y) {
	if (Box[BX][BY].get_smallBox(x, y) == 0) {
		//printf("haveChaess false\n");
		return false;
	}
	//printf("haveChaess true\n");
	return true;
}

//落子，成功返回true，不成功返回false
bool fill(int x, int y) {
	//coor_9 temp_9(x, y);
	coor_3 temp_3(x, y);
	if (!haveChess(temp_3.get_BX(), temp_3.get_BY(), temp_3.get_x(), temp_3.get_y()) &&
		Box[temp_3.get_BX()][temp_3.get_BY()].get_canFill() &&
		Box[temp_3.get_BX()][temp_3.get_BY()].get_winner() == 0) {
		Box[temp_3.get_BX()][temp_3.get_BY()].set_smallBox(temp_3.get_x(), temp_3.get_y(), currentplayer);
		upgradeBig();
		ban(temp_3.get_x(), temp_3.get_y());
		printf("%d %d\n", temp_3.get_x(), temp_3.get_y());
		//printf("fill success\n");
		return true;
	} else {
		//printf("fill false\n");
		return false;
	}
}

//判断大棋盘的胜利者
int checkBigWinner() {
	int wx = 0, wy = 0, winner = 0;
	bool flag = false;
	for (int i = 0; i < MAX; i++) {
		//判断第i行是否达到胜利条件
		if (Box[i][0].get_winner() == Box[i][1].get_winner() &&
			Box[i][1].get_winner() == Box[i][2].get_winner() &&
			Box[i][0].get_winner() != 0) {
			wx = i, wy = 0;
			flag = true;
		}
		//判断第i列是否达到胜利条件
		if (Box[0][i].get_winner() == Box[1][i].get_winner() &&
			Box[1][i].get_winner() == Box[2][i].get_winner() &&
			Box[0][i].get_winner() != 0) {
			wx = 0, wy = i;
			flag = true;
		}
		//判断对角线上的棋子是否达到胜利条件
		if (i == 0) {
			if (Box[i][i].get_winner() == Box[i + 1][i + 1].get_winner() &&
				Box[i + 1][i + 1].get_winner() == Box[i + 2][i + 2].get_winner() &&
				Box[i][i].get_winner() != 0) {
				wx = i, wy = i;
				flag = true;
			}
			if (Box[i][2 - i].get_winner() == Box[i + 1][1 - i].get_winner() &&
				Box[i + 1][1 - i].get_winner() == Box[i + 2][i].get_winner() &&
				Box[i][2 - i].get_winner() != 0) {
				wx = i, wy = 2 - i;
				flag = true;
			}
		}
	}
	if (flag) {
		winner = Box[wx][wy].get_winner();
	}
	return winner;
}

//更新大棋盘战况
void upgradeBig() {
	for (int i = 0;i < MAX;i++) {
		for (int j = 0;j < MAX;j++) {
			Box[i][j].checkSmallWinner();
		}
	}
}