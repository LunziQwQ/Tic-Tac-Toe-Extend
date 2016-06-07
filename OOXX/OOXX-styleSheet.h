class StyleSheet {
public:
	int Down = 0;
	//设定位置方法
	SDL_Rect setRect(int x, int y, int width, int height);
	SDL_Rect* getChessPoint();

	//颜色设定
	SDL_Color
		red = { 0xFF, 0x00, 0x00, 0xFF },
		black = { 0x00, 0x00, 0x00, 0xFF },
		white = { 0xFF, 0xFF, 0xFF, 0xFF },
		TYblue = { 0x66, 0xCC, 0xFF, 0xFF };
		

	//屏幕尺寸
	const int 
		SCREEN_WIDTH = 1024,
		SCREEN_HEIGHT = 768;

	//控件定位
	SDL_Rect
		titlePage_title =		//首页标题
		setRect(SCREEN_WIDTH*0.1, 100, SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.3),

		titlePage_btns[3] = {	//首页按钮集
		setRect(SCREEN_WIDTH*0.375, SCREEN_HEIGHT*0.5, SCREEN_WIDTH*0.25, 60),
		setRect(SCREEN_WIDTH*0.375, SCREEN_HEIGHT*0.65, SCREEN_WIDTH*0.25, 60),
		setRect(SCREEN_WIDTH*0.375, SCREEN_HEIGHT*0.8, SCREEN_WIDTH*0.25, 60),
		},

		gamePage_chessBoard =	//游戏页棋盘
		setRect(0, 0, SCREEN_WIDTH*0.75, SCREEN_HEIGHT),

		*gamePage_chessPoint = getChessPoint(),

		gamePage_title =		//游戏页右侧小标题
		setRect(SCREEN_WIDTH*0.75, 100, SCREEN_WIDTH*0.2, 200);

	
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
SDL_Rect* StyleSheet::getChessPoint() {
	SDL_Rect* rects = new SDL_Rect[81];
	//各个参数
	int
		count = 0,
		pawnSize = 68,						//单个棋子大小
		pawnMargin = 10,					//棋子之间的间距
		areaMargin = 20,					//每个3*3区域之间的间距
		boardMargin = 15,					//棋盘边缘和棋子的间距 - 棋子之间的间距
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

