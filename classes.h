#ifndef CLASSES_H
#define CLASSES_H

/*
*	Date and time object, minute precision
*/
class Datetime {
private:
	int y;
	int m;
	int d;
	int h;
	int min;
public:
	// Setters and getters
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMin();

	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	void setHour(int hour);
	void setMin(int minute);

	// Constructors
	Datetime();
	Datetime(const Datetime & d);
	Datetime(int y, int m, int d, int h, int min);

	// I/O overloads
	friend std::istream & operator >> (std::istream& console, Datetime& d);
	friend std::ostream & operator<< (std::ostream& console, Datetime& d);
	friend std::ifstream & operator >> (std::ifstream& console, Datetime& d);
	friend std::ofstream & operator<< (std::ofstream& console, Datetime& d);

	// Destructor
	~Datetime();

	// Comparison overloads
	friend bool operator==(Datetime & d, Datetime & d2);
	friend bool operator!=(Datetime & d, Datetime & d2);
	friend bool operator<(Datetime & d, Datetime & d2);
	friend bool operator>(Datetime & d, Datetime & d2);
};


/*
*	"Abstract" class, should not be instantiated by itself; exists only for Expenditure
*  and Income to inherit from
*/
class Transaction {
private:
	char *type;
	char *category;
	char *name;
	char *note;
	double amount;
	Datetime created_at;
	Datetime updated_at;

public:
	// Setters and getters
	char * getType();
	char * getCategory();
	char * getName();
	char * getNote();
	double getAmount();
	Datetime getCreatedAt();
	Datetime getUpdatedAt();

	void setType(char *type);
	void setCategory(char *category);
	void setName(char *name);
	void setNote(char *note);
	void setAmount(double amount);
	void setCreatedAt(Datetime date);
	void setUpdatedAt(Datetime date);

	Transaction();
	Transaction(const Transaction & other);

	Transaction & operator=(const Transaction & other);

	// Destructor
	~Transaction();
};


/*
*	Expenditure: money you spend
*/
class Expenditure : public Transaction {
private:
	int id;
	static int expenditure_id;
public:
	// Getter
	int getId();

	// Constructors
	Expenditure();
	Expenditure(const Expenditure & expenditure);
	Expenditure(char *type, char *category, char *name, char *note, double amount, Datetime created_at, Datetime updated_at);

	// Destructor
	~Expenditure();

	// I/O overrides
	friend std::istream & operator >> (std::istream& console, Expenditure& e);
	friend std::ostream & operator<< (std::ostream& console, Expenditure& e);
	friend std::ifstream & operator >> (std::ifstream& file, Expenditure& e);
	friend std::ofstream & operator<< (std::ofstream& file, Expenditure& e);

};


/*
*	Income: money you earn
*/
class Income : public Transaction {
private:
	int id;
	static int income_id;
public:
	// Getter
	int getId();

	//Constructor
	Income();
	Income(const Income & income);
	Income(char *type, char *category, char *name, char *note, double amount, Datetime created_at, Datetime updated_at);

	// Destructor
	~Income();

	// I/O overloads
	friend std::istream & operator >> (std::istream& console, Income& i);
	friend std::ostream & operator<< (std::ostream& console, Income& i);
	friend std::ifstream & operator >> (std::ifstream& console, Income& i);
	friend std::ofstream & operator<< (std::ofstream& console, Income& i);
};


/*
*	An individual account, associated with a specific user
*/
class Account {
private:
	int id;
	static int account_id;
	int total_expenditures;
	int total_incomes;
	char *holder_name;
	Income *incomes;
	Expenditure *expenditures;

public:
	// Getters
	int getId();
	char * getHolderName();
	int getTotalIncomes();
	int getTotalExpenditures();
	Income * getIncomes();
	Expenditure * getExpenditures();

	double getBottomLineAtCurrentDate();

	// Setters
	void setHolderName(char * name);
	void setIncomes(Income * income, int len);
	void setTotalIncomes(int i);
	void setTotalExpenditures(int e);
	void setExpenditures(Expenditure * expenditure, int len);

	//Constructors
	Account();
	Account(const Account & account);
	Account(char *name, Income * income, int incomelen, Expenditure * expenditures, int expendlen);

	// methods for copying incomes and expenditures
	void incomecpy(Income *dst, Income*src, int len);
	void expenditurecpy(Expenditure *dst, Expenditure *src, int len);

	// methods for adding, removing or editing incomes/expenditures
	void addIncome();
	void addExpenditure();
	void deleteIncome(char *query);
	void deleteExpenditure(char *query);
	void editIncome(char *query);
	void editExpenditure(char *query);

	// I/O overloads
	friend std::istream & operator >> (std::istream& console, Account& a);
	friend std::ostream & operator<< (std::ostream& console, Account& a);
	friend std::ifstream & operator >> (std::ifstream& console, Account& a);
	friend std::ofstream & operator<< (std::ofstream& console, Account& a);

	Account & operator=(const Account & other);

	// Destructor
	~Account();

};


/*
*	Report: select an account and generate reports based on its contents
*/
class Report {
private:
	int id;
	static int report_id;
	Account account;

public:
	// Setters/Getters
	void setAccount(Account a);

	// Constructors
	Report();
	Report(const Report & r);
	Report(Account a);

	// Business logic, can be extended to whatever your heart desires
	double getTotalExpendituresForDate(Datetime d);
	double getTotalExpendituresForItem(char *item);
	double getTotalExpendituresForAllMonths(int year);
	double getTotalExpendituresForAllYears();
	double getAverageExpendituresForCategory(char *category);
	double getTotalExpendituresForCategory(char *category);

	// Destructor
	~Report();
};


/* utility class with all static methods */
class Util {
public:
	static void menu();
	static void demo();
};

#endif
