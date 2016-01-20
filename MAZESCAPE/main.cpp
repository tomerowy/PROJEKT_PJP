#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_ttf.h>
#include<allegro5\allegro_audio.h>
#include<allegro5\allegro_acodec.h>
#include "player.h"
#include "Wall.h"



bool keys[] = { false, false, false, false, false,false, false, false, false};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, ESCAPE, N, H, L};
enum STATE{MENU,HOWTO,GAME,GAMEOVER, NEXTLEVEL, LEVEL2, LAST};

void InitPlayer(Player &player);
void DrawPlayer(Player &player);

bool Collision(int x, int y, int wx, int wy, int w, int h)
{
	if (x + w-3 < wx || x > wx + w-3 || y + h-3 < wy || y >wy + h-3)
	{
		return false;
	}
	else
		return true;
}


int main(void)
{

	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer = NULL;


	if (!al_init()) //allegro init
	{
		return -1;
	}



	display = al_create_display(640, 480);
	if (!display)
	{
		return -1;
	}



	al_set_window_title(display, " MAZESCAPE ");
	timer = al_create_timer(1.0 / 60);
	if (!timer) {

		return -1;
	}
	char *nowagra[] = { "NEW GAME" };
	char *jakgrac[] = { "HOW TO PLAY" };
	char *wyjscie[] = { "EXIT" };
	float gameTime = 0;
	int frames = 0;
	int FPS = 0;
	bool done = false, render = false, draw = true, active = false, goup = false, godown = false, goleft = false, goright = false, isLeft = true, isUp = false, isRight = false, isDown = false;
	bool bound = false, collision = false;

	int state = MENU;
	Player player;
	Wall wall; 
	
	const int stand = 4;
	const int maxFrame = 2;
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 7;

	int count = 3000;
	int count1 = 4000;

	int mapColumns = 32;
	int mapRows = 24;
	int mapSize = 768;
	int tileSize = 20;
	int tileSize1 = 20;


	
	//-----------------------------------MAPA LEVEL 1--------------------------------------------
	int labirynt_1[24][32] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0 },
		{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	
	//-----------------------------------MAPA LEVEL 2--------------------------------------------
	int labirynt_2[24][32] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0 },
		{ 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};


	al_install_keyboard();
	al_install_audio();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();
	
	//MUZYKA
	ALLEGRO_SAMPLE *music = al_load_sample("AUDIO/Nevermore.ogg");
	al_reserve_samples(1);

	ALLEGRO_FONT *font = al_load_ttf_font("FONTS/OratorStd.otf", 20, 2);
	
	//GRAFIKA MENU
	ALLEGRO_BITMAP *menu = al_load_bitmap("GFX/MENU_1.png");
	ALLEGRO_BITMAP *howtoplay = al_load_bitmap("GFX/HOW_TO_PLAY.png");
	
	//GRAFIKA POSTAC
	ALLEGRO_BITMAP *postacstoi[stand];
	ALLEGRO_BITMAP *postac[maxFrame];
	ALLEGRO_BITMAP *postac1[maxFrame];
	ALLEGRO_BITMAP *postac2[maxFrame];
	ALLEGRO_BITMAP *postac3[maxFrame];
	postacstoi[0] = al_load_bitmap("GFX/POSTAC/POSTAC_LEWA_1.png");
	postacstoi[1] = al_load_bitmap("GFX/POSTAC/POSTAC_GORA_1.png");
	postacstoi[2] = al_load_bitmap("GFX/POSTAC/POSTAC_DOL_1.png");
	postacstoi[3] = al_load_bitmap("GFX/POSTAC/POSTAC_PRAWA_1.png");
	postac[0] = al_load_bitmap("GFX/POSTAC/POSTAC_LEWA_2.png");
	postac[1] = al_load_bitmap("GFX/POSTAC/POSTAC_LEWA_3.png");
	postac1[0] = al_load_bitmap("GFX/POSTAC/POSTAC_GORA_2.png");
	postac1[1] = al_load_bitmap("GFX/POSTAC/POSTAC_GORA_3.png");
	postac2[0] = al_load_bitmap("GFX/POSTAC/POSTAC_DOL_2.png");
	postac2[1] = al_load_bitmap("GFX/POSTAC/POSTAC_DOL_3.png");
	postac3[0] = al_load_bitmap("GFX/POSTAC/POSTAC_PRAWA_2.png");
	postac3[1] = al_load_bitmap("GFX/POSTAC/POSTAC_PRAWA_3.png");
	
	//GRAFIKA LABIRYNT
	ALLEGRO_BITMAP *podloga = al_load_bitmap("GFX/POZIOMY/POZIOM_1_PODLOGA.png");
	ALLEGRO_BITMAP *labiryntsciana = al_load_bitmap("GFX/labiryntblock.png");
	ALLEGRO_BITMAP *meta = al_load_bitmap("GFX/meta.png");
	ALLEGRO_BITMAP *swiatlo = al_load_bitmap("GFX/swiatlo.png");
	ALLEGRO_BITMAP *cien = al_load_bitmap("GFX/cien.png");
	ALLEGRO_BITMAP *FOGcien = al_load_bitmap("GFX/FOGcien.png");

	//gameover i next level
	ALLEGRO_BITMAP *next = al_load_bitmap("GFX/NEXT.png");
	ALLEGRO_BITMAP *gameover = al_load_bitmap("GFX/GAMEOVER.png");
	ALLEGRO_BITMAP *last = al_load_bitmap("GFX/LAST.png");

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	
	// ------------------IKONA--------------
	al_set_display_icon(display, postacstoi[2]);

	// ------------------"DANE" GRACZA ,SCIANY--------------
	player.x = 580;
	player.y = 40;
	player.speed = 1.5;
	player.w = 20;
	player.h = 20;
	player.x1 = 580 ;
	player.y1 = 420;

	wall.x = 320;
	wall.y = 320;
	wall.w = 20;
	wall.h = 20;
	wall.bx = wall.w / 2;
	wall.by = wall.h / 2;


	
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	

	
	al_start_timer(timer);
	gameTime = al_current_time();
	while (!done){

		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		al_flip_display();



		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE]=true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				goleft = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				goright = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				goup = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				godown = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			
			case ALLEGRO_KEY_N:
				keys[N] = true;
				break;
			case ALLEGRO_KEY_H:
				keys[H] = true;
				break;
			case ALLEGRO_KEY_L:
				keys[L] = true;
				break;
		
			
		}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				goleft = false;
				
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				goright = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				goup = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				godown = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_N:
				keys[N] = false;
				break;
			case ALLEGRO_KEY_H:
				keys[H] = false;
				break;
			case ALLEGRO_KEY_L:
				keys[L] = false;
				break;
		
			}

		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		
		
		//GAMEUPDATE-----------------------------------------------------
		
		else if (event.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			
			
			
			
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				FPS = frames;
				frames = 0;
			}
			if (state == MENU)
			{
				if (keys[ESCAPE])
					done = true;

				if (keys[H])
				{
					state = HOWTO;
				}
				if (keys[N])
				{
					state = GAME;
				}
			}
			else if (state == HOWTO)
			{
				if (keys[SPACE])
					state = MENU;
			}
			else if(state == GAME)
			{
				

				if (++frameCount >= frameDelay)
				{
					if (++curFrame >= maxFrame)
						curFrame = 0;
					
					frameCount = 0;
				}
				if (keys[ESCAPE]){
					done = true;
				}
			
			
						if (keys[UP] )
							
						player.y -= player.speed;

						if (keys[DOWN])
							
							player.y += player.speed;

						if (keys[LEFT] )
							
							player.x -= player.speed;

						if (keys[RIGHT] )
							
							player.x += player.speed;

						for (int i = 0; i < mapColumns; i++){

							for (int j = 0; j < mapRows; j++){
								if (Collision(player.x, player.y, tileSize*(i%mapColumns), tileSize*(j%mapRows), 19, 19) && labirynt_1[j][i] == 1)
								{
									if (keys[UP])

										player.y += player.speed;

									if (keys[DOWN])

										player.y -= player.speed;

									if (keys[LEFT])

										player.x += player.speed;

									if (keys[RIGHT])

										player.x -= player.speed;
								}
							}
						}
			

								if (player.x <50 && player.y < 40)
								{
									state = NEXTLEVEL;
								}

						
					
				
				

				
					
				
			}
			
			else if (state == LEVEL2)
			{
				

				if (++frameCount >= frameDelay)
				{
					if (++curFrame >= maxFrame)
						curFrame = 0;

					frameCount = 0;
				}
				if (keys[ESCAPE]){
					done = true;
				}
				
				if (keys[UP])

					player.y1 -= player.speed;

				if (keys[DOWN])

					player.y1 += player.speed;

				if (keys[LEFT])

					player.x1 -= player.speed;

				if (keys[RIGHT])

					player.x1 += player.speed;

				for (int i = 0; i < mapColumns; i++){

					for (int j = 0; j < mapRows; j++){
						if (Collision(player.x1, player.y1, tileSize*(i%mapColumns), tileSize*(j%mapRows), 19, 19) && labirynt_2[j][i] == 1)
						{
							if (keys[UP])

								player.y1 += player.speed;

							if (keys[DOWN])

								player.y1 -= player.speed;
							
							if (keys[LEFT])

								player.x1 += player.speed;

							if (keys[RIGHT])

								player.x1 -= player.speed;
						}
					}
				}
				if (player.x1 >560 && player.y1 < 40)
				{
					state = LAST;
				}
				
			}
			else if (state == GAMEOVER)
			{
				if (keys[ESCAPE]){
					done = true;
				}
				
			}
			else if (state == NEXTLEVEL)
			{
				if (keys[ESCAPE]){
					done = true;
				}
				if (keys[L]){
					state = LEVEL2;
				}
			}

			else if (state == LAST)
			{
				if (keys[ESCAPE]){
					done = true;
				}

			}
		}
	
		if (render && al_is_event_queue_empty(event_queue))
		{
			
			render = false;
			switch (state)
			{
			case MENU:
				al_draw_bitmap(menu, 0, 0, 0);
				al_play_sample(music, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
			
				break;
			case HOWTO:
				al_draw_bitmap(menu, 0, 0, 0);
				al_draw_bitmap(howtoplay, 0, 0, 0);
				break;
			case GAME:
				
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(podloga, 0, 0, 0);
				
				
				//-----RYSOWANIE LABIRYNTU-----
				for (int i = 0; i < mapColumns; i++){

					for (int j = 0; j < mapRows; j++){

						if (labirynt_1[j][i] == 1)
						{
							al_draw_bitmap(labiryntsciana, tileSize*(i%mapColumns), tileSize*(j%mapRows), 0);

						}
						if (labirynt_1[j][i] == 2)
						{
							al_draw_bitmap(meta, tileSize*(i%mapColumns), tileSize*(j%mapRows), 0);

						}

					}
				}
				
				
				//-----SWIATLO-----
				al_draw_bitmap(swiatlo, player.x-40, player.y-40, 0);
				

				
				//-----PORUSZANIE POSTACI-----
							if (isLeft)
							{
								al_draw_bitmap(postacstoi[0], player.x, player.y, 0);
							}

							if (isRight){
								al_draw_bitmap(postacstoi[3], player.x, player.y, 0);
							}
							if (goleft){

								al_draw_bitmap(postac[curFrame], player.x, player.y, 0);
								isLeft = true;
								isRight = false;
								isUp = false;
								isDown = false;
							}


							if (goright){

								al_draw_bitmap(postac3[curFrame], player.x, player.y, 0);
								isLeft = false;
								isRight = true;
								isUp = false;
								isDown = false;

							}
							if (isUp){
								al_draw_bitmap(postacstoi[1], player.x, player.y, 0);
							}
							if (goup){
								al_draw_bitmap(postac1[curFrame], player.x, player.y, 0);
								isLeft = false;
								isRight = false;
								isUp = true;
								isDown = false;
							}
							if (isDown){
								al_draw_bitmap(postacstoi[2], player.x, player.y, 0);
							}
							if (godown)
							{
								al_draw_bitmap(postac2[curFrame], player.x, player.y, 0);
								isLeft = false;
								isRight = false;
								isUp = false;
								isDown = true;
							}
							
							//-----OGRANICZENIE WIDOCZNOSCI-----
							al_draw_bitmap(cien, 0, 0, 0);
							al_draw_bitmap(FOGcien, player.x-740, player.y-710, 0);
							
							//-----CZAS-----
							count--;
							al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 5, 0, "Time: %i", count);
							if (count == 0){
								state = GAMEOVER;
							}
						
							
							al_draw_textf(font, al_map_rgb(255, 255, 255), 535, 5, 0, "LEVEL 1");
				
					
					

				break;

		case LEVEL2:
			    
			    
				al_clear_to_color(al_map_rgb(0, 0, 0));
				
				

				al_draw_bitmap(podloga, 0, 0, 0);


				//-----RYSOWANIE LABIRYNTU-----
				for (int i = 0; i < mapColumns; i++){

					for (int j = 0; j < mapRows; j++){

						if (labirynt_2[j][i] == 1)
						{
							al_draw_bitmap(labiryntsciana, tileSize*(i%mapColumns), tileSize*(j%mapRows), 0);

						}
						if (labirynt_2[j][i] == 2)
						{
							al_draw_bitmap(meta, tileSize*(i%mapColumns), tileSize*(j%mapRows), 0);

						}

					}
				}


				//-----SWIATLO-----
				al_draw_bitmap(swiatlo, player.x1 - 40, player.y1 - 40, 0);



				//-----PORUSZANIE POSTACI-----
				if (isLeft)
				{
					al_draw_bitmap(postacstoi[0], player.x1, player.y1, 0);
				}

				if (isRight){
					al_draw_bitmap(postacstoi[3], player.x1, player.y1, 0);
				}
				if (goleft){

					al_draw_bitmap(postac[curFrame], player.x1, player.y1, 0);
					isLeft = true;
					isRight = false;
					isUp = false;
					isDown = false;
				}


				if (goright){

					al_draw_bitmap(postac3[curFrame], player.x1, player.y1, 0);
					isLeft = false;
					isRight = true;
					isUp = false;
					isDown = false;

				}
				if (isUp){
					al_draw_bitmap(postacstoi[1], player.x1, player.y1, 0);
				}
				if (goup){
					al_draw_bitmap(postac1[curFrame], player.x1, player.y1, 0);
					isLeft = false;
					isRight = false;
					isUp = true;
					isDown = false;
				}
				if (isDown){
					al_draw_bitmap(postacstoi[2], player.x1, player.y1, 0);
				}
				if (godown)
				{
					al_draw_bitmap(postac2[curFrame], player.x1, player.y1, 0);
					isLeft = false;
					isRight = false;
					isUp = false;
					isDown = true;
				}

				//-----OGRANICZENIE WIDOCZNOSCI-----
				al_draw_bitmap(cien, 0, 0, 0);
				al_draw_bitmap(FOGcien, player.x1 - 740, player.y1 - 710, 0);

				//-----CZAS-----
				count1--;
				al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 5, 0, "Time: %i", count1);
				if (count1 == 0){
					state = GAMEOVER;
				}

				al_draw_textf(font, al_map_rgb(255, 255, 255), 535, 5, 0, "LEVEL 2");

				


			break;
			
			case GAMEOVER:
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(podloga, 0, 0, 0);
				al_draw_bitmap(gameover, 0, 0, 0);
				break;
			
			case NEXTLEVEL:
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(podloga, 0, 0, 0);
				al_draw_bitmap(next, 0, 0, 0);

				break;

			case LAST:
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(podloga, 0, 0, 0);
				al_draw_bitmap(last, 0, 0, 0);
				break;
				
			}
		}
	

	

	
			
		al_flip_display();
		
	}


	al_destroy_bitmap(postacstoi[0]);
	al_destroy_bitmap(postacstoi[1]);
	al_destroy_bitmap(postacstoi[2]);
	al_destroy_bitmap(postacstoi[3]);
	al_destroy_bitmap(postac[0]);
	al_destroy_bitmap(postac[1]);
	al_destroy_bitmap(postac1[0]);
	al_destroy_bitmap(postac1[1]);
	al_destroy_bitmap(postac2[0]);
	al_destroy_bitmap(postac2[1]);
	al_destroy_bitmap(postac3[0]);
	al_destroy_bitmap(postac3[1]);
	al_destroy_bitmap(menu);
	al_destroy_bitmap(howtoplay);
	al_destroy_bitmap(next);
	al_destroy_bitmap(last);
	al_destroy_bitmap(gameover);
	al_destroy_bitmap(FOGcien);
	al_destroy_bitmap(swiatlo);
	al_destroy_bitmap(podloga);
	al_destroy_bitmap(labiryntsciana);
	al_destroy_bitmap(meta);
	al_destroy_sample(music);
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_display(display); 
	al_destroy_event_queue(event_queue);
	return 0;

}

