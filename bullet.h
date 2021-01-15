#ifndef BULLET_HEADER
#define BULLET_HEADER

#include "global.h"
#include "staff.h"

class Bullet {
	public:
		Bullet(const char*, int);
		void Draw();
		void Destroy();
		void Shot(Staff*);
		void Disappear();
		bool get_hidden();
		pair<int, int> get_pos();
		pair<int, int> get_size();
	
	private:
		ALLEGRO_BITMAP* graph;
		ALLEGRO_SAMPLE* ccc;
		ALLEGRO_SAMPLE_ID ccc_id;
		
		int x, y, v;
		int width, height;

		bool hidden;		
};

#endif
