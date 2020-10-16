# Mathematical-operations-on-integers-stored-as-character-arrays
1. Introduction

An intal is a non-negative integer of any arbitrary length. It holds numeric data stored as an array of characters i.e a string and is terminated by a '\0'. 
The Most Significant Digit (MSD) is located at the head of the string i.e 0th index. A variable of integer data type will always occupy the same amount of space,
it doesn't matter if the number is 0 or 2147483647 (INT_MAX). Intals on the other hand are flexible in the sense that they only occupy as much space as they need. 
In addition to this, there are no limitations i.e no MAX value that an intal can hold. An intal can be very useful for large calculations such as the results of 
factorials and combinations which are often too large to be stored in an integer variable in C. This is also true for larger numbers in the fibonacci series.


2. Approach

char* intal_add(const char* intal1, const char* intal2);

An addition of 2 intals of length m and n will result in an intal of length either max(m,n) or max(m,n)+1. Keeping this in mind, I stored the length of the larger
intal and created a sum intal of max(m,n)+1 digits and then proceeded to add corresponding digits (along with the carry) min(m,n) times from LSD. After that, I 
added the remaining digits of the longer intal with the left over carry(if any) and checked if the carry still existed after adding all digits. If yes, I hardcoded 
the first digit of the sum intal to 1 and returned it. If not, I create a new sum intal of size equal to max(m,n) digits, copy the value from sum intal and free it 
and return new sum.

int intal_compare(const char* intal1, const char* intal2);

A fairly straightforward approach involving obtaining the lengths of the two intals and then performing a series of comparisons to obtain the solution. When two 
intals are of the same length, I iterate through the intals from the MSD comparing the digits till a difference is found. The appropriate solution is returned.

char* intal_diff(const char* intal1, const char* intal2);

Since it was meant to be the difference i.e magnitude of subtraction of two intals, the larger intal and its length are first stored in n1,length and the smaller 
in n2,small. If the intals are the same, "0\0" is returned. Similar to addition, I iterate subtracting the corresponding digits from LSD till the smaller (or both) 
intal runs out of digits. After this, the remaining digits(if any) are added into the diff intal while taking into consideration the carry. Then I store it in a 
smaller intal if applicable, free all the unimportant intals and return the intal with the difference.

char* intal_multiply(const char* intal1, const char* intal2);

If either (or both) of the intals is 0, "0\0" is returned.
The larger intal and its length are stored in n1,l1. Smaller intal and its length are stored in n2,l2. A product intal is created and given the value 0. Then a 
"handwritten-multiplication" algorithm is followed i.e the multiplication that humans do on paper. Each digit of n2 is taken and multiplied with each digit of 
n1 and stored in the line intal. This line intal is then added to the product intal. If a carry out exists, it is added to the product as well. In each subsequent 
iteration, the line and the carry intals are padded with the appropriate number of 0s from the LSD side. The unimportant intals are freed and the product is stored in
 product intal reallocated to proper size which is then returned.

char* intal_mod(const char* intal1, const char* intal2);

If the second intal is larger, the first intal is returned. If the intals are equal, "0\0" is returned. The lengths of the 2 intals are stored in l1 and l2. If the 
MSD of the larger intal is larger than the MSD of the smaller intal, the smaller intal is padded with 0s to the right of the LSD till the two intals are close to each 
other i.e of the same length. If the MSD of the smaller intal is larger than the MSD of the larger intal, the smaller intal is padded with 0s to the right of the LSD 
till the smaller intal is of 1 character shorter than the larger intal. This is because the algorithm I implemented uses addition and not subtraction. The padded intal 
is stored in sum and intal2 is stored in i2.Next i2 is added to the padded smaller intal sum and stored. Then i2 is doubled and added to sum again. This repeats till 
sum exceeds intal1. When this happens, the i2 value that when added to sum caused it to exceed intal1 is deleted from sum. Thus sum is once again smaller than intal1. 
Then i2 is reset to intal2 and the entire process repeats until the difference between sum and intal1 is less than or equal to intal2. If it is equal to intal2, then 
the unimportant intals are freed and "0\0" is returned. If it is less than intal2, the difference between intal1 and sum itself is stored and returned after freeing the 
extra allocated memory.

char* intal_pow(const char* intal1, unsigned int n);

The ans intal is allocated memory and initialised to the value of intal1. Then it is multiplied with itself until twice the current exponent exceeds the required exponent. 
After this, the ans is multiplied times intal1 till the exponent is reached. Then the memory allocated is resized appropriately and then returned.

char* intal_gcd(const char* intal1, const char* intal2);

The function uses Euclid's Algorithm to find the GCD.

char* intal_fibonacci(unsigned int n);

If n is 0, 0 is returned. If n is 1, 1 is returned. Else, intals a and b are intialised to 0 and 1 respectively. Then the following operations are performed with the help of 
another intal c :- c = a+b;a = b; b = c; till the nth fibonacci number is store in c and c is returned. 

char* intal_factorial(unsigned int n);

Two intals soln and num are used. num stores the value of the loop counter which counts down from n and this value is multiplied times soln which starts out at 1. When the 
counter reaches 0, num is freed and soln is returned.

char* intal_bincoeff(unsigned int n, unsigned int k);

A char*** pointer is used as for the iterative implementation of Pascal's identity, a 2D array of numbers (intals in our case) is required. If n-k is less than k, k is made equal to n-k
because nCk = nCn-k. The identity C(n,k) = C(n-1,k) + C(n-1,k-1) is followed and appropriate memory is allocated dynamically. I freed up old memory as and when I allocated new memory so as to obey the O(k) constraint. The result is stored in 
C[n][k] which is copied into a temporary intal temp which is reallocated to the required memory size and the remaining memory is freed. temp is returned.

int intal_max(char **arr, int n);

Index of the first occurence of the maximum element is stored after traversing the intal and returned at the end.

int intal_min(char **arr, int n);

Index of the first occurence of the minimum element is stored after traversing the intal and returned at the end.

int intal_search(char **arr, int n, const char* key);

The array is traversed from the 0th index till the key is found. -1 is returned if not found and the index is returned if it is found.

int intal_binsearch(char **arr, int n, const char* key);

This function implements a binary search algorithm on an array of intals with the additional constraint that when the key is found, the index of the first occurence of the key is 
found by traversing backwards till the key is not present. The first index is returned.

void intal_sort(char **arr, int n);

A O(n log n) algorithm to sort was required so i implemented the Merge sort algorithm (which has a time complexity of O(n log n) in the worst case) and modified it to be able to 
store intals. Memory freeing is done appropriately and nothing is returned as the array arr is sorted in place.

char* coin_row_problem(char **arr, int n);

For this, I implemented the sliding window of 3 approach given in the lecture slides. The 3 intals used are prev,next and cur. Only 3 intals are used and the time complexity is O(n).

3. Future Work

Division while useful would be not possible to implement as intals have to be integers. Truncated division function could be implemented and used along with the mod function to 
obtain the result of division. If there were no restrictions, an integer array rather than a character array would make things a little easier as type casting would not be a worry. 
