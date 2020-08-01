# LRU-Scheme-In-Set-Assosciative-Caches

This is an Architecture Project on Set Assosciative Caches.
Set Asoosciative Caches use many schemes to reduce the number of misses from the processor. One of the most popular scheme is Least Recently Used or LRU scheme.

This project is a simulation of that scheme and helps is demonstrating how effective it is using the parameter hit/miss ratio. This project is build in C++.

### Implementation
To generate the main memory(hard disk) I am creating a file MainMemory.txt. This file will serve as main memory. LRU scheme is implemented in LRUScheme.cpp .

### Testing
To run the file execute the following commands on your terminal after cloning the repo.

$ g++ generateMainMemory.cpp

$ ./a.out

$ g++ LRUScheme.cpp

$ ./a.out

I have provided some sample trace files that acts as the lookups for some memory address.
