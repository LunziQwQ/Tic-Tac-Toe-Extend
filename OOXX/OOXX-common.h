//公共方法 function
bool init(StyleSheet SS);
bool mouseIsOn(SDL_Rect rect, int x, int y);
void close();
SDL_Surface* loadSurface(std::string path);
SDL_Texture* loadTexture(std::string path);
SDL_Texture* renderText(const std::string message,
	                    const std::string fontFile,
	                    SDL_Color color,
	                    int fontsize,
	                    SDL_Renderer *renderer);

//全局变量
SDL_Window* gWindow = NULL;		
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Event event;
SDL_Texture* gTexture = NULL;


//初始化SDL
bool init(StyleSheet SS) {
	bool status = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());	//加载失败返回-1，获取报错信息
			status = false;
	}else{
		gWindow = SDL_CreateWindow("Lunzi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SS.SCREEN_WIDTH, SS.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			status = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				status = false;
			}
			else {
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					status = false;
				}
				else {
					if (TTF_Init() != 0) {
						printf("SDL_ttf could not initialize! SDL_image Error: %s\n", TTF_GetError());
						status = false;
					}
					gScreenSurface = SDL_GetWindowSurface(gWindow);
				}
			}
		}
	}
	return status;
}

//释放内存，关闭SDL
void close(){
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_FreeSurface(gScreenSurface);
	gScreenSurface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

//加载图像资源
SDL_Texture* loadTexture(std::string path){
	//The final optimized image
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}else{
		//Convert surface to screen format
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL){
			printf("Unable to create texture from %s!SDL Error : %s\n", path.c_str(), SDL_GetError() );
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

SDL_Texture* renderText(const std::string message,
	                    const std::string fontFile,
	                    SDL_Color color, 
	                    int fontsize,
	                    SDL_Renderer *renderer) {

	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontsize);
	if (font == NULL) {
		printf("Unable to load TTF %s! SDL_ttf Error: %s\n", fontFile.c_str(), TTF_GetError());
	} else {
		SDL_Surface *surface = TTF_RenderText_Blended(font, message.c_str(), color);
		if (surface == NULL) {
			TTF_CloseFont(font);
			printf("RenderText Error!");
		} else {
			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
			if (texture == NULL) {
				printf("CreateTexture Error!");
			} else {
				SDL_FreeSurface(surface);
				TTF_CloseFont(font);
				return texture;
			}
		}
	}
}



//判断鼠标是否在控件上，x,y为鼠标坐标
bool mouseIsOn(SDL_Rect rect) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x < rect.x || x > (rect.x + rect.w)) return false;
	if (y < rect.y || y >(rect.y + rect.h)) return false;
	return true;
}