#include "appCashier.h"
#include "appIdle.h"


int main()
{	
	CashierDb cashDb;
	const unsigned char* name;

	int cashierNo = cashDb.appCashierLogin();
	
	if (cashierNo != 0) 
		appIdleLoop(cashDb.selectCashierNameValue(cashierNo));
	else 
		return 0;
	
}

