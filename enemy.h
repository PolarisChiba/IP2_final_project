#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "global.h"
#include "staff.h"

class Enemy {
	public:
		Enemy();
		Enemy(const char*, int, int, int, int);
	
		int get_health_point();
		int get_damage();
		pair<int, int> get_speed();
		pair<int, int> get_pos();
		pair<int, int> get_size();
		bool get_hidden();
		
		void set_hidden(bool);
		void Draw();
		void Hit(int);
		
		void Show(Staff*);
	
	private:
		ALLEGRO_BITMAP* graph;
		
		int _hp;
		int health_point;
		int damage;
		int vx, vy;
		
		int x, y;
		int height;
		int width;
		
		bool hidden;
};

#endif
