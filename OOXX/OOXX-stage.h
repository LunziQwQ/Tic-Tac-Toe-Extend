class Stage {
public:
	const StyleSheet SS;
	Uint32 index;
	virtual void onClick(int x, int y) = 0;
	virtual void load() = 0;
	virtual void exit() = 0;
};

class TitlePage :Stage {
public:
	Uint32 index = 0;
	void onClick(int x, int y) {

	}
	void load() {
		//load background
		loadMediaToScreen("resource/background.png", NULL);

		//load Title
		gTexture = renderText("OOXX Chess!",
			"ttf/consolab.ttf",
			SS.red, 256, gRenderer);
		SDL_RenderCopy(gRenderer, gTexture, NULL, &SS.titlePage_title);

		//load buttons
		SDL_SetRenderDrawColor(gRenderer, 0x66, 0xCC, 0xFF, 0xFF);
		SDL_RenderFillRects(gRenderer, SS.titlePage_btns, 3);
		std::string btnTexts[3] = { "Single Play","Multi Play","About us & Help" };
		for (int i = 0; i < 3; i++) {
			gTexture = renderText(btnTexts[i],
				"ttf/consolab.ttf",
				SS.black, 32, gRenderer);
			SDL_RenderCopy(gRenderer, gTexture, NULL, &SS.titlePage_btns[i]);
		}
		SDL_RenderPresent(gRenderer);
	}
	void exit() {

	}
};