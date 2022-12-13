#include "toolbarbitmaps.h"

wxString
    Bitmaps::
        SvgText
            [] =
                {
                    // NEW
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M11 15v2q0 .425.288.712.287.288.712.288t.713-.288Q13 17.425 13 17v-2h2q.425 0 .713-.288Q16 14.425 16 14t-.287-.713Q15.425 13 15 13h-2v-2q0-.425-.287-.713Q12.425 10 12 10t-.712.287Q11 10.575 11 11v2H9q-.425 0-.712.287Q8 13.575 8 14t.288.712Q8.575 15 9 15Zm-5 7q-.825 0-1.412-.587Q4 20.825 4 20V4q0-.825.588-1.413Q5.175 2 6 2h7.175q.4 0 .763.15.362.15.637.425l4.85 4.85q.275.275.425.637.15.363.15.763V20q0 .825-.587 1.413Q18.825 22 18 22Zm7-14V4H6v16h12V9h-4q-.425 0-.712-.288Q13 8.425 13 8ZM6 4v5-5 16V4Z" style="fill:%s"/></svg>)",
                    // OPEN
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M4 20q-.825 0-1.412-.587Q2 18.825 2 18V6q0-.825.588-1.412Q3.175 4 4 4h5.175q.4 0 .763.15.362.15.637.425L12 6h8q.825 0 1.413.588Q22 7.175 22 8H11.175l-2-2H4v12l1.975-6.575q.2-.65.738-1.038Q7.25 10 7.9 10h12.9q1.025 0 1.613.812.587.813.312 1.763l-1.8 6q-.2.65-.737 1.038Q19.65 20 19 20Zm2.1-2H19l1.8-6H7.9Zm0 0 1.8-6-1.8 6ZM4 10V6v4Z" style="fill:%s"/></svg>)",
                    // COPY
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M9 18q-.825 0-1.412-.587Q7 16.825 7 16V4q0-.825.588-1.413Q8.175 2 9 2h9q.825 0 1.413.587Q20 3.175 20 4v12q0 .825-.587 1.413Q18.825 18 18 18Zm0-2h9V4H9v12Zm-4 6q-.825 0-1.413-.587Q3 20.825 3 20V7q0-.425.288-.713Q3.575 6 4 6t.713.287Q5 6.575 5 7v13h10q.425 0 .713.288.287.287.287.712t-.287.712Q15.425 22 15 22ZM9 4v12V4Z" style="fill:%s"/></svg>)",
                    // EXPORT
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M12 16q-.425 0-.712-.288Q11 15.425 11 15V4.825l-.9.9Q9.825 6 9.413 6 9 6 8.7 5.7q-.275-.3-.275-.713 0-.412.275-.687l2.6-2.6q.125-.125.313-.2.187-.075.387-.075t.388.075q.187.075.312.2l2.6 2.6q.3.3.3.725t-.3.7Q15 6 14.588 6q-.413 0-.688-.275l-.9-.9V15q0 .425-.287.712Q12.425 16 12 16Zm-6 7q-.825 0-1.412-.587Q4 21.825 4 21V10q0-.825.588-1.413Q5.175 8 6 8h2q.425 0 .713.287Q9 8.575 9 9t-.287.712Q8.425 10 8 10H6v11h12V10h-2q-.425 0-.712-.288Q15 9.425 15 9t.288-.713Q15.575 8 16 8h2q.825 0 1.413.587Q20 9.175 20 10v11q0 .825-.587 1.413Q18.825 23 18 23Z" style="fill:%s"/></svg>)",
                    // QUERY_PANEL
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M5 4v6.025V10v10V4v5Zm3 10h2.5q.225-.575.55-1.075.325-.5.75-.925H8q-.425 0-.713.287Q7 12.575 7 13t.287.712Q7.575 14 8 14Zm0 4h2.175q-.125-.5-.162-1-.038-.5.012-1H8q-.425 0-.713.288Q7 16.575 7 17t.287.712Q7.575 18 8 18Zm-3 4q-.825 0-1.413-.587Q3 20.825 3 20V4q0-.825.587-1.413Q4.175 2 5 2h7.175q.4 0 .763.15.362.15.637.425l4.85 4.85q.275.275.425.637.15.363.15.763V10.5q-.475-.2-.975-.312-.5-.113-1.025-.163V9h-4q-.425 0-.712-.288Q12 8.425 12 8V4H5v16h6.025q.4.6.9 1.113.5.512 1.1.887Zm11.5-3q1.05 0 1.775-.725Q19 17.55 19 16.5q0-1.05-.725-1.775Q17.55 14 16.5 14q-1.05 0-1.775.725Q14 15.45 14 16.5q0 1.05.725 1.775Q15.45 19 16.5 19Zm5.8 3.3q-.275.275-.7.275-.425 0-.7-.275l-2-2q-.525.35-1.137.525Q17.15 21 16.5 21q-1.875 0-3.188-1.312Q12 18.375 12 16.5q0-1.875 1.312-3.188Q14.625 12 16.5 12q1.875 0 3.188 1.312Q21 14.625 21 16.5q0 .65-.175 1.262-.175.613-.525 1.138l2 2q.275.275.275.7 0 .425-.275.7Z" style="fill:%s"/></svg>)",
                    // SIZE_COLS
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"> <path d="m 15.731293,8.2687066 q 0.275,-0.275 0.725,-0.275 0.45,0 0.725,0.275 l 3.075,3.0750004 q 0.15,0.15 0.213,0.325 0.062,0.175 0.062,0.375 0,0.2 -0.062,0.388 -0.063,0.187 -0.213,0.312 l -3.1,3.1 q -0.275,0.275 -0.712,0.262 -0.438,-0.012 -0.713,-0.287 -0.275,-0.275 -0.275,-0.725 0,-0.45 0.275,-0.725 l 2.325,-2.325 -2.35,-2.3500004 q -0.275,-0.275 -0.263,-0.712 0.013,-0.438 0.288,-0.713 z M 3.4812934,12.043707 q 0,-0.2 0.075,-0.375 0.075,-0.175 0.2,-0.325 l 3.075,-3.0750004 q 0.275,-0.275 0.725,-0.275 0.45,0 0.725,0.275 0.275,0.275 0.275,0.725 0,0.45 -0.275,0.725 l -2.325,2.3250004 2.35,2.35 q 0.275,0.275 0.262,0.712 -0.012,0.438 -0.287,0.713 -0.275,0.275 -0.725,0.275 -0.45,0 -0.725,-0.275 l -3.075,-3.075 q -0.125,-0.125 -0.2,-0.312 -0.075,-0.188 -0.075,-0.388 z" style="fill:%s"/></svg>)",
                    // SIZE_ROWS
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="24" width="24"><path d="M8.225 8.325Q7.95 8.05 7.95 7.6q0-.45.275-.725L11.3 3.8q.15-.15.325-.213.175-.062.375-.062t.388.062q.187.063.312.213l3.1 3.1q.275.275.262.712-.012.438-.287.713-.275.275-.725.275-.45 0-.725-.275L12 6 9.65 8.35q-.275.275-.712.263-.438-.013-.713-.288ZM12 20.575q-.2 0-.375-.075t-.325-.2l-3.075-3.075q-.275-.275-.275-.725 0-.45.275-.725.275-.275.725-.275.45 0 .725.275L12 18.1l2.35-2.35q.275-.275.712-.262.438.012.713.287.275.275.275.725 0 .45-.275.725L12.7 20.3q-.125.125-.312.2-.188.075-.388.075Z" style="fill:%s"/></svg>)",
                    // DATABASE
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="20" width="20"><path d="M10 9q-3.062 0-5.031-.844Q3 7.312 3 6q0-1.229 2.062-2.115Q7.125 3 10 3q2.875 0 4.938.885Q17 4.771 17 6q0 1.312-1.969 2.156Q13.062 9 10 9Zm0 4q-2.979 0-4.99-.865Q3 11.271 3 10V8.042q0 .604.562 1.135.563.531 1.521.938.959.406 2.229.645Q8.583 11 10 11q1.417 0 2.688-.24 1.27-.239 2.229-.645.958-.407 1.521-.938Q17 8.646 17 8.042V10q0 1.271-2.01 2.135Q12.979 13 10 13Zm0 4q-2.917 0-4.958-.906Q3 15.188 3 13.896v-1.958q0 .604.573 1.156.573.552 1.542.979.968.427 2.239.677Q8.625 15 10 15t2.646-.25q1.271-.25 2.239-.677.969-.427 1.542-.979.573-.552.573-1.156v1.958q0 1.292-2.042 2.198Q12.917 17 10 17Z" style="fill:#000000"/></svg>)",
                    // TABLE
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="20" width="20"><path d="M3 17V3h14v14Zm1.5-9.562h11V4.5h-11Zm4.167 4.041h2.666V8.938H8.667Zm0 4.021h2.666v-2.521H8.667ZM4.5 11.479h2.667V8.938H4.5Zm8.333 0H15.5V8.938h-2.667ZM4.5 15.5h2.667v-2.521H4.5Zm8.333 0H15.5v-2.521h-2.667Z" style="fill:%s"/></svg>)",
                    // GROUP
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="20" width="20"><path d="M3.417 16.667q-.729 0-1.24-.511-.51-.51-.51-1.239V5.083q0-.729.51-1.239.511-.511 1.24-.511H8.25L10 5.083h6.583q.729 0 1.24.511.51.51.51 1.239v8.084q0 .729-.51 1.239-.511.511-1.24.511Zm0-11.584v9.834h13.166V6.833H9.271l-1.75-1.75H3.417Zm0 0v9.834Z" style="fill:%s"/></svg>)",
                    // QUERY_PANEL
                    R"(<svg xmlns="http://www.w3.org/2000/svg" height="20" width="20"><path d="M10 17v-1.771l4.417-4.417 1.771 1.771L11.771 17Zm-7-4.25v-1.5h6v1.5ZM16.771 12 15 10.229l.667-.667q.229-.229.531-.229.302 0 .531.229l.709.709q.229.229.229.531 0 .302-.229.531ZM3 9.625v-1.5h9v1.5ZM3 6.5V5h9v1.5Z" style="fill:#000000"/></svg>)"

};

