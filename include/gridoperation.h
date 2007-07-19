/*!
    @file
    @brief	class used to manage one grid ctrl
*/


#ifndef __gridoperation_H__
#define __gridoperation_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "../src/gridoperation.cpp"
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif


#include <wx/grid.h> // for all grid operations.

class GridOperation
{
public:
    // constructors and destructors
    /*!
    @function 
    @brief	contructor of the grid operation class
    @param      fgrid pointer to an existing wxGrid
	*/
	GridOperation(wxGrid * fgrid);
    virtual ~GridOperation();
    /*!
    @function 
    @brief	Allow to change one column name
    @param  ColumnText The new name of the column
	@param iColumn The column index to be changed, 0 is the first column.
	@param bSize If bSize = TRUE, we resize the cols to fit the content otherwise 
	the col is not resized. bSize is set to TRUE ( default).
	*/
	void GridOpChangeColumnText(wxString ColumnText, int iColumn, bool bSize=TRUE);
	
	 /*!
    @function 
    @brief	change the number of columns
    @param iNumber the new number of columns
	*/
	void GridOpSetNumberOfColumn(int iNumber);
	
	/*!
    @function 
    @brief This function will append a new row of data.
    
    @param      iColumn the number of column we want to add data to
    @param     myArray a pointer to the structure containing the data.
	*/
	void GridOpAddDataRow(int iColumn, wxArrayString * myArray);
	
    
    
    
private:
	wxGrid * pGrid;
};




#endif
