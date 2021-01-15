#ifndef HOME_PAGE
#define HOME_PAGE

#include "global.h"
#include "button.h"

class HomePage {
	public:
		HomePage(ALLEGRO_FONT*);
		void Draw();
		string Process(int, int);
		void Destroy();
		
	private:
		ALLEGRO_BITMAP* background;
		ALLEGRO_FONT* font;
		Button* staff_button;
		Button* war_button;
		Button* mission_button;
		Button* achievement_button;
		Button* store_button;
};

#endif
