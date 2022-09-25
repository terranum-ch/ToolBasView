#include "database.h"
#include "gtest/gtest.h"
#include "ogr_geometry.h"
#include "test_param.h"

class TestDatabase : public ::testing::Test {
 protected:
  static DataBase* m_db;

  static void SetUpTestSuite() {
    if (m_db == nullptr) {
      m_db = new DataBase();
    }
  }

  static void TearDownTestSuite() {
    wxDELETE(m_db);
  }

  virtual void SetUp() {
    // create the output directory
    wxFileName output_path(UNIT_TESTING_DATA_OUTPUT_PATH, wxEmptyString);
    if (!output_path.Exists()) {
      ASSERT_TRUE(output_path.Mkdir());
    }
  }
};

DataBase* TestDatabase::m_db = nullptr;

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
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
}

TEST_F(TestDatabase, DataBaseHasResults) {
  ASSERT_TRUE(m_db->DataBaseHasResults() == false);
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery("SELECT OBJECT_ID FROM generic_lines"));
  ASSERT_TRUE(m_db->DataBaseHasResults());
  m_db->DataBaseClearResults();
}

TEST_F(TestDatabase, DataBaseQueryNoResults) {
  ASSERT_FALSE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj_not_exist"));
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
  ASSERT_TRUE(myReturnedString == wxString("bord d'érosion", wxConvUTF8));  // oid = 17
  ASSERT_FALSE(m_db->DataBaseGetNextResult(myReturnedString));
  ASSERT_TRUE(myReturnedString == wxEmptyString);
  m_db->DataBaseClearResults();

  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM dmn_layer_object WHERE OBJECT_ID = 17777")));
  ASSERT_FALSE(m_db->DataBaseGetNextResult(myReturnedString));
  ASSERT_TRUE(myReturnedString == wxEmptyString);
  ASSERT_FALSE(m_db->DataBaseHasResults());
}

TEST_F(TestDatabase, ResultArrayString) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT * FROM dmn_layer_object WHERE OBJECT_ID = 17")));
  wxArrayString myResults;

  ASSERT_TRUE(m_db->DataBaseGetNextResult(myResults));
  ASSERT_TRUE(myResults.GetCount() == 13);  // 13 cols in dmn_layer_object
  ASSERT_TRUE(myResults.Item(4) == wxString("bord d'érosion", wxConvUTF8));
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
  ASSERT_TRUE(m_db->DataBaseGetResultSize(&myCols, nullptr));
  ASSERT_TRUE(myCols == 13);
  ASSERT_TRUE(m_db->DataBaseGetResultSize(nullptr, &myRows));
  ASSERT_TRUE(myRows == 1);
  myRows = 0;
  myCols = 0;
  ASSERT_TRUE(m_db->DataBaseGetResultSize(&myCols, &myRows));
  ASSERT_TRUE(myRows == 1 && myCols == 13);
  m_db->DataBaseClearResults();
}

TEST_F(TestDatabase, ResultLong) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));

  long myResult = 0;
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM dmn_layer_object WHERE OBJECT_ID = 17")));
  ASSERT_TRUE(m_db->DataBaseGetNextResult(myResult));
  ASSERT_TRUE(myResult == 17);
  m_db->DataBaseClearResults();
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
  while (true) {
    bool bReturn = m_db->DataBaseGetNextResult(myResults);
    if (i < 17) {
      ASSERT_TRUE(bReturn == true);
    } else
      ASSERT_TRUE(bReturn == false);
    i++;
    if (!bReturn) break;
  }

  m_db->DataBaseClearResults();
  ASSERT_TRUE(
      m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM dmn_layer_object WHERE OBJECT_ID <= 17 ORDER BY OBJECT_ID")));
  ASSERT_TRUE(m_db->DataBaseGetNextResult(myResults));
  ASSERT_TRUE(m_db->DataBaseGetResultSize(&myCols, &myRows));
  ASSERT_TRUE(myCols == 1 && myRows == 17);
  m_db->DataBaseClearResults();
}

TEST_F(TestDatabase, ResultDouble) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestFloat32 FROM layer_at10 WHERE OBJECT_ID = 369")));
  double value = 0;
  ASSERT_TRUE(m_db->DataBaseGetNextResult(value));
  EXPECT_NEAR(8.99, value, 0.01);
  ASSERT_TRUE(value == 8.99);
  m_db->DataBaseClearResults();
}

TEST_F(TestDatabase, ResultDoubleArray) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestFloat32 FROM layer_at10 ORDER BY OBJECT_ID")));
  wxArrayDouble values;
  ASSERT_TRUE(m_db->DataBaseGetNextResult(values));
  ASSERT_TRUE(values.Item(0) == 6.00);
  m_db->DataBaseClearResults();
}

