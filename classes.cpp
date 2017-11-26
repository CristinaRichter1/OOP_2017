#include <windows.h>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "classes.h"

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
	} else {
		throw std::exception("Invalid input, should be a valid year.");
	}
}

void Datetime::setMonth(int month) {
	if (month > 0 && month <= 12) {
		this->m = month;
	} else {
		throw std::exception("Invalid input, should be a valid month (between 1 and 12).");
	}
}

void Datetime::setDay(int day) {
	if (day > 0 && day <= 31) {
		this->d = day;
	} else {
		throw std::exception("Invalid input, should be a valid day (between 1 and 31).");
	}
}

void Datetime::setHour(int hour) {
	if (hour >= 0 && hour < 24) {
		this->h = hour;
	} else {
		throw std::exception("Invalid input, should be a valid hour of day (between 1 and 24).");
	}
}

void Datetime::setMin(int min) {
	if (min >= 0 && min < 60) {
		this->min = min;
	} else {
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
	long long int mins2 = (d2.y * 525600) + (d2.m * 43800 ) + (d2.d * 1440) + (d2.h * 60) + d2.min;
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

char * Transaction::getCategory(){
	return this->category;
};

char * Transaction::getName(){
	return this->name;
};

char * Transaction::getNote(){
	return this->note;
};

double Transaction::getAmount(){
	return (double) this->amount;
};

Datetime Transaction::getCreatedAt(){
	return this->created_at;
};

Datetime Transaction::getUpdatedAt(){
	return this->updated_at;
};

void Transaction::setType(char *type){
	int len = strlen(type);
	this->type = new char[len+1];
	strcpy(this->type, type);
};

void Transaction::setCategory(char *category){
	int len = strlen(category);
	this->category = new char[len+1];
	strcpy(this->category, category);
};

void Transaction::setName(char *name){
	int len = strlen(name);
	this->name = new char[len+1];
	strcpy(this->name, name);
};

void Transaction::setNote(char *note){
	int len = strlen(note);
	this->note = new char[len+1];
	strcpy(this->note, note);
};

void Transaction::setAmount(double amount){
	this->amount = (double) amount;
};

void Transaction::setCreatedAt(Datetime date){
	this->created_at = date;
};

void Transaction::setUpdatedAt(Datetime date){
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
	type = new char[strlen(other.type)+1];
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
	std::cout << "Destructor called\n";
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
Expenditure::Expenditure(const Expenditure & expenditure) : Transaction(expenditure), id(expenditure_id){
	/* Transaction exp = Transaction(expenditure);
	char *buffer = new char[strlen(exp.getType())+1];
	strcpy(buffer, exp.getType());
	this->setType(buffer);
	
	buffer = new char[strlen(exp.getCategory()) + 1];
	strcpy(buffer, exp.getCategory());
	this->setCategory(buffer);

	buffer = new char[strlen(exp.getName()) + 1];
	strcpy(buffer, exp.getName());
	this->setName(buffer);

	buffer = new char[strlen(exp.getNote()) + 1];
	strcpy(buffer, exp.getNote());
	this->setNote(buffer);

	this->setAmount(exp.getAmount());
	this->setCreatedAt(exp.getCreatedAt());
	this->setUpdatedAt(exp.getUpdatedAt());*/
	//*this = expenditure;
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
	// first, construct an obj of parent class
	/*Transaction inc = Transaction(income);
	// then set fields of child class
	this->setType(inc.getType());
	this->setCategory(inc.getCategory());
	this->setName(inc.getName());
	this->setNote(inc.getNote());
	this->setAmount(inc.getAmount());
	this->setCreatedAt(inc.getCreatedAt());
	this->setUpdatedAt(inc.getUpdatedAt());*/
	//*this = income;
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

	for (int i = 0; i < elen; i++) {
		sum += this->expenditures[i].getAmount();
	}

	for (int i = 0; i < ilen; i++) {
		sum += this->incomes[i].getAmount();
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

// I/O 
std::istream & operator >> (std::istream& console, Account& a) {
	std::cout << "Holder name: ";
	console >> a.holder_name;
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
	this->holder_name = new char[strlen(other.holder_name)+1];
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
		char *buff = new char[strlen(temp[i].getName()+1)];
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
	} else {
		std::cout << "\nItem `" << item << "` not found.\n";
		return 0;
	}
};

double Report::getTotalExpendituresForAllMonths(int year) {

	std::cout << "Expenditures for all months in year " << year << ":\n";
	std::cout << "Month\t |\tAmount\n";
	double months[12];
	char mnames[12][20] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
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

	for (int i = 1; i < len-1; i++) {
		if (years[i] != years[i+1] || years[i] != years[i-1]) {
			uniques[uniquelen] = years[i];
			uniquelen++;
		}
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
		char *buff = new char[strlen(temp[i].getCategory()+1)];
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
	} else {
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
		char *buff = new char[strlen(temp[i].getCategory()+1)];
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
	} else {
		std::cout << "\nCategory `" << category << "` not found.\n";
		return 0;
	}
};