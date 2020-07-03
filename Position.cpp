#include "Position.h"


//default constructor -empty cell info
Position::Position() : 
	m_checkIndex{0},
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
	m_checkIndex{ 0 },
	m_index{ linearPosition },
	m_value{ value },
	m_gridRowNumber{ linearPosition / 27 }, // is ((linearPos / 9) / 3)
	m_gridColumnNumber{ (linearPosition % 9) / 3 },
	m_cellRow{ (linearPosition / 9) % 3 },
	m_cellColumn{ (linearPosition % 9) % 3 },
	m_totalRowIndex{ linearPosition / 9 },
	m_totalColumnIndex{ linearPosition % 9 },
	m_isInitialNumber{false} //default is non initial we would set this member with correct value somewhere else
{}

void Position::setValue(int value)
{
	m_value = value;
}

void Position::setIsInitialNumber(bool filled)
{
	m_isInitialNumber = filled;
}

void Position::goToNextCheck()
{
	++this->m_checkIndex;
}

void Position::goToFirstCheck()
{
	m_checkIndex = 0;
}

bool Position::operator==(Position& check)
{
	return(this->getIndex() == check.getIndex());
}

bool Position::isThereMoreNumber()
{
	return (m_checkIndex <  (m_availableChecks.size()-1));
}

void Position::makeThisAvailablecheck(bool flag)
{
	m_availableCheckIndicator.at(m_checkIndex) = flag;
}

bool Position::flagState()
{
	return m_availableCheckIndicator[m_checkIndex];
}

const std::vector<int>& Position::getAvailableChecks()const
{
	return m_availableChecks;	// TODO: insert return statement here
}
const std::size_t Position::findCurrentTrueIndicator() const
{
	std::size_t indicator{ 0 };
	for (auto i : m_availableCheckIndicator)
		if (i) break;
		else ++indicator;
	return indicator;
		
}

std::vector<bool>& Position::getAvailableCheckIndicator() 
{
	return this->m_availableCheckIndicator;
}

void Position::setCheckIndex(int newIndex)
{
	using namespace std::chrono_literals;

	if (newIndex < m_availableChecks.size())
		m_checkIndex = newIndex;
	else
	{
		m_checkIndex =0;
		std::cout << "new checkIndex is out of range!!!";
		std::this_thread::sleep_for(5s);
	}
}

//std::vector<int>& Position::getAvailableChecks()
//{
//	return m_availableChecks;	// TODO: insert return statement here
//}

int Position::getCheckIndex()
{
	return m_checkIndex;
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

