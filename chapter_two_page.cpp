#include "chapter_two_page.h"

void ChapterTwoPage::GainMoney(int v) {
	ifstream fin("./files/money.txt");
	int money; 
	fin >> money;
	fin.close();
	ofstream fout("./files/money.txt");
	fout << money + v << endl;
	fout.close();
}

void ChapterTwoPage::Begin(Staff* _debut) {
	kills = 0;
	enemies.clear();
	
	begin_time = al_get_time();
	debut_staff = new Staff();
	*debut_staff = *_debut;
	for (int i = 0; i < 10; ++ i) {
		bullets.push_back(new Bullet("./images/bullets/bullet.bmp", 40));
	}
	
	first_story = false;
	first_battle = false;
	second_story = false;
	second_battle = false;
	
	fstory.open("./files/chapter_two_story.txt");
	fenemy.open("./files/chapter_two_enemy.txt");
	
	hello = false;
	ret = 6;
	cnt = 1;
	
	int a, b;
	fenemy >> a >> b;
	boss = new Boss("./images/enemy/boss.bmp", a, b);
	boss2 = new Boss("./images/enemy/boss.bmp", a, b - 1);
	fenemy >> a >> b;
	boss_lord = new Boss("./images/enemy/lord.bmp", a, b, 1);
	
	speed_up = 0;
}

void ChapterTwoPage::Play(bool *key_state) {
	if (now_scene == "die") return;
	
	if (debut_staff->get_health_point() == 0) {
		Die();
		return;
	}
	
	static double prev = al_get_time() - 3;
	if (first_story == false) {
		now_scene = "story";
		if (al_get_time() - prev <= 2.5) return;
		
		string res;
		if (ret) {
			getline(fstory, res);
			story_text = res;
			prev = al_get_time();
			ret -= 1;
		}
		else {
			first_story = true;
			debut_staff->set_pos(WINDOW_W / 2, WINDOW_H - 100);
			now_scene = "battle";
			begin_time = al_get_time();
			story_text = "";
		}
		return;
	}
	
	if (first_battle == false) {
		
		if ((int)(al_get_time() - begin_time) / 5 != speed_up) {
			boss->Speed(1);
			boss2->Speed(1);
			speed_up += 1;
		}

		Move(key_state);
		Shot(key_state);
		boss->Show(debut_staff->get_pos().first, debut_staff->get_pos().second);
		boss2->Show();
		
		Collide();
		
		if (30 <= al_get_time() - begin_time) {
			first_battle = true;
			ret = 8;
			cnt = 0;
			ofstream fclear("./files/clear_mission_three.txt");
			fclear << "clear" << endl;
			boss->Hit(INF);
			boss2->Hit(INF);
			GainMoney(10);
			return;
		}
		
		return;
	}

	if (second_story == false) {
		now_scene = "story";
		if (al_get_time() - prev <= 2.5) return;
		if (ret) {
			string res;
			getline(fstory, res);
			story_text = res;
			prev = al_get_time();
			ret -= 1;
		}
		else {
			second_story = true;
			debut_staff->set_pos(WINDOW_W / 2, WINDOW_H - 100);
			now_boss_time = al_get_time();
			cnt = 1;
			story_text = "";
		}
		
		return;
	}

	if (second_battle == false) {
		now_scene = "battle";

		Move(key_state);
		Shot(key_state);
		boss_lord->Show();
		Collide();
		
		if (cnt == 1) {
			Coming(cnt, prev, fenemy, false);
			cnt = 2;
		}
		else {
			Coming(cnt, prev, fenemy, true);
			cnt = 2;
		}
		
		if (boss_lord->IsAlive() == false) {
			second_battle = true;
			ret = 5;
		}
		
		return;
	}
	
	now_scene = "story";
	if (al_get_time() - prev <= 2.5) return;
	
	string res;
	if (ret) {
		getline(fstory, res);
		story_text = res;
		prev = al_get_time();
		ret -= 1;
	}
	
	ofstream fclear("./files/clear_mission_four.txt");
	fclear << "clear" << endl;
	
	return;
}



