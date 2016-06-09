#pragma once
const int MAX = 3;

//大方格类
class BigBox{
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
	BigBox(){
		canFill = true;
		isFull = false;
		winner = 0;
		for (int i = 0;i < MAX;i++) {
			for (int j = 0;j < MAX;j++) {
				smallBox[i][j] = 0;
			}
		}
	}
//获取canFill的值
	bool get_canFill() {
		return canFill;
	}
//修改canFill的值
	void set_canFill(bool x) {
		canFill = x;
	}
//获取isFull的值
	bool get_isFull() {
		return isFull;
	}
//修改isFull的值
	void set_isFull(bool x) {
		isFull = x;
	}
//获取winner的值
	int get_winner() {
		return winner;
	}
//修改winner的值
	void set_winner(int x) {
		winner = x;
	}
//获取smallBox的值
	int get_smallBox(int x, int y) {
		return smallBox[x][y];
	}
//修改smallBox的值
	void set_smallBox(int x, int y, int n) {
		smallBox[x][y] = n;
		//printf("set success\n");
	}

//检查当前小棋盘是否占满
	void ifFull() {
		for (int i = 0;i < MAX;i++) {
			for (int j = 0;j < MAX;j++) {
				if (smallBox[i][j] != 0) {
					isFull = false;
					return;
				}
			}
		}
		isFull = true;
		return;
	}
//检查当前小棋盘是否有玩家胜利，返回值为胜利的玩家编号
	void checkSmallWinner() {
		int wx = 0, wy = 0;
		bool flag = false;
		for (int i = 0; i < MAX; i++) {
			//判断第i行是否达到胜利条件
			if (smallBox[i][0] == smallBox[i][1] &&
				smallBox[i][1] == smallBox[i][2] &&
				smallBox[i][0] != 0) {
				wx = i, wy = 0;
				flag = true;
			}
			//判断第i列是否达到胜利条件
			if (smallBox[0][i] == smallBox[1][i] &&
				smallBox[1][i] == smallBox[2][i] &&
				smallBox[0][i] != 0) {
				wx = 0, wy = i;
				flag = true;
			}
			//判断对角线上的棋子是否达到胜利条件
			if (i == 0) {
				if (smallBox[i][i] == smallBox[i + 1][i + 1] &&
					smallBox[i + 1][i + 1] == smallBox[i + 2][i + 2] &&
					smallBox[i][i] != 0) {
					wx = i, wy = i;
					flag = true;
				}
				if (smallBox[i][2 - i] == smallBox[i + 1][1 - i] &&
					smallBox[i + 1][1 - i] == smallBox[i + 2][i] &&
					smallBox[i][2 - i] != 0) {
					wx = i, wy = 2 - i;
					flag = true;
				}
			}
		}
		if (flag) {
			winner = smallBox[wx][wy];
		}
	}
};
BigBox Box[MAX][MAX];