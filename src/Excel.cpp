
#include "Excel.h"

/// Constructor
Excel::Excel()
{
  file = 0;
  strcpy(error, "");
}

/// Destructor
Excel::~Excel()
{
  Close();
}

/// open a file. Returns true if succesfully opened.
/// else returns false and you can read the status via LastError();
bool Excel::Open(const char* filename)
{
  Close();

  file = fopen (filename,"wb");  // important: open binary
  if (file == 0)
  {
    sprintf(error, "Could not open file \"%.255s\"", filename);
    return false;
  }

  return true;
}

/// Close an opened excel file
void Excel::Close()
{
  if (file != 0)
  {
    fclose(file);
    file = 0;
  }
}

// Returns true if there is an excel file open
bool Excel::IsOpen()
{
  return (file != 0);
}

/// write the start bytes to the excel file
/// execute this function once before you start writing to a file
void Excel::Begin()
{
  if (!IsOpen())
  {
    strcpy(error, "Cannot begin file. No file open.");
    return;
  }

  putcc(file, 0x0809);
  putcc(file, 0x0008);
  putcc(file, 0x0000);
  putcc(file, 0x0010);
  putcc(file, 0x0000);
  putcc(file, 0x0000);
}

/// write the end bytes to the excel file
/// execute this function once after you are finished writing to a file
void Excel::End()
{
  if (!IsOpen())
  {
    strcpy(error, "Cannot end file. No file open.");
    return;
  }

  putcc(file, 0x000A);
  putcc(file, 0x0000);
}

/// write a string to the file
void Excel::Write(const int row, const int col, const char* value)
{
  if (value == 0)
  {
    strcpy(error, "Cannot write to file. No value provided.");
    return;
  }

  if (!IsOpen())
  {
    strcpy(error, "Cannot write to file. No file open.");
    return;
  }

  putcc(file, 0x0204);
  int len = 8 + strlen(value);
  putcc(file, len);
  putcc(file, row);
  putcc(file, col);
  putcc(file, 0x0000);
  putcc(file, strlen(value));
  fwrite(value, 1, strlen(value), file);
}

/// write a double to the file
void Excel::Write(const int row, const int col, const double value)
{
  if (value == 0)
  {
    strcpy(error, "Cannot write to file. No value provided.");
    return;
  }

  if (!IsOpen())
  {
    strcpy(error, "Cannot write to file. No file open.");
    return;
  }

  putcc(file, 0x0203);
  int len = 6 + 8;  // a double is 8 bytes in size
  putcc(file, len);
  putcc(file, row);
  putcc(file, col);
  putcc(file, 0x0000);
  fwrite(&value, 8, 1, file);
}

/// Returns the last error
const char* Excel::LastError() const
{
  return error;
}

/// Write given integer to the file stream as two bytes (16 bits)
void Excel::putcc(FILE* file, const int value)
{
  putc(value % 256, file);
  putc(value / 256, file);
}

