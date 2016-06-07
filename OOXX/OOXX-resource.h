extern StyleSheet SS;
class Resource {
public:
	//游戏所用到的图片资源纹理
	SDL_Texture* titlePage_background = //首页背景
		loadTexture("resource/background.png");
	SDL_Texture* gamePage_background =	//游戏页带棋盘的背景
		loadTexture("resource/gamePage-02.png");

	//游戏所用到的字体资源纹理
	SDL_Texture* titlePage_btn0 = //首页三个按钮的文字
		renderText("Single Play",
			"ttf/consolab.ttf",
			SS.black, 32, gRenderer);
	SDL_Texture* titlePage_btn1 = 
		renderText("Multi Play",
			"ttf/consolab.ttf",
			SS.black, 32, gRenderer);
	SDL_Texture* titlePage_btn2 =
		renderText("About us & Help",
			"ttf/consolab.ttf",
			SS.black, 32, gRenderer);

	SDL_Texture* titlePage_title = //首页标题
		renderText("OOXX Chess!",
			"ttf/consolab.ttf",
			SS.red, 256, gRenderer);

};

