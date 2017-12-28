#include "stdafx.h"
#include "BoardDisplay.h"

void BoardDisplay::displayBoard(const Board &board, const ConsoleLibrary &console) const{
	const std::vector<char> boardRows(board.getBoard());
	std::string boardRow;
	for (int row = 0; row < board.getHeight() - 1; ++row) {
		boardRow = "";
		for (int col = 0; col < board.getWidth(); ++col) {
			switch (boardRows.at(row * board.getWidth() + col)) {
			case Board::m_Shape:
				boardRow += m_Segment;
				break;
			case Board::m_Empty:
				boardRow += m_EmptySegment;
				break;
			case Board::m_Border:
				boardRow += m_SideBorder;
				break;
			}
		}
		boardRow += "\n";
		console.OutputString(boardRow);
	}

	boardRow = "";
	boardRow += m_Corner;
	for (int col = 1; col < board.getWidth() - 1; ++col) {
		boardRow += m_BottomBorder;
	}
	boardRow += m_Corner;
	console.OutputString(boardRow);
}