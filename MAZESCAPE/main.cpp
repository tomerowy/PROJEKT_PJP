#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_ttf.h>


const float FPS = 60;

int main(void)
{

	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer = NULL;
	

	if (!al_init()) //allegro init
	{
		return -1;
	}


	timer = al_create_timer(1.0 / FPS);	
	if (!timer) {

		return -1;
	}

	display = al_create_display(640, 480);
	if (!display)
	{
		return -1;
	}



	al_set_window_title(display, "- - - - MAZESCAPE - - - - ");


	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font = al_load_ttf_font("FONTS/OratorStd.otf", 20, 2);
	//GRAFIKA MENU
	ALLEGRO_BITMAP *menu = al_load_bitmap("GFX/MENU_1.png");
	ALLEGRO_BITMAP *howtoplay = al_load_bitmap("GFX/HOW_TO_PLAY.png");
	//GRAFIKA POSTAC
	ALLEGRO_BITMAP *postac_gora_1 = al_load_bitmap("GFX/POSTAC/POSTAC_GORA_1.png");
	ALLEGRO_BITMAP *postac_gora_2 = al_load_bitmap("GFX/POSTAC/POSTAC_GORA_2.png");
	ALLEGRO_BITMAP *postac_gora_3 = al_load_bitmap("GFX/POSTAC/POSTAC_GORA_3.png");
	ALLEGRO_BITMAP *postac_dol_1 = al_load_bitmap("GFX/POSTAC/POSTAC_DOL_1.png");
	ALLEGRO_BITMAP *postac_dol_2 = al_load_bitmap("GFX/POSTAC/POSTAC_DOL_2.png");
	ALLEGRO_BITMAP *postac_dol_3 = al_load_bitmap("GFX/POSTAC/POSTAC_DOL_3.png");
	ALLEGRO_BITMAP *postac_prawa_1 = al_load_bitmap("GFX/POSTAC/POSTAC_PRAWA_1.png");
	ALLEGRO_BITMAP *postac_prawa_2 = al_load_bitmap("GFX/POSTAC/POSTAC_PRAWA_2.png");
	ALLEGRO_BITMAP *postac_prawa_3 = al_load_bitmap("GFX/POSTAC/POSTAC_PRAWA_3.png");
	ALLEGRO_BITMAP *postac_lewa_1 = al_load_bitmap("GFX/POSTAC/POSTAC_LEWA_1.png");
	ALLEGRO_BITMAP *postac_lewa_2 = al_load_bitmap("GFX/POSTAC/POSTAC_LEWA_2.png");
	ALLEGRO_BITMAP *postac_lewa_3 = al_load_bitmap("GFX/POSTAC/POSTAC_LEWA_3.png");
	//GRAFIKA LABIRYNT
	ALLEGRO_BITMAP *podloga = al_load_bitmap("GFX/POZIOMY/POZIOM_1_PODLOGA.png");
	ALLEGRO_BITMAP *labirynt_cien = al_load_bitmap("GFX/POZIOMY/LABIRYNT_POZIOM_1_CIEN.png");
	ALLEGRO_BITMAP *labirynt = al_load_bitmap("GFX/POZIOMY/LABIRYNT_POZIOM_1.png");


	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	//MENU
	char *nowagra[] = { "NEW GAME"};
	char *jakgrac[] = { "HOW TO PLAY" };
	char *wyjscie[] = { "EXIT" };
	
	bool done = false, redraw=true;
	int enter = 0;
	int choice = 0;
	al_start_timer(timer);
	
	while (!done){

		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		al_draw_bitmap(menu, 0, 0, 0); //rysuje menu(bez wyboru)
		al_flip_display();



		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				choice--;
				break;

			case ALLEGRO_KEY_DOWN:
				choice++;
				break;

			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

			case ALLEGRO_KEY_ENTER:
				enter = 1;
				break;

			}

		}
		
	

		//wracanie z exita na new game i zmiana kolorow menu
		if (choice < 0)
		{
			choice = 2;
		}
		if (choice > 2)
		{
			choice = 0;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}

	
		for (int i = 0; i < 3; i++)
		{

			int color1, color2, color3;

			if (i == choice)
			{
				color1 = 255;
				color2 = 255;
				color3 = 255;
			}
			else
			{
				color1 = 64;
				color2 = 64;
				color3 = 64;

			}

			al_draw_text(font, al_map_rgb(color1, color2, color3), 275, 190, NULL, *nowagra);

			if (i == choice + 2)
			{
				color1 = 255;
				color2 = 255;
				color3 = 255;
			}
			else
			{
				color1 = 64;
				color2 = 64;
				color3 = 64;
			}
			

			al_draw_text(font, al_map_rgb(color1, color2, color3), 260, 260, NULL, *jakgrac);

			if (i == choice + 1)
			{
				color1 = 255;
				color2 = 255;
				color3 = 255;
			}
			else
			{
				color1 = 64;
				color2 = 64;
				color3 = 64;
			}

			al_draw_text(font, al_map_rgb(color1, color2, color3), 300, 328, NULL, *wyjscie);

		}
		redraw = false;
	
		
		
		/*if (choice == 2 && enter)
		{
			enter = 1;
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	
		if (choice == 0 && enter)
		{
			enter = 1;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(menu, 0, 0, 0);
			al_draw_bitmap(howtoplay, 0, 0, 0);	
		}*/
	
		if (choice == 1 && enter)
		{
			enter = 1;
			done = true;
		
		}
		
		if (choice == 2 && enter)
		{
			enter = 1;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			

		}
	
		
		

	
			
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	



	al_destroy_timer(timer);
	al_destroy_display(display); 
	al_destroy_event_queue(event_queue);
	return 0;

}


