#ifndef WAR_PAGE
#define WAR_PAGE

#include "global.h"
#include "button.h"

class WarPage {
	public:
		WarPage();
		void Draw();
		string Process(int, int);
		void Destroy();
		void Begin();
		
		
	private:
		ALLEGRO_BITMAP* background;
		Button *story_mode, *death_mode;
		Button *chapter_ONE, *chapter_TWO;
		Button *death_match;
		
		string chosen_mode;
};

#endif
