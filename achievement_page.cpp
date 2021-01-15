#include "achievement_page.h"

void AchievementPage::Draw() {
	al_draw_bitmap(background, 0, 0, 0);
	int res;
	ifstream hello("./files/death_match.txt");
	hello >> res;
	al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W / 2, WINDOW_H / 2, ALLEGRO_ALIGN_CENTER, ("DEATH MATCH LEVEL: " + to_string(res)).c_str());
}

void AchievementPage::Destroy() {
	al_destroy_bitmap(background);
	al_destroy_font(font);
}

AchievementPage::AchievementPage(ALLEGRO_FONT* _font) {
	background = al_load_bitmap("./images/background/achievement.bmp");
	font = _font;
}
