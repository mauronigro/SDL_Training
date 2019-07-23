#include "stage.h"

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer(void);
static void doFighters(void);
static void spawnEnemies(void);
static void drawFighters(void);
static void doBullets(void);
static void drawPlayer(void);
static void drawBullets(void);
static void clipPlayer(void);
static int hitPlayer(struct entity* e);
static struct entity* player;
static SDL_Texture* bulletTexture;
static SDL_Texture* enemyTexture;
static int enemySpawnTimer;
void initStage(void)
{
	principal.delegate.logic = logic;
	principal.delegate.draw = draw;
	
	memset(&estado, 0, sizeof(struct stage));
	estado.fighterTail = &estado.fighterHead;
	estado.bulletTail = &estado.bulletHead;
	
	initPlayer();
	
	bulletTexture = loadTexture("gfx/playerBullet.png");
	enemyTexture = loadTexture("gfx/pigeon.png");
	enemySpawnTimer = 0;
}

static void initPlayer()
{
	player = malloc(sizeof(struct entity));
	memset(player, 0, sizeof(struct entity));
	estado.fighterTail->next = player;
	estado.fighterTail = player;
	player->x = 100;
	player->y = 100;
	player->texture = loadTexture("gfx/magela.png");
	player->side = SIDE_PLAYER;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void logic(void)
{
	doPlayer();
	
	doFighters();
	
	doBullets();
	
	spawnEnemies();
	
	clipPlayer();
}

static void clipPlayer(void)
{
	if (player != NULL)
	{
		if (player->x < 0)
		{
			player->x = 0;
		}
		
		if (player->y < 0)
		{
			player->y = 0;
		}
		
		if (player->x > SCREEN_WIDTH / 2)
		{
			player->x = SCREEN_WIDTH / 2;
		}
		
		if (player->y > SCREEN_HEIGHT - player->h)
		{
			player->y = SCREEN_HEIGHT - player->h;
		}
	}
}

static void doPlayer(void)
{
	player->dx = player->dy = 0;
	if(player->reload > 0)
	{
		player->reload--;
	}
	
	if(principal.keyboard[SDL_SCANCODE_UP])
	{
		player->dy = - PLAYER_SPEED;
	}
	
	if(principal.keyboard[SDL_SCANCODE_DOWN])
	{
		player->dy = PLAYER_SPEED;
	}
	
	if(principal.keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = - PLAYER_SPEED;
	}
	
	if(principal.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_SPEED;
	}
	
	if(principal.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
	{
		fireBullet();
	}
	player->x += player->dx;
	player->y += player->dy;
}

static void doFighters(void)
{
	struct entity *e, *prev;
	for(e = estado.fighterHead.next; e != NULL; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;
		if(e != player && (e->x < -(e->w) || e->health == 0 || hitPlayer(e)))
		{
			if(e == estado.fighterTail)
			{
				estado.fighterTail = prev;
			}	
			
			prev->next = e->next;
			free(e);
			e = prev;
		}
		
		prev = e;
	}
}

static void spawnEnemies(void)
{
	struct entity* enemy;
	
	if(--enemySpawnTimer <= 0)
	{
		enemy = malloc(sizeof(struct entity));
		memset(enemy, 0, sizeof(struct entity));
		estado.fighterTail->next = enemy;
		estado.fighterTail = enemy;
		enemy->health = 2;
		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT;
		enemy->texture = enemyTexture;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
		enemy->dx = -5;
		enemySpawnTimer = 30 + (rand() % 60);
		enemy->side = SIDE_ALIEN;	
	}
}

static void drawFighters(void)
{
	struct entity* e;
	for(e = estado.fighterHead.next; e!=  NULL; e = e->next)
	{
		blit(e->texture, e->x, e->y);
	}
}

static void fireBullet(void)
{
	struct entity* bullet;
	bullet = malloc(sizeof(struct entity));
	memset(bullet, 0, sizeof(struct entity));
	estado.bulletTail->next = bullet;
	estado.bulletTail = bullet;
	
	bullet->x = 50+player->x;
	bullet->y = player->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = bulletTexture;
	bullet->side = SIDE_PLAYER;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	bullet->y += (player->h - bullet->h)/2;	
	player->reload = 8;
}

static int bulletHitFighter(struct entity* b)
{
	struct entity* e;
	for(e = estado.fighterHead.next; e != NULL; e = e->next)
	{
		if(e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
		{
			b->health = 0;
			e->health--;
			return 1;
		}
	}	
	return 0;
}

static int hitPlayer(struct entity* e)
{
	return collision(player->x, player->y, player->w, player->h, e->x, e->y, e->w, e->h);
}


static void doBullets(void)
{
	struct entity* b;
	struct entity* prev;

	prev = &estado.bulletHead;
	
	for(b = estado.bulletHead.next; b!= NULL; b= b->next)
	{
		b->x += b->dx;
		b->y += b->dy;
		
		if(bulletHitFighter(b) || b->x > SCREEN_WIDTH)
		{
			if(b == estado.bulletTail)
			{
				estado.bulletTail = prev;
			}
			
			prev->next = b->next;
			free(b);
			b = prev;
		}
		prev = b;
	}
}

static void draw(void)
{
	drawPlayer();
	drawFighters();
	drawBullets();
}

static void drawPlayer(void)
{
	blit(player->texture, player->x, player->y);
}

static void drawBullets(void)
{
	struct entity* b;
	for(b = estado.bulletHead.next; b!= NULL; b = b->next)
	{
		blit(b->texture, b->x, b->y);
	}

}