#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_ttf.h>
int main(void)
{

	ALLEGRO_DISPLAY *display;

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


	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();


	ALLEGRO_BITMAP *menu = al_load_bitmap("GFX/MENU_1.png");
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	al_draw_bitmap(menu, 0, 0, 0);
	al_flip_display();
	
	
	bool done = false;

	while (!done){
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;
		}
		
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	




	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;

}
