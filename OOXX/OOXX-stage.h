//引入需要使用的全局变量
extern StyleSheet SS;
extern BIGBOX bigbox;
extern SocketManager socketManager;

//舞台接口类，定义每个舞台必须复写的方法
class Stage {

public:
	//提前声明构造方法的参数
	Resource resource;			
	
	//鼠标点击方法
	virtual int onClick(int x, int y) = 0;		//Music按钮统一btnCode为233

	//键盘按键方法
	virtual void onKeyPress(int keyCode) = 0;

	//纹理渲染方法
	virtual void load() = 0;

	//退出转场方法
	virtual void exit() = 0;

protected:
	//舞台编号定义
	const int TITLEPAGE = 0;
	const int GAMEPAGE = 1;

	//数字按键列表
	SDL_Keycode numberKey[20] = {
		SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4,
		SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9,
		SDLK_KP_0, SDLK_KP_1, SDLK_KP_2, SDLK_KP_3, SDLK_KP_4,
		SDLK_KP_5, SDLK_KP_6, SDLK_KP_7, SDLK_KP_8, SDLK_KP_9,
	};

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
					if (pairCode[3] != -1) {	//已输入4位数字
						sendPairCode();
					} else {
						//TODO 改变界面文字提醒输入完整
					}
					return TITLEPAGE;
				case 5:
					//do something onCancleClick
					memset(pairCode, -1, sizeof(pairCode));
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
	void onKeyPress(SDL_Keycode keycode) {

		//检测是否输入为数字
		int NumInput = -1;
		for (int i = 0; i < 20; i++) {
			if (keycode == numberKey[i])
				NumInput = i % 10;
		}
		if (NumInput >= 0){
			for (int i = 0; i < 4; i++){
				if (pairCode[i] == -1) {
					pairCode[i] = NumInput;
					break;
				}
			}
		}
		

	}

	//渲染方法
	void load() {
		//加载附带标题的背景
		SDL_RenderCopy(gRenderer, resource.titlePage_background, NULL, NULL);

		//加载三个按钮
		SDL_RenderCopy(gRenderer, resource.titlePage_btn0, NULL, &SS.titlePage_btns[0]);
		SDL_RenderCopy(gRenderer, resource.titlePage_btn1, NULL, &SS.titlePage_btns[1]);
		SDL_RenderCopy(gRenderer, resource.titlePage_btn2, NULL, &SS.titlePage_btns[2]);
		
		//当点击多人游戏是打开输入配对码窗口
		if (isPairStatus) showInput();		
		
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

	//临时存储
	int pairCode[4] = {-1,-1,-1,-1};

	//显示请输入配对码窗口
	void showInput() {	
		
		SDL_RenderCopy(gRenderer, resource.common_alert, NULL, &SS.common_alertWindow);
		SDL_RenderCopy(gRenderer, resource.alert_PairCodeText, NULL, &SS.alert_alertPairCodeText);
		SDL_RenderCopy(gRenderer, resource.common_yesBtn, NULL, &SS.alert_confirmBtn);
		SDL_RenderCopy(gRenderer, resource.common_noBtn, NULL, &SS.alert_cancleBtn);
		for (int i = 0; i < 4; i++){
			if (pairCode[i] >= 0) {
				switch (pairCode[i]){
				case 0:
					SDL_RenderCopy(gRenderer, resource.num_0, NULL, &SS.alert_PairCode[i]);
					break;
				case 1:
					SDL_RenderCopy(gRenderer, resource.num_1, NULL, &SS.alert_PairCode[i]);
					break;
				case 2:
					SDL_RenderCopy(gRenderer, resource.num_2, NULL, &SS.alert_PairCode[i]);
					break;
				case 3:
					SDL_RenderCopy(gRenderer, resource.num_3, NULL, &SS.alert_PairCode[i]);
					break;
				case 4:
					SDL_RenderCopy(gRenderer, resource.num_4, NULL, &SS.alert_PairCode[i]);
					break;
				case 5:
					SDL_RenderCopy(gRenderer, resource.num_5, NULL, &SS.alert_PairCode[i]);
					break;
				case 6:
					SDL_RenderCopy(gRenderer, resource.num_6, NULL, &SS.alert_PairCode[i]);
					break;
				case 7:
					SDL_RenderCopy(gRenderer, resource.num_7, NULL, &SS.alert_PairCode[i]);
					break;
				case 8:
					SDL_RenderCopy(gRenderer, resource.num_8, NULL, &SS.alert_PairCode[i]);
					break;
				case 9:
					SDL_RenderCopy(gRenderer, resource.num_9, NULL, &SS.alert_PairCode[i]);
					break;
				}
			}
		}
	}

	void sendPairCode() {
		std::string data = "";
		//TODO 发送4位配对码到服务端
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

	//点击方法
	int onClick(int x, int y) {
		int btnCode = onBtn(x, y);
		printf("OnCLick --> KEYCODE:%d\n", btnCode);
		if (btnCode != 0) {
			if (btnCode < 81) {
				doStep(btnCode - 1, bigbox.get_currentPlayer());	//下子位置与玩家编号(获取到的玩家编号）
				return GAMEPAGE;
			}
		}
		return TITLEPAGE;
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

	//按键方法
	void onKeyPress(int keyCode) {

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
		if ( bigbox.fill((index) / 9, (index) % 9)) {
			
			//将坐标转换为字符串
			char data[4];

			//向服务器端发送坐标的字符串数据
			socketManager.sendMessage(itoa(index, data, 10));
			chessStatus[index] = bigbox.get_currentPlayer();	//1或2
		}

		//询问当前游戏状态并保存
		gameStatus = bigbox.get_bigWinner();
	}
};