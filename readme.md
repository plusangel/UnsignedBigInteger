# Custom unsigned integer

Reinventing the wheel? Yes, when you do it for learning is OK!

We designed our class that can handle unsigned integer numbers. 
We used a byte array as the internal representation (uint8_t[]). 
We implemented operator overloads for operator+ and operator and performed runtime checks for overflow.


## notes

- **Addition** implemented using the full adder algorithm. Let's assume that the size of both numbers are the same. 
 We add one by one bits from rightmost bit to leftmost bit. 
 In every iteration, we need to sum 3 bits: 2 bits of 2 given strings and carry. 
 The sum bit will be 1 if, either all of the 3 bits are set or one of them is set. 
 So we can do XOR of all bits to find the sum bit. Carry will be 1 if any of the two bits is set. 
 So we can find carry by taking OR of all pairs. 

    - Perform bit addition
        - Boolean expression for adding 3 bits a, b, c
        - Sum = a XOR b XOR c
        - Carry = (a AND b) OR ( b AND c ) OR ( c AND a )

    More [explanation](https://www.geeksforgeeks.org/add-two-bit-strings/)
    
- **Subtraction** implemented using the full subtractor algorithm. In short it looks like:
    
    - Perform bit addition
        - Boolean expression for adding 3 bits a, b, borrow
        - Difference = a XOR b XOR borrow
        - Borrow = (!a AND borrow) OR ( !a AND b ) OR ( b AND borrow )
    
    More [explanation](https://en.wikipedia.org/wiki/Subtractor)

- **Multiplication** implemented using the Russian peasant algorithm. 
The idea is to double the first number and halve the second number repeatedly till the second number doesn’t become 1. 
In the process, whenever the second number become odd, we add the first number to result (result is initialized as 0)
The following is simple algorithm.
Let the two given numbers be 'a' and 'b'
    - Initialize result 'res' as 0.
    - Do following while 'b' is greater than 0
        1. If 'b' is odd, add 'a' to 'res'
        2. Double 'a' and halve 'b'
    - Return 'res'
    
    More [explanation](https://www.geeksforgeeks.org/russian-peasant-multiply-two-numbers-using-bitwise-operators/) 

- **Division** is a tricky operation. It was implemented by shifting the divisor up until its top bit matches that of dividend, 
then xor and shift back down, recording each position where you need an xor as a bit of the quotient.

    More [explanation](https://stackoverflow.com/questions/31090578/how-can-i-divide-bitsets) 

- **Module** is actually division where we return the remainder (the dividend at the end)


## maintainer
Angelos Plastropoulos