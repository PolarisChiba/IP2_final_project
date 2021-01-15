#include "boss.h"

void Boss::Show() {
	if (hidden == true && health_point != 0) {
		x = px = WINDOW_W - width / 2;
		y = py = 0;
		hidden = false;
		health_point = _hp;
	}
	else if (hidden == false) {
		if (px == x && py == y) {
			px = rand() % (WINDOW_W - width);
			py = rand() % (WINDOW_H - height);
			if (qqq == 1) py = rand() % (WINDOW_H - height - 190);
		}
		
		
		
		if (x < px) x += min(v, abs(px - x));
		else x -= min(v, abs(px - x));
		if (y < py) y += min(v, abs(py - y));
		else y -= min(v, abs(py - y));
	}
}

void Boss::Speed(int k) {
	v += 1;
}

void Boss::Show(int _x, int _y) {
	if (hidden == true && health_point != 0) {
		x = px = WINDOW_W - width / 2;
		y = py = 0;
		hidden = false;
		health_point = _hp;
	}
	else if (hidden == false) {
		if (px == x && py == y) {
			px = _x;
			py = _y;
		}
		
		if (x < px) x += min(v, abs(px - x));
		else x -= min(v, abs(px - x));
		if (y < py) y += min(v, abs(py - y));
		else y -= min(v, abs(py - y));
	}
}

void Boss::Hit(int dam) {
	health_point -= dam;
	if (health_point <= 0) {
		health_point = 0;
		hidden = true;
	}
}

bool Boss::IsAlive() {
	return (health_point != 0 && hidden == false);
}

int Boss::get_health_point() {
	return health_point;
}

pair<int, int> Boss::get_pos() {
	return make_pair(x, y);
}

pair<int, int> Boss::get_size() {
	return make_pair(width, height);
}

void Boss::Draw() {
	if (hidden == false) {
		al_draw_bitmap(graph, x, y, 0);
	}
}

void Boss::Destroy() {
	al_destroy_bitmap(graph);
}

Boss::Boss(const char *filename, int hp, int _v, int zzz) {
	graph = al_load_bitmap(filename);
	width = al_get_bitmap_width(graph);
	height = al_get_bitmap_height(graph);
	hidden = true;
	_hp = health_point = hp;
	v = _v;
	qqq = 1;
}

Boss::Boss(const char *filename, int hp, int _v) {
	graph = al_load_bitmap(filename);
	width = al_get_bitmap_width(graph);
	height = al_get_bitmap_height(graph);
	hidden = true;
	_hp = health_point = hp;
	v = _v;
	qqq = 0;
}
