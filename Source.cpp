#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Settings.h"
#include "Field.h"
#include "Snake.h"
using namespace std;


void keyboard(Snake& S, bool game) {
	if (_kbhit()) {
		_getch();
		int key = _getch();
		switch (key) {
		case 75:
			if (S.get_direction() != 'R') {
				S.change_direction('L');
			}
			
			break;
		case 72:
			if (S.get_direction() != 'D') {
				S.change_direction('U');
			}
			break;
		case 77:
			if (S.get_direction() != 'L') {
				S.change_direction('R');
			}
			break;
		case 80:
			if (S.get_direction() != 'U') {
				S.change_direction('D');
			}
			break;

		}
	}
}


int main() {
	Settings set;
	int shape[2] = {set.rows, set.cols};
	bool game = true;
	

	if (shape[0] >= 5 && shape[1] >= 5) {
		Snake S(shape);
		Field F(shape);

		int apple_counter = 0; // счетчик итераций до появления яблока
		while (game == true) {
			keyboard(S, game); // keyboard чтобы лучше управление было
			F.draw_frame(S.get_snake(), S.get_len(), set);
			keyboard(S, game); // keyboard

			Sleep(set.delay);

			keyboard(S, game); // keyboard
			game = S.move(F, shape, set); // move snake
			keyboard(S, game); // keyboard

			if (F.is_apple() == false) {
				//spawn an apple
				apple_counter++;
				if (apple_counter == set.iters_before_apple) {
					F.init_apple(S.get_len(), set);
					apple_counter = 0;
				}
			}
			system("cls");
		}
		
	}
	else {
		cout << "Wrong shapes";
	}

	cout << "Game Over";

	_getch();
	return 0;
}