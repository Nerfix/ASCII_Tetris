// ASCII_Tetris.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Board.h"
#include "ConsoleLibrary.h"
#include "BoardDisplay.h"
#include <iostream>
#include <string>

const int boardWidth = 10;
const int boardHeight = 20;

void test() {
	Board tetrisBoard(boardWidth, boardHeight);
	tetrisBoard.initialize();
	tetrisBoard.printBoard();

	int input;
	std::cin >> input;

	Tetromino tetromino(Tetromino::J_SHAPE);
	COORD position;
	position.X = 4;
	position.Y = 4;

	tetrisBoard.addShape(tetromino, position);
	tetrisBoard.printBoard();

	std::cin >> input;

	//tetrisBoard.removeShape(tetromino, position);
	//tetrisBoard.printBoard();

	//std::cin >> input;

	COORD direction;
	direction.X = 1;
	direction.Y = 0;
	tetrisBoard.moveShape(tetromino, position, direction);
	tetrisBoard.printBoard();

	std::cin >> input;

	tetrisBoard.rotateShape(tetromino, position);
	tetrisBoard.printBoard();

	std::cin >> input;

	tetrisBoard.collapseRows();
	tetrisBoard.collapseRows();
	tetrisBoard.printBoard();

	std::cin >> input;
}

int main()
{
	//test();

	ConsoleLibrary console;
	Board board(boardWidth, boardHeight);
	BoardDisplay boardDisplay;

	board.initialize();
	
	console.SetTitle("ASCII Tetris");

	Tetromino tetromino(Tetromino::J_SHAPE);
	COORD spawnPosition;
	spawnPosition.X = (boardWidth / 2) + 1;
	spawnPosition.Y = 1;

	board.addShape(tetromino, spawnPosition);

	boardDisplay.displayBoard(board, console);

	int input;
	std::cin >> input;

	console.Clear();

    return 0;
}
