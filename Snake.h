#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;


class Snake {
private:
	char direction = 'D'; //D - down, U - up, L - Left, R - Right

	int** snake; // массив с координатами(поля) змейки
	int len = 1;
public:
	Snake(int*);

	int get_len();
	int* get_coord_head();
	int* get_coord_tail();
	int* get_coord(int);
	int** get_snake();

	bool move(Field&, int*, Settings);

	bool how_to_move(int*, char, Field&, int*);
	void move_free(int*);
	void move_eat_apple(int*);

	void change_direction(char);
	char get_direction();
	void resize();

	~Snake();
};


Snake::Snake(int* shape) {
	snake = new int* [len];
	for (int i = 0; i < len; i++) {
		snake[i] = new int[2];

		snake[i][0] = abs(shape[0] / 2);
		snake[i][1] = abs(shape[1] / 2);
	}
}

int Snake::get_len() {
	return len;
}

int* Snake::get_coord_head() {
	return snake[0];
}

int* Snake::get_coord_tail() {
	return snake[len - 1];
}

int* Snake::get_coord(int index) {
	return snake[index];
}

int** Snake::get_snake() {
	return snake;
}

void Snake::resize() {

}

bool Snake::move(Field& F, int* shape, Settings set) {
	int head[2] = { get_coord_head()[0], get_coord_head()[1] };
	int tail[2] = { get_coord_tail()[0], get_coord_tail()[1] };
	bool temp = true;
	char** field = F.get_field();

	switch (direction) {
	case 'D':
		head[0]++;
		break;
	case 'U':
		head[0]--;
		break;
	case 'L':
		head[1]--;
		break;
	case 'R':
		head[1]++;
		break;

	}
	char cell = field[head[0]][head[1]];

	if (cell == set.free_space){
		move_free(head);
	}
	else if (cell == set.borders) {
		if (head[0] == 0) {
			head[0] = shape[0] - 2;
			char cell = field[head[0]][head[1]];

			temp = how_to_move(head, cell, F, tail);
		}
		else if (head[0] == shape[0] - 1) {
			head[0] = 1;
			char cell = field[head[0]][head[1]];

			temp = how_to_move(head, cell, F, tail);
		}
		else if (head[1] == 0) {
			head[1] = shape[1] - 2;
			char cell = field[head[0]][head[1]];

			temp = how_to_move(head, cell, F, tail);
		}
		else if (head[1] == shape[1] - 1) {
			head[1] = 1;
			char cell = field[head[0]][head[1]];

			temp = how_to_move(head, cell, F, tail);
		}
		return temp;
	}
	else if (cell == set.snakes_body) {
		if (head[0] == tail[0] && head[1] == tail[1]) {
			move_free(head);
			return true;
		}
		return false;
	}
	else if (cell == set.apple)
	{
		F.eat_apple();
		move_eat_apple(head);

	}

	return true;
}

bool Snake::how_to_move(int* head, char cell, Field& F, int* tail) {
	if (cell == ' ') {
		move_free(head);
		return true;
	}
	else if (cell == '7') {
		if (head[0] == tail[0] && head[1] == tail[1]) {
			move_free(head);
			return true;
		}
		return false;
	}
	else if (cell == '1') {
		F.eat_apple();
		move_eat_apple(head);
		return true;
	}
}

void Snake::move_free(int* head) {
	if (len > 1) {
		for (int i = len - 1; i > 0; i--) {
			int temp[2] = { snake[i - 1][0], snake[i - 1][1] };
			snake[i][0] = temp[0];
			snake[i][1] = temp[1];
		}
	}
	snake[0][0] = head[0];
	snake[0][1] = head[1];
}

void Snake::move_eat_apple(int* head) {
	int** temp;
	temp = new int* [len];
	for (int i = 0; i < len; i++) {
		temp[i] = new int[2];

		temp[i][0] = snake[i][0];
		temp[i][1] = snake[i][1];
	}

	len++;
	this->snake = new int* [len];
	for (int i = 0; i < len; i++) {
		this->snake[i] = new int[2];

		if (i == 0) {
			snake[i][0] = head[0];
			snake[i][1] = head[1];
		}
		else {
			snake[i][0] = temp[i - 1][0];
			snake[i][1] = temp[i - 1][1];
		}
	}

	for (int i = 0; i < len - 1; i++) {
		delete[] temp[i];
	}
	delete[] temp;
}

void Snake::change_direction(char S) {
	direction = S;
}

char Snake::get_direction() {
	return direction;
}

Snake::~Snake() {
	for (int i = 0; i < len; i++) {
		delete[] snake[i];
	}

	delete[] snake;
}