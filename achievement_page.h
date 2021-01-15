#include "global.h"

class AchievementPage {
	public:
		AchievementPage(ALLEGRO_FONT*);
		
		void Draw();
		void Destroy();
		
	private:
		ALLEGRO_BITMAP* background;
		ALLEGRO_FONT* font;
};
