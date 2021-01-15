#ifndef STAFF
#define STAFF

#include "global.h"

class Staff {
	public:
		Staff();
		Staff(const char*, int, int, int, string);
		void Draw(int, int);
		void Draw();
		void Destroy();
		
		string get_name();
		int get_health_point();
		int get_attack_damage();
		int get_speed();
		
		pair<int, int> get_pos();
		pair<int, int> get_size();
		
		void set_pos(int, int);
		void set_v(int, int);
		
		bool Hit(int);
		
		void Change(int, int, int);
		
	private:
		ALLEGRO_BITMAP* graph;
		
		int health_point;
		int attack_damage;
		int speed;
		string name;
		
		int x, y;
		int vx, vy;
		int width, height;
};

#endif
