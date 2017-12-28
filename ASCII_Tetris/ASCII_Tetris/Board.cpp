#include "stdafx.h"
#include "Board.h"
#include "Tetromino.h"
#include <iostream>

void Board::initializeBorder() {

	for (int cell = 0; cell < (m_TotalHeight * m_TotalWidth) - m_TotalWidth; cell += m_TotalWidth) {
		// Left border
		m_Board[cell] = m_Border;
	}

	for (int cell = m_TotalWidth - 1; cell < m_TotalHeight * m_TotalWidth; cell += m_TotalWidth) {
		// Right border
		m_Board[cell] = m_Border;
	}

	for (int cell = (m_TotalHeight * m_TotalWidth) - (m_TotalWidth - 1); cell < (m_TotalHeight * m_TotalWidth) - 1; ++cell) {
		// Bottom border
		m_Board[cell] = m_Border;
	}

	// Bottom left and bottom right corners
	m_Board[(m_TotalHeight * m_TotalWidth) - m_TotalWidth] = m_Border;
	m_Board[(m_TotalHeight * m_TotalWidth) - 1] = m_Border;
}

void Board::clear() {
	for (int row = 0; row < m_TotalHeight * m_TotalWidth; row += m_TotalWidth) {
		for (int col = 0; col < m_TotalWidth; ++col) {
			m_Board[row + col] = ' ';
		}
	}
}

void Board::initialize() {
	//clear();
	m_Board.assign(calculateSize(), ' ');
	initializeBorder();
}

void initializeCoord(int x, int y, COORD &coord) {
	coord.X = x;
	coord.Y = y;
}

const std::vector<char>& Board::getBoard() const{
	return m_Board;
}

int Board::getWidth() const{
	return m_TotalWidth;
}

int Board::getHeight() const{
	return m_TotalHeight;
}

void Board::printBoard() {
	for (int row = 0; row < (m_TotalHeight * m_TotalWidth) - m_TotalWidth; row += m_TotalWidth) {
		
		std::cout << m_SideBorder;

		for (int col = 1; col < (m_TotalWidth - 1); ++col) {
			if (m_Board.at(row + col) == ' ') {
				std::cout << m_EmptyCell << m_EmptyCell;
			}
			else if (m_Board.at(row + col) == 'X') {
				std::cout << m_SegmentLeftHalf << m_SegmentRightHalf;
			}
		}

		std::cout << m_SideBorder;
		std::cout << std::endl;
	}

	int row = m_TotalHeight - 1;
	std::cout << m_Corner;

	for (int col = 1; col < (m_TotalWidth - 1); ++col) {
		std::cout << m_BottomBorder << m_BottomBorder;
	}

	std::cout << m_Corner;
	std::cout << std::endl;
}

bool Board::segmentFits(const COORD &segment, const COORD &position) {
	bool segmentFits(true);
	int xCoordinate = segment.X + position.X;
	int yCoordinate = segment.Y + position.Y;

	if (m_Board.at(yCoordinate * m_TotalWidth + xCoordinate) == m_EmptyCell) {
		return segmentFits;
	}

	return !segmentFits;
}

bool Board::shapeFits(Tetromino &tetromino, const COORD &position) {
	bool shapeFits(true);
	for (auto segment : tetromino.GetSegments()) {
		shapeFits &= segmentFits(segment, position);
	}

	return shapeFits;
}

void Board::addShape(Tetromino &tetromino, const COORD &position) {

	if (!shapeFits(tetromino, position))
		return;
	
	for (auto segment : tetromino.GetSegments()) {
		COORD segmentPosition;
		initializeCoord(segment.X + position.X, segment.Y + position.Y, segmentPosition);
		
		addSegment(segmentPosition);
	}
}

void Board::addSegment(const COORD &position) {
	m_Board.at(position.Y * m_TotalWidth + position.X) = m_Shape;
}

void Board::removeSegment(const COORD &position) {
	m_Board.at(position.Y * m_TotalWidth + position.X) = m_Empty;
}

void Board::removeShape(Tetromino &tetromino, const COORD &position) {
	for (auto segment : tetromino.GetSegments()) {
		COORD segmentPosition;
		segmentPosition.X = segment.X + position.X;
		segmentPosition.Y = segment.Y + position.Y;

		removeSegment(segmentPosition);
	}
}

bool Board::moveShape(Tetromino &tetromino, COORD &position, const COORD &direction) {
	COORD newPosition;
	initializeCoord(position.X + direction.X, position.Y + direction.Y, newPosition);

	removeShape(tetromino, position);

	if (!shapeFits(tetromino, newPosition)) {
		addShape(tetromino, position);
		return false;
	}
		
	addShape(tetromino, newPosition);
	position = newPosition;
	return true;
}

COORD rotateSegment(const COORD &segment) {
	COORD rotatedSegment;
	initializeCoord(-segment.Y, segment.X, rotatedSegment);
	return rotatedSegment;
}

void Board::rotateShape(Tetromino &tetromino, const COORD &position) {
	Tetromino rotatedTetromino(tetromino);
	COORD rotatedSegment;

	for (int index = 1; index < 4; ++index) {
		rotatedSegment = rotateSegment(rotatedTetromino.GetSegment(index));
		rotatedTetromino.SetSegment(rotatedSegment, index);
	}

	removeShape(tetromino, position);

	if (!shapeFits(rotatedTetromino, position)) {
		addShape(tetromino, position);
		return;
	}

	addShape(rotatedTetromino, position);
}

void Board::clearRow(int row) {
	if (row < 0 || row >= m_TotalHeight)
		return;
	
	for (int col = 1; col < m_TotalWidth - 1; ++col) {
		m_Board.at(row * m_TotalWidth + col) = m_Empty;
	}
}

int Board::clearCompleteRows(void) {
	int rowsCleared = 0;
	bool rowIsFull = true;
	for (int row = 0; row < m_TotalHeight - 1; ++row) {
		for (int col = 1; col < m_TotalWidth - 1; ++col) {
			if (m_Board.at(row * m_TotalWidth + col) != m_Shape)
				rowIsFull = false;
		}

		if (rowIsFull) {
			clearRow(row);
			rowsCleared += 1;
		}
	}

	return rowsCleared;
}

void Board::collapseSegment(const COORD &position) {
	COORD direction;
	initializeCoord(0, 1, direction); // DOWN

	if (!segmentFits(direction, position))
		return;

	COORD newPosition;
	initializeCoord(position.X + direction.X, position.Y + direction.Y, newPosition);

	removeSegment(position);
	addSegment(newPosition);
}

void Board::collapseRows() {
	for (int row = m_TotalHeight - 3; row >= 0; --row) {
		for (int col = 1; col < m_TotalWidth - 1; ++col) {
			if (m_Board.at(row * m_TotalWidth + col) == m_Shape) {
				COORD segment;
				initializeCoord(col, row, segment);
				collapseSegment(segment);
			}
		}
	}
}