#include "database.h"
#include "gtest/gtest.h"
#include "test_param.h"

class TestDatabase : public ::testing::Test {
 protected:
  DataBase* m_db = nullptr;

  virtual void SetUp() {
    m_db = new DataBase();
  }
  virtual void TearDown() {
    wxDELETE(m_db);
  }
};

TEST_F(TestDatabase, Empty) {
  ASSERT_TRUE(true);  // testing unit test
  ASSERT_TRUE(m_db != nullptr);
}

TEST_F(TestDatabase, DataBaseOpen) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_FALSE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj_not_exist"));
}

TEST_F(TestDatabase, DataBaseHasResults) {
  ASSERT_TRUE(m_db->DataBaseHasResults() == false);
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery("SELECT OBJECT_ID FROM generic_lines"));
  ASSERT_TRUE(m_db->DataBaseHasResults());
}

TEST_F(TestDatabase, DataBaseQueryNoResults) {
  ASSERT_FALSE(m_db->DataBaseQueryNoResults("SELECT OBJECT_ID FROM generic_lines"));
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQueryNoResults(_T("SELECT OBJECT_ID FROM generic_lines")));
  ASSERT_FALSE(m_db->DataBaseQueryNoResults(_T("SELECT COUNT(*) FROM generic_linesss")));
}

TEST_F(TestDatabase, ResultString) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  wxString myReturnedString = wxEmptyString;
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT OBJECT_DESC_0 FROM dmn_layer_object WHERE OBJECT_ID = 17")));
  ASSERT_TRUE(m_db->DataBaseGetNextResult(myReturnedString));
  ASSERT_TRUE(myReturnedString == _T("bord d'érosion"));  // oid = 17
  ASSERT_FALSE(m_db->DataBaseGetNextResult(myReturnedString));
  ASSERT_TRUE(myReturnedString == wxEmptyString);
  m_db->DataBaseClearResults();

  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM dmn_layer_object WHERE OBJECT_ID = 17777")));
  ASSERT_FALSE(m_db->DataBaseGetNextResult(myReturnedString));
  ASSERT_TRUE(myReturnedString == wxEmptyString);
}

TEST_F(TestDatabase, ResultArrayString) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT * FROM dmn_layer_object WHERE OBJECT_ID = 17")));
  wxArrayString myResults;

  ASSERT_TRUE(m_db->DataBaseGetNextResult(myResults));
  ASSERT_TRUE(myResults.GetCount() == 13);  // 13 cols in dmn_layer_object
  ASSERT_TRUE(myResults.Item(4) == _T("bord d'érosion"));
  m_db->DataBaseClearResults();
  // limit tests

  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM dmn_layer_object WHERE OBJECT_ID = 17")));
  ASSERT_TRUE(m_db->DataBaseGetNextResult(myResults));
  ASSERT_TRUE(myResults.GetCount() == 1);
  m_db->DataBaseClearResults();

  ASSERT_FALSE(m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM dmn_layer_object WHERE OBJCT_ID = 17777")));
  ASSERT_FALSE(m_db->DataBaseGetNextResult(myResults));
  ASSERT_TRUE(myResults.GetCount() == 0);
}

TEST_F(TestDatabase, CountResults) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  unsigned int myCols = 0;
  long myRows = 0;
  ASSERT_FALSE(m_db->DataBaseGetResultSize(&myCols, &myRows));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT * FROM dmn_layer_object WHERE OBJECT_ID = 17")));
  ASSERT_TRUE(m_db->DataBaseGetResultSize(&myCols, NULL));
  ASSERT_TRUE(myCols == 13);
  ASSERT_TRUE(m_db->DataBaseGetResultSize(NULL, &myRows));
  ASSERT_TRUE(myRows == 1);
  myRows = 0;
  myCols = 0;
  ASSERT_TRUE(m_db->DataBaseGetResultSize(&myCols, &myRows));
  ASSERT_TRUE(myRows == 1 && myCols == 13);
}

TEST_F(TestDatabase, ResultLong) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));

  long myResult = 0;
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM dmn_layer_object WHERE OBJECT_ID = 17")));
  ASSERT_TRUE(m_db->DataBaseGetNextResult(myResult));
  ASSERT_TRUE(myResult == 17);
}

TEST_F(TestDatabase, ResultArrayLong) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT OBJECT_ID, OBJECT_CD FROM dmn_layer_object WHERE OBJECT_ID <= 17")));

  unsigned int myCols = 0;
  long myRows = 0;

  ASSERT_TRUE(m_db->DataBaseGetResultSize(&myCols, &myRows));
  ASSERT_TRUE(myCols == 2 && myRows == 17);

  wxArrayLong myResults;
  int i = 0;
  bool bReturn = false;
  while (1) {
    bReturn = m_db->DataBaseGetNextResult(myResults);
    if (i < 17) {
      ASSERT_TRUE(bReturn == true);
    } else
      ASSERT_TRUE(bReturn == false);
    i++;
    if (bReturn == false) break;
  }

  m_db->DataBaseClearResults();
  ASSERT_TRUE(
      m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM dmn_layer_object WHERE OBJECT_ID <= 17 ORDER BY OBJECT_ID")));
  ASSERT_TRUE(m_db->DataBaseGetNextResult(myResults));
  ASSERT_TRUE(m_db->DataBaseGetResultSize(&myCols, &myRows));
  ASSERT_TRUE(myCols == 1 && myRows == 17);
}