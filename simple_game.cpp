#include "simple_game.h"

void SimpleGame::GameBegin() {
	{
		stop = false;
		time_t timer;
		time(&timer);
		
		struct tm *local = localtime(&timer);
		int a = local->tm_mday, b = local->tm_mon, c = local->tm_year;
		int _a, _b, _c;
		ifstream fin("./files/date.txt");
		fin >> _a >> _b >> _c;
		fin.close();
		if (a != _a || b != _b || c != _c) {
			int res, ret = 100;
			
			if (rand() % 3 == 1) {
				cout << "RANDOM BONUS: 100EXP" << endl;
				ret += 100;
			}
			
			int aa, bb, cc;
			ifstream fs("./files/store.txt");
			fs >> aa >> bb >> cc;
			
			if (rand() % 100 == 1) {
				cout << "SPECIAL: ATTACK UP" << endl;
				aa += 1;
			}
			if (rand() % 1000 == 1) {
				cout << "SPECIAL: SPEED UP" << endl;
				bb += 1;
			}
			if (rand() % 50 == 1) {
				cout << "SPECIAL: HP UP" << endl;
				cc += 1;
			}
			ofstream fss("./files/store.txt");
			fss << aa << " " << bb << " " << cc;
			fs.close();
			fss.close();
				
			
			ifstream fm("./files/money.txt");
			fm >> res;
			fm.close();
			
			res += ret;
			ofstream fmm("./files/money.txt");
			fmm << res;
			fmm.close();
			
			cout << "DAILY EXP GAINED" << endl;
		}
		
		ofstream fout("./files/date.txt");
		fout << a << " " << b << " " << c;
		fout.close();
	}
	
	{
		ifstream fin("./files/money.txt");
		fin >> money;
		fin.close();
	}
	
	scene = "HOME";
	home_page = new HomePage(font_pirulen_32);
	staff_page = new StaffPage();
	war_page = new WarPage();
	//chapter_one_page = new ChapterOnePage(font_pirulen_32);
	back_home = new Button("./images/button/back.png", 25, 25);
	mission_page = new MissionPage(font_pirulen_32);
	achievement_page = new AchievementPage(font_pirulen_32);
	store_page = new StorePage(font_pirulen_32);
	
	reset = new Button("./images/button/reset.png", 100, WINDOW_H - 100);
	
	memset(key_state, 0, sizeof(key_state));
	
	{
		int aa, bb, cc;
		ifstream f1("./files/store.txt");
		f1 >> aa >> bb >> cc;
		f1.close();
		
		ifstream fin("./files/staffs.txt");
		int a, b, c; string d;
		fin >> a >> b >> c >> d;
		staffs.push_back(new Staff("./images/staff/red.bmp", a + cc, b + aa, c + bb, d));
		fin >> a >> b >> c >> d;
		staffs.push_back(new Staff("./images/staff/green.bmp", a + cc, b + aa, c + bb, d));
		fin >> a >> b >> c >> d;
		staffs.push_back(new Staff("./images/staff/blue.bmp", a + cc, b + aa, c + bb, d));
		fin.close();
	}
	
	debut_staff = staffs[0];
}

void SimpleGame::GameDraw() {
	if (stop == true) return;
	if (scene == "HOME") {
		home_page->Draw();
		reset->Draw();
		debut_staff->Draw(450, 350);
	}

	if (scene == "STAFF") {
		staff_page->Draw(staffs, font_pirulen_32);
	}
	if (scene == "WAR") {
		war_page->Draw();
	}
	if (scene == "CHAPTER_ONE") {
		chapter_one_page->Play(key_state);
		chapter_one_page->Draw();
	}
	if (scene == "CHAPTER_TWO") {
		chapter_two_page->Play(key_state);
		chapter_two_page->Draw();
	}
	if (scene == "DEATH_MATCH") {
		death_match_page->Play(key_state);
		death_match_page->Draw();
	}
	if (scene == "MISSION") {
		mission_page->Draw();
	}
	if (scene == "ACHIEVEMENT") {
		achievement_page->Draw();
	}
	if (scene == "STORE") {
		store_page->Play();
	}
	
	if (scene != "HOME") {
		back_home->Draw();
	}
	al_flip_display();
}

