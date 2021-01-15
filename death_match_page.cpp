#include "death_match_page.h"

void DeathMatchPage::GainMoney(int v) {
	ifstream fin("./files/money.txt");
	int money; 
	fin >> money;
	fin.close();
	ofstream fout("./files/money.txt");
	fout << money + v << endl;
	fout.close();
}

void DeathMatchPage::Begin(Staff* _staff) {
	{
		kills = 0;
		done = false;
	}
	
	staff_one = new Staff();
	staff_two = new Staff();
	*staff_one = *staff_two = *_staff;
	level = 1;
	for (int i = 0; i < 10; ++ i) {
		bullets.push_back(new Bullet("./images/bullets/bullet.bmp", 40));
	}
	staff_one->set_pos(WINDOW_W - 100, WINDOW_H - 150);
	staff_two->set_pos(100, WINDOW_H - 150);
}

void DeathMatchPage::Play(bool *key_state) {
	if (staff_one->get_health_point() != 0 || staff_two->get_health_point() != 0) {
		Move(key_state);
		Coming();
		Shot(key_state);
		Collide();
	}
}

void DeathMatchPage::Collide() {
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
				j->Hit(staff_one->get_attack_damage());
				if (j->get_health_point() == 0) GainMoney(1), kills += 1;
			}
		}
	}
	
	for (auto &j : enemies) {
		if (j->get_hidden() == true) continue;
		if (staff_one->get_health_point() > 0 && Collide(staff_one->get_pos(), staff_one->get_size(), j->get_pos(), j->get_size())) {
			j->Hit(INF);
			staff_one->Hit(j->get_damage());
			kills += 1;
		}
		if (staff_two->get_health_point() > 0 && Collide(staff_two->get_pos(), staff_two->get_size(), j->get_pos(), j->get_size())) {
			j->Hit(INF);
			staff_two->Hit(j->get_damage());
			kills += 1;
		}
	}
	
	for (auto &j : enemies) {
		if (j->get_hidden() == true) continue;
		if (WINDOW_H - 10 < j->get_pos().second) {
			staff_one->Hit(2 * staff_one->get_health_point());
			staff_two->Hit(2 * staff_two->get_health_point());
		}
	}
}

bool DeathMatchPage::Collide(pair<int, int> bullets_pos, pair<int, int> bullets_size, pair<int, int> enemies_pos, pair<int, int> enemies_size) {
	return bullets_pos.first < enemies_pos.first + enemies_size.first
		&& bullets_pos.second < enemies_pos.second + enemies_size.second
		&& bullets_pos.first + bullets_size.first > enemies_pos.first
		&& bullets_pos.second + bullets_size.second > enemies_pos.second;
}

void DeathMatchPage::Shot(bool* key_state) {
	static double prev = 0;
	
	for (auto &i : bullets) {
		if (i->get_hidden() == false) {
			i->Shot(staff_one);
		}
	}
	
	if (0.2 <= al_get_time() - prev) {
		if (key_state[218] && staff_one->get_health_point() > 0) {
			for (auto &i : bullets) {
				if (i->get_hidden() == true) {
					i->Shot(staff_one);
					break;
				}
			}	
		}
		if (key_state[217] && staff_two->get_health_point() > 0) {
			debug("click")
			for (auto &i : bullets) {
				if (i->get_hidden() == true) {
					i->Shot(staff_two);
					break;
				}
			}
		}
		prev = al_get_time();
	}
}

void DeathMatchPage::Coming() {
	for (auto i : enemies) {
		if (i->get_health_point() != 0 && i->get_hidden() == false) {
			i->Show(staff_one);
		}
	}
	
	static double prev = al_get_time();
	if (1 <= al_get_time() - prev) {
		enemies.push_back(new Enemy("./images/enemy/enemy.bmp", 5 + level, 3 * level, level, level));
		for (auto i : enemies) {
			if (i->get_health_point() != 0 && i->get_hidden() == true) {
				i->Show(staff_one);
				break;
			}
		}
		if ((int)enemies.size() % 10 == 0) level += 1;
		prev = al_get_time();
	}
}

