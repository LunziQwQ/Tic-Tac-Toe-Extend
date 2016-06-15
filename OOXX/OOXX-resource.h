extern StyleSheet SS;
class Resource {
public:
	//游戏所用到的图片资源纹理
	SDL_Texture* titlePage_background = //首页背景
		loadTexture("resource/titlePageBG.png");
	SDL_Texture* gamePage_background =	//游戏页带棋盘的背景
		loadTexture("resource/gamePageBG.png");
	SDL_Texture* chess_O =				//O棋子
		loadTexture("resource/Opic.png");
	SDL_Texture* chess_X =				//X棋子
		loadTexture("resource/Xpic.png");
	SDL_Texture* titlePage_btn0 =		//首页的第一个棋子
		loadTexture("resource/singleBtn.png");
	SDL_Texture* titlePage_btn1 =		//首页的第二个棋子
		loadTexture("resource/mulitBtn.png");
	SDL_Texture* titlePage_btn2 =		//首页的第三个棋子
		loadTexture("resource/helpBtn.png");
	SDL_Texture* common_alert =			//通用的通知窗口
		loadTexture("resource/alert.png");
	SDL_Texture* common_yesBtn =		//通知窗口yes按钮
		loadTexture("resource/yes.png");
	SDL_Texture* common_noBtn =			//通知窗口no按钮
		loadTexture("resource/no.png");
	//TODO:rednext 框，bluenext 框， 小标题，咖啡杯，Your turn


	//游戏所用到的字体资源纹理
	//数字0-9的纹理
	SDL_Texture* num_0 = renderText("0",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);
	SDL_Texture* num_1 = renderText("1",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);
	SDL_Texture* num_2 = renderText("2",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);
	SDL_Texture* num_3 = renderText("3",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);
	SDL_Texture* num_4 = renderText("4",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);
	SDL_Texture* num_5 = renderText("5",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);
	SDL_Texture* num_6 = renderText("6",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);
	SDL_Texture* num_7 = renderText("7",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);
	SDL_Texture* num_8 = renderText("8",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);
	SDL_Texture* num_9 = renderText("9",
		"ttf/8bitlimit.ttf",
		SS.Brown, 128, gRenderer);

	//通知窗口文字纹理
	SDL_Texture* alert_PairCodeText =
		renderText("Please input pair code:",
			"ttf/consolab.ttf",
			SS.Brown, 64, gRenderer);
		
private:
	SDL_Texture* XXX() {
		SDL_Texture* temp = NULL;
		
		return temp;
	}
};

