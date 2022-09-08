/******************************************************************************
*
* Module: Server
*
* File Name: server.h
*
* Description: Header file for Server Tasks.
*
* Author: Mohamed Sayed Gedan
******************************************************************************/

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

/*******************************************************************************
 *                       Header Files & Libraries Includes                   *
 *******************************************************************************/
#include "../Terminal/terminal.h"

/*******************************************************************************
 *                            Module Data Types                              *
 *******************************************************************************/
/*
 * EN_transStat_t to define the TRANSACTION status error in server module
 */
typedef enum EN_transState_t{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
	}EN_transState_t;

/*
 * ST_transaction_t is struct type to define the transaction info in server module
 */
typedef struct ST_transaction_t{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
	}ST_transaction_t;

/*
 * EN_transStat_t to define the SERVER status error in server module
 */
typedef enum EN_serverError_t{
	OK_SERVER, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
	}EN_serverError_t ;

/*
 * ST_accountsDB_t to struct type define define the Bank Account info
 */
typedef struct ST_accountsDB_t{
	float balance;
	uint8_t primaryAccountNumber[20];
	}ST_accountsDB_t;

/*******************************************************************************
 *                Module global variables and Macros                        *
 *******************************************************************************/
#define MAX_ACCOUNT_DB 255

extern sint16_t g_index_DB;
extern uint32_t g_TSN;
extern ST_accountsDB_t AccountsDB[MAX_ACCOUNT_DB];
extern ST_transaction_t transDB[MAX_ACCOUNT_DB];

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function to search PAN key in AccountsDB API */
sint16_t LinearSearch(ST_accountsDB_t *ST_Accounts_Array, uint8_t *PAN);

 /* Function to search PAN Card on Server DB API */
EN_serverError_t isValidAccount(ST_cardData_t *cardData);

 /* Function to checks if the transaction's amount is available in balance API */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);

 /* Function to search transaction Sequence Number in  Transaction DataBase */
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData_Array);

 /*  */
EN_serverError_t saveTransaction(ST_transaction_t *transData);

 /*  */
EN_transState_t recieveTransactionData(ST_transaction_t *transData);






#endif
