#include "button.h"

void Button::Draw() {
	al_draw_bitmap(graph, x, y, 0);
}

bool Button::OnClick(int mouse_x, int mouse_y) {
	if (mouse_x < x || x + width < mouse_x) return false;
	if (mouse_y < y || y + height < mouse_y) return false;
	
	al_play_sample(bbb, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &bbb_id);
	return true;
}

void Button::Destroy() {
	debug("Destroy Button")
	al_destroy_bitmap(graph);
	al_destroy_sample(bbb);
}

Button::Button(const char *filename, int _x, int _y) {
	graph = al_load_bitmap(filename);
	x = _x;
	y = _y;
	width = al_get_bitmap_width(graph);
	height = al_get_bitmap_height(graph);
	
	bbb = al_load_sample("./bgm/button.ogg");
}