void DeathMatchPage::Move(bool* key_state) {
	{
		int vx = 0, vy = 0;
		if (key_state[ALLEGRO_KEY_UP])
	        vy -= 1;
	    if (key_state[ALLEGRO_KEY_DOWN])
	        vy += 1;
	    if (key_state[ALLEGRO_KEY_LEFT])
	        vx -= 1;
	    if (key_state[ALLEGRO_KEY_RIGHT])
	        vx += 1;
	
	    pair<int, int> _p = staff_one->get_pos();
	    pair<int, int> _sz = staff_one->get_size();
		int x = _p.first, y = _p.second;
	    y += vy * staff_one->get_speed() * (x ? 0.71f : 1);
	    x += vx * staff_one->get_speed() * (y ? 0.71F : 1);
		if (x < 0) x = 0;
		if (WINDOW_W - _sz.first < x) x = WINDOW_W - _sz.first;
		if (y < 0) y = 0;
		if (WINDOW_H - _sz.second < y) y = WINDOW_H - _sz.second;
		
		staff_one->set_pos(x, y);
	}

	{
		int vx = 0, vy = 0;
		if (key_state[ALLEGRO_KEY_W])
	        vy -= 1;
	    if (key_state[ALLEGRO_KEY_S])
	        vy += 1;
	    if (key_state[ALLEGRO_KEY_A])
	        vx -= 1;
	    if (key_state[ALLEGRO_KEY_D])
	        vx += 1;
	
	    pair<int, int> _p = staff_two->get_pos();
	    pair<int, int> _sz = staff_two->get_size();
		int x = _p.first, y = _p.second;
	    y += vy * staff_two->get_speed() * (x ? 0.71f : 1);
	    x += vx * staff_two->get_speed() * (y ? 0.71F : 1);
		if (x < 0) x = 0;
		if (WINDOW_W - _sz.first < x) x = WINDOW_W - _sz.first;
		if (y < 0) y = 0;
		if (WINDOW_H - _sz.second < y) y = WINDOW_H - _sz.second;
		
		staff_two->set_pos(x, y);
	}
	
}

void DeathMatchPage::Draw() {
	if (staff_one->get_health_point() != 0 || staff_two->get_health_point() != 0) {
		al_draw_bitmap(background, 0, 0, 0);
		if (staff_one->get_health_point() > 0) staff_one->Draw();
		if (staff_two->get_health_point() > 0)staff_two->Draw();
		for (auto &i : bullets) i->Draw();
		for (auto &i : enemies) i->Draw();
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W - 400, WINDOW_H - 300, 0, ("KILLS: " + to_string(kills)).c_str());
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W - 400, WINDOW_H - 400, 0, ("LEVEL: " + to_string(level)).c_str());
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W - 400, WINDOW_H - 200, 0, ("HP 1: " + to_string(staff_one->get_health_point())).c_str());
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W - 400, WINDOW_H - 100, 0, ("HP 2: " + to_string(staff_two->get_health_point())).c_str());
	} else {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W / 2, WINDOW_H / 2 - 150, ALLEGRO_ALIGN_CENTER, string("CLEAR").c_str());
		al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_W / 2, WINDOW_H / 2 - 50, ALLEGRO_ALIGN_CENTER, string("LEVEL: " + to_string(level)).c_str());

		ifstream meow("./files/death_match.txt");
		int res; meow >> res;
		meow.close();
		debug(res)
		
		if (res < level) {
			ofstream hey("./files/death_match.txt");
			hey << level;
			hey.close();
		}
		
		if (done == false) {
			done = true;
			
			int money;
			ifstream fin("./files/money.txt");
			fin >> money;
			money += (level - 1) * 10;
			fin.close();
			ofstream fout("./files/money.txt");
			fout << money;
			fout.close();
		}
	}
}

void DeathMatchPage::Destroy() {
	al_destroy_bitmap(background);
	al_destroy_font(font);
}

DeathMatchPage::DeathMatchPage(ALLEGRO_FONT* _font) {
	background = al_load_bitmap("./images/background/death_match.bmp");
	font = _font;
	die = false;
}
