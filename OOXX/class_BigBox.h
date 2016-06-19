#pragma once
#include "MAX.h"
#include "class_MIDBOX.h"
class BIGBOX{
private:
	int bigWinner = 0;
	int currentPlayer = 1;
public:
	BIGBOX(int player);

	MIDBOX Box[MAX][MAX];

	//获取当前玩家
	int get_currentPlayer();

	//修改当前玩家
	void set_currentPlayer(int player);

	//轮换当前玩家
	void changePlayer(int currentplayer);

	//获取大棋盘的胜利者	{0:游戏进行, 1:玩家1胜利, 2:玩家2胜利, 3:游戏结束和局}
	int get_bigWinner();

	//落子，成功返回true，不成功返回false
	bool fill(int x, int y);

	//限制对方落子
	void ban(int BX, int BY);

	//判断大棋盘的胜利者
	void checkBigWinner();

	//更新大棋盘战况
	void upgradeBig();

	//重置整个棋盘
	void reset_BIG(int player);
};
