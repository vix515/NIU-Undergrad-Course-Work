
#include <iostream>
#include <iomanip>
#include "Seller.h"
#include <cstring>

using namespace std;
 
	Seller::Seller()
	{
		name[0] = '\0';
		salesTotal = 0;
		
	}
	
	Seller::Seller(const char* newName , double newSales)
	{
		strcpy(name, newName);
		
		salesTotal = newSales;
		
	}
	
	
	const char* Seller::getName() const
	{
		return name;
	}
	
	double Seller::getSalesTotal() const
	{
		return salesTotal;
	}
	
	void Seller::setSalesTotal(double newSales)
	{
		salesTotal = newSales;	  
	}
	
	void Seller::print()
	{ 
	 cout << left << setw(30)<< name << right<<setw(9)<<  setprecision (2) << fixed << salesTotal<<endl;
	}
	
	



