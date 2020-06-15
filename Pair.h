#pragma once

#ifndef PAIR_H
#define PAIR_H
class Pair
{
	int m_x;
	int m_y;
public:
	Pair(const int x,const int y);
	Pair(const Pair& p);
	const int getRow()const;
	const int getCol()const;
	friend bool operator==(const Pair& p1, const Pair& p2);
	void const printPoint();
	const Pair& operator+=(const Pair& p);
	const Pair& operator-=(const Pair& p);
};
#endif // !PAIR_H
