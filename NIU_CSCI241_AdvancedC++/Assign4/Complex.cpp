//Including all neccessary files and libraries
//iostream to 'cout' and 'cin'
//Complex.h for prototypes

#include <iostream>
#include <iomanip>
#include "Complex.h"
#include <cstring>

using namespace std;

/*
	This is the default constructor. It will take to arguments and set them as default
	for the object. If no arguments are send to the method then it will automatically
	set the default value of '0'.
*/
Complex::Complex(double inreal, double inimag)
{
	real = inreal;
	imag = inimag;
}
/*
	This is the set method, it will set the real and imaginary values. It takes in two
	arguments and will set them up as the real and imaginary part of the object.
	Similar to Complex constructor but this method does not create an object just modifies
	its values.
*/
void Complex::setComplex(double inreal, double inimag)
{
        real = inreal;
        imag = inimag;
}
/*
	The get method when call will set up real and imaginary values of the object.
	It will write the values of the object into the argument reference of a variable.
	It doesnt return anything but alters the value of the argument through its adress.(referencing)
*/

void Complex::getComplex(double &inreal, double &inimag) const
{
	inreal=this->real;
	inimag=this->imag;
}
/*
	This is a set method, similar to the setmethod above. Except this one just
	modifies one value, the real value of the object.
*/
void Complex::setRealPart(double inreal)
{
	real=inreal;
}
/*
	This method is call to get the real number of an object, it returns a double.
*/
double Complex::getRealPart() const
{
	return real;
}
/*
  This is a set method, similar to the setmethod above. Except this one just
  modifies one value, the imaginary value of the object.
*/
void Complex::setImaginaryPart(double inimag)
{
	imag=inimag;
}
/*
  This method is call to get the imaginary number of an object, it returns a double.

*/
double Complex::getImaginaryPart() const
{
	return imag;
}

/*
	Right here we are overloading the '+' operator, in order to add objects. To add
	objects we have the caller and the object the is being added to it.
	The number being added is a reference to a const object, this way we dont create copies.
	The addition is simple we get the first real number of the caller object by using this pointer
	and we added with regular addition to the reference object's real number (using the getter).
	Adding two object creates a new object but we create a new temporary one and store the values there
	letting main decide what it wants to do with the values and the object. We are returning an object to
	main.
*/
Complex Complex::operator+(const Complex &object)const
{
	Complex temp;
	double tempReal;
	double tempImag;

	tempReal = this->real + object.getRealPart();
	tempImag = this->imag + object.getImaginaryPart();

	temp.setImaginaryPart(tempImag);
	temp.setRealPart(tempReal);
	return temp;
}

/*
  Right here we are overloading the '*' operator, in order to multiply objects. To multiply
  objects we have the caller and the object the is being multiply  to.
  The number being multiple by is a reference to a const object, this way we dont create copies.
  The multiplication is simple we get the first real number of the caller object by using this pointer
  and we multiply it  with the realpart of the reference object. We then subtract the imaginary times the
	second imaginary, from the first operation.

	To get the imaginay we use regular multiplication of the real number times the object's imaginary
	minues the imaginary times the real number of the object beinged referenced too.

	We save this in a new object we create at the beginning this is so we can return and object and not
	alter and existing one. The data will be use in main.
*/

Complex Complex::operator*(const Complex &object)const
{
	Complex temp;
	double tempReal;
	double tempImag;

	tempReal = (this->real * object.getRealPart())-(this->imag*object.getImaginaryPart());
	tempImag = (this->real * object.getImaginaryPart())+(this->imag*object.getRealPart());

	temp.setImaginaryPart(tempImag);
	temp.setRealPart(tempReal);
	return temp;

}
/*
	Here we are overloading the '==' operator to compare two objects.
	We take the object that called the methos and the one being compare too (as a reference object)
	From here we do regular number comparison with the reals and the imaginary numbers. We return
	a boolean stating wheter its a true or false equality.
*/

bool Complex::operator==(const Complex &object)const
{
	return (this->real == object.getRealPart()) && (this->imag == object.getImaginaryPart());
}

/*
	This is NOT A METHOD is a FRIEND FUNCTION. We are overloading the operator '<<'
	This is for  when we want to print out an object we resort to thi function.
	The function will take the object and print what ever we want. In this case
	We are calling an object's getter methods to get its info and print it out.
	We then return the out statement for cout to interpret as an outgoing message.
*/
ostream & operator<<(ostream &out, const Complex &object)
{
	out << "( " << object.getRealPart() << ", " << object.getImaginaryPart() << " )";
	return out;
}
/*
	This is NOT A METHOD is a FRIEND FUNCTION. We are overloading the operator'>>'
	This is for when we want to write into and object. This function will allow
	us to write to an object instead of a character or string. It will take the
	object that is calling it and ask the users to change its variables in the
	format (a,b). We create a dump for the extra characters and only use the
	doubles entered to store them as the new variables. We return in for 'cin'
	to process.
*/
istream & operator>>(istream &in, Complex &object)
{
	char dump;
	in>> dump >> object.real >> dump >> object.imag  >>dump;
	return in;
}
