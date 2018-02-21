#ifndef SELLER_H
   #define SELLER_H
   //*****************************************************************
   // FILE:      Seller.h
   // AUTHOR:    Victor Padilla

   /* PURPOSE:
		The Purpose of the header is to declare the variables and method prototypes used on the Class.
		We Declare private Variables to keep security around them and only accesible with permissions
		This will pass the information to main about can it can be used and what is accesible to reconfigure.
	*/

   //*****************************************************************

   class Seller
      {
          // Data members and method prototypes for the Seller class go here
    		private:
    			 char name[31];		// a char array of size 31 is needed to store an incoming name from main.The name is generalized and that why is called name only.
    			 double salesTotal;	//We generalized a souble to be a representation of a number passed through main.

    		public:
    			Seller();			//this is a default constructor and will allow an object with 0 parameters to be created
    			Seller(const char* , double);	//this a constructor that will take 2 paramaters and create and object with such specifics
    		  const char* getName() const;	//this prototype sets up a method to allow main to retrieve an objects name
    			double getSalesTotal() const;	//this prototype sets up a method to allow mainn to retrieve an objects character such as its Total Sales
    			void setSalesTotal(double);	//this prototype sets up a method to allow main to set a new number of total sales
    			void print();			// this prototype will allow main to print any information we allowed to pass through


      };

#endif
