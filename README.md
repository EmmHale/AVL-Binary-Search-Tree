# AVL-Binary-Search-Tree

This implementation of an AVL tree uses a weight system to decide when to rotate, when add and removing nodes, in order to balance the tree. 

Using weighted nodes greatly increases performance compared to calling a recursive height function to find balance. 
Each new level of the tree doubles the number of height functions needed to be called. 
This results in a O(2^N) calculation time, where N is the height of the tree. 
A weighted add node function only needs to make one call per height on the tree, resulting in a O(N) calculation time.
