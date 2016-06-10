#pragma once
#include "MAX.h"

//大方格类
class MIDBOX{
private:
//该棋盘本回合是否允许落子
	bool canFill;

//该小棋盘是否填满
	bool isFull;

//该小棋盘是哪位玩家获胜
	int winner;

//小棋盘用二维数组记录
	int smallBox[MAX][MAX];
public:
//初始化小棋盘	
	MIDBOX();
//获取canFill的值
	bool get_canFill();
//修改canFill的值
	void set_canFill(bool x);
//获取isFull的值
	bool get_isFull();
//修改isFull的值
	void set_isFull(bool x);
//获取winner的值
	int get_winner();
//修改winner的值
	void set_winner(int x);
//获取smallBox的值
	int get_smallBox(int x, int y);
//修改smallBox的值
	void set_smallBox(int x, int y, int n);

//检查当前小棋盘是否占满
	void ifFull();
//检查当前小棋盘是否有玩家胜利，返回值为胜利的玩家编号
	void checkSmallWinner();

//当前落子坐标是否已经有棋
	bool haveChess(int x, int y);
};  
