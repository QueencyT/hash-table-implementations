#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>

#include "../../includes/hash/double_hash.h"
#include "../../includes/hash/chained_hash.h"
#include "../../includes/hash/record.h"

using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_insert(bool debug){
  bool flag1 = true; 
  DoubleHash<record> mHash; 
  record mRecords[] = {record(120, 13.5), record(121, 14.7), record(42, 13.8), record(190, 13.8), record(308, 13.8), record(422, 13.8)}; 
  int size = 6; 
  for(int i = 0; i < size; i++){
    mHash.insert(mRecords[i]); 
  }

  if(debug){
    record insertRec(190, 15.89); 
    cout<<"INSERTING EXISTING RECORD - CASE - DOUBLE HASH"<<endl; 
    cout<<"current structure: "<<endl; 
    cout<<mHash<<endl; 

    flag1 = !mHash.insert(insertRec); 
    cout<<"inserting: "<<insertRec<<endl; 
    cout<<"after insertion: "<<endl; 
    cout<<mHash<<endl; 
  }
  return flag1; 
}

bool test_find_index(bool debug){
  bool flag1 = true, flag2 = true, flag3 = true; 
  DoubleHash<record> mHash; 
  record mRecords[] = {record(120, 13.5), record(121, 14.7), record(42, 13.8), record(190, 13.8), record(308, 13.8), record(422, 13.8)}; 
  int size = 6; 
  for(int i = 0; i < size; i++){
    mHash.insert(mRecords[i]); 
  }

  if(debug){
    record foundRecord; 
    cout<<"FIND INDEX - DOUBLE HASH - FIND MIDDLE - TEST: "<<endl; 
    cout<<"current structure: "<<endl; 
    cout<<mHash<<endl; 

    cout<<boolalpha<<"is 42 there?: "<<mHash.find(42, foundRecord)<<endl; 
    flag1 = mHash.find(42, foundRecord); 
  }

  if(debug){
    record temp; 
    record foundRecord; 
    cout<<"FIND INDEX - DOUBLE HASH - FIND EVERYTHING - TEST: "<<endl; 
    cout<<"current structure: "<<endl; 
    cout<<mHash<<endl; 

    for(int i = 0; i < size; i++){
      cout<<"found?: "<<mRecords[i]<<boolalpha<<mHash.find(mRecords[i]._key, temp)<<endl; 
      if(!mHash.find(mRecords[i]._key, temp)){
        cout<<"failed to find: "<<mRecords[i]<<endl; 
        flag2 = false; 
        break; 
      }
    }
  }

  if(debug){
    record nonRecord(5362, 20.5), temp; 
    cout<<"FIND INDEX - DOUBLE HASH - DOES NOT EXIST - TEST"<<endl; 
    cout<<"current structure: "<<endl; 
    cout<<mHash<<endl; 

    cout<<"finding: "<<nonRecord<<endl; 
    flag3 = !mHash.find(nonRecord._key, temp); 
    cout<<"found?: "<<boolalpha<<flag3<<endl; 
  }

  return flag1 && flag2 && flag3; 
}

bool test_remove(bool debug){
  bool flag1 = true, flag2 = true, flag3 = true;
  DoubleHash<record> mHash; 
  record mRecords[] = {record(120, 13.5), record(121, 14.7), record(42, 13.8), record(38, 13.9), record(159, 13.8)}; 
  int size = 5; 

  for(int i = 0; i < size; i++){
    mHash.insert(mRecords[i]); 
  }

  if(debug){
    flag1 = true; 
    cout<<"TEST - REMOVE UNTIL EMPTY- DOUBLE HASH: "<<endl; 
    cout<<"before removal: "<<endl; 
    cout<<mHash<<endl;

    for(int i = 0; mHash.size() != 0; i++){
      cout<<"removing: "<<mRecords[i]<<endl; 
      if(!mHash.remove(mRecords[i]._key)){
        cout<<"failed to remove: "<<mRecords[i]<<endl; 
        flag1 = false; 
        break;  
      }
      cout<<"after removal: "<<endl; 
      cout<<mHash<<endl; 
    }
  }

  for(int i = 0; i < size; i++){
    mHash.insert(mRecords[i]); 
  }

  if(debug){
    flag2 = true; 
    cout<<"TEST - REMOVING END - DOUBLE HASH: "<<endl; 
    cout<<"before removal: "<<endl; 
    cout<<mHash<<endl;

    cout<<"removing: "<<mRecords[size - 1]<<endl; 
    flag2 = mHash.remove(mRecords[size-1]._key);
    cout<<mHash<<endl; 

    cout<<"present?: "<<mRecords[size - 1]<<boolalpha<<mHash.is_present(mRecords[size-1]._key)<<endl;
  }

  
  if(debug){
    flag3 = true; 
    cout<<"TEST - REMOVING MIDDLE - DOUBLE HASH: "<<endl; 
    cout<<"before removal: "<<endl; 
    cout<<mHash<<endl;

    cout<<"removing: "<<mRecords[size/2]<<endl; 
    flag3 = mHash.remove(mRecords[size/2]._key);
    cout<<mHash<<endl; 

    cout<<"present?: "<<mRecords[size/2]<<boolalpha<<mHash.is_present(mRecords[size/2]._key)<<endl; 
  }

  return flag1 && flag2 && flag3; 
}

