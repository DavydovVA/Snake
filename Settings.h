struct Settings {
	int delay = 500;

	const char snakes_body = 'o';
	const char snakes_head = '+';
	const char borders = '#';
	const char apple = '$';
	const char free_space = ' ';


	int iters_before_apple = 5;

	int rows = 6; // Number of Rows
	int cols = 9; // Number of Columns
};