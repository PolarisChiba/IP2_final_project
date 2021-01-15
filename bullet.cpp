#include "bullet.h"

void Bullet::Shot(Staff* staff) {
	if (hidden == true) {
		x = staff->get_pos().first + staff->get_size().first / 2 - width / 2;
		y = staff->get_pos().second;
		hidden = false;
		al_play_sample(ccc, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &ccc_id);
		return;
	}
	else if (hidden == false) {
		y -= v;
		if (y <= -height) {
			hidden = true;
			return;
		}
	}
}

void Bullet::Disappear() {
	hidden = true;
}

void Bullet::Draw() {
	if (hidden == false) {
		al_draw_bitmap(graph, x, y, 0);
	}
}

void Bullet::Destroy() {
	al_destroy_bitmap(graph);
	al_destroy_sample(ccc);
}

bool Bullet::get_hidden() {
	return hidden;
}

pair<int, int> Bullet::get_pos() {
	return make_pair(x, y);
}

pair<int, int> Bullet::get_size() {
	return make_pair(width, height);
}

Bullet::Bullet(const char* filename, int _v) {
	graph = al_load_bitmap(filename);
	v = _v;
	hidden = true;
	
	width = al_get_bitmap_width(graph);
	height = al_get_bitmap_height(graph);
	
	ccc = al_load_sample("./bgm/bullet.ogg");
}
