#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>

#include "../../includes/hash/double_hash.h"
#include "../../includes/hash/record.h"

using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_find_index(bool debug){
  DoubleHash<record> mHash; 
  record mRecords[] = {record(120, 13.5), record(121, 14.7), record(42, 13.8)}; 
  int size = 3; 
  for(int i = 0; i < size; i++){
    mHash.insert(mRecords[i]); 
  }

  if(debug){
    record foundRecord; 
    cout<<"FIND INDEX - DOUBLE HASH - TEST: "<<endl; 
    cout<<"current structure: "<<endl; 
    cout<<mHash<<endl; 

    cout<<boolalpha<<"is 42 there?: "<<mHash.find(42, foundRecord)<<endl; 
  }
}

TEST(TEST_DOUBLE_HASH, testFindIndex){
  EXPECT_EQ(1, test_find_index(true)); 
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

