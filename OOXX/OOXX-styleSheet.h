class StyleSheet {
public:
	int Down = 0;
	//设定位置方法
	SDL_Rect setRect(int x, int y, int width, int height);

	//颜色设定
	SDL_Color
		red = { 0xFF, 0x00, 0x00, 0xFF },
		black = { 0x00, 0x00, 0x00, 0xFF },
		white = { 0xFF, 0xFF, 0xFF, 0xFF },
		Gray = { 0xC0,0xC0,0xC0 ,0xFF },
		TYblue = { 0x66, 0xCC, 0xFF, 0xFF };
		
		

	//屏幕尺寸
	const int 
		SCREEN_WIDTH = 1024,
		SCREEN_HEIGHT = 768;

	//控件定位
	SDL_Rect
		//首页*********************
		titlePage_title =		//首页标题
		setRect(SCREEN_WIDTH*0.1, 100, SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.3),

		titlePage_btns[3] = {	//首页按钮集
		setRect(SCREEN_WIDTH*0.375, SCREEN_HEIGHT*0.5, SCREEN_WIDTH*0.25, 60),
		setRect(SCREEN_WIDTH*0.375, SCREEN_HEIGHT*0.65, SCREEN_WIDTH*0.25, 60),
		setRect(SCREEN_WIDTH*0.375, SCREEN_HEIGHT*0.8, SCREEN_WIDTH*0.25, 60),
	},


		//游戏页********************
		gamePage_chessBoard =	//游戏页棋盘
		setRect(0, 0, SCREEN_WIDTH*0.75, SCREEN_HEIGHT),

		*gamePage_chessPoint = getChessPointRects(),	//81个棋子

		gamePage_title =		//游戏页右侧小标题
		setRect(SCREEN_WIDTH*0.75, 100, SCREEN_WIDTH*0.2, 200),


		//通知窗口******************
		alert_alertPairCodeText =	//"请输入配对码"
		setRect(SCREEN_WIDTH*0.15, SCREEN_HEIGHT*0.35, 400, 50),

		*alert_PairCode = getPairCodeRects(),	//四个配对码

		alert_confirmBtn =						//通知窗口确定按钮
		setRect(SCREEN_WIDTH*0.77, SCREEN_HEIGHT*0.62, 100, 50),

		alert_cancleBtn =						//通知窗口取消按钮
		setRect(SCREEN_WIDTH*0.65, SCREEN_HEIGHT*0.62, 100, 50),


		//通用**********************
		common_musicSwitchBtn =					//背景音乐控制按钮
		setRect(SCREEN_WIDTH-60, SCREEN_HEIGHT-60, 50, 50),

		common_alertWindow =	//通用的通知窗口
		setRect(SCREEN_WIDTH*0.1, SCREEN_HEIGHT*0.3, SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.4);

private:
	SDL_Rect* getChessPointRects();
	SDL_Rect* getPairCodeRects();
};
//设定位置
SDL_Rect StyleSheet::setRect(int x, int y, int width, int height) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y + Down;
	rect.w = width;
	rect.h = height;
	return rect;
}

//生成棋盘rects数组
SDL_Rect* StyleSheet::getChessPointRects() {
	SDL_Rect* rects = new SDL_Rect[81];

	//各个参数
	int
		count = 0,
		pawnSize = 70,						//单个棋子大小
		pawnMargin = 9,						//棋子之间的间距
		areaMargin = 12,					//每个3*3区域之间的间距
		boardMargin = 20,					//棋盘边缘和棋子的间距 - 棋子之间的间距
		prev_x = boardMargin,				//运算中间变量，上一个棋子的x偏移量
		prev_y = boardMargin + pawnMargin;	//运算中间变量，上一个棋子的y偏移量
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					rects[count++] = setRect(prev_x + pawnMargin, prev_y, pawnSize, pawnSize);
					prev_x += pawnMargin + pawnSize;
				}
				prev_x += areaMargin - pawnMargin;
			}
			prev_x = boardMargin;
			prev_y += pawnSize + pawnMargin;
		}
		prev_x = boardMargin;
		prev_y += areaMargin - pawnMargin;
	}
	return rects;
}

//生成四位验证码位置
SDL_Rect* StyleSheet::getPairCodeRects() {
	SDL_Rect* rects = new SDL_Rect[4];
	for (int i = 0; i < 4; i++){
		rects[i] = setRect(SCREEN_WIDTH*0.21+i*(50+SCREEN_WIDTH*0.11), SCREEN_HEIGHT*0.42, SCREEN_WIDTH*0.11, SCREEN_HEIGHT*0.18);
	}
	return rects;
}
