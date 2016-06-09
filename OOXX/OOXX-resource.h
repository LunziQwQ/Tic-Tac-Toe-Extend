extern StyleSheet SS;
class Resource {
public:
	//游戏所用到的图片资源纹理
	SDL_Texture* titlePage_background = //首页背景
		loadTexture("resource/background.png");
	SDL_Texture* gamePage_background =	//游戏页带棋盘的背景
		loadTexture("resource/gamePage-02.png");
	SDL_Texture* chess_O =				//O棋子
		loadTexture("resource/Opic.png");
	SDL_Texture* chess_X =				//X棋子
		loadTexture("resource/Xpic.png");

	//游戏所用到的字体资源纹理
	SDL_Texture* titlePage_btn0 = //首页三个按钮的文字
		renderText("Single Play",
			"ttf/consolab.ttf",
			SS.black, 64, gRenderer);
	SDL_Texture* titlePage_btn1 = 
		renderText("Multi Play",
			"ttf/consolab.ttf",
			SS.black, 64, gRenderer);
	SDL_Texture* titlePage_btn2 =
		renderText("About us & Help",
			"ttf/consolab.ttf",
			SS.black, 64, gRenderer);

	SDL_Texture* titlePage_title = //首页标题
		renderText("OOXX Chess!",
			"ttf/consolab.ttf",
			SS.red, 256, gRenderer);

	//数字0-9的纹理
	SDL_Texture* num_0 = renderText("0",
		"ttf/consolab.ttf",
		SS.black, 64, gRenderer);
	SDL_Texture* num_1 = renderText("1",
		"ttf/consolab.ttf",
		SS.black, 64, gRenderer);
	SDL_Texture* num_2 = renderText("2",
		"ttf/consolab.ttf",
		SS.black, 64, gRenderer);
	SDL_Texture* num_3 = renderText("3",
		"ttf/consolab.ttf",
		SS.black, 64, gRenderer);
	SDL_Texture* num_4 = renderText("4",
		"ttf/consolab.ttf",
		SS.black, 64, gRenderer);
	SDL_Texture* num_5 = renderText("5",
		"ttf/consolab.ttf",
		SS.black, 64, gRenderer);
	SDL_Texture* num_6 = renderText("6",
		"ttf/consolab.ttf",
		SS.black, 64, gRenderer);
	SDL_Texture* num_7 = renderText("7",
		"ttf/consolab.ttf",
		SS.black, 64, gRenderer);
	SDL_Texture* num_8 = renderText("8",
		"ttf/consolab.ttf",
		SS.black, 64, gRenderer);
	SDL_Texture* num_9 = renderText("9",
			"ttf/consolab.ttf",
			SS.black, 64, gRenderer); 

	//通知窗口文字纹理
	SDL_Texture* alert_PairCodeText =
		renderText("Please input pair code:",
			"ttf/consolab.ttf",
			SS.black, 64, gRenderer);
		
private:
	SDL_Texture* XXX() {
		SDL_Texture* temp = NULL;
		
		return temp;
	}
};

