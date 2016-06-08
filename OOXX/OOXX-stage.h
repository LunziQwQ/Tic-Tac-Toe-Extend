extern StyleSheet SS;

class Stage {

public:
	Resource resource;
	const int TITLEPAGE = 0;
	const int GAMEPAGE = 1;
	virtual int onClick(int x, int y) = 0;
	virtual void onKeyPress(int keyCode) = 0;
	virtual void load() = 0;
	virtual void exit() = 0;

};

class TitlePage :public Stage {
public:
	TitlePage(Resource temp) {
		resource = temp;
	}

	int onClick(int x, int y) {
		int btnCode = onBtn(x, y);
		printf("KEYCODE:%d\n", btnCode);

		if (btnCode != 0) {
			switch (btnCode){
			case 1:
				return GAMEPAGE;
			case 2:
				isInputStatus = true;
				return TITLEPAGE;
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

		if (isInputStatus)
			showInput();
		
	}
	void exit() {
	}

	int onBtn(int x,int y) {
		for (int i = 0; i < 3; i++) {
			SDL_Rect item = SS.titlePage_btns[i];
			if (!(x<item.x || x>(item.x + item.w) || y<item.y || y>(item.y + item.h)))
				return i+1;
		}
		return 0;
	}
private:
	bool isInputStatus = false;
	void showInput() {
			
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
		printf("KEYCODE:%d\n", btnCode);
		if (btnCode != 0) {
			if (btnCode < 81) {
				doStep(btnCode - 1, 1);	//下子位置与玩家编号
				return GAMEPAGE;
			}
		}
		printf("NOWSTATUS:%d\n");
		return TITLEPAGE;
	}
	void load() {

		//加载背景
		SDL_RenderCopy(gRenderer, resource.gamePage_background, NULL, NULL);
		for (int i = 0; i < 81; i++){
			if (chessStatus[i] == 1)
				SDL_RenderCopy(gRenderer, resource.chess_O, NULL, &SS.gamePage_chessPoint[i]);
			if (chessStatus[i] == 2)
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
	int chessStatus[81];
	void doStep(int index, int player) {
		chessStatus[index] = player;
	}
};