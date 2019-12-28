# Custom integer

Reinventing the wheel? Yes, when you do it for learning is OK!

We designed our class that can handle integer numbers. 
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
    
- **Subtraction** for binary numbers is straightforward. Given two numbers a and b, we can subtract b from a 
by using 2’s Complement method, just because negative numbers represented as 2’s Complement of positive ones.

    So the problem moves to calculate the 2nd complement. First, we need to calculate 1’s complement of a binary number 
which is another binary number obtained by toggling all bits in it, i.e., transforming the 0 bit to 1 and the 1 bit to 0.

    Then, the 2’s complement of a binary number is 1 added to the 1’s complement of the binary number.
We traverse the one’s complement starting from LSB (least significant bit), and look for 0. 
We flip all 1’s (change to 0) until we find a 0. Finally, we flip the found 0. 

    More explanation [here](https://www.geeksforgeeks.org/subtraction-of-two-numbers-using-2s-complement/) 
    and [here](https://www.geeksforgeeks.org/1s-2s-complement-binary-number/).

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

## todo
- [ ] Make sure that your operator overloads work for other integer types as well 
- [ ] Implement an operator int type conversion
- [ ] Perform a runtime check if narrowing would occur
- [ ] Implement operator/ and operator%
- [ ] Complete documentation
- [ ] Add unit tests