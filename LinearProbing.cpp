#include "LinearProbing.h"
// comment out printDatabase
// change the value of mod that is the size of 



void LinearProbing :: MergeFunction(std::vector<int>&v, int start, int index, int end ){
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

void LinearProbing :: merge_sort(std::vector<int>&v, int start, int end ){

if(start<end){
    int s= start;
    int e = end;
    int mid = (s+e)/2;
    merge_sort(v,s,mid);
    merge_sort(v,mid+1,e);
    MergeFunction(v,s,mid,e);
}

}

int LinearProbing :: GetHashCode(std::string id){
    int hash = 0;
    int h =0;
    for(int i=0;i<5;i++){
        h += h*i + id[i];
    }
    for(int i=16;i<id.size();i+=1){
        hash += hash*2+ id[i];
    }
    return (hash*h)%mod;
}


int LinearProbing :: GetIndex(std::string id){



    int intital_hash_code = GetHashCode(id);
 if(bankStorage1d[intital_hash_code].id == id){
    return intital_hash_code;
 }


 int index = 0;
 while(bankStorage1d[(intital_hash_code+index)%mod].id!=id && index<mod){

    index++;
 
 }

if(index==mod){
    return -1;
}

return (intital_hash_code+ index)%mod;
  
}



LinearProbing :: LinearProbing(){
    
    //constructor : intitalizing 100000 size array with intital balance = 0 and id = "e";
    mod = 100003; // mod =99991 
     DBsize =0;

    Account empty;
    
    empty.balance =-1;
    empty.id = "e";
  
    for(int i=0;i<mod;i++){
  

        bankStorage1d.push_back(empty);
    }
    //  std:: cout << "outside constructor " << std:: endl;
}

int LinearProbing :: f(int i){
    return i;
}



void LinearProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if(DBsize == bankStorage1d.size()){
        // cannot insert hash table is full
        // std::cout << "hash table is full" << std::endl;
        return;
    }

    int hash_index = hash(id);
    bankStorage1d[hash_index].id = id;
    bankStorage1d[hash_index].balance = count;
    DBsize++;

    return;
}




std::vector<int> LinearProbing::getTopK(int k) {


    std::vector<int>v;  
    std::vector<int>t;  
 
    for(int i =0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id!="e"){
            v.push_back(bankStorage1d[i].balance);
        }
    }     
    int start=0;
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



int LinearProbing::getBalance(std::string id) {

    int index = GetIndex(id);
    if(index==-1){
        return -1;
    }

    return bankStorage1d[index].balance;

}

void LinearProbing::addTransaction(std::string id, int count){     
    int index = GetIndex(id);
    if(index==-1){
        // then create a new account;

        // count <0 case ? 
        createAccount(id,count);
    

        return;

    }

   if(bankStorage1d[index].balance+count >=0){
    bankStorage1d[index].balance+=count; 
   }
   return;
}


bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(DBsize==0){
        return 0;
    }

    int index = GetIndex(id);
    if(index>=0){
        bankStorage1d[index].id = "e";
        bankStorage1d[index].balance = -1;
        DBsize--;
        return true;
    }
    

    return false; // Placeholder return value
}

int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return DBsize;
}



int LinearProbing::hash(std::string id) {

    // this function will return the hashing index for the given id whever inserting
    int initial_hash_code =  GetHashCode(id);
    if(bankStorage1d[initial_hash_code].id =="e"){ 
        return initial_hash_code;
    }

    int i=1;
    int copy =initial_hash_code;
    while(bankStorage1d[copy].id!="e"){
        copy = (initial_hash_code+f(i))%mod;
        i++;
    }
        return copy;
}




bool LinearProbing::doesExist(std::string id){

    if(GetIndex(id)==-1){
        return false;
    }

    return true;

}



void LinearProbing :: printDatabase(){

     std ::  cout << std:: endl;
    for(int i =0;i<bankStorage1d.size();i++){
        std::cout  << i << " [ " << bankStorage1d[i].id << "," << bankStorage1d[i].balance<< "]" <<std::endl;
    }
    std ::  cout << std:: endl;
}



// void print(std::vector<int>v){
//     for(int i =0;i<v.size();i++){
//         std :: cout << v[i] << " ";
//     }std::cout << std::endl;
// }



// int main(){

//     LinearProbing b;
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
// }

