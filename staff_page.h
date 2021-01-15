#include "global.h"
#include "staff.h"
#include "button.h"

class StaffPage {
	public:
		StaffPage();
		void Draw(vector<Staff*>, ALLEGRO_FONT*);
		string Process(int, int);
		void NextStaff(vector<Staff*>, int);
		void Destroy();
		
	private:
		ALLEGRO_BITMAP* background;
		Button *default_staff;
		
		string staff_show;
};
