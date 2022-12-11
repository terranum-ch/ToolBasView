
#include "toolbarbitmaps.h"

wxBitmap ToolbarBitmaps::GetBitmapFromSVG(ToolbarBitmapsID id, const wxString& colour, const wxSize& size) {
  wxString my_bmp_txt [] =
  {
    // NEW
    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M11 15v2q0 .425.288.712.287.288.712.288t.713-.288Q13 17.425 13 17v-2h2q.425 0 .713-.288Q16 14.425 16 14t-.287-.713Q15.425 13 15 13h-2v-2q0-.425-.287-.713Q12.425 10 12 10t-.712.287Q11 10.575 11 11v2H9q-.425 0-.712.287Q8 13.575 8 14t.288.712Q8.575 15 9 15Zm-5 7q-.825 0-1.412-.587Q4 20.825 4 20V4q0-.825.588-1.413Q5.175 2 6 2h7.175q.4 0 .763.15.362.15.637.425l4.85 4.85q.275.275.425.637.15.363.15.763V20q0 .825-.587 1.413Q18.825 22 18 22Zm7-14V4H6v16h12V9h-4q-.425 0-.712-.288Q13 8.425 13 8ZM6 4v5-5 16V4Z" style="fill:%s"/></svg>)",
    // OPEN,
    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M4 20q-.825 0-1.412-.587Q2 18.825 2 18V6q0-.825.588-1.412Q3.175 4 4 4h5.175q.4 0 .763.15.362.15.637.425L12 6h8q.825 0 1.413.588Q22 7.175 22 8H11.175l-2-2H4v12l1.975-6.575q.2-.65.738-1.038Q7.25 10 7.9 10h12.9q1.025 0 1.613.812.587.813.312 1.763l-1.8 6q-.2.65-.737 1.038Q19.65 20 19 20Zm2.1-2H19l1.8-6H7.9Zm0 0 1.8-6-1.8 6ZM4 10V6v4Z" style="fill:%s"/></svg>)",
    // COPY,
    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M9 18q-.825 0-1.412-.587Q7 16.825 7 16V4q0-.825.588-1.413Q8.175 2 9 2h9q.825 0 1.413.587Q20 3.175 20 4v12q0 .825-.587 1.413Q18.825 18 18 18Zm0-2h9V4H9v12Zm-4 6q-.825 0-1.413-.587Q3 20.825 3 20V7q0-.425.288-.713Q3.575 6 4 6t.713.287Q5 6.575 5 7v13h10q.425 0 .713.288.287.287.287.712t-.287.712Q15.425 22 15 22ZM9 4v12V4Z" style="fill:%s"/></svg>)",
    // EXPORT,
    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M12 16q-.425 0-.712-.288Q11 15.425 11 15V4.825l-.9.9Q9.825 6 9.413 6 9 6 8.7 5.7q-.275-.3-.275-.713 0-.412.275-.687l2.6-2.6q.125-.125.313-.2.187-.075.387-.075t.388.075q.187.075.312.2l2.6 2.6q.3.3.3.725t-.3.7Q15 6 14.588 6q-.413 0-.688-.275l-.9-.9V15q0 .425-.287.712Q12.425 16 12 16Zm-6 7q-.825 0-1.412-.587Q4 21.825 4 21V10q0-.825.588-1.413Q5.175 8 6 8h2q.425 0 .713.287Q9 8.575 9 9t-.287.712Q8.425 10 8 10H6v11h12V10h-2q-.425 0-.712-.288Q15 9.425 15 9t.288-.713Q15.575 8 16 8h2q.825 0 1.413.587Q20 9.175 20 10v11q0 .825-.587 1.413Q18.825 23 18 23Z" style="fill:%s"/></svg>)",
    // QUERY,
    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M5 4v6.025V10v10V4v5Zm3 10h2.5q.225-.575.55-1.075.325-.5.75-.925H8q-.425 0-.713.287Q7 12.575 7 13t.287.712Q7.575 14 8 14Zm0 4h2.175q-.125-.5-.162-1-.038-.5.012-1H8q-.425 0-.713.288Q7 16.575 7 17t.287.712Q7.575 18 8 18Zm-3 4q-.825 0-1.413-.587Q3 20.825 3 20V4q0-.825.587-1.413Q4.175 2 5 2h7.175q.4 0 .763.15.362.15.637.425l4.85 4.85q.275.275.425.637.15.363.15.763V10.5q-.475-.2-.975-.312-.5-.113-1.025-.163V9h-4q-.425 0-.712-.288Q12 8.425 12 8V4H5v16h6.025q.4.6.9 1.113.5.512 1.1.887Zm11.5-3q1.05 0 1.775-.725Q19 17.55 19 16.5q0-1.05-.725-1.775Q17.55 14 16.5 14q-1.05 0-1.775.725Q14 15.45 14 16.5q0 1.05.725 1.775Q15.45 19 16.5 19Zm5.8 3.3q-.275.275-.7.275-.425 0-.7-.275l-2-2q-.525.35-1.137.525Q17.15 21 16.5 21q-1.875 0-3.188-1.312Q12 18.375 12 16.5q0-1.875 1.312-3.188Q14.625 12 16.5 12q1.875 0 3.188 1.312Q21 14.625 21 16.5q0 .65-.175 1.262-.175.613-.525 1.138l2 2q.275.275.275.7 0 .425-.275.7Z" style="fill:%s"/></svg>)",
    // SIZE_COLS,
    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"> <path d="m 15.731293,8.2687066 q 0.275,-0.275 0.725,-0.275 0.45,0 0.725,0.275 l 3.075,3.0750004 q 0.15,0.15 0.213,0.325 0.062,0.175 0.062,0.375 0,0.2 -0.062,0.388 -0.063,0.187 -0.213,0.312 l -3.1,3.1 q -0.275,0.275 -0.712,0.262 -0.438,-0.012 -0.713,-0.287 -0.275,-0.275 -0.275,-0.725 0,-0.45 0.275,-0.725 l 2.325,-2.325 -2.35,-2.3500004 q -0.275,-0.275 -0.263,-0.712 0.013,-0.438 0.288,-0.713 z M 3.4812934,12.043707 q 0,-0.2 0.075,-0.375 0.075,-0.175 0.2,-0.325 l 3.075,-3.0750004 q 0.275,-0.275 0.725,-0.275 0.45,0 0.725,0.275 0.275,0.275 0.275,0.725 0,0.45 -0.275,0.725 l -2.325,2.3250004 2.35,2.35 q 0.275,0.275 0.262,0.712 -0.012,0.438 -0.287,0.713 -0.275,0.275 -0.725,0.275 -0.45,0 -0.725,-0.275 l -3.075,-3.075 q -0.125,-0.125 -0.2,-0.312 -0.075,-0.188 -0.075,-0.388 z" style="fill:%s"/></svg>)",
    // SIZE_ROWS
    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M8.225 8.325Q7.95 8.05 7.95 7.6q0-.45.275-.725L11.3 3.8q.15-.15.325-.213.175-.062.375-.062t.388.062q.187.063.312.213l3.1 3.1q.275.275.262.712-.012.438-.287.713-.275.275-.725.275-.45 0-.725-.275L12 6 9.65 8.35q-.275.275-.712.263-.438-.013-.713-.288ZM12 20.575q-.2 0-.375-.075t-.325-.2l-3.075-3.075q-.275-.275-.275-.725 0-.45.275-.725.275-.275.725-.275.45 0 .725.275L12 18.1l2.35-2.35q.275-.275.712-.262.438.012.713.287.275.275.275.725 0 .45-.275.725L12.7 20.3q-.125.125-.312.2-.188.075-.388.075Z" style="fill:%s"/></svg>)"
  };

  wxASSERT(id < (sizeof (my_bmp_txt) / sizeof (wxString)));
  wxString my_bmp = wxString::Format(my_bmp_txt[id], colour);
  return wxBitmapBundle::FromSVG(my_bmp, size).GetBitmap(size);
}
