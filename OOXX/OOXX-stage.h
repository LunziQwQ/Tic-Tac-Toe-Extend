//引入需要使用的全局变量
extern StyleSheet SS;
extern BIGBOX bigbox;
extern SocketManager socketManager;
extern bool isMulti;
extern bool isFirst;

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

	//是否开启了通知窗口
	bool isAlertStatus = false;

	//数字按键列表
	SDL_Keycode numberKey[20] = {
		SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4,
		SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9,
		SDLK_KP_0, SDLK_KP_1, SDLK_KP_2, SDLK_KP_3, SDLK_KP_4,
		SDLK_KP_5, SDLK_KP_6, SDLK_KP_7, SDLK_KP_8, SDLK_KP_9,
	};

};

//标题页面舞台-----------------------------------------------------------
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

		if (btnCode != 0) {

			//配对窗口存在时的点击事件
			if (isAlertStatus) {
				switch (btnCode) {
				case 4:
					if (pairCode[3] != -1) {	//已输入4位数字
						sendPairCode();
						isMulti = true;
						isAlertStatus = false;
						return GAMEPAGE;
					} else {
						memset(pairCode, -1, sizeof(pairCode));
						isAlertStatus = false;
						return TITLEPAGE;
					}
					return TITLEPAGE;
				case 5:
					memset(pairCode, -1, sizeof(pairCode));
					isAlertStatus = false;
					return TITLEPAGE;
				}
			}

			//非配对窗口存在时点击事件
			else {
				switch (btnCode) {
				case 1:
					return GAMEPAGE;
				case 2:
					isAlertStatus = true;
					return TITLEPAGE;
				case 3:
					system("explorer \"https://github.com/LunziQwQ/OOXXChessGame-bySDL\" ");
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
		if (isAlertStatus) showInput();
		
	}

	//舞台退出与转场方法
	void exit() {

	}

	//判定按键方法扩展
	int onBtn(int x,int y) {
		SDL_Rect item;
		if (!isAlertStatus) {
			for (int i = 0; i < 3; i++) {
				item = SS.titlePage_btns[i];
				if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
					return i + 1;
			}
		}
		if (isAlertStatus) {
			item = SS.alert_confirmBtn;		//若为确定按钮 keycode = 4
			if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
				return 4;
			item = SS.alert_cancleBtn;		//若为取消按钮 keycode = 5
			if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
				return 5;
		}
		return 0;
	}
private:
	//是否点击了多人游戏按钮，是则弹出输出配对码窗口

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
		for (int i = 0; i < 4; i++)	{
			std::stringstream ss;
			ss << pairCode[i];
			std::string temp;
			ss >> temp;
			data += temp;
		}
		data = "code:" + data;
		socketManager.sendMessage(data.c_str());
		//TODO 发送4位配对码到服务端
	}
};



 //游戏页舞台-----------------------------------------------------------------
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
			//正常游戏状态
			if (!isAlertStatus && bigbox.get_bigWinner() == 0) {
				if (btnCode <= 81) {

					if (!isMulti
						|| (isMulti && bigbox.get_currentPlayer() == 1 && isFirst)
						|| (isMulti && bigbox.get_currentPlayer() != 1 && !isFirst)) {

						doStep(btnCode - 1, bigbox.get_currentPlayer());	//下子位置与玩家编号(获取到的玩家编号）
						return GAMEPAGE;
					}
				}
				if (btnCode == 100) {
					isAlertStatus = true;
				}

			//触发了游戏结束，弹出结算Alert
			}else if (isAlertStatus && bigbox.get_bigWinner() != 0) {
				if (btnCode == 99) {
					isAlertStatus = false;
					bigbox.reset_BIG(1);
					memset(chessStatus, 0, sizeof(chessStatus));
					return TITLEPAGE;
				}
			//触发了是否游戏结束Alert
			}else if (isAlertStatus && bigbox.get_bigWinner() == 0) {
				if (btnCode == 99) {
					isAlertStatus = false;
					bigbox.reset_BIG(1);
					memset(chessStatus, 0, sizeof(chessStatus));
					return TITLEPAGE;
				}
				if (btnCode == 98) {
					isAlertStatus = false;
					return GAMEPAGE;
				}

			}
		}
		return GAMEPAGE;
	}

	//渲染方法
	void load() {

		//加载背景
		SDL_RenderCopy(gRenderer, resource.gamePage_background, NULL, NULL);
		SDL_RenderCopy(gRenderer, resource.gamePage_title, NULL, &SS.gamePage_title);
		SDL_RenderCopy(gRenderer, resource.gamePage_nowTurn, NULL, &SS.gamePage_nowTurn); 
		SDL_RenderCopy(gRenderer, resource.gamePage_coffeeCup, NULL, &SS.gamePage_cup);

		//右侧 NowTurn 区域图片
		if (bigbox.get_currentPlayer() == 1)
			SDL_RenderCopy(gRenderer, resource.chess_BX, NULL, &SS.gamePage_nowTurnIMG);
		else
			SDL_RenderCopy(gRenderer, resource.chess_BO, NULL, &SS.gamePage_nowTurnIMG);

		for (int i = 0; i < 81; i++){
			if (chessStatus[i] == 1)		//玩家1
				SDL_RenderCopy(gRenderer, resource.chess_O, NULL, &SS.gamePage_chessPoint[i]);
			if (chessStatus[i] == 2)		//玩家2
				SDL_RenderCopy(gRenderer, resource.chess_X, NULL, &SS.gamePage_chessPoint[i]);
		}

		if (!isMulti						
			|| (isMulti && bigbox.get_currentPlayer() == 1 && isFirst)
			|| (isMulti && bigbox.get_currentPlayer() != 1 && !isFirst)) {
			showWhereCanFill();			
		}

		showMidBoxStatus();
		
		if (bigbox.get_bigWinner() != 0) {	//游戏出现结果
			isAlertStatus = true;
			SDL_RenderCopy(gRenderer, resource.common_alert, NULL, &SS.common_alertWindow);
			SDL_RenderCopy(gRenderer, resource.common_yesBtn, NULL, &SS.alert_confirmBtn);

			if (bigbox.get_bigWinner() == 1)
				SDL_RenderCopy(gRenderer, resource.alert_redWin, NULL, &SS.alert_gameOver);
			if (bigbox.get_bigWinner() == 2)
				SDL_RenderCopy(gRenderer, resource.alert_blueWin, NULL, &SS.alert_gameOver);
			if (bigbox.get_bigWinner() == 3)
				SDL_RenderCopy(gRenderer, resource.alert_drawing, NULL, &SS.alert_gameOver);
		}
		//点击了是否退出Aleat
		if (bigbox.get_bigWinner() == 0 && isAlertStatus) {
			SDL_RenderCopy(gRenderer, resource.common_alert, NULL, &SS.common_alertWindow);
			SDL_RenderCopy(gRenderer, resource.common_yesBtn, NULL, &SS.alert_confirmBtn);
			SDL_RenderCopy(gRenderer, resource.common_noBtn, NULL, &SS.alert_cancleBtn);
			SDL_RenderCopy(gRenderer, resource.alert_wantExit, NULL, &SS.alert_wantExit);
			SDL_RenderCopy(gRenderer, resource.alert_willLose, NULL, &SS.alert_willLose);
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
		//正常游戏状态
		if (!isAlertStatus && bigbox.get_bigWinner() == 0) {
			for (int i = 0; i < 81; i++) {
				SDL_Rect item = SS.gamePage_chessPoint[i];
				if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
					return i + 1;
			}
			SDL_Rect item = SS.gamePage_title;
			if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
				return 100;	//弹出alert是否退出主菜单

		//触发了游戏结束，弹出结算Alert
		} else if(isAlertStatus && bigbox.get_bigWinner() != 0){
			SDL_Rect item = SS.alert_confirmBtn;
			if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
				return 99;	//点击确定
		//触发了是否游戏结束Alert
		} else if (isAlertStatus && bigbox.get_bigWinner() == 0) {
			SDL_Rect item = SS.alert_confirmBtn;
			if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
				return 99;	//点击确定
			item = SS.alert_cancleBtn;
			if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
				return 98;	//点击取消
		}
		return 0;
	}

	void getMultiStep(std::string result) {
		int index = atoi(result.c_str());
		if (bigbox.fill((index) / 9, (index) % 9)) {
			chessStatus[index] = bigbox.get_currentPlayer();
		}
	}

	//当鼠标在可落子区域时提示对手下一步的可落子区域    喵喵喵喵喵*****************************************
	void onHover(int x, int y) {
		int btnCode = onBtn(x, y);
		if (btnCode != 0) {
			int index = (btnCode - 1) / 9 % 3 * 3 + (btnCode - 1) % 9 % 3;
			COOR_3 temp((btnCode - 1) / 9, (btnCode - 1) % 9);
			if (bigbox.Box[temp.get_BX()][temp.get_BY()].get_canFill()
				&& !bigbox.Box[temp.get_BX()][temp.get_BY()].haveChess(temp.get_x(),temp.get_y())) {	//当前鼠标位置可落子

				if (bigbox.Box[index / 3][index % 3].get_winner() == 0) {	//映射midBox可落子

					if (bigbox.get_currentPlayer() == 1)
						SDL_RenderCopy(gRenderer, resource.gamePage_blueNext, NULL, &SS.gamePage_midBox[index]);
					else
						SDL_RenderCopy(gRenderer, resource.gamePage_redNext, NULL, &SS.gamePage_midBox[index]);

				} else {

					for (int i = 0; i < 9; i++) {
						if (bigbox.Box[i / 3][i % 3].get_winner() == 0) {

							if (bigbox.get_currentPlayer() == 1)
								SDL_RenderCopy(gRenderer, resource.gamePage_blueNext, NULL, &SS.gamePage_midBox[i]);
							else
								SDL_RenderCopy(gRenderer, resource.gamePage_redNext, NULL, &SS.gamePage_midBox[i]);

						}
					}

				}

			}
		}
	}


private:
	int gameStatus = 0;			//{0:游戏进行, 1 : 玩家1胜利, 2 : 玩家2胜利, 3 : 游戏结束和局}
	int chessStatus[81];


	//落子方法，
	void doStep(int index, int player) {

		//检测该点是否能落子
		if ( bigbox.fill((index) / 9, (index) % 9)) {

			//若为联机模式追加数据发送
			if (isMulti) {

				//将坐标转换为字符串
				char data[4];
				//向服务器端发送坐标的字符串数据
				socketManager.sendMessage(itoa(index, data, 10));
				cout << data << endl;
			}
			chessStatus[index] = bigbox.get_currentPlayer();	//1或2
		}

		//询问当前游戏状态并保存
		gameStatus = bigbox.get_bigWinner();
	}

	//显示可落子的区域 半透明色块
	void showWhereCanFill() {
		for (int i = 0; i < 9; i++){
			if (bigbox.Box[i / 3][i % 3].get_canFill()) {
				SDL_RenderCopy(gRenderer, resource.gamePage_canFill, NULL, &SS.gamePage_midBox[i]);
			}
		}
	}

	//显示MIDBOX战果
	void showMidBoxStatus() {
		for (int i = 0; i < 9; i++){
			if (bigbox.Box[i / 3][i % 3].get_winner() == 1)
				SDL_RenderCopy(gRenderer, resource.chess_BX, NULL, &SS.gamePage_midBox[i]);
			if (bigbox.Box[i / 3][i % 3].get_winner() == 2)
				SDL_RenderCopy(gRenderer, resource.chess_BO, NULL, &SS.gamePage_midBox[i]);
			//if (bigbox.Box[i / 3][i % 3].get_winner() == 3)
				//TODO 和棋时MIDBOX的状态

		}
	}


};