#include "init.h"
void init()
{
	int windowflags, rendererflags;
	rendererflags = SDL_RENDERER_ACCELERATED;
	windowflags = 0;
	// Inicializa o suporte de video do SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Nao foi possivel inicializar SDL: %s\n", SDL_GetError());
		exit(1);
	}
	// Cria uma janela
	principal.window = SDL_CreateWindow("Magela Simulator 1.0", SDL_WINDOWPOS_UNDEFINED, 
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowflags);
	
	if(!principal.window)
	{
		printf("Falha de abrir janela: %s\n", SDL_GetError());
		exit(1);
	}
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	
	principal.renderer = SDL_CreateRenderer(principal.window, -1, rendererflags);
	
	if(!principal.renderer)
	{
		printf("Nao foi possivel renderizar: %s\n", SDL_GetError());
		exit(1);
	}
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void clean()
{
	SDL_DestroyRenderer(principal.renderer);
	SDL_DestroyWindow(principal.window);
	SDL_Quit();
}