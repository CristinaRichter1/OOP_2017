#include <windows.h>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "[Project][1051][Kovacs_Erik]_Classes.h"

/* ====================================== Implementation for class Datetime ====================================== */
// Setter/Getter definitions for class Datetime
int Datetime::getYear() {
	return this->y;
}

int Datetime::getMonth() {
	return this->m;
}

int Datetime::getDay() {
	return this->d;
}

int Datetime::getHour() {
	return this->h;
}

int Datetime::getMin() {
	return this->min;
}

void Datetime::setYear(int year) {
	if (year >= 0) {
		this->y = year;
	}
	else {
		throw std::exception("Invalid input, should be a valid year.");
	}
}

void Datetime::setMonth(int month) {
	if (month > 0 && month <= 12) {
		this->m = month;
	}
	else {
		throw std::exception("Invalid input, should be a valid month (between 1 and 12).");
	}
}

void Datetime::setDay(int day) {
	if (day > 0 && day <= 31) {
		this->d = day;
	}
	else {
		throw std::exception("Invalid input, should be a valid day (between 1 and 31).");
	}
}

void Datetime::setHour(int hour) {
	if (hour >= 0 && hour < 24) {
		this->h = hour;
	}
	else {
		throw std::exception("Invalid input, should be a valid hour of day (between 1 and 24).");
	}
}

void Datetime::setMin(int min) {
	if (min >= 0 && min < 60) {
		this->min = min;
	}
	else {
		throw std::exception("Invalid input, should be a valid minute (between 0 and 59).");
	}
}

// Datetime default constructor
Datetime::Datetime() {
	SYSTEMTIME st;
	GetSystemTime(&st);
	this->setYear(st.wYear);
	this->setMonth(st.wMonth);
	this->setDay(st.wDay);
	this->setHour(st.wHour);
	this->setMin(st.wMinute);
}

// Datetime copy constructor
Datetime::Datetime(const Datetime & d) {
	this->setYear(d.y);
	this->setMonth(d.m);
	this->setDay(d.d);
	this->setHour(d.h);
	this->setMin(d.min);
}

// Explicit constructor for Datetime
Datetime::Datetime(int y, int m, int d, int h, int min) {
	this->setYear(y);
	this->setMonth(m);
	this->setDay(d);
	this->setHour(h);
	this->setMin(min);
}

// I/O 
std::istream & operator >> (std::istream& console, Datetime& d) {
	int buff;
	std::cout << "\nYear: ";
	console >> buff;
	d.setYear(buff);
	std::cout << "\nMonth: ";
	console >> buff;
	d.setMonth(buff);
	std::cout << "\nDay: ";
	console >> buff;
	d.setDay(buff);
	std::cout << "\nHour: ";
	console >> buff;
	d.setHour(buff);
	std::cout << "\nMinute: ";
	console >> buff;
	d.setMin(buff);
	return console;
};

std::ostream & operator << (std::ostream& console, Datetime& d) {
	console << d.d << "/" << d.m << "/" << d.y << " " << d.h << ":" << d.min;
	return console;
};

std::ifstream & operator >> (std::ifstream& file, Datetime& d) {
	file >> d.y >> d.m >> d.d >> d.h >> d.min;
	return file;
};

std::ofstream & operator << (std::ofstream& file, Datetime& d) {
	file << d.y << std::endl
		<< d.m << std::endl
		<< d.d << std::endl
		<< d.h << std::endl
		<< d.min << std::endl;
	return file;
};

// Destructor for Datetime
Datetime::~Datetime() {
};

// Comparison overloads
bool operator==(Datetime & d, Datetime & d2) {
	if (d.y == d2.y && d.m == d2.m && d.d == d2.d && d.h == d2.h && d.min == d2.min)
		return true;
	return false;
};

bool operator!=(Datetime & d, Datetime & d2) {
	return !(d == d2);
};

bool operator<(Datetime & d, Datetime & d2) {
	long long int mins1 = (d.y * 525600) + (d.m * 43800) + (d.d * 1440) + (d.h * 60) + d.min;
	long long int mins2 = (d2.y * 525600) + (d2.m * 43800) + (d2.d * 1440) + (d2.h * 60) + d2.min;
	return (mins1 < mins2);
};

bool operator>(Datetime & d, Datetime & d2) {
	return !(d < d2);
};

/* ====================================== Implementation for class Transaction ====================================== */

//Setters/Getters for class Transaction

char * Transaction::getType() {
	return this->type;
};

char * Transaction::getCategory() {
	return this->category;
};

char * Transaction::getName() {
	return this->name;
};

char * Transaction::getNote() {
	return this->note;
};

double Transaction::getAmount() {
	return (double) this->amount;
};

Datetime Transaction::getCreatedAt() {
	return this->created_at;
};

Datetime Transaction::getUpdatedAt() {
	return this->updated_at;
};

void Transaction::setType(char *type) {
	int len = strlen(type);
	this->type = new char[len + 1];
	strcpy(this->type, type);
};

