#ifndef BOSS_HEADER
#define BOSS_HEADER

#include "global.h"

class Boss {
	public:
		Boss(const char*, int, int);
		Boss(const char*, int, int, int);
		
		void Draw();
		void Destroy();
		
		void Show();
		void Show(int, int);
		pair<int, int> get_pos();
		pair<int, int> get_size();
		void Speed(int);
		void Hit(int);
		bool IsAlive();
		
		int get_health_point();
	
	private:
		ALLEGRO_BITMAP* graph;
		
		int _hp;
		int health_point;
		int x, y;
		int px, py;
		int v;
		int qqq;
		int width, height;
		
		bool hidden;
};

#endif