wxString Bitmaps::SvgLogo =
    R"lit(<?xml version="1.0" encoding="UTF-8"?><svg version="1.1" viewBox="0 0 1024 1024" xmlns="http://www.w3.org/2000/svg" xmlns:bx="https://boxy-svg.com"><g><path d="m269.75 31.954h484.5c131.74 0 237.8 106.06 237.8 237.8v484.5c0 131.74-106.06 237.8-237.8 237.8h-484.5c-131.74 0-237.8-106.06-237.8-237.8v-484.5c0-131.74 106.06-237.8 237.8-237.8z" color="#000000" fill="#6fb231" stroke-width="49.908" style="-inkscape-stroke:none"/><path d="m269.75 7c-145.13 0-262.75 117.62-262.75 262.75v484.5c0 145.13 117.62 262.75 262.75 262.75h484.5c145.13 0 262.75-117.62 262.75-262.75v-484.5c0-145.13-117.62-262.75-262.75-262.75zm0 49.908h484.5c118.35 0 212.84 94.496 212.84 212.84v484.5c0 118.35-94.496 212.84-212.84 212.84h-484.5c-118.35 0-212.84-94.496-212.84-212.84v-484.5c0-118.35 94.496-212.84 212.84-212.84z" color="#000000" style="-inkscape-stroke:none"/><g transform="matrix(.9576 0 0 .78182 22.617 17.723)"><g stroke-linejoin="round"><path d="m364.94 424.27 56.121 167.52-98.518 272.95-145.54-0.93565z" color="#000000" stroke-width="46.782" style="-inkscape-stroke:none"/><path d="m360.27 401.35a23.393 23.393 0 0 0-16.838 13.721l-187.94 439.53a23.393 23.393 0 0 0 21.357 32.588l145.54 0.93555a23.393 23.393 0 0 0 22.152-15.449l98.518-272.95a23.393 23.393 0 0 0 0.17774-15.373l-56.121-167.52a23.393 23.393 0 0 0-26.85-15.486zm2.0137 88.623 34.014 101.52-90.141 249.74-93.812-0.60156z" color="#000000" style="-inkscape-stroke:none"/></g><g stroke-linejoin="round"><path d="m421.06 591.78 161.02-446.11 264.82 718.12-334.96-5e-3 -90.882-272.01" color="#000000" fill="#fff" stroke-width="46.782" style="-inkscape-stroke:none"/><path d="m587.65 122.96a23.393 23.393 0 0 0-27.576 14.771l-161.02 446.11 22.002 7.9414-22.186 7.4121 90.883 272.01a23.393 23.393 0 0 0 22.186 15.979l334.96 6e-3a23.393 23.393 0 0 0 21.945-31.485l-264.82-718.12a23.393 23.393 0 0 0-16.371-14.619zm-5.3398 90.957 231.03 626.49-284.56-6e-3 -82.967-248.32z" color="#000000" style="-inkscape-stroke:none"/></g><path d="m656.65 399.44-166.68 456.33 43.941 16.051 166.68-456.33z" color="#000000" style="-inkscape-stroke:none"/><path d="m617.22 627.54-43.893 16.186 84.141 228.17 43.893-16.186z" color="#000000" style="-inkscape-stroke:none"/></g></g><g stroke-linecap="square" stroke-linejoin="round"><g><path d="m192.11 772.18 139.37 0.7408 93.146 103.07-158.67 0.55047z" color="#000000" stroke-width="40" style="-inkscape-stroke:none"/><path d="m192.21 752.18a20.002 20.002 0 0 0-16.432 31.553l73.844 104.36a20.002 20.002 0 0 0 16.396 8.4473l158.67-0.55078a20.002 20.002 0 0 0 14.77-33.41l-93.146-103.07a20.002 20.002 0 0 0-14.73-6.5898zm38.693 40.207 91.646 0.48633 57.18 63.271-103.46 0.35938z" color="#000000" style="-inkscape-stroke:none"/></g><path d="m512.85 772.18-88.224 103.81 346.98-1.1435 62.005-102.67z" color="#000000" fill="#fff" stroke-width="40" style="-inkscape-stroke:none"/><path d="m512.85 752.18a20.002 20.002 0 0 0-15.24 7.0488l-88.223 103.81a20.002 20.002 0 0 0 15.305 32.951l346.98-1.1426a20.002 20.002 0 0 0 17.053-9.6602l62.006-102.67a20.002 20.002 0 0 0-17.119-30.34zm9.25 40 276.06 4e-3 -37.869 62.703-292.3 0.96289z" color="#000000" style="-inkscape-stroke:none"/></g></svg>)lit";

wxBitmap Bitmaps::GetBitmap(Bitmaps::ID id, const wxString& colour, const wxSize& size) {
  wxString my_bmp = wxString::Format(Bitmaps::SvgText[id], colour);
  return wxBitmapBundle::FromSVG(my_bmp, size).GetBitmap(size);
}

wxBitmap Bitmaps::GetLogo(const wxSize& size) {
  return wxBitmapBundle::FromSVG(Bitmaps::SvgLogo, size).GetBitmap(size);
}