void Transaction::setCategory(char *category) {
	int len = strlen(category);
	this->category = new char[len + 1];
	strcpy(this->category, category);
};

void Transaction::setName(char *name) {
	int len = strlen(name);
	this->name = new char[len + 1];
	strcpy(this->name, name);
};

void Transaction::setNote(char *note) {
	int len = strlen(note);
	this->note = new char[len + 1];
	strcpy(this->note, note);
};

void Transaction::setAmount(double amount) {
	this->amount = (double)amount;
};

void Transaction::setCreatedAt(Datetime date) {
	this->created_at = date;
};

void Transaction::setUpdatedAt(Datetime date) {
	this->updated_at = date;
};

Transaction & Transaction::operator=(const Transaction & other) {
	this->setType(other.type);
	this->setCategory(other.category);
	this->setName(other.name);
	this->setNote(other.note);
	this->setAmount(other.amount);
	this->setCreatedAt(other.created_at);
	this->setUpdatedAt(other.updated_at);
	return *this;
};

Transaction::Transaction() {
};


Transaction::Transaction(const Transaction & other) {
	type = new char[strlen(other.type) + 1];
	strcpy(type, other.type);
	category = new char[strlen(other.category) + 1];
	strcpy(category, other.category);
	note = new char[strlen(other.note) + 1];
	strcpy(note, other.note);
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	amount = other.amount;
	created_at = other.created_at;
	updated_at = other.updated_at;
};

// Destructor for Transaction

Transaction::~Transaction() {
	if (this->type)
		delete[] this->type;

	if (this->category)
		delete[] this->category;

	if (this->name)
		delete[] this->name;

	if (this->note)
		delete[] this->note;
};

/* ====================================== Implementation for class Expenditure ====================================== */

// Getters/Setters for class Expenditure
int Expenditure::getId() {
	return this->id;
};


// Default constructor for class Expenditure
Expenditure::Expenditure() : id(expenditure_id) {
	this->setType("N/A");
	this->setCategory("N/A");
	this->setName("expenditure");
	this->setNote("-");
	this->setAmount(0);
	Datetime now = Datetime();
	this->setCreatedAt(now);
	this->setUpdatedAt(now);
	expenditure_id++;
};

// Copy constructor
Expenditure::Expenditure(const Expenditure & expenditure) : Transaction(expenditure), id(expenditure_id) {
	expenditure_id++;
};

Expenditure::Expenditure(char *type, char *category, char *name, char *note, double amount, Datetime created_at, Datetime updated_at) : id(expenditure_id) {
	this->setType(type);
	this->setCategory(category);
	this->setName(name);
	this->setNote(note);
	this->setAmount(amount);
	this->setCreatedAt(created_at);
	this->setUpdatedAt(updated_at);
	expenditure_id++;
}

// I/O 
std::istream & operator >> (std::istream& console, Expenditure& e) {
	char buffer[100];
	double amtbuffer;

	std::cout << "\nType: ";
	console >> buffer;
	e.setType(buffer);

	std::cout << "\nCategory: ";
	console >> buffer;
	e.setCategory(buffer);

	std::cout << "\nName: ";
	console >> buffer;
	e.setName(buffer);

	std::cout << "\nNote: ";
	console >> buffer;
	e.setNote(buffer);

	std::cout << "\nAmount: ";
	console >> amtbuffer;
	e.setAmount(amtbuffer);

	Datetime now = Datetime();
	e.setUpdatedAt(now);
	return console;
};

std::ostream & operator << (std::ostream& console, Expenditure& e) {
	console << e.getType() << "  |  " << e.getCategory() << "  |  " << e.getName() << "  |  " << e.getNote() << "  |  " << e.getAmount() << "  |  " << e.getCreatedAt() << "  |  " << e.getUpdatedAt() << "\n";
	return console;
};

std::ifstream & operator >> (std::ifstream& file, Expenditure& e) {
	/* Solution inspired by: https://stackoverflow.com/questions/9778806/serializing-a-class-with-a-pointer-in-c */
	size_t sizebuff;
	char   mark;
	char *result;
	double a;
	Datetime d;
	file >> sizebuff >> mark;
	if (!file || mark != '%')
	{
		throw std::exception("Invalid file format! Aborting...");
	}
	result = new char[sizebuff + 1]();
	file.read(result, sizebuff);
	e.setType(result);
	delete[] result;

	file >> sizebuff >> mark;
	if (!file || mark != '%')
	{
		throw std::exception("Invalid file format! Aborting...");
	}
	result = new char[sizebuff + 1]();
	file.read(result, sizebuff);
	e.setCategory(result);
	delete[] result;

	file >> sizebuff >> mark;
	if (!file || mark != '%')
	{
		throw std::exception("Invalid file format! Aborting...");
	}
	result = new char[sizebuff + 1]();
	file.read(result, sizebuff);
	e.setName(result);
	delete[] result;

	file >> sizebuff >> mark;
	if (!file || mark != '%')
	{
		throw std::exception("Invalid file format! Aborting...");
	}
	result = new char[sizebuff + 1]();
	file.read(result, sizebuff);
	e.setNote(result);
	delete[] result;

	file >> a;
	e.setAmount(a);
	file >> d;
	e.setCreatedAt(d);
	file >> d;
	e.setUpdatedAt(d);

};

