#include "database.h"
#include "gtest/gtest.h"
#include "ogr_geometry.h"
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

TEST(TestGeneric, HaveGEOS) {
  ASSERT_TRUE(OGRGeometryFactory::haveGEOS());
}

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
/*
TEST_F(TestDatabase, ResultDouble) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestFloat32 FROM layer_at10 WHERE OBJECT_ID = 1")));
  double value = 0;
  ASSERT_TRUE(m_db->DataBaseGetNextResult(value));
  ASSERT_TRUE(DOUBLES_EQUAL(8.99, value, 0.01);
  ASSERT_TRUE(value == 8.99);
}

TEST_F(TestDatabase, ResultArrayDouble) {
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads/"), _T("testfields")) == true);
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestFloat32 FROM layer_at1 ORDER BY OBJECT_ID")));
  wxArrayDouble values;
  ASSERT_TRUE(m_db->DataBaseGetNextResult(values));
  ASSERT_TRUE(values.Item(0) == 8.99);
}

TEST_F(TestDatabase, ColResultsString) {
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads/"), _T("testfields")) == true);
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestText FROM layer_at1 ORDER BY OBJECT_ID")));
  wxArrayString myResults;
  ASSERT_TRUE(m_db->DataBaseGetResults(myResults));
  ASSERT_TRUE(myResults.GetCount() == 2);
  ASSERT_TRUE(myResults.Item(1) == _T("Ceci est un test pour un max de caracteres ke lonp"));
  ASSERT_TRUE(m_db->DataBaseGetResults(myResults) == false);
  ASSERT_TRUE(myResults.GetCount() == 0);
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestText FROM layer_at1 ORDER BY OBJECT_ID")));
  m_db->DataBaseClearResults();
}

TEST_F(TestDatabase, ColResultsLong) {
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads/"), _T("testfields")) == true);
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM layer_at1 ORDER BY OBJECT_ID")));
  wxArrayLong myResults;
  ASSERT_TRUE(m_db->DataBaseGetResults(myResults));
  ASSERT_TRUE(myResults.GetCount() == 2);
  ASSERT_TRUE(myResults.Item(1) == 4);
}

TEST_F(TestDatabase, ColResultsDouble) {
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads/"), _T("testfields")) == true);
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestFloat32 FROM layer_at1 ORDER BY OBJECT_ID")));
  wxArrayDouble myResults;
  ASSERT_TRUE(m_db->DataBaseGetResults(myResults));
  ASSERT_TRUE(myResults.GetCount() == 2);
  ASSERT_TRUE(myResults.Item(1) == 6.00);
}

TEST_F(TestDatabase, PathName) {
  ASSERT_TRUE(m_db->DataBaseGetName() == wxEmptyString);
  ASSERT_TRUE(m_db->DataBaseGetPath() == wxEmptyString);
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads/"), _T("testfields")) == true);
  ASSERT_TRUE(m_db->DataBaseGetName() == _T("testfields"));
  ASSERT_TRUE(m_db->DataBaseGetPath() == _T("/Users/Lucien/Downloads/"));
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads"), _T("testfieldssss")) == false);
  ASSERT_TRUE(m_db->DataBaseGetName() == wxEmptyString);
  ASSERT_TRUE(m_db->DataBaseGetPath() == wxEmptyString);
}

TEST_F(TestDatabase, QueriesNumber) {
  wxString myQueries = _T("SELECT * FROM COUCOU; INSERT INTO ..; SELECT ALL");
  ASSERT_TRUE(m_db->DataBaseQueriesNumber(myQueries) == 3);
  wxString myQueries2 = _T("SELECT * FROM COUCOU; INSERT INTO; SELECT ALL;");
  ASSERT_TRUE(m_db->DataBaseQueriesNumber(myQueries) == 3);
}

TEST_F(TestDatabase, Version) {
  ASSERT_TRUE(DataBase::DataBaseGetVersion() == _T("5.1.33"));
}

TEST_F(TestDatabase, CreateNewDatabase) {
  ASSERT_TRUE(m_db->DataBaseCreateNew(_T("/Users/Lucien/Downloads/"), _T("mytest1")) == false);
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads/"), _T("mytest1")));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SHOW TABLES FROM mytest1")));
}

TEST_F(TestDatabase, GetDataBaseSize) {
  wxString myFailMsg = _("Not available");
  wxString myDBSize = m_db->DataBaseGetSize(2, myFailMsg);
  ASSERT_TRUE(myDBSize == myFailMsg);
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads/"), _T("mytest1")));
  myDBSize = m_db->DataBaseGetSize(2, myFailMsg);
  wxLogDebug(myDBSize);
  ASSERT_TRUE(myDBSize != myFailMsg);

  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/DATA/SIG/COMBIOULA/CORRIGE/TOOLMAP/"), _T("combioula_correct")) ==
              true);
  myDBSize = m_db->DataBaseGetSize(2, myFailMsg);
  wxLogDebug(myDBSize);
  ASSERT_TRUE(myDBSize != myFailMsg);
}

TEST_F(TestDatabase, GetLastInsertID) {
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads/"), _T("testfields")) == true);
  long myIID = m_db->DataBaseGetLastInsertedID();
  ASSERT_TRUE(myIID == wxNOT_FOUND);
  ASSERT_TRUE(m_db->DataBaseQueryNoResults(_T("INSERT INTO dmn_layer_object (OBJECT_CD) VALUES (1)")));

  myIID = m_db->DataBaseGetLastInsertedID();
  ASSERT_TRUE(myIID != wxNOT_FOUND);
  wxLogDebug(_T("Last inserted ID = %d"), myIID);

  myIID = m_db->DataBaseGetLastInsertedID();
  ASSERT_TRUE(myIID != wxNOT_FOUND);
}

TEST_F(TestDatabase, GetRawRow) {
  ASSERT_TRUE(m_db->DataBaseOpen(_T("/Users/Lucien/Downloads/"), _T("testfields")) == true);
  ASSERT_TRUE(m_db->DataBaseQuery(
      _T("SELECT Envelope(OBJECT_GEOMETRY) FROM generic_lines WHERE OBJECT_ID = 1")));  // WHERE OBJECT_ID = 2")));
  MYSQL_ROW myRow;
  tmArrayULong myLength;
  ASSERT_TRUE(m_db->DataBaseGetNextRowResult(myRow, myLength));
  ASSERT_TRUE(myRow != NULL);
  ASSERT_TRUE(myLength.GetCount() > 0);
  ASSERT_TRUE(m_db->DataBaseGetNextRowResult(myRow, myLength) == false);
  ASSERT_TRUE(myRow == NULL);
  ASSERT_TRUE(myLength.GetCount() == 0);
}
*/