#pragma once
#include "MAX.h"
#include "class_MIDBOX.h"
class BIGBOX{
private:
	int bigWinner = 0;
	int currentPlayer = 0;
public:
	BIGBOX(int player);

	MIDBOX Box[MAX][MAX];

	//获取当前玩家
	int get_currentPlayer();

	//修改当前玩家
	void set_currentPlayer(int player);

	//轮换当前玩家
	void changePlayer(int currentplayer);

	//获取大棋盘的胜利者
	int get_bitWinner();

	//落子，成功返回true，不成功返回false
	bool fill(int x, int y);

	//限制对方落子
	void ban(int BX, int BY);

	//判断大棋盘的胜利者
	int checkBigWinner();

	//更新大棋盘战况
	void upgradeBig();
};