#include "stdafx.h"
#include "Tetromino.h"

Tetromino::Tetromino(TetrominoType type) {
	switch (type) {
	case TetrominoType::I_SHAPE:
		m_Segments.at(0).X = 0;
		m_Segments.at(0).Y = 0;

		m_Segments.at(1).X = 0;
		m_Segments.at(1).Y = -1;

		m_Segments.at(2).X = 0;
		m_Segments.at(2).Y = 1;

		m_Segments.at(3).X = 0;
		m_Segments.at(3).Y = 2;
		break;

	case TetrominoType::J_SHAPE:
		m_Segments.at(0).X = 0;
		m_Segments.at(0).Y = 0;

		m_Segments.at(1).X = 0;
		m_Segments.at(1).Y = -1;

		m_Segments.at(2).X = 0;
		m_Segments.at(2).Y = 1;

		m_Segments.at(3).X = -1;
		m_Segments.at(3).Y = 1;
		break;

	case TetrominoType::L_SHAPE:
		m_Segments.at(0).X = 0;
		m_Segments.at(0).Y = 0;

		m_Segments.at(1).X = 0;
		m_Segments.at(1).Y = -1;

		m_Segments.at(2).X = 0;
		m_Segments.at(2).Y = 1;

		m_Segments.at(3).X = 1;
		m_Segments.at(3).Y = 1;
		break;

	case TetrominoType::O_SHAPE:
		m_Segments.at(0).X = 0;
		m_Segments.at(0).Y = 0;

		m_Segments.at(1).X = 1;
		m_Segments.at(1).Y = 0;

		m_Segments.at(2).X = 1;
		m_Segments.at(2).Y = 1;

		m_Segments.at(3).X = 0;
		m_Segments.at(3).Y = 1;
		break;

	case TetrominoType::S_SHAPE:
		m_Segments.at(0).X = 0;
		m_Segments.at(0).Y = 0;

		m_Segments.at(1).X = 1;
		m_Segments.at(1).Y = 0;

		m_Segments.at(2).X = 0;
		m_Segments.at(2).Y = 1;

		m_Segments.at(3).X = -1;
		m_Segments.at(3).Y = 1;
		break;

	case TetrominoType::T_SHAPE:
		m_Segments.at(0).X = 0;
		m_Segments.at(0).Y = 0;

		m_Segments.at(1).X = 1;
		m_Segments.at(1).Y = 0;

		m_Segments.at(2).X = 0;
		m_Segments.at(2).Y = 1;

		m_Segments.at(3).X = -1;
		m_Segments.at(3).Y = 0;
		break;

	case TetrominoType::Z_SHAPE:
		m_Segments.at(0).X = 0;
		m_Segments.at(0).Y = 0;

		m_Segments.at(1).X = -1;
		m_Segments.at(1).Y = 0;

		m_Segments.at(2).X = 0;
		m_Segments.at(2).Y = 1;

		m_Segments.at(3).X = 1;
		m_Segments.at(3).Y = 1;
		break;
	}
}

Tetromino::Tetromino(const Tetromino &tetromino) {
	m_Segments = tetromino.GetSegments();
}

Tetromino::~Tetromino(void) {

}

COORD Tetromino::GetSegment(int index) const{
	if (index >= 0 && index < m_Segments.size()) {
		return m_Segments.at(index);
	}
}

std::array<COORD, 4> Tetromino::GetSegments() const{
	return m_Segments;
}

void Tetromino::SetSegment(COORD coord, int index) {
	if (index >= 1 && index < m_Segments.size()) {
		m_Segments.at(index) = coord;
	}
}