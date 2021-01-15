#include "global.h"
#include "staff.h"
#include "button.h"

class StorePage {
	public:
		StorePage(ALLEGRO_FONT*);
		void Draw();
		void Destroy();
		
		void Play();
		void Process(vector<Staff*>&, int, int);
		
	private:
		ALLEGRO_BITMAP* background;
		ALLEGRO_FONT* font;
		
		Button *attack, *speed, *hp, *mmm;
		int a, s, h;
};
