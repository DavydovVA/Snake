#include <iostream>
#include<stdio.h>
#include <thread>

#ifdef WIN32
 #include <conio.h>
 #include <Windows.h>
#else
 #include <unistd.h>
 #include <cstdlib>
 #include <sys/ioctl.h>
 #include <termios.h>
 #include <chrono>
#endif

#include "Settings.h"
#include "Field.h"
#include "Snake.h"

// Definition of keyboard arrows
#ifdef WIN32
	#define UP 72
	#define DOWN 80
	#define LEFT 75
	#define RIGHT 77
#else
	#define UP 65
	#define DOWN 66
	#define LEFT 68
	#define RIGHT 67
#endif


// Clear screen function
void clearScreen() {
#ifdef WIN32
	std::system("cls");
#else
	std::system ("clear");
#endif
}


#ifndef WIN32
// Imitation of _getch() from Windows
int _getch() {
    /*int ch;
    struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

    return ch;*/
	
	char buf = 0;
	struct termios old = {0};
	if (tcgetattr(0, &old) < 0)
			perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0)
			perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0)
			perror ("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
			perror ("tcsetattr ~ICANON");
	return (buf);
}
#endif


void RunKeyBoard(Snake& S, bool& game) {
	while(true) {
		if (!game)
			return;

		int key = _getch();
		
		switch (key) {
		case LEFT:
			if (S.get_direction() != 'R') {
				S.change_direction('L');
			}
			
			break;
		case UP: 
			if (S.get_direction() != 'D') {
				S.change_direction('U');
			}
			
			break;
		case RIGHT:
			if (S.get_direction() != 'L') {
				S.change_direction('R');
			}
			
			break;
		case DOWN:
			if (S.get_direction() != 'U') {
				S.change_direction('D');
			}
			
			break;
		}
	}
}


void RunGame(Settings& set, Field& F, Snake& S, bool& game) {
	int apple_counter = 0; // счетчик итераций до появления яблока
	while (game == true) {
		F.draw_frame(S.get_snake(), S.get_len(), set);

#ifdef WIN32
		Sleep(set.delay);
#else
		std::this_thread::sleep_for(std::chrono::milliseconds(set.delay));
#endif

		game = S.move(F, set); // move snake

		if (F.is_apple() == false) {
			// spawn an apple
			apple_counter++;
			if (apple_counter == set.iters_before_apple) {
				F.init_apple(S.get_len(), set);
				apple_counter = 0;
			}
		}
		
		clearScreen();
	}

	std::cout << "Game Over\n";
	fflush(stdin);
	
	return;
}


int main() {
	clearScreen();

	Settings set;
	
	int shape[2] = {set.rows, set.cols};
	if (!(shape[0] >= 5 && shape[1] >= 5)) {
		std::cout << "Wrong shapes\n";
		
		getchar();
	}
	
	bool game = true;
	Snake S(shape);
	Field F(shape);
	
	auto t1 = std::thread(RunGame, std::ref(set),
					std::ref(F),
					std::ref(S),
					std::ref(game));
	auto t2 = std::thread(RunKeyBoard, std::ref(S),
					std::ref(game));
	
	t1.join();
	t2.join();
	
	getchar();
	clearScreen();
	
	return 0;
}