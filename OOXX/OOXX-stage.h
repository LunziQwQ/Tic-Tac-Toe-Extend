extern StyleSheet SS;
extern Resource resource;

class Stage {

public:
	const int TITLEPAGE = 0;
	const int GAMEPAGE = 1;
	virtual int onClick(int x, int y) = 0;
	virtual void load() = 0;
	virtual void exit() = 0;
};

class TitlePage :public Stage {
public:

	int onClick(int x, int y) {
		int btnCode = onBtn(x, y);
		printf("KEYCODE:%d\n", btnCode);

		if (btnCode != 0) {
			switch (btnCode){
			case 1:
				return GAMEPAGE;
			}
		}
		

		return TITLEPAGE;
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
};



 
class GamePage :public Stage {
public:

	int onClick(int x, int y) {
		int btnCode = onBtn(x, y);
		printf("KEYCODE:%d\n", btnCode);
		if (btnCode != 0) {
			if (btnCode < 81) {
				SDL_Rect item = SS.gamePage_chessPoint[btnCode - 1];
				return GAMEPAGE;
			}
		}
		printf("NOWSTATUS:%d\n");
		return TITLEPAGE;
	}
	void load() {

			//加载背景

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRects(gRenderer, SS.gamePage_chessPoint, 81);
			SDL_SetTextureAlphaMod(gTexture, 0);

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
	
};