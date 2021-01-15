#include "staff.h"

string Staff::get_name() {
	return name;
}
int Staff::get_health_point() {
	return health_point;
}
int Staff::get_attack_damage() {
	return attack_damage;
}
int Staff::get_speed() {
	return speed;
}

pair<int, int> Staff::get_pos() {
	return make_pair(x, y);
}

pair<int, int> Staff::get_size() {
	return make_pair(width, height);
}

void Staff::set_pos(int _x, int _y) {
	x = _x;
	y = _y;
}

void Staff::set_v(int _vx, int _vy) {
	vx = _vx;
	vy = _vy;
}

bool Staff::Hit(int dam) {
	health_point -= dam;
	if (health_point <= 0) {
		health_point = 0;
		return false;
	}
	return true;
}

void Staff::Change(int _a, int _s, int _h) {
	health_point += _h;
	speed += _s;
	attack_damage += _a;
}

void Staff::Draw() {
	al_draw_bitmap(graph, x, y, 0);
}

void Staff::Draw(int _x, int _y) {
	al_draw_bitmap(graph, _x, _y, 0);
}

void Staff::Destroy() {
	al_destroy_bitmap(graph);
}

Staff::Staff() {
	
}

Staff::Staff(const char* filename, int hp, int ad, int sp, string _name) {
	graph = al_load_bitmap(filename);
	
	health_point = hp;
	attack_damage = ad;
	speed = sp;
	name = _name;
	
	x = y = 0;
	vx = vy = 0;
	width = al_get_bitmap_width(graph);
	height = al_get_bitmap_height(graph);
}
