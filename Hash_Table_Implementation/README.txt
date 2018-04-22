Given an array of data, how do you know if a specific piece of data is in that array?
This is the question answered by searching algorithms. 

A very simple searching algorithm, the sequential search, solves this problem by checking every single item, one-by-one, until the desired item is found, 
or the end of the array is reached. The sequential search has a Big-Oh efficiency of O(n), where n is the number of elements in the array.

If we wish to improve on the sequential search, we need to modify the array itself to enhance search speed. 
By ensuring that the array is sorted, that is, ordered in a specific fashion, the binary search algorithm cuts the list in half with each iteration.
The binary search has a Big-Oh efficiency of O(log(n)).

By arranging the data in a predictable manner, we cut down the time needed to search for a piece of data.
The next question then, is there a different way of storing data that can increase the efficiency of a search algorithm?
This is the question answered by the Hash table.

The hash table is not my original idea, rather I am implementing it as a proof of concept that I learned in a class.
It is a side project more than anything else.

While I ended the description of the other two sorting algorithms with the Big-Oh notation, I shall start with the Big-Oh for a hash table search.
The Big-Oh average case for a hash table is O(1), something much faster than even a binary search when given an arbitrarily large amount of data.

First, we must understand what a hash table is:
The hash table (HT for short) is an array length n of buckets. 
	n is the number of objects you expect to handle, but in this implementation n is arbitrary. 
	The efficiency of the hash table increases with n, as will be proved below.
	Each index in the array is another data structure, which I refer to as a bucket (making the HT an array of buckets).
		The data structure you use for buckets is arbitrary, I use vectors due to their scaleability and well-recognized functionality.
		Provided that a data structure can access each element at any time, it will suffice as a bucket if a vector is not suitable.
	
Given an item we wish to store in the HT, we can sort the data via a hashing function.
	A hashing function is any function in which data is converted into a value in which it is impossible to retrieve the original value from the output data.
	The hashing function for an HT simply returns an integer, which is the index of a bucket in the array.
	So, to store an item in the HT, we hash the item and add the item to the bucket whose location (or index) is retrieved from the Hash function.

Given an item we wish to check is in the HT, we can find that item with a constant speed.
	First, hash the item as described above.
	Second, check the bucket that the hash function indicates for data. 
	If the bucket is empty, we know that the item isn't in the hash table (best case scenario).
	If the bucket has information in it, we can check that single bucket, ignoring the n-1 other buckets, and all data in those buckets.
	This method of searching for data is extremely fast for massive amounts of data because we reduce time by only having to search a single bucket.

In an ideal world, the buckets only have one piece of data per bucket, but unfortunately, we don't live in an ideal world.
The hashing function will guarentee at least one collision if you enter an amount of data equal to the length of the HT array + 1. 
How do we handle collisions?
	As mentioned previously, in my implementation, each "bucket" is in fact a vector. 
	In our search function, if we arrive at a vector that has more than one piece of data within it, 
	then we simply engage in another searching algorithm. In this implementation, I use the sequential search algorithm.

On the subject of collisions, the hash table's worse case scenario would be a series of data that when hashed, resulted in the same value. 
If this were the case, then the HT is no more efficient then a standard array. However, given an arbitrarily large random data set, 
the amount of collisions would still remain rather low, and the HT's methods of reducing the amount of data sorted through at any given 
point is still negligible. This is why when measuring the Big-Oh notation of the HT, it is more accurate to use the average case, 
rather then the worse case: O(n). This is also why the efficiency of the HT search increases with the n values, because it reduces bucket size.

While the sequential search algorithm is not very efficient, it doesn't need to be. Given a sufficiently large n-value (n being the size
of the array containing buckets), the amount of collisions would be relatively small. So, while my hash table implementation could be 
optimized by sorting buckets and using a binary search, the change in run-time speed would be miniscule. Only in the worse case scenario
is that optimization going to be more effective, but you then are required to sort all data as it is added to each bucket.