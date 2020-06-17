#include "Position.h"


//default constructor -empty cell info
Position::Position() : 
	m_index{0},
	m_value{0},
	m_gridRowNumber{0},
	m_gridColumnNumber{0},
	m_cellRow{0},
	m_cellColumn{0},
	m_totalRowIndex{0},
	m_totalColumnIndex{0},
	m_isInitialNumber{ false }
{}
//constructor with setting position using
//3x3 grid of 3x3 blocks
//if value is non zero cell is initial
Position::Position(const int linearPosition, const int value) :
	m_index{ linearPosition },
	m_value{ value },
	m_gridRowNumber{ linearPosition / 27 }, // is ((linearPos / 9) / 3)
	m_gridColumnNumber{ (linearPosition % 9) / 3 },
	m_cellRow{ (linearPosition / 9) % 3 },
	m_cellColumn{ (linearPosition % 9) % 3 },
	m_totalRowIndex{ linearPosition / 9 },
	m_totalColumnIndex{ linearPosition % 9 },
	m_isInitialNumber{false} //default is non initial we would set this member with correct value somewhere else
{

}

void Position::setValue(int value)
{
	m_value = value;
}

void Position::setIsInitialNumber(bool filled)
{
	m_isInitialNumber = filled;
}

int Position::getIndex() const
{
	return m_index;
}

int Position::getGridRowNumber() const
{
	return m_gridRowNumber;
}

int Position::getGridColumnNumber() const
{
	return m_gridColumnNumber;
}

int Position::getCellRow() const
{
	return m_cellRow;
}

int Position::getCellColumn() const
{
	return m_cellColumn;
}

int Position::getTotalRowIndex() const
{
	return m_totalRowIndex;
}

int Position::getTotalColumnIndex() const
{
	return m_totalColumnIndex;
}

int Position::getValue() const
{
	return m_value;
}

bool Position::getIsInitial() const
{
	return m_isInitialNumber;
}

Position::~Position()
{
}
