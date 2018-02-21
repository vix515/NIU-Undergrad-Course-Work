#ifndef SALESDB_H
#define SALESDB_H
#include "Seller.h"
/****************************************************************
   FILE:      Seller.h
   AUTHOR:    Victor Padilla
   LOGON ID:  Z1689628 (your Z number here)
   DUE DATE:  9/22/2015

   PURPOSE:   This header file sets up the methos prototypes and default variables.
		It will serve as an information pool for a Seller class to get its purpose from

****************************************************************/
   class SalesDB
   {
     private:
     	 Seller object[30];
     	 int amount;
     public:
     	 SalesDB();
  	   SalesDB(const char* );
  	   void print();
  	   void sortSellers();
  	   int  searchForSeller(const char* )const ;
     	 void processSalesData(const char* );
   };
#endif
