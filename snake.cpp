#include "snake.h"

void gotoxy(HANDLE hOut, int x, int y) {  
    COORD pos;  
    pos.X = x;  
    pos.Y = y; 
    SetConsoleCursorPosition(hOut, pos);  
}

void Snake::printOneNode(int index) const {
	gotoxy(handle, snake_body[index].x, snake_body[index].y);
	if (index == 0) {
		cout << '@';
	} else {
		cout << '#';
	}
}

void Snake::printSnake() const {
	for (int i = 0; i < snake_len; ++i) {
		printOneNode(i);
	}
}

Snake::Snake() {
	for (int i = 0; i < snake_len; ++i) {
		SnakeNode temp;
		temp.x = MaxLen / 2;
		temp.x -= i;
		temp.y = MaxWid / 2;
		snake_body.push_back(temp);
	}
}

void Snake::printScore() const {
	gotoxy(handle, 0, MaxWid + 2);
	cout << "Your score: " << score << endl;
}

void Snake::moveOneNode(int index) {
	if (snake_body[index].direction == 'U') {
		--snake_body[index].y;
	} else if (snake_body[index].direction == 'D') {
		++snake_body[index].y;
	} else if (snake_body[index].direction == 'L') {
		--snake_body[index].x;
	} else if (snake_body[index].direction == 'R') {
		++snake_body[index].x;
	}
} 

void Snake::handleTheTurningNode() {	
	for (int i = snake_len - 1; i >= 0; --i) {
		if (snake_body[i].isTurning) {
			snake_body[i].isTurning = false;
			if (i != snake_len - 1) {
				snake_body[i + 1].isTurning = true;
				snake_body[i + 1].direction = snake_body[i].direction;
			}
		}
	}
}

void Snake::moveSnake() {
	for (int i = 0; i < snake_len; ++i) {
		moveOneNode(i);
	}
	handleTheTurningNode();
}

void Snake::moveUp() {
	if (snake_body[0].direction != 'U' && snake_body[0].direction != 'D') {
		snake_body[0].isTurning = true;
		snake_body[0].direction = 'U';
	}
}

void Snake::moveDown() {
	if (snake_body[0].direction != 'D' && snake_body[0].direction != 'U') {
		snake_body[0].isTurning = true;
		snake_body[0].direction = 'D';
	}
}

void Snake::moveLeft() {
	if (snake_body[0].direction != 'L' && snake_body[0].direction != 'R') {
		snake_body[0].isTurning = true;
		snake_body[0].direction = 'L';
	}
}

void Snake::moveRight() {
	if (snake_body[0].direction != 'R' && snake_body[0].direction != 'L') {
		snake_body[0].isTurning = true;
		snake_body[0].direction = 'R';
	}
}

void Snake::eatFood() {
	if (snake_maze[snake_body[0].y][snake_body[0].x] == '$') {
		SnakeNode tail(snake_body[snake_len - 1]);
		if (tail.direction == 'U') {
			++tail.y;
		} else if (tail.direction == 'D') {
			--tail.y;
		} else if (tail.direction == 'L') {
			++tail.x;
		} else if (tail.direction == 'R') {
			--tail.x;
		}
		snake_body.push_back(tail);
		++snake_len;
		score += 100;
		snake_maze[snake_body[0].y][snake_body[0].x] = '\0';
		makeFood();
	}
}

void Snake::makeFood() {
	srand(time(NULL));
	int foodX, foodY;
	foodX = (rand() % (MaxLen - 2)) + 1;
	Sleep(rand() % 25);
	foodY = (rand() % (MaxWid - 2)) + 1;
	snake_maze[foodX][foodY] = '$';
}

bool Snake::checkIfDead() const {
	if (snake_maze[snake_body[0].y][snake_body[0].x] == 'o') {
		return true;
	} else if (snake_len >= 5){
		for (int i = 4; i < snake_len; ++i) {
			if (snake_body[i].x == snake_body[0].x && snake_body[i].y == snake_body[0].y) {
				return true;
			}
		}
	}
	return false;
}