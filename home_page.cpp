#include "home_page.h"

void HomePage::Draw() {
	al_draw_bitmap(background, 0, 0, 0);
	staff_button->Draw();
	war_button->Draw();
	mission_button->Draw();
	achievement_button->Draw();
	store_button->Draw();
	
	int money;
	ifstream fin("./files/money.txt");
	fin >> money;
	fin.close();
	
	string name;
	ifstream fname("./files/name.txt");
	getline(fname, name);
	fname.close();
	
	al_draw_text(font, al_map_rgb(255, 255, 255), 100, 50, 0, ("Name: " + name).c_str());
	al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W / 2, 50, 0, ("Exp: " + to_string(money)).c_str());
}

string HomePage::Process(int mouse_x, int mouse_y) {
	if (staff_button->OnClick(mouse_x, mouse_y)) return "staff_page";
	else if (war_button->OnClick(mouse_x, mouse_y)) return "war_page";
	else if (mission_button->OnClick(mouse_x, mouse_y)) return "mission_page";
	else if (achievement_button->OnClick(mouse_x, mouse_y)) return "achievement_page";
	else if (store_button->OnClick(mouse_x, mouse_y)) return "store_page";
	else return "nothing";
}

void HomePage::Destroy() {
	debug("Destroy HomePage")
	al_destroy_bitmap(background);
	staff_button->Destroy();
	delete staff_button;
	war_button->Destroy();
	mission_button->Destroy();
	achievement_button->Destroy();
	delete war_button;
	store_button->Destroy();
	delete store_button;
}

HomePage::HomePage(ALLEGRO_FONT* _font) {
	background = al_load_bitmap("./images/background/home.bmp");
	if (!background) debug("al_load_bitmap: ./images/background/home.bmp");
	
	font = _font;
	
	war_button = new Button("./images/button/war.png", WINDOW_W - 600, 150);
	staff_button = new Button("./images/button/staff.png", WINDOW_W - 475, 350);
	mission_button = new Button("./images/button/mission.png", WINDOW_W - 600, 550);
	achievement_button = new Button("./images/button/achievement.png", WINDOW_W - 300, 550);
	store_button = new Button("./images/button/store.png", WINDOW_W - 500, 750);
}
