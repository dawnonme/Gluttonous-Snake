#include "snake.cpp"

inline void initializeMaze() {
	for (int i = 0; i < MaxLen; ++i) {
		for (int j = 0; j < MaxWid; ++j) {
			if (i == 0 || j == 0 || i == MaxLen - 1 || j == MaxWid - 1) {
				snake_maze[i][j] = 'o';
			} else {
				snake_maze[i][j] = '\0';
			}
		}
	}
}

inline void printMaze() {
	for (int i = 0; i < MaxLen; ++i) {
		for (int j = 0; j < MaxWid; ++j) {
			cout << snake_maze[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	while (true) {
		gotoxy(handle, 0, MaxWid / 2 - 1 );
		cout << "This is a simple snake game, enjoy it!!!" << endl;
		cout << "Please choose a challenge level: 1~10: ";
		int level;
		cin >> level;
		initializeMaze();
		system("cls");
		printMaze();
		Snake the_snake;
		the_snake.printSnake();
		the_snake.printScore();
		the_snake.makeFood();
		while (!the_snake.checkIfDead()) {
			the_snake.eatFood();
			if (!kbhit()) {
				the_snake.moveSnake();
			} else {
				char instruction = getch();
				switch (instruction) {
					case 119: {
						the_snake.moveUp();
						break;
					} case 115: {
						the_snake.moveDown();
						break;
					} case 97: {
						the_snake.moveLeft();
						break;
					} case 100: {
						the_snake.moveRight();
						break;
					} case 13: {
						gotoxy(handle, 0, MaxWid + 3);
						system("pause");
					}
					default: {
						break;
					}
				}
				the_snake.moveSnake();
			}
			system("cls");
			printMaze();
			the_snake.printSnake();
			the_snake.printScore();
			Sleep(11 -  level);
		}
		system("cls");
		gotoxy(handle, MaxLen / 2, MaxWid / 2);
		cout << "Game over!!! Do you wanna try again? Press n to exit" << endl;
		char instruction = getch();
		if (instruction == 'n') {
			break;
		} 
		system("cls");
	}
	return 0;
}