TEST_F(TestDatabase, ResultsStringArray) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestText FROM layer_at10 ORDER BY OBJECT_ID")));
  wxArrayString myResults;
  ASSERT_TRUE(m_db->DataBaseGetResults(myResults));
  ASSERT_TRUE(myResults.GetCount() == 2);
  ASSERT_TRUE(myResults.Item(0) == _T("This is a test for the character length because it"));
  ASSERT_FALSE(m_db->DataBaseGetResults(myResults));
  ASSERT_TRUE(myResults.GetCount() == 0);
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestText FROM layer_at10 ORDER BY OBJECT_ID")));
  m_db->DataBaseClearResults();
}

TEST_F(TestDatabase, ResultsLongArray) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT OBJECT_ID FROM layer_at10 ORDER BY OBJECT_ID")));
  wxArrayLong myResults;
  ASSERT_TRUE(m_db->DataBaseGetResults(myResults));
  ASSERT_TRUE(myResults.GetCount() == 2);
  ASSERT_TRUE(myResults.Item(1) == 369);
}

TEST_F(TestDatabase, ResultsDoubleArray) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(_T("SELECT TestFloat32 FROM layer_at10 ORDER BY OBJECT_ID")));
  wxArrayDouble myResults;
  ASSERT_TRUE(m_db->DataBaseGetResults(myResults));
  ASSERT_TRUE(myResults.GetCount() == 2);
  ASSERT_TRUE(myResults.Item(0) == 6.00);
  m_db->DataBaseClearResults();
}

TEST_F(TestDatabase, PathName) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseGetName() == _T("test_prj"));
  ASSERT_TRUE(m_db->DataBaseGetPath() == UNIT_TESTING_DATA_PATH);
  ASSERT_FALSE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, _T("no_existing_db")));
  ASSERT_TRUE(m_db->DataBaseGetName() == wxEmptyString);
  ASSERT_TRUE(m_db->DataBaseGetPath() == wxEmptyString);
}

TEST_F(TestDatabase, NumberQueries) {
  wxString myQueries = _T("SELECT * FROM COUCOU; INSERT INTO ..; SELECT ALL");
  ASSERT_EQ(m_db->DataBaseQueriesNumber(myQueries), 3);
}

TEST_F(TestDatabase, GetRawRow) {
  ASSERT_TRUE(m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "test_prj"));
  ASSERT_TRUE(m_db->DataBaseQuery(
      _T("SELECT Envelope(OBJECT_GEOMETRY) FROM generic_lines WHERE OBJECT_ID = 1")));  // WHERE OBJECT_ID = 2")));
  MYSQL_ROW myRow;
  tmArrayULong myLength;
  ASSERT_TRUE(m_db->DataBaseGetNextRowResult(myRow, myLength));
  ASSERT_TRUE(myRow != NULL);
  ASSERT_TRUE(myLength.GetCount() > 0);
  ASSERT_FALSE(m_db->DataBaseGetNextRowResult(myRow, myLength));
  ASSERT_TRUE(myRow == NULL);
  ASSERT_TRUE(myLength.GetCount() == 0);
  m_db->DataBaseClearResults();
}

TEST_F(TestDatabase, CreateNewDatabase) {
  // remove database if existing
  wxFileName my_dirname(UNIT_TESTING_DATA_PATH, "new_db");
  if (my_dirname.Exists()) {
    m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, "new_db");
    m_db->DataBaseDelete();
    wxLogMessage("Removing: %s", my_dirname.GetFullPath());
  }
  ASSERT_FALSE(my_dirname.Exists());
  ASSERT_TRUE(m_db->DataBaseCreateNew(UNIT_TESTING_DATA_PATH, "new_db"));
}

TEST_F(TestDatabase, GetLastInsertID) {
  wxFileName db_path(UNIT_TESTING_DATA_PATH, "new_insert_id");
  if (db_path.Exists()) {
    m_db->DataBaseOpen(UNIT_TESTING_DATA_PATH, db_path.GetName());
    m_db->DataBaseDelete();
  }
  ASSERT_FALSE(db_path.Exists());

  ASSERT_TRUE(m_db->DataBaseCreateNew(UNIT_TESTING_DATA_PATH, db_path.GetName()));
  ASSERT_TRUE(m_db->DataBaseQueryNoResults(
      "CREATE TABLE Persons (PersonID int NOT NULL AUTO_INCREMENT, LastName varchar(255), PRIMARY KEY (PersonID));"));
  long myIID = m_db->DataBaseGetLastInsertedID();
  ASSERT_TRUE(myIID == wxNOT_FOUND);
  ASSERT_TRUE(m_db->DataBaseQueryNoResults("INSERT INTO Persons (LastName) VALUES ('Mr. SMITH');"));
  myIID = m_db->DataBaseGetLastInsertedID();
  ASSERT_TRUE(myIID != wxNOT_FOUND);
  wxLogMessage(_T("Last inserted ID = %ld"), myIID);
  myIID = m_db->DataBaseGetLastInsertedID();
  ASSERT_TRUE(myIID != wxNOT_FOUND);
}
