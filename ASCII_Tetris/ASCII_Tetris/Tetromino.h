#pragma once

#include <array>
#include <Windows.h>

class Tetromino
{
private:
	std::array<COORD, 4> m_Segments;

public:
	enum TetrominoType {
		Z_SHAPE,
		S_SHAPE,
		I_SHAPE,
		T_SHAPE,
		L_SHAPE,
		J_SHAPE,
		O_SHAPE
	};

	Tetromino(TetrominoType type);
	Tetromino(const Tetromino &tetromino);
	~Tetromino(void);

	COORD GetSegment(int index) const;
	std::array<COORD, 4> GetSegments(void) const;
	void SetSegment(COORD segment, int index);
};