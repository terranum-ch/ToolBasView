#include "database.h"
#include "gtest/gtest.h"

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