std::ofstream & operator << (std::ofstream& file, Expenditure& e) {
	size_t sizebuff;
	sizebuff = strlen(e.getType());
	file << sizebuff << "%" << e.getType() << std::endl;
	sizebuff = strlen(e.getCategory());
	file << sizebuff << "%" << e.getCategory() << std::endl;
	sizebuff = strlen(e.getName());
	file << sizebuff << "%" << e.getName() << std::endl;
	sizebuff = strlen(e.getNote());
	file << sizebuff << "%" << e.getNote() << std::endl;

	/* The rest is written normally */
	file << e.getAmount() << std::endl;
	file << e.getCreatedAt() << std::endl;
	file << e.getUpdatedAt() << std::endl;

	return file;
};

// Destructor for class Expenditure
Expenditure::~Expenditure() {
};

/* ====================================== Implementation for class Income ====================================== */

// Getters/Setters for class Income
int Income::getId() {
	return this->id;
};

// Default constructor for class Income
Income::Income() : id(income_id) {
	this->setType("N/A");
	this->setCategory("N/A");
	this->setName("income");
	this->setNote("-");
	this->setAmount(0);
	Datetime now = Datetime();
	this->setCreatedAt(now);
	this->setUpdatedAt(now);
	income_id++;
};

// Copy constructor
Income::Income(const Income & income) : Transaction(income), id(income_id) {
	income_id++;
};

Income::Income(char *type, char *category, char *name, char *note, double amount, Datetime created_at, Datetime updated_at) : id(income_id) {
	this->setType(type);
	this->setCategory(category);
	this->setName(name);
	this->setNote(note);
	this->setAmount(amount);
	this->setCreatedAt(created_at);
	this->setUpdatedAt(updated_at);
	income_id++;
};

// Destructor for class Income
Income::~Income() {
};

// I/O 
std::istream & operator >> (std::istream& console, Income& i) {
	char buffer[100];
	double amtbuffer;

	std::cout << "\nType: ";
	console >> buffer;
	i.setType(buffer);

	std::cout << "\nCategory: ";
	console >> buffer;
	i.setCategory(buffer);

	std::cout << "\nName: ";
	console >> buffer;
	i.setName(buffer);

	std::cout << "\nNote: ";
	console >> buffer;
	i.setNote(buffer);

	std::cout << "\nAmount: ";
	console >> amtbuffer;
	i.setAmount(amtbuffer);

	Datetime now = Datetime();
	i.setUpdatedAt(now);
	return console;
};

std::ostream & operator << (std::ostream& console, Income& i) {
	console << i.getType() << "  |  " << i.getCategory() << "  |  " << i.getName() << "  |  " << i.getNote() << "  |  " << i.getAmount() << "  |  " << i.getCreatedAt() << "  |  " << i.getUpdatedAt() << "\n";
	return console;
};

std::ifstream & operator >> (std::ifstream& file, Income& i) {
	size_t sizebuff;
	char   mark;
	char *result;
	double a;
	Datetime d;
	file >> sizebuff >> mark;
	if (!file || mark != '%')
	{
		throw std::exception("Invalid file format! Aborting...");
	}
	result = new char[sizebuff + 1]();
	file.read(result, sizebuff);
	i.setType(result);
	delete[] result;

	file >> sizebuff >> mark;
	if (!file || mark != '%')
	{
		throw std::exception("Invalid file format! Aborting...");
	}
	result = new char[sizebuff + 1]();
	file.read(result, sizebuff);
	i.setCategory(result);
	delete[] result;

	file >> sizebuff >> mark;
	if (!file || mark != '%')
	{
		throw std::exception("Invalid file format! Aborting...");
	}
	result = new char[sizebuff + 1]();
	file.read(result, sizebuff);
	i.setName(result);
	delete[] result;

	file >> sizebuff >> mark;
	if (!file || mark != '%')
	{
		throw std::exception("Invalid file format! Aborting...");
	}
	result = new char[sizebuff + 1]();
	file.read(result, sizebuff);
	i.setNote(result);
	delete[] result;

	file >> a;
	i.setAmount(a);
	file >> d;
	i.setCreatedAt(d);
	file >> d;
	i.setUpdatedAt(d);
	return file;
};

std::ofstream & operator << (std::ofstream& file, Income& i) {
	size_t sizebuff;
	sizebuff = strlen(i.getType());
	file << sizebuff << "%" << i.getType() << std::endl;
	sizebuff = strlen(i.getCategory());
	file << sizebuff << "%" << i.getCategory() << std::endl;
	sizebuff = strlen(i.getName());
	file << sizebuff << "%" << i.getName() << std::endl;
	sizebuff = strlen(i.getNote());
	file << sizebuff << "%" << i.getNote() << std::endl;

	/* The rest is written normally */
	file << i.getAmount() << std::endl;
	file << i.getCreatedAt() << std::endl;
	file << i.getUpdatedAt() << std::endl;
	return file;
};

