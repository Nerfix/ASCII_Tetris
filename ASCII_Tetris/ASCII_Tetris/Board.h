#pragma once

#include <vector>
#include "Tetromino.h"

class Board {
private:
	int m_Width;
	int m_Height;
	int m_TotalWidth;
	int m_TotalHeight;
	std::vector<char> m_Board;

	int calculateSize() { return (m_Width + 2) * (m_Height + 3); }

	void initializeBorder();
	void clear();

	void addSegment(const COORD &segment);
	void removeSegment(const COORD &segment);
	bool segmentFits(const COORD &segment, const COORD &position);
	bool shapeFits(Tetromino &tetromino, const COORD &position);
	void clearRow(int row);
	void collapseSegment(const COORD &position);

public:
	// Internal representation
	static constexpr char m_Shape = 'X';
	static constexpr char m_Empty = ' ';
	static constexpr char m_Border = '#';

	Board(int width, int height) : m_Width(width), m_Height(height) { 
		m_Board.reserve(calculateSize());
		m_TotalWidth = width + 2;
		m_TotalHeight = height + 3;
	}
	~Board(void) {}

	void initialize();
	const std::vector<char>& getBoard() const;
	int getWidth() const;
	int getHeight() const;
	bool addShape(Tetromino &shape, const COORD &position);
	void removeShape(Tetromino &shape, const COORD &position);
	bool moveShape(Tetromino &shape, COORD &position, const COORD &direction);
	void rotateShape(Tetromino &shape, const COORD &position);
	int clearCompleteRows(void);
	void collapseRows(void);
};