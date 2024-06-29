// desgin optimal hash function 
// mod ? 

// #include "BaseClass.h"
#include "Chaining.h"



void Chaining :: MergeFunction(std::vector<int>&v, int start, int index, int end ){
// 10 8 6
// 11 9 1   --> 11  10  9 8  6 1  
//0-2 sorted, 3-5 sorted decreasing order 
// std::cout <<"merging" << std::endl;
    std::vector<int>ans;
    int i=start;
    int j = index+1;

    while(i<=index && j<=end){

        if(v[i]>=v[j]){
            ans.push_back(v[i]);
            i++;
        }

        else{
            ans.push_back(v[j]);
            j++;
        }
    }

    while(i<=index){
        ans.push_back(v[i]);i++;
    }
    while (j<=end){
        ans.push_back(v[j]);j++;
    }
    //now ans is sorted // copy back in v
    for(int i=start;i<=end;i++){
        v[i] = ans[i-start];
    }
}

void Chaining :: merge_sort(std::vector<int>&v, int start, int end ){

if(start<end){
    int s= start;
    int e = end;
    int mid = (s+e)/2;
    merge_sort(v,s,mid);
    merge_sort(v,mid+1,e);
    MergeFunction(v,s,mid,e);
}
}



Chaining :: Chaining(){
       for(int i=0;i<100000;i++){
        std::vector<Account> VecAcc;
        bankStorage2d.push_back(VecAcc);
        DBsize =0;
    }
}



void Chaining :: InsertSorted(int balance, std::vector<int>&v){
    if(v.size()==0){
        v.push_back(balance);
    }
    else{
        int i=0;
        while(v[i]>balance && i<v.size()){
            i++;
        }
        v.insert(v.begin()+i,balance);
    }
}



void Chaining::createAccount(std::string id, int count){

        Account newAccount;
        newAccount.id =id;
        newAccount.balance = count;
        int hash_index= hash(id);
        if(bankStorage2d[hash_index].empty()){
            std::vector<Account> vec;
            vec.push_back(newAccount);
            DBsize++;
            bankStorage2d[hash_index] = vec;
            return;
        }
        DBsize++;
        bankStorage2d[hash_index].push_back(newAccount);
        }


std::vector<int> Chaining::getTopK(int k) {
    
    std:: vector<int>v;
    std:: vector<int>t;   

    for(int i =0;i<bankStorage2d.size();i++){

        for(int j =0;j<bankStorage2d[i].size();j++){
            v.push_back(bankStorage2d[i][j].balance);
        }
    }

    int start =0;
    int end = v.size()-1;
    merge_sort(v,start,end);
    
    if(k>DBsize){
    for(int i=0;i<DBsize;i++){
        t.push_back(v[i]);
    }
    }



    else{
        for(int i=0;i<k;i++){
        t.push_back(v[i]);
    }
    }
    return t;
}



int Chaining::getBalance(std::string id) { 

    int hash_index= hash(id);
    int balance =  -1;
    for(int i=0;i<bankStorage2d[hash_index].size();i++){
        if(bankStorage2d[hash_index][i].id==id){
           balance =  bankStorage2d[hash_index][i].balance;
           break;
        }
    }
    return balance;
}


void Chaining::addTransaction(std::string id, int count){

    int hash_code = hash(id);
    for(int i=0;i<bankStorage2d[hash_code].size();i++){
        if(bankStorage2d[hash_code][i].id == id){
            bankStorage2d[hash_code][i].balance  += count;          
            return;
        }
    }
    createAccount(id,count);
}



bool Chaining::doesExist(std::string id) {
    int hash_index= hash(id);
    std::vector<Account>v;
    v = bankStorage2d[hash_index];
    for(int i=0;i<v.size();i++){
        if(v[i].id == id){
            return true;
        }
    }
   return false;
}

bool Chaining::deleteAccount(std::string id){
    if(!doesExist(id)){
    return false;
    }

    int hash_index = hash(id);
    int index = -1;
    for(int i=0;i<bankStorage2d[hash_index].size();i++){
        if(bankStorage2d[hash_index][i].id == id){
            index = i;
            break;
        }
    }
    bankStorage2d[hash_index].erase(bankStorage2d[hash_index].begin()+index);
    DBsize--;
    return true;
}



int Chaining::databaseSize() {
    return DBsize;
}



int Chaining::hash(std::string id){

    int hash_code=0;
    int mod = 100003; // for now 
    for(int i=0;i<id.size();i++){
        hash_code +=id[i];
    }
    return hash_code%mod;
}


void Chaining :: printDatabase(void){
    for(int i =0;i<bankStorage2d.size();i++){
        if(!bankStorage2d[i].empty()){
        for(int j=0;j<bankStorage2d[i].size();j++){
        
            std::cout << " [ hash code : " <<  hash(bankStorage2d[i][j].id) << ", id : " << bankStorage2d[i][j].id << ", balance : "<< bankStorage2d[i][j].balance << " ] -> "; 

        }
        std::cout << std::endl;
        }
}
}



void print(std::vector<int>v){
    for(int i =0;i<v.size();i++){
        std :: cout << v[i] << " ";
    }std::cout << std::endl;
}



// int main(){
//     Chaining b;
//     b.createAccount("CDAD7786825_7990768648", 648);
//     b.createAccount("DCDA7547234_9919615552", 552);
//     b.createAccount("AACB1850545_7974534788", 788);
//     std::cout << b.databaseSize() << std::endl;
//     b.createAccount("CDBD5250777_1124276711", 711);
//     b.createAccount("ABCB8377155_0656808575", 575);
//     print(b.getTopK(1));
//     b.createAccount("CDDC3792028_3313680038", 38);
//     b.createAccount("CBBA9574444_7470182321", 321);
//     b.createAccount("DBCC4334636_8057544188", 188);
//     print(b.getTopK(3));
//     b.createAccount("BABD5741078_5109455304", 304);
//     b.createAccount("BCBA7529510_0817878868", 868);
//     std::cout << b.databaseSize() << std::endl;
//     print(b.getTopK(1));
//     b.addTransaction("BCBA7529510_0817878868", -860);
//     std:: cout << b.getBalance("BCBA7529510_0817878868") << std::endl;
//     print(b.getTopK(1));
//     b.addTransaction("DCDA7547234_9919615552", 592);
//     print(b.getTopK(5));
 
//     std::cout << b.deleteAccount("DCDA7547234_9919615552") << std::endl;
//     // b.printDatabase();
//     print(b.getTopK(4));
//     std::cout << b.databaseSize() << std::endl;
//     b.printDatabase();
// }