/* ====================================== Implementation for class Account ====================================== */

// Getters/Setters for class Account
int Account::getId() {
	return this->id;
};

char * Account::getHolderName() {
	return this->holder_name;
};

int Account::getTotalExpenditures() {
	return this->total_expenditures;
}

int Account::getTotalIncomes() {
	return this->total_incomes;
}


Income * Account::getIncomes() {
	return this->incomes;
};


Expenditure * Account::getExpenditures() {
	return this->expenditures;
};

double Account::getBottomLineAtCurrentDate() {
	double sum = 0;
	int elen = this->getTotalExpenditures();
	int ilen = this->getTotalIncomes();

	for (int i = 0; i < ilen; i++) {
		sum += this->incomes[i].getAmount();
	}

	for (int i = 0; i < elen; i++) {
		sum -= this->expenditures[i].getAmount();
	}

	return sum;
};

void Account::setHolderName(char * name) {
	int len = strlen(name);
	this->holder_name = new char[len + 1];
	strcpy(this->holder_name, name);
};

void Account::setTotalExpenditures(int t) {
	this->total_expenditures = t;
};

void Account::setTotalIncomes(int t) {
	this->total_incomes = t;
};

void Account::setIncomes(Income * incomes, int len) {
	this->setTotalIncomes(0);
	this->incomes = new Income[len];
	for (int i = 0; i < len; i++) {
		this->incomes[i] = incomes[i];
		this->total_incomes++;
	}
};

void Account::setExpenditures(Expenditure * expenditures, int len) {
	this->setTotalExpenditures(0);
	this->expenditures = new Expenditure[len];
	for (int i = 0; i < len; i++) {
		this->expenditures[i] = expenditures[i];
		this->total_expenditures++;
	}
};


// Constructors
Account::Account() : id(account_id) {
	this->setHolderName("N/A");
	this->setTotalIncomes(0);
	this->setTotalExpenditures(0);
	Income *incptr = NULL;
	Expenditure *exptr = NULL;
	this->incomes = incptr;
	this->expenditures = exptr;
	account_id++;
};


Account::Account(const Account & account) : id(account_id) {
	holder_name = new char[strlen(account.holder_name) + 1];
	strcpy(holder_name, account.holder_name);

	this->setTotalExpenditures(account.total_expenditures);
	this->setTotalIncomes(account.total_incomes);

	this->setIncomes(account.incomes, account.total_incomes);
	this->setExpenditures(account.expenditures, account.total_expenditures);
	account_id++;
};


Account::Account(char *name, Income * incomes, int incomelen, Expenditure * expenditures, int expendlen) : id(account_id) {
	this->setHolderName(name);
	this->setTotalExpenditures(expendlen);
	this->setTotalIncomes(incomelen);
	this->setIncomes(incomes, incomelen);
	this->setExpenditures(expenditures, expendlen);
	account_id++;
};


// utility methods
void Account::incomecpy(Income *dst, Income*src, int len) {
	for (int i = 0; i < len; i++) {
		dst[i] = src[i];
	}
};


void Account::expenditurecpy(Expenditure *dst, Expenditure *src, int len) {
	for (int i = 0; i < len; i++) {
		dst[i] = src[i];
	}
};

// methods for adding, removing or editing incomes/expenditures
void Account::addIncome() {
	// save incomes in temp array, allocate space for one more and copy
	Income *temp = new Income[this->total_incomes + 1];
	this->incomecpy(temp, this->incomes, this->total_incomes);
	Income newIncome;
	std::cin >> newIncome;
	temp[this->total_incomes] = newIncome;
	this->setTotalIncomes(this->total_incomes + 1);
	this->setIncomes(temp, this->total_incomes);
};


void Account::addExpenditure() {
	// same as above
	Expenditure *temp = new Expenditure[this->total_incomes + 1];
	this->expenditurecpy(temp, this->expenditures, this->total_expenditures);
	Expenditure newExpenditure;
	std::cin >> newExpenditure;
	temp[this->total_expenditures] = newExpenditure;
	this->setTotalExpenditures(this->total_expenditures + 1);
	this->setExpenditures(temp, this->total_expenditures);
};


void Account::deleteIncome(char *query) {
	// save in temp array except for those found by query, reallocate and copy
	int foundAt[100];
	int k = 0;
	for (int i = 0; i < this->total_incomes; i++) {
		if (strcmp(this->incomes[i].getName(), query) == 0) {
			foundAt[k] = i;
			k++;
		}
		else if (strcmp(this->incomes[i].getCategory(), query) == 0) {
			foundAt[k] = i;
			k++;
		}
		else if (strcmp(this->incomes[i].getType(), query) == 0) {
			foundAt[k] = i;
			k++;
		}
	}

	Income *temp = new Income[this->total_incomes - k];
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (i != foundAt[j]) {
				temp[i] = this->incomes[i];
			}
		}
	}

	if (k > 0) {
		this->setTotalIncomes(this->total_incomes - k);
		this->setIncomes(temp, this->total_incomes);
		std::cout << "Deleted " << k << " items containing term `" << query << "`.\n";
	}
	else {
		std::cout << "Term `" << query << "` not found.\n";
	}
};


