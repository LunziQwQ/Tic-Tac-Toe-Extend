class Animation {
public:
	void scale(std::string path, SDL_Rect* rect, std::string mode, Uint32 startVal, Uint32 finalVal);
	void fade(std::string path, SDL_Rect* rect, std::string mode, Uint32 startVal, Uint32 finaVal);
	void pullDown(std::string path, SDL_Rect* rect);

private:


};
/*
图片切换动画
淡入淡出
比例缩放
平移
*/