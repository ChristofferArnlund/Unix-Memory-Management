# Unix-Memory-Management

Code Handles memory allocation. We are given a memory allocation request and then
have to choose were in the memory we should allocate.
Two different algorithms are studied and implemented – Best Fit and Worst Fit.
The Best Fit algorithm tries to make a clever choice in where to allocate
memory. The algorithm is going through the memory to see which space that is big enough to
fit the new allocation and then choose the smallest of possible place were it fits. The pros with
Best fit is that you get the smallest possible remaining unallocated spaces in the memory in
the end, but it may leave a lot of small unusable chunks left.