void Account::deleteExpenditure(char *query) {
	// same
	int foundAt[100];
	int k = 0;
	for (int i = 0; i < this->total_expenditures; i++) {
		if (strcmp(this->expenditures[i].getName(), query) == 0) {
			foundAt[k] = i;
			k++;
		}
		else if (strcmp(this->expenditures[i].getCategory(), query) == 0) {
			foundAt[k] = i;
			k++;
		}
		else if (strcmp(this->expenditures[i].getType(), query) == 0) {
			foundAt[k] = i;
			k++;
		}
	}

	Expenditure *temp = new Expenditure[this->total_expenditures - k];
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (i != foundAt[j]) {
				temp[i] = this->expenditures[i];
			}
		}
	}

	if (k > 0) {
		this->setTotalExpenditures(this->total_expenditures - k);
		this->setExpenditures(temp, this->total_expenditures);
		std::cout << "Deleted " << k << " items containing term `" << query << "`.\n";
	}
	else {
		std::cout << "Term `" << query << "` not found.\n";
	}
};


void Account::editIncome(char *query) {
	this->deleteIncome(query);
	std::cout << "\nNew values:\n";
	this->addIncome();
};


void Account::editExpenditure(char *query) {
	this->deleteExpenditure(query);
	std::cout << "\nNew values:\n";
	this->addExpenditure();
};


// I/O 
std::istream & operator >> (std::istream& console, Account& a) {
	std::cout << "Holder name: ";
	char buff[100];
	console >> buff;
	a.holder_name = new char[strlen(buff) + 1];
	strcpy(a.holder_name, buff);

	std::cout << "\nHow many income items? ";
	std::cin >> a.total_incomes;
	std::cout << "\nHow many expenditure items? ";
	std::cin >> a.total_expenditures;

	a.incomes = new Income[a.total_incomes];
	a.expenditures = new Expenditure[a.total_expenditures];

	std::cout << "Input incomes: \n";
	for (int i = 0; i < a.total_incomes; i++) {
		std::cin >> a.incomes[i];
	};

	std::cout << "Input expenditures: \n";
	for (int i = 0; i < a.total_expenditures; i++) {
		std::cin >> a.expenditures[i];
	};

	return console;
};

std::ostream & operator << (std::ostream& console, Account& a) {
	int i, j;
	std::cout << "Account no." << a.account_id << "\n" << "User: " << a.holder_name << "\n";
	std::cout << "Incomes:\n";
	for (i = 0; i < a.total_incomes; i++) {
		std::cout << a.incomes[i];
	}
	std::cout << "Expenditures:\n";
	for (j = 0; j < a.total_expenditures; j++) {
		std::cout << a.expenditures[j];
	}
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Bottom line: " << a.getBottomLineAtCurrentDate() << "\n";
	return console;
};

std::ifstream & operator >> (std::ifstream& file, Account& a) {
	size_t sizebuff;
	char mark;
	char *result;

	file >> a.total_expenditures;
	file >> a.total_incomes;

	file >> sizebuff >> mark;
	if (!file || mark != '%')
	{
		throw std::exception("Invalid file format! Aborting...");
	}
	result = new char[sizebuff + 1]();
	file.read(result, sizebuff);

	a.incomes = new Income[a.total_incomes];
	a.expenditures = new Expenditure[a.total_expenditures];

	for (int i = 0; i < a.total_incomes; i++) {
		file >> a.incomes[i];
	}

	for (int i = 0; i < a.total_expenditures; i++) {
		file >> a.expenditures[i];
	}

	return file;
};

std::ofstream & operator << (std::ofstream& file, Account& a) {

	size_t sizebuff;

	file << a.total_expenditures << std::endl;
	file << a.total_incomes << std::endl;

	sizebuff = strlen(a.holder_name);
	file << sizebuff << "%" << a.holder_name << std::endl;

	for (int i = 0; i < a.total_incomes; i++) {
		file << a.incomes[i] << std::endl;
	}

	for (int i = 0; i < a.total_expenditures; i++) {
		file << a.expenditures[i] << std::endl;
	}

	return file;
};

Account & Account::operator=(const Account & other) {
	this->holder_name = new char[strlen(other.holder_name) + 1];
	strcpy(this->holder_name, other.holder_name);
	this->total_expenditures = other.total_expenditures;
	this->total_incomes = other.total_incomes;
	this->expenditures = new Expenditure[other.total_expenditures];
	this->expenditurecpy(this->expenditures, other.expenditures, other.total_expenditures);
	this->incomes = new Income[other.total_incomes];
	this->incomecpy(this->incomes, other.incomes, other.total_incomes);
	return *this;
};

