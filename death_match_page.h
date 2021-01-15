#include "global.h"
#include "staff.h"
#include "bullet.h"
#include "enemy.h"

class DeathMatchPage {
	public:
		DeathMatchPage(ALLEGRO_FONT*);
		
		void Draw();
		void Destroy();
		
		void Begin(Staff*);
		void Play(bool*);
		void Move(bool*);
		void Coming();
		void Shot(bool*);
		
		bool Collide(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);
		void Collide();
		void GainMoney(int);

	private:
		ALLEGRO_BITMAP* background;
		ALLEGRO_FONT* font;
		
		Staff* staff_one, *staff_two;
		int level;
		
		vector<Bullet*> bullets;
		vector<Enemy*> enemies;
		
		bool done;
		bool die;
		int kills;
};
