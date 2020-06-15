#pragma once
#include "Block.h"
#include "BlockGrid.h"
#include "Pair.h"


class Position
{
private:
	int m_index;					//holds the index of position
	int m_value;					//holds the value of position
	int m_gridRowNum;				// block row position in block grid vector
	int m_gridColNum;				//block col position in block grid vector
	int m_cellRow;					//cell row in block vector
	int m_cellCol;					//cell col in block vector
	int m_totalRowIndex;			//index of row in block grid
	int m_totalColIndex;			//index of col in block grid
	bool m_isInitNum;				//true if provided in inital grid
public:
	Position();
	Position(const int linearPos,const int val);		//default constructor		
	void setValue(int val);								//set value of cell
	void setIsInitNum(bool filled);						//marks cell as initial
	
	int getIndex()const;			//returning position data
	int getGridRowNum()const;		//returning row of grid where block that the cell is in!
	int getGridColNum()const;		//returning col of grid where block that the cell is in!
	int getCellRow()const;			//returning row block that the cell is in!
	int getCellCol()const;			//returning col block that the cell is in!
	int getTotalRowIndex()const;	//returning whole puzzle's row number which cell is in 
	int getTotalColIndex()const;	//returning whole puzzle's col number which cell is in
	int getValue()const;			//get the cell value
	bool getIsInit()const;			//return whether cell is marked as initial or not
	~Position();
};

