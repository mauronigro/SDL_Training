#include "common.h"

extern void blit(SDL_Texture* texture, int x, int y);
extern SDL_Texture* loadTexture(char* filename);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern struct app principal;
extern struct stage estado;