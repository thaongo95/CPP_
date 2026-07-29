
***********************************NOTE*******************************************

-  VECTOR and STRING hold their elements in contiguous memory --> its fast to access element from its index
                                                              --> its slow to insert or remove because it has to moved to maintain contiguity.
                                                              --> adding new element is move into new storage.

- LIST(doubly linked list) and FORWARD_LIST(singly linked list) --> fast to insert and remove because just change the link between two element
                                                                --> show to access to random element from its index, has to access by iterating
                                                                --> memory overhead(doesnt have size() operation).

- DEQUE is fast random access anf fast insert and remove from the front and back
- ARRAY is safer, easier to use alternative to built-in array.

LIBRARY CONTAINER is better than the primitive structures like built-in array.


++++++++++++++++++++++++Ordinarily, it is BEST to use VECTOR unless there is a good reason to prefer another container+++++++++++++++++++++++++++++++++++++++++++++++++++++


Best practices: use iterators not subscripts, because it is common operation to all container