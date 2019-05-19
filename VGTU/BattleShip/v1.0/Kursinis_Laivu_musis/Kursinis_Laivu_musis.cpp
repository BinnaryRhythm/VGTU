#include "pch.h"
#include <iostream>
#include <time.h> 
#include <stdlib.h>
#include <conio.h>
#include "curses.h" 
#include <vector>

using namespace std;

class Ships {
private:

	bool HorVer = 0; // Horizontal/Vertical
	bool CantShot = 0;
	bool hit_again = 0;
	
	char axis = 0;
	bool left_alive = false;

	int Hit = 0;

	char field_letters_cordinates_print = 65;
	int Map_player[12][12] = { 0 };
	int Map_enemy[12][12] = { 0 };
	int pp = 0, ppi = 0, pp2 = 0;
	int ch = 0;
	int x = 4, y = 6;		//player
	int tempx = 0, tempy = 0;
	int ppcc; //plius plius can cant
	int temppp = 1;

	int Alive = 21;
	int Alive_enemy = 21;

	int x_atm, y_atm;

	char Movement[4] = { 119,115,97,100 };

	bool is_ship_fully_dead = 0;
	vector<pair<int,int> > temp_cordinates_to_add_to_vector;
	vector< vector<pair<int, int> > > cordinates_where_saved_ships_player;
	vector< vector<pair<int, int> > > cordinates_where_saved_ships_enemy;

public:
	void Meniu() {
		//Start_Art();
		_getch();
		Print_Map();
		Place_ships_enemy(4);
		Place_ships_enemy(3);
		Place_ships_enemy(1);
		Place_ships_enemy(1);
		Place_ships_enemy(3);
		Place_ships_enemy(2);
		Place_ships_enemy(1);
		Place_ships_enemy(2);
		Place_ships_enemy(1);
		Place_ships_enemy(2);
		x = 5; y = 7;
		Move_the_ships(4);
		Move_the_ships(3);
		Move_the_ships(3);
		Move_the_ships(2);
		Move_the_ships(2);
		Move_the_ships(2);
		Move_the_ships(1);
		Move_the_ships(1);
		Move_the_ships(1);
		Move_the_ships(1);
		Print_Map();
		_getch();
		while(1) {
			Move_aim_enemy(rand()%7+2, rand() % 7 + 2);
			Move_aim_player(5, 5);
			if (cordinates_where_saved_ships_enemy.size()==0) {
				cout << "Win" << endl;
				break;
			}
			else if (cordinates_where_saved_ships_player.size()==0) {
				cout << "lose" << endl;
				break;
			}
		}
		Print_Map();
		_getch();
		endwin(); //end curses mode
	}
	/*
	void Start_Art() {
		initscr();
		int r = 100, g = 100, b = 100;

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 40; j++) {

				r++; g++, b++;
				Colors(r, g, b);
				attron(COLOR_PAIR(10));
				mvprintw(i, j, "#");
				Remove_color();
			}
		}
		refresh();
	}
	*/


	void Print_Map() {
		initscr();
		Colors();
		mvprintw(1, 1, "   1   2   3   4   5   6   7   8   9   10        1   2   3   4   5   6   7   8   9   10");
		ppi = 0;
		for (int i = 1; i <= 10; i++) {
			pp = 0;
			mvprintw(i * 2, 1, "%c ", field_letters_cordinates_print);
			for (int j = 1; j <= 10; j++) {
				if (Map_player[i][j] == 1) {
					Print_player_ship(i, j, 0);
				}
				else if (Map_player[i][j] == 3) {
					attron(COLOR_PAIR(9));
					Print_player_ship(i, j, 0);
					Remove_color();
				}
				else if (Map_player[i][j] == 2) {
					attron(COLOR_PAIR(6));
					Print_blank_map(i, j, 0);
					Remove_color();
				}
				else {
					Colorize_map_print(i, j);
					Print_blank_map(i, j, 0);
					Remove_color();
				}
			}
			pp = 0;
			mvprintw(i * 2, 43, "    %c", field_letters_cordinates_print);
			mvprintw(i * 2 + 1, 43, "     ", field_letters_cordinates_print);
			for (int j = 1; j <= 10; j++) {
				if (Map_enemy[i][j] == 1) {
					Print_player_ship(i, j, 46);
				}
				else if (Map_enemy[i][j] == 3) {
					attron(COLOR_PAIR(9));
					Print_player_ship(i, j, 46);
					Remove_color();
				}
				else if (Map_enemy[i][j] == 2) {
					attron(COLOR_PAIR(6));
					Print_blank_map(i, j, 46);
					Remove_color();
				}
				else {
					Colorize_map_print(i, j);
					Print_blank_map(i, j, 46);
					Remove_color();
				}
			}
			field_letters_cordinates_print++;
			ppi++;
		}
		ppi = 0;
		field_letters_cordinates_print = 65;
		mvprintw(22, 1, "                 (player 1)                                     (enemy)");
		refresh();
	}


