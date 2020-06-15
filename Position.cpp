#include "Position.h"


//default constructor -empty cell info
Position::Position() : 
	m_index{0},
	m_value{0},
	m_gridRowNum{0},
	m_gridColNum{0},
	m_cellRow{0},
	m_cellCol{0},
	m_totalRowIndex{0},
	m_totalColIndex{0},
	m_isInitNum{ false }
{}
//constructor with setting position using
//3x3 grid of 3x3 blocks
//if val is non zero cell is initial
Position::Position(const int linearPos, const int val) :
	m_index{ linearPos },
	m_value{ val },
	m_gridRowNum{ linearPos / 27 }, // is ((linearPos / 9) / 3)
	m_gridColNum{ (linearPos % 9) / 3 },
	m_cellRow{ (linearPos / 9) % 3 },
	m_cellCol{ (linearPos % 9) % 3 },
	m_totalRowIndex{ linearPos / 9 },
	m_totalColIndex{ linearPos % 9 },
	m_isInitNum{false} //default is non initial we would set this member with correct value somewhere else
{

}

void Position::setValue(int val)
{
	m_value = val;
}

void Position::setIsInitNum(bool filled)
{
	m_isInitNum = filled;
}

int Position::getIndex() const
{
	return m_index;
}

int Position::getGridRowNum() const
{
	return m_gridRowNum;
}

int Position::getGridColNum() const
{
	return m_gridColNum;
}

int Position::getCellRow() const
{
	return m_cellRow;
}

int Position::getCellCol() const
{
	return m_cellCol;
}

int Position::getTotalRowIndex() const
{
	return m_totalRowIndex;
}

int Position::getTotalColIndex() const
{
	return m_totalColIndex;
}

int Position::getValue() const
{
	return m_value;
}

bool Position::getIsInit() const
{
	return m_isInitNum;
}

Position::~Position()
{
}
