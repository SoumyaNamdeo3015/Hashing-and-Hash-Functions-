# Hashing-and-Hash-Functions

## Introduction 
This project involves managing a banking system using a hashmap to store bank account information. Each account is characterized by its IFSC code and account number. <br>
### Key aspects include :
&bull; Maintaining accurate storage and retrieval of millions of bank accounts. <br>
&bull;Experimenting with collision resolution strategies to handle hash function collisions. <br>

# Strategies to be Implemented: 
- ## Chaining <br>
- In this strategy, the goal is to manange collision by creating a vector at each has table index. Each vector handles all accounts that share the same hash code.<br>
- ## Linear Probing <br>
- Linear Probing will allow us to navigate hash table in a linear fashion to find the next available space when collision occurs.<br>
- ## Quadratic Probing <br>
- The quadratic probing strategy introduces a more sophisticated approach by using quadratic increments to
find the next available slot.This technique strikes a balance between proximity and distribution, providing
an alternative to linear probing.<br>
- ## Cubic Probing <br>
Taking the concept further, cubic probing employs cubic increments to search for open slots. This strategy
adds an extra layer of complexity to the probe sequence, aiming to distribute data evenly and mitigate
clustering issues. <br>
# Structure and Fucntions :

- In BaseClass.h there's an Account struct. <br>
- There are two vectors namely bankStorage1d (for probing strategies) and bankStorage2d for(chaining strategies). 

