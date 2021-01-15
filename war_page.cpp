#include "war_page.h"

void WarPage::Begin() {
	chosen_mode = "STORY";
}

void WarPage::Draw() {
	al_draw_bitmap(background, 0, 0, 0);
	story_mode->Draw();
	death_mode->Draw();
	
	if (chosen_mode == "STORY") {
		chapter_ONE->Draw();
		ifstream fin("./files/clear_mission_two.txt");
		string s = "";
		fin >> s; 
		fin.close();
		if (s != "clear") return;
		chapter_TWO->Draw();
	}
	else if (chosen_mode == "DEATH") {
		death_match->Draw();
	}
}

string WarPage::Process(int mouse_x, int mouse_y) {
	ifstream fin("./files/clear_mission_two.txt");
	string s = "";
	fin >> s; 
	fin.close();

	if (story_mode->OnClick(mouse_x, mouse_y)) {
		chosen_mode = "STORY";
		return "WAR";
	}
	else if (death_mode->OnClick(mouse_x, mouse_y)) {
		chosen_mode = "DEATH";
		return "WAR";
	}
	else {
		if (chosen_mode == "STORY") {
			if (chapter_ONE->OnClick(mouse_x, mouse_y)) return "CHAPTER_ONE";
			else if (s == "clear" && chapter_TWO->OnClick(mouse_x, mouse_y)) return "CHAPTER_TWO";
		}
		else if (chosen_mode == "DEATH") {
			if (death_match->OnClick(mouse_x, mouse_y)) {
				return "DEATH_MATCH";
			}
		}
	}

	return "WAR";
}

void WarPage::Destroy() {
	al_destroy_bitmap(background);
	story_mode->Destroy();
	death_mode->Destroy();
}

WarPage::WarPage() {
	background = al_load_bitmap("./images/background/war.bmp");
	if (!background) debug("al_load_bitmap war.bmp");
	
	story_mode = new Button("./images/button/story.png", 50, 900);
	death_mode = new Button("./images/button/death.png", 375, 900);
	
	chapter_ONE = new Button("./images/button/chapter_one.png", 300, 300);
	chapter_TWO = new Button("./images/button/chapter_two.png", WINDOW_W - 800, 300);
	
	death_match = new Button("./images/button/death_match.png", 700, 300);
	
	chosen_mode = "STORY";
}
