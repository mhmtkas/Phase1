#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "sqlite/sqlite3.h"
#include <fstream>
#include <string>
#include <stdio.h> 
#include <sstream>

using namespace std;

class CashierDb 
{

	public:

		int rc;
		sqlite3* db;
		sqlite3_stmt* stmt;
		char* err;

		

		CashierDb();
		static bool check_number(string str);

		int selectCashierPswValue(int cashierNo);
		int* selectCashierIdValues();
		const unsigned char* selectCashierNameValue(int no);
		int checkCashierDb();
		int insertValues();
		int appCashierLogin();
		int checkCashierLogin();
};








