#ifndef  SNAKE_H_
#define SNAKE_H_

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#define MaxLen 22 
#define MaxWid 22
using namespace std;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
char snake_maze[MaxLen][MaxWid];
void gotoxy(HANDLE hOut, int x, int y);

class SnakeNode {
public:
	int x = 0, y = 0;
	bool isTurning = false;
	char direction = 'R';

	SnakeNode() {}
};

class Snake {
private:
	int snake_len = 3;
	vector<SnakeNode> snake_body;
	int score = 0;

public:
	Snake();

	void printSnake() const;
	void printScore() const;
	void printOneNode(int index) const;
	void moveOneNode(int index);
	void handleTheTurningNode();
	void moveSnake();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void eatFood();
	void makeFood();
	bool checkIfDead() const;
};

#endif