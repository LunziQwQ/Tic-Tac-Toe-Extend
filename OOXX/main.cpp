#include "string"
#include "cstring"
#include "sstream"
#include "stdio.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "OOXX-styleSheet.h"
#include "OOXX-common.h"
#include "OOXX-timer.h"
#include "OOXX-animation.h"
#include "OOXX-resource.h"
#include "MAX.h"
#include "class_coor_3.h"
#include "class_MIDBOX.h"
#include "class_BigBox.h"
#include "class_coor_9.h"
#include "function.h"
#include "OOXX_SocketManager.h"
#include "OOXX-stage.h"

//需要用的前置类的实例化
StyleSheet SS;			//SDL————样式表类
Timer timer;			//SDL————计时（帧）器类
BIGBOX bigbox(1);		//Logic————大棋盘

//页面的编号定义
const int TITLEPAGE = 0;
const int GAMEPAGE = 1;

//Network 初始化
std::string host("119.29.177.191");
std::string service("4001");
SocketManager socketManager(host, service);
char buf[100];

//主函数入口
int main(int argc, char* args[]) {

	//网络连接
	socketManager.link();
	printf("Network link success\n");
	
	//验证SDL是否成功加载
	if (!init(SS)){										
		printf("Failed to initialize!\n");
	}else {
		bool quit = false;		//程序退出flag
		int status = 0;			//当前舞台编号

		//需要等待SDL初始化完成后实例化的类

		Resource resource;		//加载纹理资源				

		//舞台初始化
		TitlePage titlePage(resource);
		GamePage gamePage(resource);


		//程序渲染主循环，当用户退出时结束
		while (!quit){		

			//事件处理循环
			while (SDL_PollEvent(&event) != 0){

				//退出事件：触发时跳出主循环
				if (event.type == SDL_QUIT){
					quit = true; 
				}

				//鼠标事件
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					int x, y;
					SDL_GetMouseState(&x, &y);			//获取鼠标点击坐标

					switch (status){
					case TITLEPAGE: status = titlePage.onClick(x, y);
						break;
					case GAMEPAGE: status = gamePage.onClick(x, y);
						break;
					}
				}

				//按键事件
				if (event.type == SDL_KEYDOWN) {
					switch (status){
					case TITLEPAGE:
						titlePage.onKeyPress(event.key.keysym.sym);
						break;
					}

				}
			}
			
			//根据状态的变化调用不同舞台的方法实现切换舞台
			switch (status) {
			case TITLEPAGE:	
				titlePage.load();
				break;
			case GAMEPAGE:
				gamePage.load();
				break;
			}

			//Test temp
			SDL_SetRenderDrawColor(gRenderer, 0x66, 0xCC, 0xFF, 0xFF);
			SDL_RenderFillRect(gRenderer, &SS.common_musicSwitchBtn);	//每个页面都存在的音乐开关

			//Network define API
			int count = socketManager.receive(buf, 100);
			if (count>0)
			{
				/*
					1.  传进去的下子信息 
					2.  error:0
					3.  red
					4.  blue
				*/
				std::string resultString(buf);

			}


			SDL_RenderPresent(gRenderer);	//渲染当前帧的纹理
			SDL_RenderClear(gRenderer);		//清除上一帧的纹理
			timer.fpsControl();				//帧数控制
		}
	}
	close();		//关闭并释放SDL相关
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
Class stage
*/
//触发事件后选择函数（选择执行哪些动作函数
//触发各个事件的动作封装为函数
//17FPS

//渲染MIDBOX状态
//bigbox.Box[][].get	 //0-2 0-2 