bool test_find_chained_hash(bool debug){
  bool flag1 = true, flag2 = true, flag3 = true;
  ChainedHash<record> mHash; 
  record mRecords[] = {record(120, 13.5), record(121, 14.7), record(42, 13.8), record(38, 13.9), record(159, 13.8)}; 
  record temp; 
  int size = 5; 
  
  for(int i = 0; i < size; i++){
    mHash.insert(mRecords[i]); 
  }

  if(debug){
    cout<<"TEST - FIND EVERYTHING - CHAINED HASH"<<endl; 
    cout<<"current structure: "<<endl; 
    cout<<mHash<<endl; 
    cout<<"total records: "<<mHash.size()<<endl; 

    for(int i = 0; i < size; i++){
      if(!mHash.find(mRecords[i]._key, temp)){
        cout<<"failed to find: "<<mRecords[i]<<endl; 
        flag1 = false; 
        break; 
      }
    }
  }

  return flag1; 
}

bool test_remove_chained_hash(bool debug){
  bool flag1 = true, flag2 = true, flag3 = true;
  ChainedHash<record> mHash; 
  record mRecords[] = {record(120, 13.5), record(121, 14.7), record(42, 13.8), record(38, 13.9), record(159, 13.8)}; 
  record temp; 
  int size = 5; 
 
  
  for(int i = 0; i < size; i++){
    mHash.insert(mRecords[i]); 
  } 

  if(debug){
    cout<<"REMOVE - CHAINED HASH - TILL EMPTY\n"; 
    cout<<"current structure\n";
    cout<<mHash<<endl; 
    for(int i = 0; mHash.size() != 0; i++){
      cout<<"removing: "<<mRecords[i]<<endl;
      mHash.remove(mRecords[i]._key); 
      cout<<"size: "<<mHash.size()<<endl; 
    }
  }
  cout<<"after removal"<<endl; 
  cout<<mHash<<endl; 

  return true; 
}

bool test_insert_chained_hash(bool debug){
  bool flag1 = true, flag2 = true, flag3 = true;
  ChainedHash<record> mHash; 
  record mRecords[] = {record(120, 13.5), record(121, 14.7), record(42, 13.8), record(38, 13.9), record(159, 13.8)}; 
  record temp; 
  int size = 5; 
 
  for(int i = 0; i < size; i++){
    mHash.insert(mRecords[i]); 
  }  

  if(debug){
    record insertRec(38, 14.5); 
    cout<<"TEST - INSERT ALREADY EXIST - CHAINED HASH"<<endl; 
    cout<<"current structure: "<<endl;
    cout<<mHash<<endl; 

    cout<<"inserting: "<<insertRec<<endl; 
    mHash.insert(insertRec); 
    cout<<"after insertion: "<<endl; 
    cout<<mHash<<endl; 
    cout<<"size: "<<mHash.size()<<endl; 
  }
  return true; 
}

TEST(TEST_DOUBLE_HASH, testInsert){
  EXPECT_EQ(1, test_insert(false)); 
}

TEST(TEST_DOUBLE_HASH, testFindIndex){
  EXPECT_EQ(1, test_find_index(false)); 
}

TEST(TEST_DOUBLE_HASH, testRemove){
  EXPECT_EQ(1, test_remove(false)); 
}

TEST(TEST_CHAINED_HASH, testFind){
  EXPECT_EQ(1, test_find_chained_hash(false)); 
}

TEST(TEST_CHAINED_HASH, testRemoveChain){
  EXPECT_EQ(1, test_remove_chained_hash(true)); 
}

TEST(TEST_CHAINED_HASH, testInsertChain){
  EXPECT_EQ(1, test_insert_chained_hash(true)); 
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

