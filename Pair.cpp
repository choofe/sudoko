#include <iostream>
#include "Pair.h"

Pair::Pair(const int x,const int y) :m_x{ x }, m_y{ y }{}
Pair::Pair(const Pair& p) : m_x{ p.m_x }, m_y{ p.m_y }
{
	*this = p;
}
void const Pair::printPoint() { std::cout << m_x << " " << m_y << '\n'; }
const Pair& Pair::operator+=(const Pair& p)
{
	m_x += p.m_x;
	m_y += p.m_y;
	return *this;
}
const Pair& Pair::operator-=(const Pair& p)
{
	m_x -= p.m_x;
	m_y -= p.m_y;
	return *this;
	// TODO: insert return statement here
}
//void Pair::printPoint()
//{
//	std::cout << m_x << " " << m_y << '\n';
//}
const int Pair::getRow()const { return m_x; }
const int Pair::getCol()const { return m_y; }
bool operator==(const Pair& p1, const Pair& p2)
{
	return(p1.getCol() == p2.getCol() && p1.getRow() == p2.getRow());
}
