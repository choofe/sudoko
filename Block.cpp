#include "Block.h"

Block::Block(const block_t& block) :m_block{ block } {} //in case user provide a block_t
Block::Block(const Block& b) {m_block = b.m_block;}		//copy constructor
// too lazy to think of a more intuitive way to call this constructor!
// so just throw a parameter to do so!!! 
// and this one create a int'0' filled block
// no matter zero is true or false
Block::Block(bool zero) 
{
	block_t temp{ block_t(BLOCKROWSIZE, std::vector<int>(BLOCKCOLSIZE)) };
	m_block = temp;
}

//returns true if val is not present in this block
//returns false if val is present in this block
bool Block::blockCheck(int val)
{
	for (size_t i{ 0 }; i < m_block.size(); ++i)
		for (size_t j{ 0 }; j < m_block.at(0).size(); ++j)
		{
			if (val == m_block.at(i).at(j)) return false;
		}
	return true;
}


// create a shuffled block_t which contains digits 1~9 in a random order
Block::Block() //default constructor
{
	block_t temp{ block_t(BLOCKROWSIZE, std::vector<int>(BLOCKCOLSIZE)) };
	m_block = fillShuffle(temp);
}

//shuffling method
block_t& Block::fillShuffle(block_t& b)
{
	//fill b with sorted number 1 ~ 9
	//////////////////////////////////////////
	int count{ 1 };
	for (size_t i{ 0 }; i < b.size(); ++i)
		for (size_t j{ 0 }; j < b.at(0).size(); ++j)
		{
			b.at(i).at(j) = count;
			++count;
		}
	///////////////////////////////////////////
	
	//shuffling sort filled b 
	///////////////////////////////////////////
	static std::mt19937 rand{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	static std::uniform_int_distribution row{ 0,static_cast<int>(b.size() - 1) };//uniform distribution between 0 and rowsize 
	static std::uniform_int_distribution col{ 0,static_cast<int>(b.at(0).size() - 1) };//uniform distribution between 0 and column size
	int numOfShuffling{ 100 }; //number of shuffling-not !

	for (int i{ 0 }; i <= numOfShuffling; ++i)
	{
		Pair p1(row(rand), col(rand));
		Pair p2(row(rand), col(rand));
		swap(b, p1, p2);
	}
	return b;
}
//swapping method
void Block::swap(block_t& b, Pair& p1, Pair& p2)
{
	if (p1 == p2) return;
	int t{ 0 };
	t = b.at(p1.getRow()).at(p1.getCol());
	b.at(p1.getRow()).at(p1.getCol()) = b.at(p2.getRow()).at(p2.getCol());
	b.at(p2.getRow()).at(p2.getCol()) = t;
}

//returning whole rowIndex row of block
const std::vector<int> Block::getRow(int rowIndex) const
{
	std::vector<int> row;
	for (size_t i{ 0 }; i < m_block.size(); ++i)
		row.push_back(m_block.at(rowIndex).at(i));
	return row;
}
//returning whole rowIndex row of block
const std::vector<int> Block::getCol(int colIndex) const
{
	std::vector<int> row;
	for (size_t i{ 0 }; i < m_block.at(colIndex).size(); ++i)
		row.push_back(m_block.at(i).at(colIndex));
	return row;
}

//returning basic data
const block_t& Block::getBlock() const {return m_block;}
int Block::getRowSize() { return m_block.size(); } //rows number
int Block::getColSize() { return m_block.at(0).size(); } //cols number
void Block::printBlock() { std::cout << *this; } //print current m_block
const int Block::memberAccess(int x, int y) const { return m_block.at(x).at(y); } //cell value in [x,y]

//setting value in p with val
void Block::memberSet(const Pair& p,int val)
{
	m_block.at(p.getRow()).at(p.getCol()) = val;
}

//believe it or not! this overloading was necessary!!
//so I just put it here. No harm!
std::ostream& operator<<(std::ostream& out, std::ostream& in) 
{
	return in;
}

std::ostream& operator<<(std::ostream& out,const Block& b)  
{
	for (unsigned int i{ 0 }; i < b.m_block.size(); ++i)
	{
		for (unsigned int j{ 0 }; j < b.m_block[i].size(); ++j)
			out << b.m_block.at(i).at(j) << " ";
		out << '\n';
	}
	return out;
}

Block::~Block()
{
}