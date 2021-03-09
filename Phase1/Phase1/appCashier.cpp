#include "appCashier.h"



CashierDb::CashierDb(){}	

bool CashierDb::check_number(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}

string ReplaceString(std::string subject, const std::string& search, // using for 
	const std::string& replace)										  //splitting lines 
{																		//to get values
	size_t pos = 0;
	while((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
} 

int lineCount()                        // counting line in Cashier.dat
{
	ifstream infile("Cashier.dat");
	char c;
	int count = 0;

	if (infile.is_open()) {

		while (infile.get(c)) {
			if (c == '\n')
				count++;
		}
		infile.close();
	}
	return count+1;
} 

int CashierDb::checkCashierDb()        // creating table in the cashregister.db
{
	
	sqlite3_open("cashregister.db", &db);
	rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS cashier(cashierId INT,name varchar(100), password INT)", NULL, NULL, &err);
	
	if (rc != SQLITE_OK) { cout << "error: " << err << endl; return 0; }
	else { return 1; }

} 

int CashierDb::insertValues()              //taking values from Cashier.dat and  
{										   //insert to cashregister.db
	
	ifstream readFile("Cashier.dat");
	string line = "";
	string values[4];
	string query;


	while (getline(readFile, line))
	{
		int i = 0;
		cout << line << endl;
		line = ReplaceString(line, ", ", " ");
		stringstream ssin(line);
		while (ssin.good() && i < 4) {
			ssin >> values[i];
			++i;
		}
		query = "INSERT INTO cashier VALUES(" + values[0] + ", '" + values[1] + " " + values[2] + "'," + values[3] + ")";
		cout << query << endl;
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);	
		if (rc != SQLITE_OK) { cout << "error: " << err << endl; return 0; }
		
	}
	readFile.close();
	return 1;
}

const unsigned char* CashierDb::selectCashierNameValue(int no)  //selecting name values
{
	string query;
	const unsigned char *cashierName=NULL;
	int psw = 0;
	query = "SELECT name, cashierId FROM cashier WHERE cashierId ='" + to_string(no) + "'";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	if(sqlite3_step(stmt) != SQLITE_DONE)
	{
		cashierName = sqlite3_column_text(stmt, 0);
	}
	return cashierName;
}

int CashierDb::selectCashierPswValue(int cashierNo)    //selecting password values
{
	string query;
	int psw=0;
	query = "SELECT password, cashierId FROM cashier WHERE cashierId ='" + to_string(cashierNo)+ "'";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	if (sqlite3_step(stmt) != SQLITE_DONE)
		psw = sqlite3_column_int(stmt, 0);
	return psw;
}	

int* CashierDb::selectCashierIdValues()    //selecting all ýd values to check user login
{
	sqlite3_prepare_v2(db, "SELECT cashierId FROM cashier", -1, &stmt, 0);
	int cashierID,valueCount;
	valueCount = lineCount();
	static int cashierIdArr[10];
	int i = 0;
	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		cashierID = sqlite3_column_int(stmt, 0);
		cashierIdArr[i] = cashierID;
		i=i+1;
	}
	return cashierIdArr;
}

bool existFile(const string& name)  //checking cashregister.db exist or not
{
	ifstream f(name.c_str());
	return f.good();
}

int CashierDb::appCashierLogin()    //the function that login process happen
{
	
	if (existFile("cashregister.db"))
	{
		checkCashierDb();
	}
	else
	{
		checkCashierDb();
		insertValues();
	}
	int control = 0, choice=0;
	string temp;
	control = checkCashierLogin();
	while (!control)
	{
		
		cout << "1- TEKRAR DENE" << endl;
		cout << "2- CIKIS" << endl;
		cout << "Seciminizi Yapiniz: ";
		cin >> temp;
		if (check_number(temp))
			choice = stoi(temp);
		else {
			cout << "Yanlis karakter girildi." << endl;
			continue;
		}
		if (choice == 1) 
		{
			control = checkCashierLogin();
		}
		else if (choice == 2)
		{
			return 0;
		}
		else
		{
			cout << "Yanlis bir giris yapildi." << endl;
		}
	}
	return control;
}

int CashierDb::checkCashierLogin()   //the function that checking user login succesfull or not
{
	string temp;
	int cashierNoInput;
	int cashierPsw,cashierNo=0;
	int * p;
	cout << "Kasiyer Numarasi Giriniz: ";
	cin >> temp;  
	if (check_number(temp))
		cashierNoInput = stoi(temp);
	else {
		cout << "Yanlis karakter girildi." << endl;
		return 0;
	}
	
	p = selectCashierIdValues(); //taking all id values from cashregister.db
	
	for (int i = 0; i < sizeof(*p) + 1; i++)
	{
		if (cashierNoInput == *(p + i))
		{
			cashierNo = cashierNoInput;
			break;
		}
	}
	if (cashierNo == 0) 
	{
		cout << "Kasiyer Bulunamadi." << endl;
		return 0;
	}
	cout << "Sifre Giriniz: ";
	cin >> cashierPsw;

	if (cashierPsw == selectCashierPswValue(cashierNo))
	{
		if (cashierNo!=0) return cashierNo;
	}
	else
	{
		cout << "Sifre Yanlis Girildi." << endl;
		return 0;
	}

}