bool ChapterTwoPage::Collide(pair<int, int> bullets_pos, pair<int, int> bullets_size, pair<int, int> enemies_pos, pair<int, int> enemies_size) {
	return bullets_pos.first < enemies_pos.first + enemies_size.first
		&& bullets_pos.second < enemies_pos.second + enemies_size.second
		&& bullets_pos.first + bullets_size.first > enemies_pos.first
		&& bullets_pos.second + bullets_size.second > enemies_pos.second;
}

void ChapterTwoPage::Collide() {
	for (auto &i : bullets) {
		for (auto &j : enemies) {
			if (i->get_hidden() == true || j->get_hidden() == true) continue;
			pair<int, int> bullets_pos = i->get_pos();
			pair<int, int> bullets_size = i->get_size();
			pair<int, int> enemies_pos = j->get_pos();
			pair<int, int> enemies_size = j->get_size();
			
			if (Collide(bullets_pos, bullets_size, enemies_pos, enemies_size)) {
				debug("collide")
				i->Disappear();
				j->Hit(debut_staff->get_attack_damage());
				if (j->get_health_point() == 0) {
					kills += 1;
					GainMoney(1);
				}
			}
		}
	}
	
	for (auto &j : enemies) {
		if (j->get_hidden() == true) continue;
		if (Collide(debut_staff->get_pos(), debut_staff->get_size(), j->get_pos(), j->get_size())) {
			j->Hit(INF);
			if (j->get_health_point() == 0) {
				kills += 1;
				GainMoney(1);
			}
			if (debut_staff->Hit(j->get_damage()) == false) {
				Die();
			}
		}
	}
	
	for (auto &j : enemies) {
		if (j->get_hidden() == true) continue;
		if (WINDOW_H - 10 < j->get_pos().second) {
			Die();
		}
	}
	
	if (boss2 != nullptr && boss->IsAlive() == true) {
		if (Collide(debut_staff->get_pos(), debut_staff->get_size(), boss2->get_pos(), boss2->get_size())) {
			if (debut_staff->Hit(INF) == false) {
				Die();
			}
		}
	}
	
	if (boss != nullptr && boss->IsAlive() == true) {
		if (Collide(debut_staff->get_pos(), debut_staff->get_size(), boss->get_pos(), boss->get_size())) {
			if (debut_staff->Hit(INF) == false) {
				Die();
			}
		}
		
		for (auto &i : bullets) {
			if (i->get_hidden() == true) continue;
			if (Collide(i->get_pos(), i->get_size(), boss->get_pos(), boss->get_size())) {
				boss->Hit(debut_staff->get_attack_damage());
				i->Disappear();
			}
		}
	}
	
	if (boss_lord != nullptr && boss_lord->IsAlive() == true) {
		if (Collide(debut_staff->get_pos(), debut_staff->get_size(), boss_lord->get_pos(), boss_lord->get_size())) {
			if (debut_staff->Hit(INF) == false) {
				Die();
			}
		}
		
		for (auto &i : bullets) {
			if (i->get_hidden() == true) continue;
			if (Collide(i->get_pos(), i->get_size(), boss_lord->get_pos(), boss_lord->get_size())) {
				boss_lord->Hit(debut_staff->get_attack_damage());
				i->Disappear();
			}
		}
	}
}

void ChapterTwoPage::Die() {
	now_scene = "die";
}