// Destructor
Account::~Account() {
	if (this->holder_name)
		delete[] this->holder_name;
	if (this->incomes)
		delete[] this->incomes;
	if (this->expenditures)
		delete[] this->expenditures;
};

/* ====================================== Implementation for class Report ====================================== */

// Getters/Setters
void Report::setAccount(Account a) {
	this->account = a;
};


// Constructors
Report::Report() {
	Account a = Account();
	this->setAccount(a);
};

Report::Report(const Report & r) {
	this->setAccount(r.account);
};

Report::Report(Account a) {
	this->setAccount(a);
};

// Destructor
Report::~Report() {
	// 
};

double Report::getTotalExpendituresForDate(Datetime d) {
	std::cout << "Expenditures for date " << d << ":\n";
	int len = this->account.getTotalExpenditures();
	double total = 0;
	Expenditure *temp = new Expenditure[len];
	this->account.expenditurecpy(temp, this->account.getExpenditures(), this->account.getTotalExpenditures());
	for (int i = 0; i < len; i++) {
		if (temp[i].getCreatedAt() == d) {
			std::cout << temp[i];
			total += temp[i].getAmount();
		}
	}

	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Total:\t" << total << "\n";
	return total;
};

double Report::getTotalExpendituresForItem(char *item) {

	std::cout << "Expenditures for item `" << item << "`:\n";
	int len = this->account.getTotalExpenditures();
	double total = 0;
	bool flag = false;
	Expenditure *temp = new Expenditure[len];
	this->account.expenditurecpy(temp, this->account.getExpenditures(), this->account.getTotalExpenditures());
	for (int i = 0; i < len; i++) {
		char *buff = new char[strlen(temp[i].getName() + 1)];
		strcpy(buff, temp[i].getName());

		if (strcmp(buff, item) == 0) {
			std::cout << temp[i];
			total += temp[i].getAmount();
			flag = true;
		}
	}

	if (flag) {
		std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
		std::cout << "Total:\t" << total << "\n";
		return total;
	}
	else {
		std::cout << "\nItem `" << item << "` not found.\n";
		return 0;
	}
};

double Report::getTotalExpendituresForAllMonths(int year) {

	std::cout << "Expenditures for all months in year " << year << ":\n";
	std::cout << "Month\t |\tAmount\n";
	double months[12];
	char mnames[12][20] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	int len = this->account.getTotalExpenditures();
	double total = 0;

	for (int i = 0; i < 12; i++) {
		months[i] = 0;
	}

	Expenditure *temp = new Expenditure[len];
	this->account.expenditurecpy(temp, this->account.getExpenditures(), this->account.getTotalExpenditures());
	for (int i = 0; i < len; i++) {
		if (temp[i].getCreatedAt().getYear() == year) {
			for (int j = 0; j < 12; j++) {
				if (temp[i].getCreatedAt().getMonth() == j + 1) {
					total += temp[i].getAmount();
					months[j] += temp[i].getAmount();
				}
			}
		}
	}

	for (int i = 0; i < 12; i++) {
		std::cout << mnames[i] << ":\t\t" << months[i] << "\n";
	}

	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Total:\t" << total << "\n";
	return total;
};


double Report::getTotalExpendituresForAllYears() {

	std::cout << "Expenditures for all years :\n";
	std::cout << "Year |\tAmount\n";
	int len = this->account.getTotalExpenditures();
	double total = 0;
	int *years = new int[len];
	int *uniques = new int[len];
	int uniquelen = 0;
	Expenditure *temp = new Expenditure[len];

	this->account.expenditurecpy(temp, this->account.getExpenditures(), this->account.getTotalExpenditures());
	for (int i = 0; i < len; i++) {
		years[i] = temp[i].getCreatedAt().getYear();
	}

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (years[i] < years[j]) {
				int tmp = years[i];
				years[i] = years[j];
				years[j] = tmp;
			}
		}
	}

	for (int i = 1; i < len - 1; i++) {
		if (years[i] != years[i + 1] || years[i] != years[i - 1]) {
			uniques[uniquelen] = years[i];
			uniquelen++;
		}
	}

	/* a quick hack because i noticed this does not work if you only have one expenditure */
	if (uniquelen < 1) {
		uniquelen = 1;
	}

	double *uniquevals = new double[uniquelen];

	for (int i = 0; i < uniquelen; i++) {
		uniquevals[i] = 0;
	}

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < uniquelen; j++) {
			if (temp[i].getCreatedAt().getYear() == uniques[j]) {
				uniquevals[j] += temp[i].getAmount();
				total += temp[i].getAmount();
			}
		}
	}

	/* a quick hack because i noticed this does not work if you only have one expenditure */
	if (len == 1) {
		uniques[0] = years[0];
		uniquevals[0] = temp[0].getAmount();
		total = temp[0].getAmount();
	}

	for (int i = 0; i < uniquelen; i++) {
		std::cout << uniques[i] << " |\t " << uniquevals[i] << "\n";
	}

	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Total:\t" << total << "\n";

	delete[] uniques; delete[] uniquevals; delete[] years;
	return total;
};


