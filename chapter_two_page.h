#include "global.h"
#include "staff.h"
#include "enemy.h"
#include "bullet.h"
#include "boss.h"

class ChapterTwoPage {
	public:
		ChapterTwoPage(ALLEGRO_FONT*);
		void Draw();
		void Destroy();
		
		void Begin(Staff*);
		void Play(bool*);
		void First();
		
		void Move(bool*);
		void Shot(bool*);
		void Coming(int&, double&, ifstream&, bool);
		void Collide();
		bool Collide(pair<int, int>, pair<int,int>, pair<int, int>, pair<int, int>);
		void Die();
		void GainMoney(int);
		
	private:
		ALLEGRO_BITMAP* background;
		ALLEGRO_FONT* font;
		
		string now_scene;
		string story_text;
		float begin_time;
		
		Staff* debut_staff;
		vector<Bullet*> bullets;
		vector<Enemy*> enemies;
		
		Boss* boss, *boss2;
		Boss* boss_lord;
		
		bool first_story;
		bool first_battle;
		bool second_story;
		bool second_battle;
		
		int ret;
		int cnt;
		bool hello;
		int kills;
		int speed_up;
		
		ifstream fstory, fenemy;
		double now_boss_time;
};
