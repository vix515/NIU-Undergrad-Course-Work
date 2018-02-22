/****************************************************************
   FILE:      Complex.h
   AUTHOR:    Victor Padilla
   LOGON ID:  Z1689628
   DUE DATE:  10/15/15

   PURPOSE:   	This is a head file for the cpp file Complex.cpp
		and for the program assign4. This header file contains
		all the neccessary declartions for its methods and variables.
****************************************************************/

#ifndef COMPLEX_H
   #define COMPLEX_H
#include <iostream>
using std::ostream;
using std::istream;

	class Complex
      		{	//This is a friend functions which will allow us to access the
			//variables of the object that is calling it
			//Its overloading an operator for 'cout'
			friend ostream & operator<<(ostream &, const Complex &object);
			//This is a friend functions which will allow us to access the
                        //variables of the object that is calling it
                        //Its overloading an operator for 'cin'
			friend istream & operator>>(istream &, Complex &object);

      			private:
				double real;	//declaration of a double for the real number
				double imag;	//declaration of a double for the imaginary number

			public:
				//Set up for the constructor, initalize value at 0
				//for it to work as a defualt constructor aswell
				Complex(double=0, double=0);
				//method to setup the values imag and real
				//its a void method because its not returning anything
				void setComplex(double, double);
				//gathering of the real and imag numbers
				void getComplex(double &, double &)const;
				//method to setup the real number of the object
				void setRealPart(double);
				//methos to return a double as the real number of the object
				double getRealPart()const;
				//method to set up the imagniary doubl of the object
				void setImaginaryPart(double);
				//method to return the imaginary number as a double
				double getImaginaryPart()const;
				//operator overloading of the '+' and return of a complex object
				Complex operator+(const Complex &)const;
				//operator overloading of the '*' and return of a complex object
				Complex operator*(const Complex &)const;
				//operator overloading of the '==' and return of a complex object
				bool operator==(const Complex &)const;
		};

#endif 