double Report::getAverageExpendituresForCategory(char *category) {
	std::cout << "Average expenditure for category `" << category << "`:\n";
	int len = this->account.getTotalExpenditures();
	double total = 0;
	bool flag = false;
	int noOfItems = 0;
	Expenditure *temp = new Expenditure[len];
	this->account.expenditurecpy(temp, this->account.getExpenditures(), this->account.getTotalExpenditures());
	for (int i = 0; i < len; i++) {
		char *buff = new char[strlen(temp[i].getCategory() + 1)];
		strcpy(buff, temp[i].getCategory());

		if (strcmp(buff, category) == 0) {
			total += temp[i].getAmount();
			noOfItems++;
			flag = true;
		}
	}

	double avg = total / noOfItems;
	if (flag) {
		std::cout << "- per item :\t" << avg << "\n";
		std::cout << "- total :\t" << total << "\n";
		return avg;
	}
	else {
		std::cout << "\nCategory `" << category << "` not found.\n";
		return 0;
	}
};


double Report::getTotalExpendituresForCategory(char *category) {
	std::cout << "Expenditures for category `" << category << "`:\n";
	int len = this->account.getTotalExpenditures();
	double total = 0;
	bool flag = false;
	Expenditure *temp = new Expenditure[len];
	this->account.expenditurecpy(temp, this->account.getExpenditures(), this->account.getTotalExpenditures());

	for (int i = 0; i < len; i++) {
		char *buff = new char[strlen(temp[i].getCategory() + 1)];
		strcpy(buff, temp[i].getCategory());

		if (strcmp(buff, category) == 0) {
			std::cout << temp[i];
			total += temp[i].getAmount();
			flag = true;
		}
	}

	if (flag) {
		std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
		std::cout << "Total:\t" << total << "\n";
		return total;
	}
	else {
		std::cout << "\nCategory `" << category << "` not found.\n";
		return 0;
	}
};


/* =============================== Implementation for class Util (just a wrapper for main() functions) ================================ */

/* demo() is a demonstration of basic functionality */
void Util::demo() {
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
};

