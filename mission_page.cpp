#include "mission_page.h"

void MissionPage::Draw() {
	al_draw_bitmap(background, 0, 0, 0);
	vector<string> s = {"./files/clear_mission_one.txt", "./files/clear_mission_two.txt", "./files/clear_mission_three.txt", "./files/clear_mission_four.txt"};
	
	ifstream f;
	for (int i = 0; i < s.size(); ++ i) {
		f.open(s[i]);
		string res, ret;
		if (f >> res) {
			ret = "MISSION " + to_string(i + 1) + " CLEAR"; 
		}
		else ret = "MISSION " + to_string(i + 1) + " NOT CLEAR";
		al_draw_text(font, al_map_rgb(0, 0, 0), 350, 200 + i * 150, 0, ret.c_str());
		f.close();
	}
}

void MissionPage::Destroy() {
	al_destroy_bitmap(background);
}

MissionPage::MissionPage(ALLEGRO_FONT* _font) {
	background = al_load_bitmap("./images/background/mission.bmp");
	font = _font;
}
