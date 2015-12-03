#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_ttf.h>
#include "player.h"


bool keys[] = { false, false, false, false, false,false, false, false };
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, ESCAPE, N, H};
enum STATE{MENU,HOWTO,GAME,GAMEOVER};

void InitPlayer(Player &player);
void DrawPlayer(Player &player);

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



	al_set_window_title(display, "- - - - MAZESCAPE - - - - ");
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
	bool done = false, render = false, draw=true, active=false;
	int state = MENU;
	Player player;
	const int stand = 4;
	const int maxFrame = 2;
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 7;


	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	
	
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
	ALLEGRO_BITMAP *labirynt = al_load_bitmap("GFX/POZIOMY/LABIRYNT_POZIOM_1.png");
	ALLEGRO_BITMAP *labiryntcien = al_load_bitmap("GFX/POZIOMY/LABIRYNT_POZIOM_1_CIEN.png");


	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	
	player.x = 410;
	player.y = 390;
	player.speed = 3;
	player.boundx = 20;
	player.boundy = 20;
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	//MENU

	
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
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
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
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
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
				if (keys[UP])
					player.y -= player.speed;
				if (player.y < 60)
					player.y = 60;

				if (keys[DOWN])
					player.y += player.speed;
					if (player.y > 395)
						player.y = 395;
				if (keys[LEFT])
					player.x -= player.speed;
					if (player.x < 55)
						player.x = 55;
				if (keys[RIGHT])
					player.x += player.speed;
					if (player.x > 575)
						player.x = 575;

			}
			else if (state == GAMEOVER)
			{
			}
		}
	
		if (render && al_is_event_queue_empty(event_queue))
		{
			
			render = false;
			switch (state)
			{
			case MENU:
				al_draw_bitmap(menu, 0, 0, 0);
			
				break;
			case HOWTO:
				al_draw_bitmap(menu, 0, 0, 0);
				al_draw_bitmap(howtoplay, 0, 0, 0);
				break;
			case GAME:
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(podloga, 0, 0, 0);
				al_draw_bitmap(labiryntcien, 0, 0, 0);
				al_draw_bitmap(labirynt, 0, 0, 0);
				
				
			
					if (keys[LEFT]){

						al_draw_bitmap(postac[curFrame], player.x, player.y, 0);
					}

					else if (keys[RIGHT]){

						al_draw_bitmap(postac3[curFrame], player.x, player.y, 0);
					}

					else if (keys[UP]){

						al_draw_bitmap(postac1[curFrame], player.x, player.y, 0);
					}
					else if (keys[DOWN]){

						al_draw_bitmap(postac2[curFrame], player.x, player.y, 0);
					}
					
					

				break;
			case GAMEOVER:

				break;
			}
		}
	

	
		
		
	
	
	
		
		

	
			
		al_flip_display();
		
	}
	


	
	al_destroy_timer(timer);
	al_destroy_display(display); 
	al_destroy_event_queue(event_queue);
	return 0;

}



