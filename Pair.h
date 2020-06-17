
#ifndef PAIR_H
#define PAIR_H
class Pair
{
	int m_x;
	int m_y;
public:
	Pair(const int x,const int y);
	Pair(const Pair& pair);
	const int getRow()const;
	const int getColumn()const;
	friend bool operator==(const Pair& p1, const Pair& p2);
	void const printPoint();
	const Pair& operator+=(const Pair& pair);
	const Pair& operator-=(const Pair& pair);
};
#endif // !PAIR_H
