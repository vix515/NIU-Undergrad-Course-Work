/***********************************************************
CSCI 340 - Assignment 3 - Fall 2016

Progammer: Victor Padilla
Z-ID: z1689628
Date Due: Feb 16, 2016

Purpose: This program is dedicated to extract all primes from
2 to n. It uses an algorithm to sort out all numbers that are only divisible 
by one and itself.
************************************************************/ 
#include <iostream>
#include <iomanip> 
#include <set>

using namespace std; 

/***************************************************************
Function: sieve

Use: extract all numbers that are prime and put them in a set 

Parameters: an empty set to store numbers and and integer n to get all
primes within the set.

Returns: Returns nothing

Notes: We start by putting the only even prime in the set (2)

1. We know any number that is even its not prime. Therefore only
search through the numbers that are odd.

2. We know that a number only has divisor in its first half. That is
a number can not be divided by a number gretaer than its half.
This is because the biggest you can divide a number is in half. 

3. With #2 then we can search for divisors of a number that its in its lower half.
therefore start at 1 and because we are only searching through odds increment by 2.
we stop until we get to half point. Becuase with rule #2 we know that there wont be any divisor after
middle gorund, this optimizes the program.

4. when a number is being divided there mus be a remainder. Meaning that a mod division 
should not equal 0. if it equals zero then it divides said number. Becuase we start with 1
then 1 divides all numbers allowing 1 to be the only divisor of said number.

5.With rul #4 we set a counter counting the amount of times a number is evenly divided.
since we start with 1 we let the counter get to 1 if the counter is greater than 1 then the number has
some other number dividing it therefore not prime. If the counter is already at 2 or greater optimize the program and stop the
search we already know its not prime therefore move to the next number. with this we just set j=n forcing the loop to exit
and move to the next number.

6. after each number we make sure that counter is only at 1 if so save the number, that number is a prime.
***************************************************************/
void sieve( set<int>& s, int n) {
  
  
  int count = 0;
  if(n >=2)
    s.insert(2);
    
   for(int i=3; i<=n; i=(i + 2)){
     count=0;
    for(int j=1; j<(i/2)+1; j= (j+2)){
      if((i%j) == 0){
        count++;
        if(count >= 2)
          j = n;
      }
        
    }
    if(count == 1)
      s.insert(i);
  }
        
}

/***************************************************************
Function: print_primes

Use: prints the elements in a set 

Parameters: A set to print its elements

Returns: Returns nothing

Notes: iterate through the set and print all its elements. set a counter 
to count every 8 numbers and print a new line. also set a width of 6 for printing aligment. 
***************************************************************/
void print_primes( const set<int>& s) {

  int count=0;
  for (std::set<int>::iterator it=s.begin(); it!=s.end(); ++it){
    cout <<setw(6)<< *it << ' ';
    count++;
    if((count % 8) == 0)
      cout<<endl;
    
  }
    cout<< endl;
}

int main() {
    set<int> s;
    sieve(s, 500);
    print_primes(s);
    return 0;
}