/* menu creates a menu for user to navigate through the functionality of the program */
void Util::menu() {
	/* logo :) */
	std::cout
		<< "  _____      _ _      _                         _           _   \n"
		<< " | ____|_ __(_) | __ ( )  ___   _ __  _ __ ___ (_) ___  ___| |_ \n"
		<< " |  _| | '__| | |/ / |/  / __| | '_ \\| '__/ _ \\| |/ _ \\/ __| __|\n"
		<< " | |___| |  | |   <      \\__ \\ | |_) | | | (_) | |  __/ (__| |_ \n"
		<< " |_____|_|  |_|_|\__\\     |___/ | .__/|_|  \\___// |\\___|\\___|\\__|\n"
		<< "                               |_|           |__/               \n\n";

	/* menu loop */
	int choice;
	do {
		std::cout << "1. Create new user.\n"
			<< "2. Select existing user.\n"
			<< "3. Display report.\n"
			<< "4. Exit.\n";
		std::cin >> choice;
		if (choice == 1) {
			int choice2;
			Account acc;
			std::cin >> acc;
			std::cout << "1. Report now.\n2. Save to disk.\n3. Back.\n";
			std::cin >> choice2;
			if (choice2 == 1) {
				/* create reports */
				Report r;
				r.setAccount(acc);
				std::cout << "What kind of report do you want to see?\n"
					<< "1. Total expenditures for date.\n"
					<< "2. Total expenditures for item.\n"
					<< "3. Total expenditures for all months.\n"
					<< "4. Total expenditures for all years.\n"
					<< "5. Exit.\n";

				int choice3;
				std::cin >> choice3;

				Datetime d;

				if (choice3 == 1) {
					std::cout << "Enter query date: ";
					std::cin >> d;
					r.getTotalExpendituresForDate(d);
				}
				else if (choice3 == 2) {
					char buff[100];
					std::cout << "Enter query term: ";
					std::cin >> buff;
					std::cout << "\n";
					r.getTotalExpendituresForItem(buff);
				}
				else if (choice3 == 3) {
					int year;
					std::cout << "Enter query year: ";
					std::cin >> year;
					r.getTotalExpendituresForAllMonths(year);
				}
				else if (choice3 == 4) {
					r.getTotalExpendituresForAllYears();
				}
				else {
					exit(0);
				}
			}
			else if (choice2 == 2) {
				/* write this stuff to file */
				std::ofstream of;
				char fname[100];
				strcpy(fname, acc.getHolderName());
				strcat(fname, ".bin");
				of.open(fname, std::ios::out | std::ios::app | std::ios::binary);
				of << acc;
				of.close();
			}
			else {
				choice = 1;
			}
		}
		else if (choice == 2) {
			std::cout << "Enter the name of the user (hint: type `example` to see a demonstration): ";
			char name[100], fname[100];
			std::cin >> name;
			strcpy(fname, name);
			strcat(fname, ".bin");

			std::ifstream ifs;
			ifs.open(fname, std::ios::in | std::ios::binary);
			if (!ifs) {
				std::cout << "Unknown user `" << name << "`.\n";
				choice = 1;
			}
			else {
				Account acc;
				try {
					ifs >> acc;
				}
				catch (std::exception & e) {
					std::cerr << e.what();
				}
				acc.setHolderName(name);
				/* update or delete records */
				std::cout << "What do you want to do?\n1. Modify record.\n2. Delete record.\n3. Add record.\n4. Delete account.\n5. Output all.\n6.Back.\n";
				int choice4;
				std::cin >> choice4;

				if (choice4 == 1) {
					std::cout << "1. Expenditure\n2. Income\n";
					int choice5;
					std::cin >> choice5;
					std::cout << "Enter your query: ";
					char query[100];
					std::cin >> query;
					std::cout << "\n";
					if (choice5 == 1) {
						acc.editExpenditure(query);
					}
					else {
						acc.editIncome(query);
					}

					std::ofstream of;
					char fname[100];
					strcpy(fname, acc.getHolderName());
					strcat(fname, ".bin");
					of.open(fname, std::ios::out | std::ios::binary);
					of << acc;
					of.close();
				}
				else if (choice4 == 2) {
					std::cout << "1. Expenditure\n2. Income\n";
					int choice5;
					std::cin >> choice5;
					std::cout << "Enter your query: ";
					char query[100];
					std::cin >> query;
					std::cout << "\n";
					if (choice5 == 1) {
						acc.deleteExpenditure(query);
					}
					else {
						acc.deleteIncome(query);
					}
					/* this stuff REALLY should be a function... */
					std::ofstream of;
					char fname[100];
					strcpy(fname, acc.getHolderName());
					strcat(fname, ".bin");
					of.open(fname, std::ios::out | std::ios::binary);
					of << acc;
					of.close();
				}
				else if (choice4 == 3) {
					std::cout << "1. Expenditure\n2. Income\n";
					int choice5;
					std::cin >> choice5;
					if (choice5 == 1) {
						acc.addExpenditure();
						std::ofstream of;
						char fname[100];
						strcpy(fname, acc.getHolderName());
						strcat(fname, ".bin");
						of.open(fname, std::ios::out | std::ios::binary);
						of << acc;
						of.close();
					}
					else {
						acc.addIncome();
						std::cout << acc;
						std::ofstream of;
						char fname[100];
						strcpy(fname, acc.getHolderName());
						strcat(fname, ".bin");
						of.open(fname, std::ios::out | std::ios::binary);
						of << acc;
						of.close();
					}
				}
				else if (choice4 == 4) {
					std::cout << "Are you sure? This action cannot be undone! y/n ";
					char ans;
					std::cin >> ans;
					if (ans = 'y') {
						if (remove(fname) != 0) {
							perror("An error has occurred");
						}
						else {
							std::cout << "Account `" << name << "` deleted.\n";
						}
					}
					else {
						choice = 2;
						break;
					}
				}
				else if (choice4 == 5) {
					std::cout << acc;
				}
				else {
					choice = 2;
					break;
				}
			}
			ifs.close();
		}
		else if (choice == 3) {
			std::cout << "Enter the name of the user: ";
			char name[100], fname[100];
			std::cin >> name;
			strcpy(fname, name);
			strcat(fname, ".bin");

			std::ifstream ifs;
			ifs.open(fname, std::ios::in | std::ios::binary);
			if (!ifs) {
				std::cout << "Unknown user `" << name << "`.\n";
				choice = 1;
			}
			else {
				Account acc;
				try {
					ifs >> acc;
				}
				catch (std::exception & e) {
					std::cerr << e.what();
				}
				ifs.close();
				acc.setHolderName(name);
				std::cout << "User is now " << acc.getHolderName() << ". What do you want to do?\n"
					<< "1. Total expenditures for date.\n"
					<< "2. Total expenditures for item.\n"
					<< "3. Total expenditures for all months.\n"
					<< "4. Total expenditures for all years.\n"
					<< "5. Exit.\n";
				Report r;

				r.setAccount(acc);

				int choice3;
				std::cin >> choice3;

				Datetime d;

				if (choice3 == 1) {
					std::cout << "Enter query date: ";
					std::cin >> d;
					r.getTotalExpendituresForDate(d);
				}
				else if (choice3 == 2) {
					char buff[100];
					std::cout << "Enter query term: ";
					std::cin >> buff;
					std::cout << "\n";
					r.getTotalExpendituresForItem(buff);
				}
				else if (choice3 == 3) {
					int year;
					std::cout << "Enter query year: ";
					std::cin >> year;
					r.getTotalExpendituresForAllMonths(year);
				}
				else if (choice3 == 4) {
					r.getTotalExpendituresForAllYears();
				}
				else {
					exit(0);
				}
			}
		}
	} while (choice != 4);

	/* TODO:: move the file i/o into separate methods */
}
