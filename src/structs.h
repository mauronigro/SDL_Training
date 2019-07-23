#include "defs.h"
struct delegate{
	void(*logic)(void);
	void(*draw)(void);
};


struct app
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	struct delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];	
};

struct entity{
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int side;
	int reload;
	SDL_Texture* texture;
	struct entity* next;
};

struct stage
{
	struct entity fighterHead, *fighterTail;
	struct entity bulletHead,  *bulletTail;
};
