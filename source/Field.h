#include <iostream>
//#include <conio.h>
#include <time.h>
using namespace std;


class Field {
private:
	int rows, cols;
	char** field;

	bool apple;
	int apple_coord[2] = {0, 0};
public:
	Field(int*);

	void init_field(Settings);
	void init_snake(int**, int, Settings);
	void init_apple(int, Settings);

	void draw_frame(int**, int, Settings);

	char** get_field();
	bool is_apple();
	void eat_apple();

	~Field();
};


Field::Field(int* shape) {
	rows = shape[0];
	cols = shape[1];


	apple = false;
	//init_field();
}

void Field::init_field(Settings set) {
	field = new char* [rows];
	for (int i = 0; i < rows; i++) {
		field[i] = new char[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			field[i][j] = set.free_space;
		}
	}

	for (int i = 0; i < rows; i++) {
		field[i][0] = set.borders;
		field[i][cols - 1] = set.borders;
	}
	for (int i = 0; i < cols; i++) {
		field[0][i] = set.borders;
		field[rows - 1][i] = set.borders;
	}

	if (apple) {
		field[apple_coord[0]][apple_coord[1]] = set.apple;
	}
}

void Field::init_snake(int** snake, int len, Settings set) {
	for (int i = 0; i < len; i++) {
		if (i == 0) {
			field[snake[i][0]][snake[i][1]] = set.snakes_head;
			continue;
		}
		field[snake[i][0]][snake[i][1]] = set.snakes_body;
	}
}

void Field::init_apple(int len, Settings set) {
	int f_cells = (rows - 2) * (cols - 2) - len;

	srand(time(NULL));
	int cell_num = rand() % f_cells;

	int counter = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (field[i][j] == ' ') {
				counter++;
				if (counter == cell_num) {
					field[i][j] = set.apple;
					apple_coord[0] = i;
					apple_coord[1] = j;
				}
			}
			
		}
	}
	apple = true;
}

void Field::draw_frame(int** snake, int len, Settings set) {
	init_field(set);
	init_snake(snake, len, set);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << field[i][j] << " ";
		}
		cout << endl;
	}
}

char** Field::get_field() {
	return field;
}

bool Field::is_apple() {
	return apple;
}

void Field::eat_apple() {
	apple = false;
}

Field::~Field() {
	for (int i = 0; i < rows; i++) {
		delete[] this->field[i];
	}

	delete[] this->field;
}