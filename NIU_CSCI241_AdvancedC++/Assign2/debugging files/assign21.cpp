#include <iostream>
#include "Seller.h"
//#include "Seller.cpp"
using std::cout;
using std::endl;

int main()
      {
      // Test default constructor
      Seller seller1;

      // Test alternate constructor
      char s[] = "Jones, Martin";
      Seller seller2(s, 1234.56);

      // Test print() method and whether constructors
      // properly initialized objects
      cout << "Printing seller1\n\n";
      seller1.print();
      cout << endl << endl;

      cout << "Printing seller2\n\n";
      seller2.print();
      cout << endl << endl;

      // Test accessor methods
      cout << seller2.getName() << endl;
      cout << seller2.getSalesTotal() << endl;

      seller2.setSalesTotal(6543.21);
      cout << seller2.getSalesTotal() << endl;

      return 0;
      }


