#include "Block.h"
#include "Pair.h"
#include "Header.h" 

#ifndef POSITION_H
#define POSITION_H


class Position
{
private:
	std::vector<int> m_availableChecks; //hold cell's possible correct candidates
	std::vector<bool> m_availableCheckIndicator; //hold the place to create a block combinations
	std::size_t m_checkIndex;
	int m_index;					//holds the index of position
	int m_value;					//holds the value of position
	int m_gridRowNumber;				// block row position in block grid vector
	int m_gridColumnNumber;				//block column position in block grid vector
	int m_cellRow;					//cell row in block vector
	int m_cellColumn;					//cell column in block vector
	int m_totalRowIndex;			//index of row in block grid
	int m_totalColumnIndex;			//index of column in block grid
	bool m_isInitialNumber;				//true if provided in initial grid
public:
	Position();
	Position(const int linearPos, const int value);		//default constructor		
	void setValue(int value);								//set value of cell
	void setIsInitialNumber(bool filled);						//marks cell as initial
	void goToNextCheck();
	void goToFirstCheck();
	friend position_t initaialPositions(const BlockGrid& grid);
	bool operator==(Position& check);
	bool isThereMoreNumber(); //check if there are more possible numbers to check 
	void makeThisAvailablecheck(bool flag);
	bool flagState();
	const std::vector<int>& getAvailableChecks() const; //returns available check vector read only mode
	const std::size_t findCurrentTrueIndicator()const;
	std::vector<bool>& getAvailableCheckIndicator() ;
	void setCheckIndex(int newIndex);

	int getCheckIndex();
	int getIndex()const;			//returning position data
	int getGridRowNumber()const;		//returning row of grid where block that the cell is in!
	int getGridColumnNumber()const;		//returning column of grid where block that the cell is in!
	int getCellRow()const;			//returning row block that the cell is in!
	int getCellColumn()const;			//returning column block that the cell is in!
	int getTotalRowIndex()const;	//returning whole puzzle's row number which cell is in 
	int getTotalColumnIndex()const;	//returning whole puzzle's column number which cell is in
	int getValue()const;			//get the cell value
	bool getIsInitial()const;			//return whether cell is marked as initial or not
	
};


#endif // !POSITION_H
