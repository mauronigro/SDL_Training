#include "draw.h"

SDL_Texture* loadTexture(char* filename)
{
	SDL_Texture* texture;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	
	texture = IMG_LoadTexture(principal.renderer,filename);
	
	return texture;
}

void blit(SDL_Texture* texture, int x, int y)
{
	SDL_Rect dest;
	dest.x  = x;
	dest.y  = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	SDL_RenderCopy(principal.renderer, texture, NULL, &dest);
}

void prepareScene()
{
	SDL_SetRenderDrawColor(principal.renderer, 0, 0, 0, 255);
	SDL_RenderClear(principal.renderer);
}

void presentScene()
{
	SDL_RenderPresent(principal.renderer);

}
