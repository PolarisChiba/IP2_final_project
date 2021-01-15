#include "global.h"

class MissionPage {
	public:
		MissionPage(ALLEGRO_FONT*);
			
		void Draw();
		void Destroy();
		
	private:
		ALLEGRO_BITMAP* background;
		ALLEGRO_FONT* font;
};