void SimpleGame::GamePlay() {
	GameBegin();
	GameDraw();
	al_play_sample(bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &bgm_id);
	while (true) {
		bool res = GameRun();
		if (res == false) break;
		GameDraw();
	}
	GameDestroy();
}

bool SimpleGame::GameRun() {
	al_wait_for_event(game_event_queue, &event);
	
	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		debug("end game button pressed");
		return false;	
	}
	else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
		debug("KEY DOWN")
		debug(event.keyboard.keycode);
		key_state[event.keyboard.keycode] = true;
		if (event.keyboard.keycode == ALLEGRO_KEY_R) {
			stop ^= 1;
			return true;
		}
	}
	if (event.type == ALLEGRO_EVENT_TIMER) {
		if (event.timer.source == game_update_timer) {
			GameDraw();
		}
	}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) {
		debug("KEY UP")
		debug(event.keyboard.keycode)
        key_state[event.keyboard.keycode] = false;
	}
	
	if (stop) return true;
	
	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		debug(event.mouse.button);
		debug(event.mouse.x);
		debug(event.mouse.y);
		
		if (event.mouse.button == 1) {
			if (scene == "HOME") {
				if (reset->OnClick(event.mouse.x, event.mouse.y)) {
					Reset();
				}
				string res = home_page->Process(event.mouse.x, event.mouse.y);
				if (res == "staff_page") {
					scene = "STAFF";
					return true;
				}
				else if (res == "war_page") {
					scene = "WAR";
					war_page->Begin();
					return true;
				}
				else if (res == "mission_page") {
					scene = "MISSION";
					return true;
				}
				else if (res == "achievement_page") {
					scene = "ACHIEVEMENT";
					return true;
				}
				else if (res == "store_page") {
					scene = "STORE";
					return true;
				}
			}
			
			if (scene != "HOME") {
				if (back_home->OnClick(event.mouse.x, event.mouse.y)) {
					al_stop_sample(&battle_id);
					if (scene == "CHAPTER_ONE" || scene == "CHAPTER_TWO" || scene == "DEATH_MATCH") 
						al_play_sample(bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &bgm_id);
					scene = "HOME";
					return true;
				}
			}
			
			if (scene == "STAFF") {
				if (event.mouse.x <= 100) {
					staff_page->NextStaff(staffs, -1);
					return true;
				}
				if (900 <= event.mouse.x) {
					staff_page->NextStaff(staffs, 1);
					return true;
				}
				string res = staff_page->Process(event.mouse.x, event.mouse.y);
				if (res != "nothing") {
					for (auto i : staffs) {
						if (i->get_name() == res) {
							debut_staff = i;
						}
					}
					return true;
				}
			}
			
			if (scene == "STORE") {
				store_page->Process(staffs, event.mouse.x, event.mouse.y);
				return true;
			}
			
			if (scene == "WAR") {
				string res = war_page->Process(event.mouse.x, event.mouse.y);
				debug(res)
				if (res == "CHAPTER_ONE") {
					scene = "CHAPTER_ONE";
					al_stop_sample(&bgm_id);
					al_rest(0.5);
					al_play_sample(battle, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &battle_id);
					if (chapter_one_page != nullptr) delete chapter_one_page;
					chapter_one_page = new ChapterOnePage(font_pirulen_32);
					chapter_one_page->Begin(debut_staff);
				}
				else if (res == "CHAPTER_TWO") {
					{
						string ret;
						ifstream fin("./files/clear_mission_two.txt");
						fin >> ret;
						if (ret == "") {
							cout << "Please clear chapter one first." << endl;
							return true;
						}
					}
					
					scene = "CHAPTER_TWO";
					al_stop_sample(&bgm_id);
					al_rest(0.5);
					al_play_sample(battle, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &battle_id);
					if (chapter_two_page != nullptr) delete chapter_two_page;
					chapter_two_page = new ChapterTwoPage(font_pirulen_32);
					chapter_two_page->Begin(debut_staff);
				}
				else if (res == "DEATH_MATCH") {
					scene = "DEATH_MATCH";
					al_stop_sample(&bgm_id);
					al_rest(0.5);
					al_play_sample(battle, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &battle_id);
					if (death_match_page != nullptr) delete death_match_page;
					death_match_page = new DeathMatchPage(font_pirulen_32);
					death_match_page->Begin(debut_staff);
				}
			}
		}
		
	}
	
	
	return true;
}

