class Timer{
public:
	void fpsControl();				//限制帧数
	Uint32 fpsCount = 0;			//帧数计数器，程序每渲染一帧都会计数

private:
	const Uint32 fps = 30;			//帧数（控制帧数请修改这个变量）
	const Uint32 FPS = 1000 / fps;	//一帧持续多少Tick
	Uint32 fpsTimer = 0;			//上一帧的Tick
};

void Timer::fpsControl() {
	if (SDL_GetTicks() - fpsTimer < FPS) {
		SDL_Delay(FPS - SDL_GetTicks() + fpsTimer);
	}
	fpsTimer = SDL_GetTicks();
	fpsCount++;
	printf("FPS Count:%d\r", fpsCount);
}