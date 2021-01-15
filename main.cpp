#include "simple_game.h"

int main() {
	string name;
	ifstream fin("./files/name.txt");
	getline(fin, name);
	fin.close();
	
	if (name == "") {
		ofstream fout("./files/name.txt");
		cout << "Please enter your name: ";
		getline(cin, name);
		fout << name;
		fout.close();
	}

	SimpleGame *game = new SimpleGame();
	debug("begin");
	
	game->GamePlay();
	delete game;
	
	return 0;
}
