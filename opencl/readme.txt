First I am getting the elements to get sorted in 'a'. The number of elements need to be even
I am segregating the elements into odd position(odd.cl) and even position(even.cl) elements' sublists (namely b and c)
I am applying odd-even transposition sorting to the sublists
Now time to merge
I am merging without using additional array. When I do so, whenever there is a swap between 'b' and 'c', c is 
to be sorted again for which I use odd even transposition sorting (comp.cl and comp2.cl)
 