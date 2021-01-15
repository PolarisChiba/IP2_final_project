#include "store_page.h"

void StorePage::Play() {
	Draw();
}

void StorePage::Draw() {
	al_draw_bitmap(background, 0, 0, 0);
	attack->Draw();
	speed->Draw();
	hp->Draw();
	mmm->Draw();
	
	int money;
	ifstream fin("./files/money.txt");
	fin >> money;
	fin.close();
	
	al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W / 2, 50, 0, ("Exp: " + to_string(money)).c_str());
	al_draw_text(font, al_map_rgb(255, 255, 255), 200, 700, 0, string("300 EXP").c_str());
	al_draw_text(font, al_map_rgb(255, 255, 255), 700, 700, 0, string("1000 Exp").c_str());
	al_draw_text(font, al_map_rgb(255, 255, 255), 1200, 700, 0, string("100 Exp").c_str());
	
	al_draw_text(font, al_map_rgb(255, 255, 255), 200, 185, 0, to_string(a).c_str());
	al_draw_text(font, al_map_rgb(255, 255, 255), 700, 185, 0, to_string(s).c_str());
	al_draw_text(font, al_map_rgb(255, 255, 255), 1200, 185, 0, to_string(h).c_str());
}

void StorePage::Process(vector<Staff*> &staffs, int mouse_x, int mouse_y) {
	int money;
	ifstream fmoney("./files/money.txt");
	fmoney >> money;
	fmoney.close();
	
	if (attack->OnClick(mouse_x, mouse_y)) {
		if (money >= 300) {
			money -= 300;
			a += 1;
			for (auto &i : staffs) i->Change(1, 0, 0);
		}
		else cout << "EXP not enough" << endl;
	}
	if (speed->OnClick(mouse_x, mouse_y)) {
		if (money >= 1000) {
			money -= 1000;
			s += 1;
			for (auto &i : staffs) i->Change(0, 1, 0);
		}
		else cout << "EXP not enough" << endl;
	}
	if (hp->OnClick(mouse_x, mouse_y)) {
		if (money >= 100) {
			money -= 100;
			h += 1;
			for (auto &i : staffs) i->Change(0, 0, 1);
		}
		else cout << "EXP not enough" << endl;
	}
	if (mmm->OnClick(mouse_x, mouse_y)) {
		cout << "Please enter the code:";
		string s;
		cin >> s;
		
		ifstream fin("./files/mmm.txt");
		string x;
		fin >> x;
		fin.close();
		
		if (x == s) {
			ofstream fout("./files/mmm.txt");
			random_shuffle(x.begin(), x.end());
			debug(x);
			fout << x;
			money += 30000;
			fout.close();
		}
		else {
			cout << "Code incorrect" << endl;
		}
	}
	
	ofstream f1("./files/money.txt");
	f1 << money;
	f1.close();
	
	ofstream f2("./files/store.txt");
	f2 << a << " " << s << " " << h;
	f2.close();
}

void StorePage::Destroy() {
	al_destroy_bitmap(background);
}

StorePage::StorePage(ALLEGRO_FONT* _font) {
	background = al_load_bitmap("./images/background/store.bmp");
	font = _font;
	
	attack = new Button("./images/button/attack.png", 200, 300);
	speed = new Button("./images/button/speed.png", 700, 300);
	hp = new Button("./images/button/hp.png", 1200, 300);
	mmm = new Button("./images/button/mmm.png", WINDOW_W - 200, WINDOW_H - 150);
	
	ifstream fin("./files/store.txt");
	fin >> a >> s >> h;
	fin.close();
}