	void Move_the_ships(int Ship_size) {

		Place_ships(x, y, Ship_size, Map_player, 1);
		while (ch != 13) {
			Place_ships(x, y, Ship_size, Map_player, 1);
			ch = _getch();

			if (ch == 13 && (ppcc != Ship_size)) {
				ch = 0;
			}

			if (HorVer == 0 && (ch == 119 || ch == 72) && y != Ship_size)
				Place_ships(x, y - 1, Ship_size, Map_player, 1);
			else if (HorVer == 1 && (ch == 119 || ch == 72) && y != 1)
				Place_ships(x, y - 1, Ship_size, Map_player, 1);
			if ((ch == 115 || ch == 80) && y != 10)
				Place_ships(x, y + 1, Ship_size, Map_player, 1);

			if (HorVer == 0 && (ch == 97 || ch == 75) && x != 1)
				Place_ships(x - 1, y, Ship_size, Map_player, 1);
			else if (HorVer == 1 && (ch == 97 || ch == 75) && x != Ship_size)
				Place_ships(x - 1, y, Ship_size, Map_player, 1);
			if ((ch == 100 || ch == 77) && x != 10)
				Place_ships(x + 1, y, Ship_size, Map_player, 1);

			if (ch == 113 || ch == 101 || ch == 32) {
				if (HorVer == 0 && x >= Ship_size) {
					HorVer = !HorVer;
					Place_ships(x, y, Ship_size, Map_player, 1);
				}
				else if (HorVer == 1 && y >= Ship_size) {
					HorVer = !HorVer;
					Place_ships(x, y, Ship_size, Map_player, 1);
				}
			}
		}
		ch = 0;
		Save_player_cordinates(Ship_size, Map_player,1);
	}

	void Place_ships(int argX, int argY, int Ship_size, int Map[][12], bool player) {
		Colors();
		x = argX;
		y = argY;
		ppcc = 0;
		initscr();
		for (int i = 1; i <= 10; i++) {
			pp = 0;
			for (int j = 1; j <= 10; j++) {
				if (x == j && y == i || (x == j + HorVer * 1 && y == i + !HorVer * 1 && Ship_size > 1)
					|| (x == j + HorVer * 2 && y == i + !HorVer * 2 && Ship_size > 2)
					|| (x == j + HorVer * 3 && y == i + !HorVer * 3 && Ship_size > 3)) {
					Place_the_ships_can_cant(i, j, ppcc, Map);
					if (player == 1)Print_player_ship(i, j, 0);
					tempx = j - ((Ship_size - 1)*HorVer);
					tempy = i - ((Ship_size - 1) * !HorVer);
					Remove_color();
				}
				else if ((player == 1) && (Map[i][j] == 0)) {
					Colorize_map_print(i, j);
					Print_blank_map(i, j, 0);
					Remove_color();
				}
				else if ((player == 1) && (Map[i][j] == 1)) {
					Print_player_ship(i, j, 0);
				}
			}
			ppi++;
		}
		ppi = 0;
		refresh();
	}