void SimpleGame::GameDestroy() {
	al_destroy_sample(bgm);
	al_destroy_sample(battle);

	home_page->Destroy();
	delete home_page;
	staff_page->Destroy();
	delete staff_page;
	war_page->Destroy();
	delete war_page;
	back_home->Destroy();
	delete back_home;
	reset->Destroy();
	delete reset;
	for (auto &i : staffs) {
		i->Destroy();
		delete i;
	}
	staffs.clear();

	debug("0")
	al_destroy_display(game_display);
	debug("1")
	al_destroy_event_queue(game_event_queue);
	debug("2")
	al_destroy_timer(game_update_timer);
	debug("3")
	al_destroy_font(font_pirulen_32);
	debug("4")
    al_destroy_font(font_pirulen_24);
    debug("5")
}

SimpleGame::SimpleGame() {
	if (!al_init()) debug("al_init");
	if (!al_init_primitives_addon()) debug("al_init_primitives_addon");
	if (!al_init_image_addon()) debug("al_init_image_addon");
	if (!al_init_font_addon()) debug("al_init_font_addon");
	if (!al_init_ttf_addon()) debug("al_init_ttf_addon");
	if (!al_install_mouse()) debug("al_install_mouse");
	if (!al_install_keyboard()) debug("al_install_keyboard");
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(10);
	
	bgm = al_load_sample("./bgm/home.ogg");
	battle = al_load_sample("./bgm/battle.ogg");
	
	font_pirulen_32 = al_load_font("./fonts/Caviar_Dreams_Bold.ttf", 72, 0);
	font_pirulen_24 = al_load_font("./fonts/Caviar_Dreams_Bold.ttf", 72, 0);

	game_display = al_create_display(WINDOW_W, WINDOW_H);
	if (!game_display) debug("create_display");
	al_set_window_title(game_display, "A Simple Game");
	
	game_update_timer = al_create_timer(1.0f / 60);
	if (!game_update_timer) debug("game_update_timer");
	
	game_event_queue = al_create_event_queue();
	if (!game_event_queue) debug("al_create_event_queue");
	
	al_register_event_source(game_event_queue, al_get_display_event_source(game_display));
	al_register_event_source(game_event_queue, al_get_mouse_event_source());
	al_register_event_source(game_event_queue, al_get_keyboard_event_source());
	al_register_event_source(game_event_queue, al_get_timer_event_source(game_update_timer));
	
	al_start_timer(game_update_timer);
}

void SimpleGame::Reset() {
	GameDestroy();
	cout << "Reset the game?(yes/no)" << endl;
	string ans;
	cin >> ans;
	if (ans != "yes") {
		cout << "Not succeed";
		exit(0);
	}
	
	ofstream fdate("./files/date.txt");
	fdate << "0 0 0";
	fdate.close();
	
	ofstream fstore("./files/store.txt");
	fstore << "0 0 0";
	fstore.close();
	
	ofstream fname("./files/name.txt");
	fname << "";
	fname.close();
	
	ofstream fmoney("./files/money.txt");
	fmoney << "0";
	fmoney.close();
	
	ofstream fdeath("./files/death_match.txt");
	fdeath << "0";
	fdeath.close();
	
	ofstream fmone("./files/clear_mission_one.txt");
	fmone << "";
	fmone.close();
	
	ofstream fmtwo("./files/clear_mission_two.txt");
	fmtwo << "";
	fmtwo.close();
	
	ofstream fmthree("./files/clear_mission_three.txt");
	fmthree << "";
	fmthree.close();
	
	ofstream fmfour("./files/clear_mission_four.txt");
	fmfour << "";
	fmfour.close();

	ofstream fmmm("./files/mmm.txt");
	fmmm << "C8763";
	fmmm.close();

	exit(0);
}
