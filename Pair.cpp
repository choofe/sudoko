#include <iostream>
#include "Pair.h"

Pair::Pair(const int x,const int y) :m_x{ x }, m_y{ y }{}
Pair::Pair(const Pair& pair) : m_x{ pair.m_x }, m_y{ pair.m_y }
{
	*this = pair;
}
void const Pair::printPoint() { std::cout << m_x << " " << m_y << '\n'; }
const Pair& Pair::operator+=(const Pair& pair)
{
	m_x += pair.m_x;
	m_y += pair.m_y;
	return *this;
}
const Pair& Pair::operator-=(const Pair& pair)
{
	m_x -= pair.m_x;
	m_y -= pair.m_y;
	return *this;
	// TODO: insert return statement here
}
//void Pair::printPoint()
//{
//	std::cout << m_x << " " << m_y << '\n';
//}
const int Pair::getRow()const { return m_x; }
const int Pair::getColumn()const { return m_y; }
bool operator==(const Pair& p1, const Pair& p2)
{
	return(p1.getColumn() == p2.getColumn() && p1.getRow() == p2.getRow());
}
