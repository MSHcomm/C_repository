/*
 * main.c
 *
 *  Created on: Jul 19, 2022
 *      Author: msh20
 */

#include "Application/app.h"

/*******************************************************************************
 *                Module global variables declared                        *
 *******************************************************************************/

ST_cardData_t g_cardData = { "Mohamed Sayed Hussien" , "5594444590216702" , "05/25" };
ST_terminalData_t g_termData = { 0.00 , 5000.00 , "22/07/2022" };

 /* global variable for the index of current account client */
sint16_t g_index_DB = -1;

 /* global variable g_transaction Sequence Number in current  */
uint32_t g_TSN = 0;


/*
 * AccountsDB[MAX_ACCOUNT_DB] is Accounts DataBase in Server-side
 * global array of ST_accountsDB_t type for the valid accounts database in Bank server
 * This array has a maximum of 255 element/account data
 */
ST_accountsDB_t AccountsDB[MAX_ACCOUNT_DB] = {{10000.00,"5594444590216702"},
											  { 5000.25,"4276620041157847"},
											  { 4000.15,"1753015653082110"},
											  { 3000.00,"2793846231019186"},
											  { 2000.20,"4228052678334532"},
											  { 1550.15,"0974994342140791"},
											  { 7500.00,"0121327314376923"},
											  { 3820.25,"6022960103954075"},
											  { 3250.14,"9789064041664453"},
											  { 8800.88,"9784992035571992"},
											  { 6600.66,"2622424935357646"}};


/*
 * transDB[MAX_ACCOUNT_DB] is Transaction DataBase in Server-side
 * global array of ST_transaction_t type for the transactions database in Bank server
 * This array has a maximum of 255 element/account data
 */
ST_transaction_t transDB[MAX_ACCOUNT_DB]={0};

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("MSH - Payment System Project\n");
	printf("---   Terminal Data -  Max.Transaction = 5000.00   ---\n");

	 /***************************************************************************
	 * Test Case.1:       "Transaction approved user story"
	 * 					  valid and not expired card
	 * 					  withdraw an amount of money less than Terminal allowed
	 * 					  less than the amount in balance
	 * Expectation:		  Approved Process
	 ****************************************************************************/
//	 printf("\n---------        Test Case.1        ---------\n");
//	 printf("---        Transaction approved user story        ---\n");
//	 appStart();

	 /***************************************************************************
	 * Test Case.2:       "Exceed the maximum amount user story"
	 * 					  valid and not expired card
	 * 					  withdraw an amount of money exceeds the Terminal allowed
	 *
	 * Expectation:		  Declined Process
	 ****************************************************************************/
//	 printf("\n---------        Test Case.2        ---------\n");
//	 printf("---        Exceed the maximum amount user story        ---\n");
//	 appStart();

	 /***************************************************************************
	 * Test Case.3:       "Insufficient fund user story"
	 * 					  valid and not expired card
	 * 					  withdraw an amount of money less than Terminal allowed
	 * 					  larger than the amount in balance
	 * Expectation:		  Declined Process
	 ****************************************************************************/
//	 printf("\n---------        Test Case.3        ---------\n");
//	 printf("---        Insufficient fund user story        ---\n");
//	 appStart();

	 /***************************************************************************
	 * Test Case.4:       "Expired card user story"
	 * 					  *****************************************************
	 * 					  *****************************************************
	 * Expectation:		  Declined Process
	 ****************************************************************************/
//	 printf("\n---------        Test Case.4        ---------\n");
//	 printf("---        Expired card user story        ---\n");
//	 appStart();

	 /***************************************************************************
	 * Test Case.5:       "Invalid card user story"
	 * 					  valid and not expired STOLEN card
	 * 					  *****************************************************
	 * 					  *****************************************************
	 * Expectation:		  Declined Process
	 ****************************************************************************/
//	 printf("\n---------        Test Case.5        ---------\n");
//	 printf("---        Invalid card user story        ---\n");
//	 appStart();

	return 0;
}
