#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    Chaining();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    void printDatabase(void);
    
private:
    
    // Other data members and functions specific to Chaining
    void InsertSorted(int balance, std::vector<int>&v);
    int DBsize;
    void MergeFunction(std::vector<int>&v,int start, int mid, int end );
    void merge_sort(std::vector<int>&v, int start, int end);
        
};

#endif // CHAINING_H
