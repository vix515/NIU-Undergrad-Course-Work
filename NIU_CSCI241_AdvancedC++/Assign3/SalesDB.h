#ifndef SALESDB_H
#define SALESDB_H
#include "Seller.h"
/****************************************************************
   FILE:      Seller.h
   AUTHOR:    Victor Padilla
   LOGON ID:  Z1689628 (your Z number here)
   DUE DATE:  9/29/2015

   PURPOSE:   This header file sets up the methods prototypes and default variables.
		It will serve as an information pool for a Seller class to get its purpose from
		
****************************************************************/		  
   class SalesDB
   {
   private:
   	
   	Seller object[3][6]; 				//double array to have a group and objects inside a group

   public:	
   	SalesDB();					//prototype for default constructor
	SalesDB(const char* );				//prototype for constructor with an argument
	void print()const;				//print method protoype no return so its a void method
   	void processSalesData(const char* );		//prototype for data processor no return so its a void method
   };
#endif
	


