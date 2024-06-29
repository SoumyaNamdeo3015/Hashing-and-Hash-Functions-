#include "CubicProbing.h"

int CubicProbing :: GetHashCode(std::string id){

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


void CubicProbing :: MergeFunction(std::vector<int>&v, int start, int index, int end ){
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

void CubicProbing :: merge_sort(std::vector<int>&v, int start, int end ){

if(start<end){
    int s= start;
    int e = end;
    int mid = (s+e)/2;
    merge_sort(v,s,mid);
    merge_sort(v,mid+1,e);
    MergeFunction(v,s,mid,e);
}

}


int CubicProbing :: GetIndex(std::string id){


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
  



    //  int initial_hash_code =  GetHashCode(id);
    // if(bankStorage1d[initial_hash_code].id ==id){ 
    //     return initial_hash_code;
    // }

    // int i=1;
    // int copy =initial_hash_code;
    // while(bankStorage1d[copy].id!=id){

    //     copy = (initial_hash_code+f(i))%mod;
    //     if(copy==initial_hash_code){
    //         break;
    //     }

    //     if(bankStorage1d[copy].id == id){
    //         return copy;
    //     }
    //     i++;
    // }
    //     return -1;

}


int CubicProbing :: f(int i){
    return i*i*i;
}



CubicProbing :: CubicProbing(){

    mod = 100003; // mod =99991 
    DBsize =0;
    Account empty;
    empty.balance =-1;
    empty.id = "e";


    for(int i=0;i<mod;i++){
        bankStorage1d.push_back(empty);
    }
}

void CubicProbing::createAccount(std::string id, int count) {
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



std::vector<int> CubicProbing::getTopK(int k) {
    
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



int CubicProbing::getBalance(std::string id) {

    int index = GetIndex(id);
    if(index==-1){
        return -1;
    }

    return bankStorage1d[index].balance;

}

void CubicProbing::addTransaction(std::string id, int count){     
    int index = GetIndex(id);
    if(index==-1){
        // then create a new account;
        createAccount(id,count);
        return;

    }

   if(bankStorage1d[index].balance+count >=0){
    bankStorage1d[index].balance+=count; 
   }
   return;
}


bool CubicProbing::deleteAccount(std::string id) {
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

int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return DBsize;
}



int CubicProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE

    // this function will return the hashing index for the given id 
    int initial_hash_code =  GetHashCode(id);
    if(bankStorage1d[initial_hash_code].id =="e"){ 
        return initial_hash_code;
    }

    int i=1;
    int copy =initial_hash_code;
    while(bankStorage1d[copy].id!="e"){
        // std :: cout <<"#"; 
        copy = (initial_hash_code+f(i))%mod;
        i++;
    }
    
        // bankStorage1d.id and balance updation in create account 

        return copy;
}





bool CubicProbing::doesExist(std::string id){

    if(GetIndex(id)==-1){
        return false;
    }

    return true;
}



