#include "MAX.h"
#include "class_BIGBOX.h"
#include "class_COOR_3.h"
#include <stdio.h>
BIGBOX::BIGBOX(int player) {
	currentPlayer = player;
}

void BIGBOX::ban(int BX, int BY) {
	if (Box[BX][BY].get_winner() != 0 || Box[BX][BY].get_isFull()) {				//不可落子的位置
		for (int i = 0;i < MAX;i++) {
			for (int j = 0;j < MAX;j++) {
				if (Box[i][j].get_winner() == 0 && !Box[i][j].get_isFull()) {
					Box[i][j].set_canFill(true);
				}
			}
		}
		printf("ban can't\n");
	} else if (Box[BX][BY].get_winner() == 0 && !Box[BX][BY].get_isFull()) {			//可以落子的位置
		for (int i = 0;i < MAX;i++) {
			for (int j = 0;j < MAX;j++) {
				if (i == BX && j == BY) {
					Box[i][j].set_canFill(true);
				} else {
					Box[i][j].set_canFill(false);
				}
			}
		}
		printf("ban can\n");
	}
}

//落子，成功返回true，不成功返回false
bool BIGBOX::fill(int x, int y) {
	COOR_3 temp_3(x, y);
	if (!Box[temp_3.get_BX()][temp_3.get_BY()].haveChess(temp_3.get_x(), temp_3.get_y()) &&
		Box[temp_3.get_BX()][temp_3.get_BY()].get_canFill() && 
		Box[temp_3.get_BX()][temp_3.get_BY()].get_winner() == 0) {
		Box[temp_3.get_BX()][temp_3.get_BY()].set_smallBox(temp_3.get_x(), temp_3.get_y(), currentPlayer);
		Box[temp_3.get_BX()][temp_3.get_BY()].checkSmallWinner();
		ban(temp_3.get_x(),temp_3.get_y());
		printf("%d %d\n", temp_3.get_x(), temp_3.get_y());
		printf("fill success %d\n",currentPlayer);
		changePlayer(currentPlayer);
		upgradeBig();
		return true;
	} else {
		printf("%d\nfill false\n", Box[temp_3.get_BX()][temp_3.get_BY()].get_canFill());
		return false;
	}
}

//判断大棋盘的胜利者
int BIGBOX::checkBigWinner() {
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
		bigWinner = Box[wx][wy].get_winner();
	}

	return winner;
}

//更新大棋盘战况
void BIGBOX::upgradeBig() {
	for (int i = 0;i < MAX;i++) {
		for (int j = 0;j < MAX;j++) {
			checkBigWinner();
		}
	}
	printf("ubpgradeBig success\n");
}

//获取当前玩家
int BIGBOX::get_currentPlayer() {
	return currentPlayer;
}
//修改当前玩家
void BIGBOX::set_currentPlayer(int player) {
	currentPlayer = player;
}
//获取大棋盘的胜利者
int BIGBOX::get_bigWinner() {
	return bigWinner;
}

void BIGBOX::changePlayer(int currentPlayer) {
	if (currentPlayer == 1) {
		this->currentPlayer = 2;
	} else if (currentPlayer == 2) {
		this->currentPlayer = 1;
	}
}

void BIGBOX::reset_BIG(int player) {
	currentPlayer = player;
	bigWinner = 0;
	for (int i = 0;i < MAX;i++) {
		for (int j = 0;j < MAX;j++) {
			Box[i][j].reset_MID();
		}
	}
}