#include <iostream>
#include <fstream>
#include "classes.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

/**
*	
*   SPEC:
*
*	Aplicatie pentru gestiunea bugetului. Se inregistreaza cheltuielile pe categorii (alimentare, utilitati etc.). Se pot adauga cheltuieli noi pentru fiecare zi, 
*	se pot modifica cheltuielile deja introduse sau se pot sterge. Aplicatia pastreaza istoricul datelor introduse, folosind fisiere text sau binare. Se pun la 
*	dispozitia utilizatorului rapoarte de cheltuieli, dupa criterii multiple (total cheltuieli pentru o anumita data, grupate pe categorii sau prezentate individual,  
*	total cheltuieli lunare, anuale, suma medie a cumparaturilor pentru o anumita categorie, etc).
*
*
*/

int Expenditure::expenditure_id = 0;
int Income::income_id = 0;
int Account::account_id = 0;

int main() {
	int d;
	while (std::cin >> d) {

		std::cout << "I.Class Datetime: \n";

		Datetime d = Datetime();
		Datetime kennedy = Datetime(1963, 11, 22, 12, 30);
		std::cout << "Lee Harvey Oswald shot President Kennedy on " << kennedy.getDay() <<
			"/" << kennedy.getMonth() << "/" << kennedy.getYear() << " at " << kennedy.getHour() << ":" << kennedy.getMin() << ".\n";

		std::cout << "II.Classes Expenditure & Income: \n";

		Expenditure exp = Expenditure("Daily", "Food", "BigMac", "Bought at mcDonald's", -1000, d, d);
		Expenditure exp2 = exp;
		std::cout << exp2.getName() << " " << exp2.getAmount() << "\n";

		Datetime d2 = Datetime();
		Income inc = Income("Monthly", "-", "Salary", "-", 1500, d2, d2);
		Income inc2 = inc;

		Account acc = Account();
		Expenditure *arr1 = new Expenditure[3];
		Income *arr2 = new Income[2];

		Datetime d3 = Datetime(1963, 11, 22, 12, 30);

		Expenditure exp3 = Expenditure("Daily", "Food", "BigMac", "Bought at mcDonald's", 0, d3, d3);
		arr1[0] = exp;
		arr1[1] = exp2;
		arr1[2] = exp3;
		arr2[0] = inc;
		arr2[1] = inc2;
		acc.setExpenditures(arr1, 3);
		acc.setIncomes(arr2, 2);
		acc.setHolderName("Erik Kovacs");

		std::cout << exp3;

		std::cout << exp << exp2;
		std::cout << inc << inc2;

		std::cout << d2 << "\n";
		std::cout << "III.Class Account: \n";
		std::cout << acc;

		std::cout << "IV.Class Report: \n";

		Report r = Report(acc);

		std::cout << "1.\n";
		r.getTotalExpendituresForDate(d);
		std::cout << "2.\n";
		r.getTotalExpendituresForItem("BigMac");
		std::cout << "3.\n";
		r.getTotalExpendituresForAllMonths(2017);
		std::cout << "4.\n";
		r.getTotalExpendituresForAllYears();
		std::cout << "5.\n";
		r.getAverageExpendituresForCategory("Food");
		std::cout << "6.\n";
		r.getTotalExpendituresForCategory("Food");

		std::cout << "V.Writing to file: \n";

		std::ofstream outFile;
		outFile.open("backup.txt", std::ios::out | std::ios::trunc);

		try {
			outFile << acc;
		}
		catch (std::exception & e) {
			std::cerr << e.what();
		}

		std::cout << "VI.Reading object from file: \n";

		std::ifstream inFile;
		inFile.open("backup.txt", std::ios::in);

		Account acc2;
		try {
			inFile >> acc2;
		}
		catch (std::exception & e) {
			std::cerr << e.what();
		}

		std::cout << acc2;

		std::cout << "VII.Program has finished. Performing cleanup... ";

		std::cout << "Freeing memory... ";
		delete[] arr1; delete[] arr2;
		std::cout << "Closing file handles... ";
		inFile.close();
		outFile.close();
	}
	/*Account acc = Account();
	Expenditure *arr1 = new Expenditure[3];
	Income *arr2 = new Income[2];
	Expenditure exp = Expenditure();
	Expenditure exp2 = Expenditure();
	Expenditure exp3 = Expenditure();
	Income inc = Income();
	Income inc2 = Income();
	arr1[0] = exp;
	arr1[1] = exp2;
	arr1[2] = exp3;
	arr2[0] = inc;
	arr2[1] = inc2;
	acc.setExpenditures(arr1, 3);
	acc.setIncomes(arr2, 2);
	acc.setHolderName("Erik Kovacs");
	std::cout << acc;
	Report r = Report(acc);

	Datetime d = Datetime();
	std::cout << "1.\n";
	r.getTotalExpendituresForDate(d);
	std::cout << "2.\n";
	r.getTotalExpendituresForItem("BigMac");
	std::cout << "3.\n";
	r.getTotalExpendituresForAllMonths(2017);
	std::cout << "4.\n";
	r.getTotalExpendituresForAllYears();
	std::cout << "5.\n";
	r.getAverageExpendituresForCategory("Food");
	std::cout << "6.\n";
	r.getTotalExpendituresForCategory("Food");
	return 0;*/
	_CrtDumpMemoryLeaks();
	return 0;
}