	void Place_ships_enemy(int Ship_size) {

		HorVer = rand() % 2;
		x = 5;
		y = 5;
		if (HorVer == 0 && x >= Ship_size) {
			HorVer = !HorVer;
			Place_ships(x, y, Ship_size, Map_enemy, 0);
		}
		else if (HorVer == 1 && y >= Ship_size) {
			HorVer = !HorVer;
			Place_ships(x, y, Ship_size, Map_enemy, 0);
		}
		Place_ships(x, y, Ship_size, Map_enemy, 0);

		temppp = 1;

		while (ch != 13) {
			ch = Movement[rand() % 4];
			if ((temppp % 10 == 0) && (ppcc != Ship_size)) {
				ch = 0;
			}
			else if (temppp % 10 == 0) ch = 13;

			if (HorVer == 0 && (ch == 119 || ch == 72) && y != Ship_size)
				Place_ships(x, y - 1, Ship_size, Map_enemy, 0);
			else if (HorVer == 1 && (ch == 119 || ch == 72) && y != 1)
				Place_ships(x, y - 1, Ship_size, Map_enemy, 0);
			if ((ch == 115 || ch == 80) && y != 10)
				Place_ships(x, y + 1, Ship_size, Map_enemy, 0);

			if (HorVer == 0 && (ch == 97 || ch == 75) && x != 1)
				Place_ships(x - 1, y, Ship_size, Map_enemy, 0);
			else if (HorVer == 1 && (ch == 97 || ch == 75) && x != Ship_size)
				Place_ships(x - 1, y, Ship_size, Map_enemy, 0);
			if ((ch == 100 || ch == 77) && x != 10)
				Place_ships(x + 1, y, Ship_size, Map_enemy, 0);

			temppp++;
		}
		ch = 0;
		Save_player_cordinates(Ship_size, Map_enemy, 0);
	}

