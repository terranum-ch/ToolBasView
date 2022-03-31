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