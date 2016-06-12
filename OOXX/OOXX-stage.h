extern StyleSheet SS;
extern BIGBOX bigbox;
extern SocketManager socketManager;

class Stage {

public:
	Resource resource;
	const int TITLEPAGE = 0;
	const int GAMEPAGE = 1;
	virtual int onClick(int x, int y) = 0;		//Music按钮统一btnCode为233
	//virtual void onKeyPress(int keyCode) = 0;
	virtual void load() = 0;
	virtual void exit() = 0;

private:
};


class TitlePage :public Stage {
public:
	TitlePage(Resource temp) {
		resource = temp;
	}

	int onClick(int x, int y) {
		int btnCode = onBtn(x, y);	//获取btnCode，若不在按键上返回 0
		printf("OnClick --> KEYCODE:%d\n", btnCode);
		if (btnCode == 233) {
//			switchMusic()
			//TODO
		}
		if (btnCode != 0) {
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
			else {
				//非配对窗口存在时点击事件
				switch (btnCode) {
				case 1:
					return GAMEPAGE;
				case 2:
					isPairStatus = true;
					return TITLEPAGE;
				}
			}
		}
		
		return TITLEPAGE;
	}

	void onKeyPress(int keyCode) {
		
	}

	void load() {
		//加载背景
		SDL_RenderCopy(gRenderer, resource.titlePage_background, NULL, NULL);

		//加载标题
		SDL_RenderCopy(gRenderer, resource.titlePage_title, NULL, &SS.titlePage_title);

		//加载三个按钮
		SDL_SetRenderDrawColor(gRenderer, 0x66, 0xCC, 0xFF, 0xFF);
		SDL_RenderFillRects(gRenderer, SS.titlePage_btns, 3);
		SDL_RenderCopy(gRenderer, resource.titlePage_btn0, NULL, &SS.titlePage_btns[0]);
		SDL_RenderCopy(gRenderer, resource.titlePage_btn1, NULL, &SS.titlePage_btns[1]);
		SDL_RenderCopy(gRenderer, resource.titlePage_btn2, NULL, &SS.titlePage_btns[2]);
		

		if (isPairStatus) showInput();		//当点击多人游戏是打开输入配对码窗口
		
	}
	void exit() {

	}

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
		item = SS.common_musicSwitchBtn;		//若为music按钮 keycode = 233
		if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
			return 233;
		return 0;
	}
private:
	bool isPairStatus = false;		//是否点击了多人游戏按钮，是则弹出输出配对码窗口
	//显示请输入配对码窗口
	void showInput() {	
		SDL_SetRenderDrawColor(gRenderer, 0xC0, 0xC0, 0xC0, 0xFF);
		SDL_RenderFillRect(gRenderer, &SS.common_alertWindow);
		SDL_RenderCopy(gRenderer, resource.alert_PairCodeText, NULL, &SS.alert_alertPairCodeText);
		SDL_SetRenderDrawColor(gRenderer, 0x66, 0xCC, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &SS.alert_confirmBtn);
		SDL_RenderFillRect(gRenderer, &SS.alert_cancleBtn);
		SDL_RenderFillRects(gRenderer, SS.alert_PairCode, 4);


	}
};



 
class GamePage :public Stage {
public:
	GamePage(Resource temp) {
		resource = temp;
		memset(chessStatus, 0, sizeof(chessStatus));
	}
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
	void exit() {

	}
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
	void doStep(int index, int player) {
		//检测该点是否能落子
		if ( bigbox.fill((index + 1) / 9, (index + 1) % 9)) {
			
			//将坐标转换为字符串
			char data[4];

			//发送坐标的字符串数据
			socketManager.sendMessage(itoa(index,data,10));
			chessStatus[index] = player;
		}
		gameStatus = bigbox.get_bigWinner();
	}
};