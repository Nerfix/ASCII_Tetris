// ASCII_Tetris.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Board.h"
#include "ConsoleLibrary.h"
#include "BoardDisplay.h"
#include "KeyHandle.h"
#include <thread>
#include <iostream>
#include <string>

const int boardWidth = 10;
const int boardHeight = 20;

const COORD DIRECTION_LEFT = { -1, 0 };
const COORD DIRECTION_RIGHT = { 1, 0 };
const COORD DIRECTION_DOWN = { 0, 1 };

enum Key {
	LEFT_KEY,
	RIGHT_KEY,
	DOWN_KEY,
	ROTATE_KEY
};

void initializeKey(KeyHandle &keyHandle, int id) {
	keyHandle.state = false;
	
	switch (id) {
	case LEFT_KEY:
		keyHandle.key = 0x41;
		break;
	case RIGHT_KEY:
		keyHandle.key = 0x44;
		break;
	case DOWN_KEY:
		keyHandle.key = 0x53;
		break;
	case ROTATE_KEY:
		keyHandle.key = 0x57;
		break;
	}
}

void initializeKeys(std::array<KeyHandle, 4> &keyHandles) {
	for (int i = 0; i < keyHandles.size(); ++i) {
		initializeKey(keyHandles.at(i), i);
	}
}

Tetromino::TetrominoType getRandomTetrominoType() {
	int type = rand() % 7;
	return static_cast<Tetromino::TetrominoType>(type);
}

int main()
{
	ConsoleLibrary console;
	Board board(boardWidth, boardHeight);
	BoardDisplay boardDisplay;
	bool gameOver = false;

	board.initialize();
	srand((unsigned)time(0));
	
	console.SetTitle("ASCII Tetris");

	Tetromino tetromino(getRandomTetrominoType());
	COORD spawnPosition;
	spawnPosition.X = (boardWidth / 2);
	spawnPosition.Y = 1;
	COORD tetrominoPosition = spawnPosition;
	board.addShape(tetromino, spawnPosition);

	int score = 0;

	console.Clear();

	int maxCycles = 20;
	int cyclesCount = 0;
	bool applyGravity = false;

	bool rotationLocked = false;

	std::array<KeyHandle, 4> keyHandles;
	initializeKeys(keyHandles);

	while (!gameOver) {
		// Simulate a cycle =======================
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		cyclesCount++;
		applyGravity = (cyclesCount == maxCycles);

		// Process input ==========================
		for (int index = 0; index < 4; ++index) {
			keyHandles.at(index).state = GetAsyncKeyState(keyHandles.at(index).key);
		}

		// Update game state ======================
		// TODO refactor to use loop
		if (keyHandles.at(0).state) { board.moveShape(tetromino, tetrominoPosition, DIRECTION_LEFT); }
		if (keyHandles.at(1).state) { board.moveShape(tetromino, tetrominoPosition, DIRECTION_RIGHT); }
		if (keyHandles.at(2).state) { board.moveShape(tetromino, tetrominoPosition, DIRECTION_DOWN); }

		if (keyHandles.at(3).state) { 
			if (!rotationLocked) {
				board.rotateShape(tetromino, tetrominoPosition);
				rotationLocked = true;
			}
		}
		else {
			rotationLocked = false;
		}

		if (applyGravity) {
			// TODO Increase difficulty
			cyclesCount = 0;

			if (!board.moveShape(tetromino, tetrominoPosition, DIRECTION_DOWN)) {
				int completeRows = board.clearCompleteRows();
				score += completeRows * 100;
				for (int i = 0; i < completeRows; ++i) {
					board.collapseRows();
				}

				tetromino = Tetromino(getRandomTetrominoType());
				tetrominoPosition = spawnPosition;

				if (!board.addShape(tetromino, tetrominoPosition)) {
					gameOver = true;
				}
			}
		}

		// Display board ==========================
		console.Clear();
		boardDisplay.displayBoard(board, console);
		boardDisplay.displayScore(score, console);
		
	}

	console.Clear();
	console.OutputString("Game Over!\n");

    return 0;
}
