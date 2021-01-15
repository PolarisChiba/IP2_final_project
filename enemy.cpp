#include "enemy.h"

int Enemy::get_health_point() {
	return health_point;
}

pair<int, int> Enemy::get_speed() {
	return make_pair(vx, vy);
}

int Enemy::get_damage() {
	return damage;
}

pair<int, int> Enemy::get_pos() {
	return make_pair(x, y);
}

pair<int, int> Enemy::get_size() {
	return make_pair(width, height);
}

bool Enemy::get_hidden() {
	return hidden;
}

void Enemy::set_hidden(bool i) {
	hidden = i;
}

void Enemy::Hit(int dam) {
	health_point -= dam;
	if (health_point <= 0) {
		health_point = 0;
		hidden = true;
	}
}

void Enemy::Show(Staff* staff) {
	if (hidden == true) {
		health_point = _hp;
		x = rand() % WINDOW_W;
		y = -height;
		hidden = false;
	}
	else {
		if (health_point <= 0) {
			health_point = 0;
			hidden = true;
			return;
		}

		if (rand() % 100 == 1) vx = -vx;
		
		x += vx;
		y += vy;
		
		if (x < 0) x = 0;
		if (WINDOW_W - width < x) x = WINDOW_W - width;
		
		if (WINDOW_H < y) {
			health_point = 0;
			hidden = true;
			return;
		}
	}
}

void Enemy::Draw() {
	if (hidden == false) {
		al_draw_bitmap(graph, x, y, 0);
	}
}

Enemy::Enemy() {
	
}

Enemy::Enemy(const char *filename, int hp, int dg, int _vx, int _vy) {
	graph = al_load_bitmap(filename);
	_hp = health_point = hp;
	vx = _vx, vy = _vy;
	damage = dg;
	
	height = al_get_bitmap_height(graph);
	width = al_get_bitmap_width(graph);
	
	hidden = true;
}