	//Mini functions
	// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Print_blank_map(int i, int j, int move_left) {
		mvaddch(i + 1 + ppi, j + move_left + 3 + pp, 176 + ((i + j) % 2));
		mvaddch(i + 1 + ppi, j + move_left + 2 + pp, 176 + ((i + j) % 2));
		mvaddch(i + 1 + ppi, j + move_left + 5 + pp, 176 + ((i + j) % 2));
		mvaddch(i + 1 + ppi, j + move_left + 4 + pp, 176 + ((i + j) % 2));
		mvaddch(i + 2 + ppi, j + move_left + 3 + pp, 176 + ((i + j) % 2));
		mvaddch(i + 2 + ppi, j + move_left + 2 + pp, 176 + ((i + j) % 2));
		mvaddch(i + 2 + ppi, j + move_left + 5 + pp, 176 + ((i + j) % 2));
		mvaddch(i + 2 + ppi, j + move_left + 4 + pp, 176 + ((i + j) % 2));
		pp += 3;
	}

	void Colorize_map_print(int i, int j) {
		if (((i + j) % 2) == 1)attron(COLOR_PAIR(1));
		else attron(COLOR_PAIR(2));
	}

	void Place_the_ships_can_cant(int i, int j, int pc, int Map[][12]) {
		ppcc = pc;
		if (Map[i][j] == 1 || Map[i][j - 1] == 1 || Map[i][j + 1] == 1											//***
			|| Map[i + 1][j] == 1 || Map[i + 1][j - 1] == 1 || Map[i + 1][j + 1] == 1							//Galima statyti ar negalima.
			|| Map[i - 1][j] == 1 || Map[i - 1][j - 1] == 1 || Map[i - 1][j + 1] == 1) {						//***
			attron(COLOR_PAIR(3));
		}
		else {
			attron(COLOR_PAIR(4));
			ppcc++;
		}
	}

	void Print_player_ship(int i, int j, int move_left) {
		mvaddch(i + 1 + ppi, j + 3 + pp + move_left, 178);
		mvaddch(i + 1 + ppi, j + 2 + pp + move_left, 178);
		mvaddch(i + 1 + ppi, j + 5 + pp + move_left, 178);
		mvaddch(i + 1 + ppi, j + 4 + pp + move_left, 178);
		mvaddch(i + 2 + ppi, j + 3 + pp + move_left, 178);
		mvaddch(i + 2 + ppi, j + 2 + pp + move_left, 178);
		mvaddch(i + 2 + ppi, j + 5 + pp + move_left, 178);
		mvaddch(i + 2 + ppi, j + 4 + pp + move_left, 178);
		pp += 3;
	}

	void Save_player_cordinates(int Ship_size, int Map[][12], bool player) {
		if (player == 1) {
			if (HorVer == 0)	for (int i = 0; i < Ship_size; i++) {
				temp_cordinates_to_add_to_vector.push_back(make_pair(tempy + i,tempx));
				Map[tempy + i][tempx] = 1;
			}
			else if (HorVer == 1)	for (int i = 0; i < Ship_size; i++){
				temp_cordinates_to_add_to_vector.push_back(make_pair(tempy, tempx + i));
				Map[tempy][tempx + i] = 1;
			}
			cordinates_where_saved_ships_player.push_back(temp_cordinates_to_add_to_vector);
		}
		if (player == 0) {
			if (HorVer == 0)	for (int i = 0; i < Ship_size; i++) {
				temp_cordinates_to_add_to_vector.push_back(make_pair(tempy + i, tempx));
				Map[tempy + i][tempx] = 1;
			}
			else if (HorVer == 1)	for (int i = 0; i < Ship_size; i++) {
				temp_cordinates_to_add_to_vector.push_back(make_pair(tempy, tempx + i));
				Map[tempy][tempx + i] = 1;
			}
			cordinates_where_saved_ships_enemy.push_back(temp_cordinates_to_add_to_vector);
		}
		temp_cordinates_to_add_to_vector.clear();
	}

	void Colors(int r = 0, int g = 0, int b = 0) {
		start_color();
		init_color(10, r, g, b);
		init_color(1, 0, 200, 400);				//Dark Blue.
		init_color(2, 0, 500, 600);				//Light Blue.
		init_color(3, 1000, 300, 300);			//Red.
		init_color(4, 0, 1000, 0);				//Green.
		init_color(5, 200, 200, 200);			//Gray.
		init_color(6, 500, 0, 100);				//Dark Red.
		init_color(8, 700, 10, 0);				//Dark orange.
												//****************
		init_pair(10, 10, 0);
		init_pair(1, 2, 1);						//For map 1
		init_pair(2, 1, 2);						//For map 2
		init_pair(3, 3, 5);						//Can't place ship.
		init_pair(4, 4, COLOR_GREEN);			//Can place ship.
		init_pair(5, 6, 3);						//Target
		init_pair(6, 5, 6);						//Cant shoot
		init_pair(9, 6, COLOR_BLACK);			//Cant shoot darker
		init_pair(7, 8, COLOR_BLACK);			//Dead
		init_pair(8, COLOR_BLUE, COLOR_BLACK);	//Miss

	}
	void Remove_color() {
		attroff(COLOR_PAIR(1));
		attroff(COLOR_PAIR(2));
		attroff(COLOR_PAIR(3));
		attroff(COLOR_PAIR(4));
		attroff(COLOR_PAIR(5));
		attroff(COLOR_PAIR(6));
		attroff(COLOR_PAIR(7));
		attroff(COLOR_PAIR(8));
		attroff(COLOR_PAIR(9));
		attroff(COLOR_PAIR(10));
	}
	void Color_old_shoots(int i, int j, int Map[][12]) {
		if (Map[i][j] > 2) {
			attron(COLOR_PAIR(7));
		}
		else {
			attron(COLOR_PAIR(8));
		}
	}
	void Shoot_can_cant(int i, int j, int Map[][12]) {
		if (Map[i][j] > 2) {
			attron(COLOR_PAIR(9));
			CantShot = true;
		}
		else if (Map[i][j] > 1) {
			attron(COLOR_PAIR(6));
			CantShot = true;
		}
		else {
			attron(COLOR_PAIR(5));
		}
	}
	void Print_aim(int i, int j, int pp2) {
		mvaddch(i + 1 + ppi, j + 3 + pp2 + pp, 176);
		mvaddch(i + 1 + ppi, j + 2 + pp2 + pp, 176);
		mvaddch(i + 1 + ppi, j + 5 + pp2 + pp, 177);
		mvaddch(i + 1 + ppi, j + 4 + pp2 + pp, 177);
		mvaddch(i + 2 + ppi, j + 3 + pp2 + pp, 177);
		mvaddch(i + 2 + ppi, j + 2 + pp2 + pp, 177);
		mvaddch(i + 2 + ppi, j + 5 + pp2 + pp, 176);
		mvaddch(i + 2 + ppi, j + 4 + pp2 + pp, 176);
		pp += 3;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//*********************************************************************Part II. Start war.***************************************************************
	void Move_aim_player(int argX, int argY) {
		x = argX;
		y = argY;
		Aim(x, y, Map_enemy, 1);
		while (ch != 13) {

			ch = _getch();

			if ((ch == 13) && (CantShot == 1)) {
				ch = 0;
			}

			if ((ch == 119 || ch == 72) && (y != 1))
				Aim(x, y - 1, Map_enemy, 1);
			if ((ch == 115 || ch == 80) && (y != 10))
				Aim(x, y + 1, Map_enemy, 1);
			if ((ch == 97 || ch == 75) && (x != 1))
				Aim(x - 1, y, Map_enemy, 1);
			if ((ch == 100 || ch == 77) && (x != 10))
				Aim(x + 1, y, Map_enemy, 1);
		}
		ch = 0;
		Fire(tempx, tempy, 1);
		Mark_dead_around_on_map(0);
		if (Map_enemy[y][x] == 3) Move_aim_player(x, y);
	}

	void Aim(int argX, int argY, int Map[][12], bool player) {
		Colors();
		CantShot = 0;
		x = argX;
		y = argY;
		initscr();
		if (player == 0) pp2 = 0;
		else pp2 = 46;
		for (int i = 1; i <= 10; i++) {
			pp = 0;
			for (int j = 1; j <= 10; j++) {
				if (x == j && y == i) {
					Shoot_can_cant(i, j, Map);
					if (player == 1)Print_aim(i, j, pp2);
					else pp += 3;
					tempx = j;
					tempy = i;
					Remove_color();
				}

				else if (Map[i][j] <= 1) {
					Colorize_map_print(i, j);
					if (player == 1)Print_blank_map(i, j, pp2);
					else pp += 3;
					Remove_color();
				}
				else if (Map[i][j] > 1) {

					Color_old_shoots(i, j, Map);
					Print_aim(i, j, pp2);
					Remove_color();
				}
			}
			ppi++;
		}
		ppi = 0;
		refresh();
	}

	void Move_aim_enemy(int argX, int argY) {
		x = argX;
		y = argY;
			temppp = 0;
			Hit = 0;
			while (ch != 13) {
				ch = Movement[rand() % 4];;

				if ((ch == 119 || ch == 72) && (y != 1))
					Aim(x, y - 1, Map_player, 0);
				if ((ch == 115 || ch == 80) && (y != 10))
					Aim(x, y + 1, Map_player, 0);
				if ((ch == 97 || ch == 75) && (x != 1))
					Aim(x - 1, y, Map_player, 0);
				if ((ch == 100 || ch == 77) && (x != 10))
					Aim(x + 1, y, Map_player, 0);
				if ((temppp % 10 == 0)&&(CantShot == 0)) ch = 13;
				temppp++;

			}
			ch = 0;
			Fire(tempx, tempy, 0);
			Aim(x, y, Map_player, 0);
			//cout << "x"<<x<<"y"<<y<<Map_player[y][x] << endl;
			Mark_dead_around_on_map(1);
			if (Map_player[y][x] == 3) {
				x_atm = x;
				y_atm = y;
				Move_aim_enemy_first_hit(x , y);			
			}
	}
	void Move_aim_enemy_first_hit(int argX, int argY) {
		x = argX;
		y = argY;
		if (Map_player[argY + 1][argX] == 1 || Map_player[argY - 1][argX] == 1 || Map_player[argY][argX + 1] == 1 || Map_player[argY][argX - 1] == 1) {
			while (1) {
				if (Map_player[argY][argX - 1] != 3 && Map_player[argY][argX - 1] != 2 && argX!=1) {
					while (Map_player[y][x] == 3&&Map_player[y][x - 1] != 3 && Map_player[y][x - 1] != 2 && x != 1) {
						Aim(x-1, y, Map_player, 0);
						Fire(tempx, tempy, 0);
					}
					Mark_dead_around_on_map(1);
					Aim(0, 0, Map_player, 0);
					Move_aim_player(5, 5);
					Move_aim_enemy_first_hit(x_atm, y_atm);
					break;
				}
				else if (Map_player[argY][argX + 1] != 3 && Map_player[argY][argX + 1] != 2 && argX != 10) {
					while (Map_player[y][x] == 3&&Map_player[y][x + 1] != 3 && Map_player[y][x + 1] != 2 && x != 10) {
						Aim(x+1, y, Map_player, 0);
						Fire(tempx, tempy, 0);
					}
					Mark_dead_around_on_map(1);
					Aim(0, 0, Map_player, 0);
					Move_aim_player(5, 5);
					Move_aim_enemy_first_hit(x_atm, y_atm);
					break;
				}
				else if (Map_player[argY - 1][argX] != 3 && Map_player[argY - 1][argX] != 2 && argY != 1) {
					while (Map_player[y][x] == 3&& Map_player[y - 1][x] != 3 && Map_player[y - 1][x] != 2 && y != 1) {
						Aim(x , y-1, Map_player, 0);
						Fire(tempx, tempy, 0);
					}
					Mark_dead_around_on_map(1);
					Aim(0, 0, Map_player, 0);
					Move_aim_player(5, 5);
					Move_aim_enemy_first_hit(x_atm, y_atm);
					break;
				}
				else if (Map_player[argY + 1][argX] != 3 && Map_player[argY + 1][argX] != 2 && argY != 10) {
					while (Map_player[y][x] == 3&& Map_player[y + 1][x] != 3 && Map_player[y + 1][x] != 2 && y != 10) {
						Aim(x , y+1, Map_player, 0);
						Fire(tempx, tempy, 0);
					}
					Mark_dead_around_on_map(1);
					Aim(0, 0, Map_player, 0);
					Move_aim_player(5, 5);
					Move_aim_enemy_first_hit(x_atm, y_atm);
					break;
				}
			}
		}
		else Move_aim_enemy(rand() % 7 + 2, rand() % 7 + 2);
	}

	void Mark_dead_around_on_map(bool mark_on_map_player) {
		if (mark_on_map_player == 1) {
			for (int Ship_number = 0; Ship_number < cordinates_where_saved_ships_player.size(); Ship_number++) {
				is_ship_fully_dead = true;
				for (int Ship_cordinate_number = 0; Ship_cordinate_number < cordinates_where_saved_ships_player[Ship_number].size(); Ship_cordinate_number++) {
					if (Map_player[cordinates_where_saved_ships_player[Ship_number][Ship_cordinate_number].first][cordinates_where_saved_ships_player[Ship_number][Ship_cordinate_number].second] == 1) { //first, second = x,y;

						is_ship_fully_dead = false;
						Ship_cordinate_number = cordinates_where_saved_ships_player[Ship_number].size();
					}
				}
				if (is_ship_fully_dead == true) {
					for (int i = cordinates_where_saved_ships_player[Ship_number][0].first - 1; i <= cordinates_where_saved_ships_player[Ship_number][cordinates_where_saved_ships_player[Ship_number].size() - 1].first + 1; i++) {
						for (int j = cordinates_where_saved_ships_player[Ship_number][0].second - 1; j <= cordinates_where_saved_ships_player[Ship_number][cordinates_where_saved_ships_player[Ship_number].size() - 1].second + 1; j++) {
							if (Map_player[i][j] == 0) Map_player[i][j] = 2;
						}
					}
					if (cordinates_where_saved_ships_player.size() != 1) {
						cordinates_where_saved_ships_player.erase(cordinates_where_saved_ships_player.begin() + Ship_number);
						Ship_number = cordinates_where_saved_ships_player.size();
					}
					else if (cordinates_where_saved_ships_player.size() == 1)
						cordinates_where_saved_ships_player.clear();
				}
			}
		}
		else {
			for (int Ship_number = 0; Ship_number < cordinates_where_saved_ships_enemy.size(); Ship_number++) {
				is_ship_fully_dead = true;
				for (int Ship_cordinate_number = 0; Ship_cordinate_number < cordinates_where_saved_ships_enemy[Ship_number].size(); Ship_cordinate_number++) {
					if (Map_enemy[cordinates_where_saved_ships_enemy[Ship_number][Ship_cordinate_number].first][cordinates_where_saved_ships_enemy[Ship_number][Ship_cordinate_number].second] == 1) { //first, second = x,y;

						is_ship_fully_dead = false;
						Ship_cordinate_number = cordinates_where_saved_ships_enemy[Ship_number].size();
					}
				}
				if (is_ship_fully_dead == true) {
					for (int i = cordinates_where_saved_ships_enemy[Ship_number][0].first - 1; i <= cordinates_where_saved_ships_enemy[Ship_number][cordinates_where_saved_ships_enemy[Ship_number].size() - 1].first + 1; i++) {
						for (int j = cordinates_where_saved_ships_enemy[Ship_number][0].second - 1; j <= cordinates_where_saved_ships_enemy[Ship_number][cordinates_where_saved_ships_enemy[Ship_number].size() - 1].second + 1; j++) {
							if (Map_enemy[i][j] == 0) Map_enemy[i][j] = 2;
						}
					}
					if (cordinates_where_saved_ships_enemy.size() != 1) {
						cordinates_where_saved_ships_enemy.erase(cordinates_where_saved_ships_enemy.begin() + Ship_number);
						Ship_number = cordinates_where_saved_ships_enemy.size();
					}
					else if (cordinates_where_saved_ships_enemy.size() == 1)
						cordinates_where_saved_ships_enemy.clear();
				}
			}
		}
	}
	void Fire(int x, int y, bool player) {

		if (player == 1) {
			Map_enemy[y][x] += 2;
			if (Map_enemy[y][x] > 2) {
				Alive_enemy--;
			}
			}
		if (player == 0) {
			if (Map_player[y][x] == 2) cout<< "klaida" << endl;
			Map_player[y][x] += 2;

			if (Map_player[y][x] > 2) {
				Alive--;
			}
		}

	}

};

