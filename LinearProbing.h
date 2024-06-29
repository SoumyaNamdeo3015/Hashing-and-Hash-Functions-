#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass {
public:
    LinearProbing();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
     void printDatabase();
     
    
private:
    // Other data members and functions specific to Linear Probing
    int DBsize;
    int mod;
    int GetHashCode(std::string id);
    int GetIndex(std::string id);
    int f(int i);
    void MergeFunction(std::vector<int>&v,int start, int mid, int end );
    void merge_sort(std::vector<int>&v, int start, int end);
     
    

    
};

#endif // LINEARPROBING_H
