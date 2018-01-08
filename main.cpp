#include <iostream>
#include <fstream>
#include "[Project][1051][Kovacs_Erik]_Classes.h"

/**
*
*   SPEC:
*
*   PHASE 1:
*	Aplicatie pentru gestiunea bugetului. Se inregistreaza cheltuielile pe categorii (alimentare, utilitati etc.). Se pot adauga cheltuieli noi pentru fiecare zi,
*	se pot modifica cheltuielile deja introduse sau se pot sterge. Aplicatia pastreaza istoricul datelor introduse, folosind fisiere text sau binare. Se pun la
*	dispozitia utilizatorului rapoarte de cheltuieli, dupa criterii multiple (total cheltuieli pentru o anumita data, grupate pe categorii sau prezentate individual,
*	total cheltuieli lunare, anuale, suma medie a cumparaturilor pentru o anumita categorie, etc).
*
*	PHASE 2:
*	Implement a module/class to manage input files (text type) using the main function arguments (for example: if the application is called ProjectPOO.exe then it is
*	executed with the next command line command ProjectPOO.exe invoices.txt expense.txt; only text files are used);
*	implement a module that will allow the user to save application data into binary files. Application data is considered to be the data obtained from input text files
*	received as main arguments or data uploaded by users during its session (console input). If the application does not get arguments through the main function (it launches
*	with ProjectPOO.exe) then it will access binary files placed at locations known by the programmer. Binary files will allow users to save all the data that was loaded into
*	the application by different methods.
*	Entities that manage files and their specific operations are implemented through classes (source code used to manage files must be included in methods that belong to new
*	classes added to the project)
*	It implements a module by which the user can generate different reports for all data (eg list of clients, list of invoices in a certain category, costs categories, etc.) to
*	be displayed on the console but also in text files (minimum 3 reports)
*	It implements a module that manages a simple console ASCII based menu that the user can use to navigate through the application functions (after the application starts,
*	the user can use numeric keys or enter text to decide which functions to activate - eg to see bills in the system, generate different types of reports, etc.)
*	The application allows uploading data from comma separated values ​​(CSV) files; the symbol that separates the values ​​is chosen by the programmer and is used for all CSV files
*
*
*/

int Expenditure::expenditure_id = 0;
int Income::income_id = 0;
int Account::account_id = 0;

int main(int argc, char **argv) {
	/* menu */
	if (argc == 1) {
		Util::menu();
		/* demonstration */
	}
	else if (argc == 2 && (strcmp(argv[1], "demo") == 0)) {
		Util::demo();
		/* call exe with 2 params to import incomes and expenditures -- UNDER CONSTRUCTION */
	}
	else if (argc == 3) {
		std::cout << argv[1] << " " << argv[2] << "\nNOTICE: this section is under construction, better use the menu.\n";
		std::ifstream f1, f2;
		f1.open(argv[1], std::ios::in);
		f2.open(argv[2], std::ios::in);
		/* exit if no files are present */
		if (!f1) {
			std::cout << "Cannot open `" << argv[1] << "`. Make sure file exists.\n";
			exit(-1);
		}
		else if (!f2) {
			std::cout << "Cannot open `" << argv[2] << "`. Make sure file exists.\n";
			exit(-1);
		}
		else {
			/* parse incomes */
			int expenditures_num, incomes_num;
			char mark;
			f1 >> incomes_num >> mark;

			if (mark != '%') {
				std::cout << "Unsupported file format. Exiting...\n";
				exit(-1);
			};

			if (incomes_num == 0) {
				std::cout << "No information in file. Exiting...\n";
				exit(-1);
			};

			Income *incomes = new Income[incomes_num];
			for (int i = 0; i < incomes_num; i++) {
				f1 >> incomes[i];
			};

			/* parse expenditures */
			f2 >> expenditures_num >> mark;

			if (mark != '%') {
				std::cout << "Unsupported file format. Exiting...\n";
				exit(-1);
			};

			if (expenditures_num == 0) {
				std::cout << "No information in file. Exiting...\n";
				exit(-1);
			};

			Expenditure *expenditures = new Expenditure[incomes_num];
			for (int i = 0; i < incomes_num; i++) {
				f2 >> incomes[i];
			};

			/* create temp account */
			Account acc;

			acc.setTotalIncomes(incomes_num);
			acc.setIncomes(incomes, incomes_num);
			acc.setTotalExpenditures(expenditures_num);
			acc.setExpenditures(expenditures, expenditures_num);

			std::cout << "What do you want to do with this data?\n"
				<< "1. Save it to disk.\n"
				<< "2. Display a report.\n"
				<< "3. Exit program.\n";

			int choice;
			std::cin >> choice;

			if (choice == 1) {
				std::cout << "Enter name of the owner:\n";
				char buff[100], buff2[100];
				std::cin >> buff;
				acc.setHolderName(buff);
				/* here it should be saved to disk */
			}
			else if (choice == 2) {
				/* reports */
				std::cout << "What kind of report do you want to see?\n"
					<< "1. Total expenditures for date.\n"
					<< "2. Total expenditures for item.\n"
					<< "3. Total expenditures for all months.\n"
					<< "4. Total expenditures for all years.\n"
					<< "5. Exit.\n";

				int choice2;
				std::cin >> choice2;

				Datetime d;
				Report r;
				r.setAccount(acc);

				if (choice2 == 1) {
					std::cout << "Enter query date: ";
					std::cin >> d;
					r.getTotalExpendituresForDate(d);
				}
				else if (choice2 == 2) {
					char buff[100];
					std::cout << "Enter query term: ";
					std::cin >> buff;
					std::cout << "\n";
					r.getTotalExpendituresForItem(buff);
				}
				else if (choice2 == 3) {
					int year;
					std::cout << "Enter query year: ";
					std::cin >> year;
					r.getTotalExpendituresForAllMonths(year);
				}
				else if (choice2 == 4) {
					r.getTotalExpendituresForAllYears();
				}
				else {
					exit(0);
				}
			}
			else {
				exit(0);
			}

		}
		/* if input unrecognised, show usage */
	}
	else {
		std::cout << "\nUnknown parameter. Usage: project_oop <incomes> <expenditures> or specify no parameters to access the menu.\n";
	}
	return 0;
}