void ChapterTwoPage::Coming(int &cnt, double &prev, ifstream& fin, bool hello) {
	
	if (enemies.size() == 0) {
		if (0 <= al_get_time() - prev) {
			static int x, a, b, c, d; 
			if (hello == false) fin >> x >> a >> b >> c >> d;
			for (int i = 1; i <= x; ++ i) {
				enemies.push_back(new Enemy("./images/enemy/enemy.bmp", a + i / 5, b + i / 3, c + i / 15, d + i / 20));
			}
			prev = al_get_time();
		}
	}
	else {
		for (auto i : enemies) {
			if (i->get_health_point() != 0 && i->get_hidden() == false) {
				i->Show(debut_staff);
			}
		}
	
		if (1 <= al_get_time() - prev) {

			for (auto i : enemies) {
				if (i->get_health_point() != 0 && i->get_hidden() == true) {
					i->Show(debut_staff);
					break;
				}
			}
			prev = al_get_time();
		}
		
		bool ok = false;
		for (auto i : enemies) {
			if (i->get_health_point() != 0) {
				ok = true;
			}
		}
		if (ok == false) {
			cnt += 1;
			enemies.clear();
		}
	}
}

void ChapterTwoPage::Shot(bool* key_state) {
	static double prev = 0;
	
	for (auto &i : bullets) {
		if (i->get_hidden() == false) {
			i->Shot(debut_staff);
		}
	}
	
	if (0.2 <= al_get_time() - prev) {
		if (key_state[ALLEGRO_KEY_SPACE]) {
			for (auto &i : bullets) {
				if (i->get_hidden() == true) {
					i->Shot(debut_staff);
					prev = al_get_time();
					break;
				}
			}	
		}
		
	}
}

void ChapterTwoPage::Move(bool* key_state) {
	int vx = 0, vy = 0;
	if (key_state[ALLEGRO_KEY_UP])
        vy -= 1;
    if (key_state[ALLEGRO_KEY_DOWN])
        vy += 1;
    if (key_state[ALLEGRO_KEY_LEFT])
        vx -= 1;
    if (key_state[ALLEGRO_KEY_RIGHT])
        vx += 1;

    pair<int, int> _p = debut_staff->get_pos();
    pair<int, int> _sz = debut_staff->get_size();
	int x = _p.first, y = _p.second;
    y += vy * debut_staff->get_speed() * (x ? 0.71f : 1);
    x += vx * debut_staff->get_speed() * (y ? 0.71F : 1);
	if (x < 0) x = 0;
	if (WINDOW_W - _sz.first < x) x = WINDOW_W - _sz.first;
	if (y < 0) y = 0;
	if (WINDOW_H - _sz.second < y) y = WINDOW_H - _sz.second;
	
	debut_staff->set_pos(x, y);
}

void ChapterTwoPage::Draw() {
	if (now_scene == "story") {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W / 2, WINDOW_H / 2 - 100, ALLEGRO_ALIGN_CENTER, story_text.c_str());
	}
	else if (now_scene == "battle") {
		al_draw_bitmap(background, 0, 0, 0);
		debut_staff->Draw();
		for (auto i : bullets) {
			i->Draw();
		}
		for (auto i : enemies) {
			i->Draw();
		}
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W - 400, WINDOW_H - 300, 0, ("KILLS: " + to_string(kills)).c_str());
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W - 400, WINDOW_H - 200, 0, ("HP: " + to_string(debut_staff->get_health_point())).c_str());
		if (boss != nullptr && boss->IsAlive() == true) {
			boss->Draw();
			al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W - 400, WINDOW_H - 100, 0, (to_string((int)(30 - al_get_time() + begin_time)) + " sec").c_str());
		}
		if (boss2 != nullptr && boss2->IsAlive() == true) {
			boss2->Draw();
		}
		if (boss_lord != nullptr && boss_lord->IsAlive() == true) {
			boss_lord->Draw();
			al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W - 600, WINDOW_H - 100, 0, ("Enemy HP: " + to_string(boss_lord->get_health_point())).c_str());
		}
	}
	else if (now_scene == "die") {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W / 2, WINDOW_H / 2, ALLEGRO_ALIGN_CENTER, string("Game Over").c_str());
	}
	
}

void ChapterTwoPage::Destroy() {
	al_destroy_bitmap(background);
}

ChapterTwoPage::ChapterTwoPage(ALLEGRO_FONT* _font) {
	background = al_load_bitmap("./images/background/chapter_two.bmp");
	font = _font;
	
	now_scene = "story";
}
