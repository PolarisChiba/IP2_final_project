#ifndef SIMPLE_GAME
#define SIMPLE_GAME

#include "global.h"
#include "home_page.h"
#include "staff_page.h"
#include "war_page.h"
#include "chapter_one_page.h"
#include "chapter_two_page.h"
#include "mission_page.h"
#include "achievement_page.h"
#include "store_page.h"
#include "death_match_page.h"

class SimpleGame {
	public:
		SimpleGame();
		void GamePlay();
		void GameBegin();
		void GameDraw();
		bool GameRun();
		void GameDestroy();
		void Reset();
		
	private:
		ALLEGRO_DISPLAY *game_display;
		ALLEGRO_EVENT_QUEUE *game_event_queue;
		ALLEGRO_EVENT event;
		ALLEGRO_TIMER *game_update_timer;
		ALLEGRO_FONT *font_pirulen_32, *font_pirulen_24;
		ALLEGRO_SAMPLE* bgm, *battle;
		ALLEGRO_SAMPLE_ID bgm_id, battle_id;
		
		string scene;
		HomePage *home_page;
		StaffPage *staff_page;
		WarPage *war_page;
		MissionPage *mission_page;
		ChapterOnePage *chapter_one_page;
		ChapterTwoPage *chapter_two_page;
		DeathMatchPage *death_match_page;
		AchievementPage *achievement_page;
		StorePage *store_page;
		Button *back_home;
		Button *reset;
				
		vector<Staff*> staffs;
		Staff* debut_staff;
		
		int money;
		bool key_state[1000];
		bool stop;
};

#endif
