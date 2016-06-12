//引入需要使用的全局变量
extern StyleSheet SS;
extern BIGBOX bigbox;
extern SocketManager socketManager;

//舞台接口类，定义每个舞台必须复写的方法
class Stage {

public:
	//提前声明构造方法的参数
	Resource resource;			

	//舞台编号定义
	const int TITLEPAGE = 0;
	const int GAMEPAGE = 1;

	//鼠标点击方法
	virtual int onClick(int x, int y) = 0;		//Music按钮统一btnCode为233

	//virtual void onKeyPress(int keyCode) = 0;

	//纹理渲染方法
	virtual void load() = 0;

	//退出转场方法
	virtual void exit() = 0;

private:

};

//标题页面舞台
class TitlePage :public Stage {

public:
	//构造方法
	TitlePage(Resource temp) {
		resource = temp;
	}

	//鼠标点击方法
	int onClick(int x, int y) {
		int btnCode = onBtn(x, y);	//获取btnCode，若不在按键上返回 0
		printf("OnClick --> KEYCODE:%d\n", btnCode);

		if (btnCode == 233) {
			//switchMusic()
			//TODO
		}
		if (btnCode != 0) {

			//配对窗口存在时的点击事件
			if (isPairStatus) {
				switch (btnCode) {
				case 4:
					//do something onConfirmClick
					return TITLEPAGE;
				case 5:
					//do something onCancleClick
					isPairStatus = false;
					return TITLEPAGE;
				}
			}

			//非配对窗口存在时点击事件
			else {
				switch (btnCode) {
				case 1:
					return GAMEPAGE;
				case 2:
					isPairStatus = true;
					return TITLEPAGE;
				}
			}
		}

		//点击未定义空白时默认不切换舞台
		return TITLEPAGE;
	}

	//按键方法
	void onKeyPress(int keyCode) {
		
	}

	//渲染方法
	void load() {
		//加载附带标题的背景
		SDL_RenderCopy(gRenderer, resource.titlePage_background, NULL, NULL);

		//加载三个按钮
		SDL_RenderCopy(gRenderer, resource.titlePage_btn0, NULL, &SS.titlePage_btns[0]);
		SDL_RenderCopy(gRenderer, resource.titlePage_btn1, NULL, &SS.titlePage_btns[1]);
		SDL_RenderCopy(gRenderer, resource.titlePage_btn2, NULL, &SS.titlePage_btns[2]);
		

		if (isPairStatus) showInput();		//当点击多人游戏是打开输入配对码窗口
		
	}

	//舞台退出与转场方法
	void exit() {

	}

	//判定按键方法扩展
	int onBtn(int x,int y) {
		SDL_Rect item;
		for (int i = 0; i < 3; i++) {
			item = SS.titlePage_btns[i];
			if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
				return i+1;
		}
		item = SS.alert_confirmBtn;		//若为确定按钮 keycode = 4
		if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
			return 4;
		item = SS.alert_cancleBtn;		//若为取消按钮 keycode = 5
		if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
			return 5;
		item = SS.common_musicSwitchBtn;//若为music按钮 keycode = 233
		if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
			return 233;
		return 0;
	}
private:
	//是否点击了多人游戏按钮，是则弹出输出配对码窗口
	bool isPairStatus = false;		

	//显示请输入配对码窗口
	void showInput() {	

		SDL_RenderCopy(gRenderer, resource.common_alert, NULL, &SS.common_alertWindow);
		SDL_RenderCopy(gRenderer, resource.alert_PairCodeText, NULL, &SS.alert_alertPairCodeText);

		SDL_RenderCopy(gRenderer, resource.common_yesBtn, NULL, &SS.alert_confirmBtn);
		SDL_RenderCopy(gRenderer, resource.common_noBtn, NULL, &SS.alert_cancleBtn);
		SDL_RenderFillRects(gRenderer, SS.alert_PairCode, 4);
	}
};



 //游戏页舞台
class GamePage :public Stage {

public:
	//构造方法
	GamePage(Resource temp) {
		resource = temp;
		memset(chessStatus, 0, sizeof(chessStatus));
	}

	//按键方法
	int onClick(int x, int y) {
		int btnCode = onBtn(x, y);
		printf("OnCLick --> KEYCODE:%d\n", btnCode);
		if (btnCode != 0) {
			if (btnCode < 81) {
				doStep(btnCode - 1, bigbox.get_currentPlayer());	//下子位置与玩家编号(获取到的玩家编号）
				return GAMEPAGE;
			}
		}
		return GAMEPAGE;
	}

	//渲染方法
	void load() {

		//加载背景
		SDL_RenderCopy(gRenderer, resource.gamePage_background, NULL, NULL);
		for (int i = 0; i < 81; i++){

			if (chessStatus[i] == 1)		//玩家1
				SDL_RenderCopy(gRenderer, resource.chess_O, NULL, &SS.gamePage_chessPoint[i]);
			if (chessStatus[i] == 2)		//玩家2
				SDL_RenderCopy(gRenderer, resource.chess_X, NULL, &SS.gamePage_chessPoint[i]);
		}
	}

	//舞台退出及转场方法
	void exit() {

	}

	//判定点击位置方法 return BtnCode
	int onBtn(int x, int y) {
		for (int i = 0; i < 81; i++) {
			SDL_Rect item = SS.gamePage_chessPoint[i];
			if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
				return i + 1;
		}
		return 0;
	}

private:
	int gameStatus = 0;			//{0:游戏进行, 1 : 玩家1胜利, 2 : 玩家2胜利, 3 : 游戏结束和局}
	int chessStatus[81];

	//落子方法，
	void doStep(int index, int player) {

		//检测该点是否能落子
		if ( bigbox.fill((index + 1) / 9, (index + 1) % 9)) {
			
			//将坐标转换为字符串
			char data[4];

			//向服务器端发送坐标的字符串数据
			socketManager.sendMessage(itoa(index,data,10));
			chessStatus[index] = bigbox.get_currentPlayer();	//1或2
		}

		//询问当前游戏状态并保存
		gameStatus = bigbox.get_bigWinner();
	}
};