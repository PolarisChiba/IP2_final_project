#include "staff_page.h"

void StaffPage::NextStaff(vector<Staff*> staffs, int next) {
	int res = 0;
	for (int i = 0; i < (int)staffs.size(); ++ i) {
		if (staffs[i]->get_name() == staff_show)
			res = i;
	}
	staff_show = staffs[(res + next + (int)staffs.size()) % (int)staffs.size()]->get_name();
}

string StaffPage::Process(int mouse_x, int mouse_y) {
	if (default_staff->OnClick(mouse_x, mouse_y)) return staff_show;
	return "nothing";
}

void StaffPage::Draw(vector<Staff*> staffs, ALLEGRO_FONT* font) {
	al_draw_bitmap(background, 0, 0, 0);
	default_staff->Draw();
	
	for (auto i : staffs) {
		if (i->get_name() == staff_show) {
			i->Draw(450, 350);
			al_draw_text(font, al_map_rgb(0, 0, 0), 450, WINDOW_H - 300, 0, i->get_name().c_str());
			al_draw_text(font, al_map_rgb(0, 0, 0), WINDOW_W - 800, 100, 0, ("Health Point: " + to_string(i->get_health_point())).c_str());
			al_draw_text(font, al_map_rgb(0, 0, 0), WINDOW_W - 800, 300, 0, ("Attack Damage: " + to_string(i->get_attack_damage())).c_str());
			al_draw_text(font, al_map_rgb(0, 0, 0), WINDOW_W - 800, 500, 0, ("Speed: " + to_string(i->get_speed())).c_str());
		}
	}
}

void StaffPage::Destroy() {
	debug("Destroy StaffPage")
	al_destroy_bitmap(background);
	default_staff->Destroy();
}

StaffPage::StaffPage() {
	background = al_load_bitmap("./images/background/staff.bmp");
	if (!background) debug("al_load_bitmap: ./images/background/staff.bmp");
	
	default_staff = new Button("./images/button/default.png", 450, WINDOW_H - 150);
	staff_show = "Red";
}
