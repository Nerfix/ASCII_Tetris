#pragma once
#include <string>
#include "Board.h"
#include "ConsoleLibrary.h"

class BoardDisplay{
private:
	const std::string m_Segment;
	const std::string m_EmptySegment;
	const std::string m_SideBorder;
	const std::string m_BottomBorder;
	const std::string m_Corner;
public:
	BoardDisplay() : m_Segment("[]"), m_EmptySegment("  "), m_SideBorder("|"), m_BottomBorder("--"), m_Corner("+") {}
	~BoardDisplay() {}
	void displayBoard(const Board &board, const ConsoleLibrary &console) const;
	void displayScore(int score, ConsoleLibrary &console);
};