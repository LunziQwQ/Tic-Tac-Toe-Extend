#include "string"
#include "cstring"
#include "stdio.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "OOXX-styleSheet.h"
#include "OOXX-common.h"
#include "OOXX-timer.h"
#include "OOXX-animation.h"

int main(int argc, char* args[]) {
	StyleSheet SS;
	Timer timer;
	if (!init(SS)){
		printf("Failed to initialize!\n");
	}else {
		//Title
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		loadMediaToScreen("resource/background.png", NULL);
		
		/*gTexture = renderText("OOXX Chess!",
			                  "ttf/consolab.ttf",
			                  SS.red, 64, gRenderer);
		SDL_RenderCopy(gRenderer, gTexture, NULL, &SS.titlePage_title);
		SDL_SetRenderDrawColor(gRenderer, 0x66, 0xCC, 0xFF, 0xFF);
		SDL_RenderFillRects(gRenderer, SS.titlePage_btns, 3);
		*/
		SDL_SetRenderDrawColor(gRenderer, 0x66, 0xCC, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &SS.gamePage_chessBoard);
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRects(gRenderer, SS.gamePage_chessPoint, 81);
		SDL_SetTextureAlphaMod(gTexture,255);

		bool quit = false;
		while (!quit){
			//SDL_RenderClear(gRenderer);
			//SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
			SDL_RenderPresent(gRenderer);
			while (SDL_PollEvent(&event) != 0){
				if (event.type == SDL_QUIT){
					quit = true;
				}
				if (event.type == SDL_KEYDOWN){
					switch (event.key.keysym.sym){
						case SDLK_UP: SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
							break;
						case SDLK_DOWN: SDL_SetRenderDrawColor(gRenderer, 0x66, 0xCC, 0xFF, 0xFF);
							break;
					}
				}if (event.type == SDL_MOUSEBUTTONDOWN) {
					
				}
			}
			timer.fpsControl();
		}
	}
	close();
	return 0;
}
//OOP
/*
Class Mouse
Class Button
Class RankList
Class GameRound
Class chessBoard
Class StyleSheet
Class Animation

*/
//触发事件后选择函数（选择执行哪些动作函数
//触发各个事件的动作封装为函数
//17FPS