int main()
{
	system("chcp 437"); //For symbols.
	system("cls");
	srand(time(NULL)); //Kad veiktu random
	Ships A;
	A.Meniu();
}		
/*
mvprintw(17, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[0][0], Map_player[0][1], Map_player[0][2], Map_player[0][3], Map_player[0][4], Map_player[0][5], Map_player[0][6], Map_player[0][7], Map_player[0][8], Map_player[0][9], Map_player[0][10], Map_player[0][11]);
mvprintw(18, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[1][0], Map_player[1][1], Map_player[1][2], Map_player[1][3], Map_player[1][4], Map_player[1][5], Map_player[1][6], Map_player[1][7], Map_player[1][8], Map_player[1][9], Map_player[1][10], Map_player[1][11]);
mvprintw(19, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[2][0], Map_player[2][1], Map_player[2][2], Map_player[2][3], Map_player[2][4], Map_player[2][5], Map_player[2][6], Map_player[2][7], Map_player[2][8], Map_player[2][9], Map_player[2][10], Map_player[2][11]);
mvprintw(20, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[3][0], Map_player[3][1], Map_player[3][2], Map_player[3][3], Map_player[3][4], Map_player[3][5], Map_player[3][6], Map_player[3][7], Map_player[3][8], Map_player[3][9], Map_player[3][10], Map_player[3][11]);
mvprintw(21, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[4][0], Map_player[4][1], Map_player[4][2], Map_player[4][3], Map_player[4][4], Map_player[4][5], Map_player[4][6], Map_player[4][7], Map_player[4][8], Map_player[4][9], Map_player[4][10], Map_player[4][11]);
mvprintw(22, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[5][0], Map_player[5][1], Map_player[5][2], Map_player[5][3], Map_player[5][4], Map_player[5][5], Map_player[5][6], Map_player[5][7], Map_player[5][8], Map_player[5][9], Map_player[5][10], Map_player[5][11]);
mvprintw(23, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[6][0], Map_player[6][1], Map_player[6][2], Map_player[6][3], Map_player[6][4], Map_player[6][5], Map_player[6][6], Map_player[6][7], Map_player[6][8], Map_player[6][9], Map_player[6][10], Map_player[6][11]);
mvprintw(24, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[7][0], Map_player[7][1], Map_player[7][2], Map_player[7][3], Map_player[7][4], Map_player[7][5], Map_player[7][6], Map_player[7][7], Map_player[7][8], Map_player[7][9], Map_player[7][10], Map_player[7][11]);
mvprintw(25, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[8][0], Map_player[8][1], Map_player[8][2], Map_player[8][3], Map_player[8][4], Map_player[8][5], Map_player[8][6], Map_player[8][7], Map_player[8][8], Map_player[8][9], Map_player[8][10], Map_player[8][11]);
mvprintw(26, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[9][0], Map_player[9][1], Map_player[9][2], Map_player[9][3], Map_player[9][4], Map_player[9][5], Map_player[9][6], Map_player[9][7], Map_player[9][8], Map_player[9][9], Map_player[9][10], Map_player[9][11]);
mvprintw(27, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[10][0], Map_player[10][1], Map_player[10][2], Map_player[10][3], Map_player[10][4], Map_player[10][5], Map_player[10][6], Map_player[10][7], Map_player[10][8], Map_player[10][9], Map_player[10][10], Map_player[10][11]);
mvprintw(28, 20, "%d %d %d %d %d %d %d %d %d %d %d %d", Map_player[11][0], Map_player[11][1], Map_player[11][2], Map_player[11][3], Map_player[11][4], Map_player[11][5], Map_player[11][6], Map_player[11][7], Map_player[11][8], Map_player[11][9], Map_player[11][10], Map_player[11][11]);
*/