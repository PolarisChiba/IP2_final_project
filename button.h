#ifndef BUTTON
#define BUTTON

#include "global.h"

class Button {
	public:
		Button(const char*, int, int);
		void Draw();
		bool OnClick(int, int);
		void Destroy();
	
	private:
		ALLEGRO_BITMAP *graph;
		int x, y;
		int width, height;
		
		ALLEGRO_SAMPLE* bbb;
		ALLEGRO_SAMPLE_ID bbb_id;
};

#endif
