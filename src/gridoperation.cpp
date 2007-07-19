/*!
    @file gridoperation.cpp
    @brief	class used to manage one grid ctrl
*/


#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "../src/gridoperation.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "../include/gridoperation.h"



GridOperation::GridOperation(wxGrid * fgrid)
{
	pGrid = fgrid;
}

GridOperation::~GridOperation()
{
}

void GridOperation::GridOpChangeColumnText(wxString ColumnText, int iColumn, bool bSize)
{
	pGrid->SetColLabelValue (iColumn,ColumnText);
	
	// check if there is enough place for the label
	if (bSize) 
	{
		pGrid->AutoSizeColumn(iColumn,FALSE);
		if (pGrid->GetColSize(iColumn) < 80)
		{
			pGrid->SetColSize (iColumn,80);
		}		
	}
	
}


void GridOperation::GridOpSetNumberOfColumn(int iNumber)
{
	int myNumberOfCols = pGrid->GetNumberCols();
	int myDiff = abs(myNumberOfCols - iNumber);
	
	// delete or add cols 
	if (myNumberOfCols > iNumber)
	{
		pGrid->DeleteCols(myNumberOfCols - myDiff,myDiff);
	}
	else if (myNumberOfCols < iNumber)
	{
		pGrid->AppendCols(myDiff);
	}
	
	// delete all rows...
	pGrid->DeleteRows(0,pGrid->GetNumberRows(),FALSE);
	
	
}



void GridOperation::GridOpAddDataRow(int iColumn, wxArrayString * myArray)
{
	// append a new row
	pGrid->AppendRows(1,FALSE);
	
	// get the number of rows
	int iRow = pGrid->GetNumberRows();
	
	for (int i=0; i<iColumn; i++)
	 {
		pGrid->SetCellValue(iRow-1,i,myArray->Item(i));
	}
}



