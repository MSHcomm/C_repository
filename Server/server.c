/******************************************************************************
*
* Module: Server
*
* File Name: server.c
*
* Description: Source file for Server Tasks.
*
* Author: Mohamed Sayed Gedan
******************************************************************************/
#include "server.h"

/***************************************************************
* Service Name:       LinearSearch
* Parameters (in):    ST_Accounts_Array - address of DataBase Array of Accounts
* 					  PAN - pointer to PAN no gets before from CardData
* Return value:       i, element index in Accounts DB
* Description:        Function to search PAN key in AccountsDB API
*					  If PAN is found its return the index in DB, else return -1
****************************************************************/
sint16_t LinearSearch(ST_accountsDB_t *ST_Accounts_Array, uint8_t *PAN){
	sint16_t i = 0; /* index of account in DB */
	const char *strIn2 = (char *)PAN;
		  char *strIn1 = (char *)(ST_Accounts_Array[i]).primaryAccountNumber;

    for (i = 0; i < MAX_ACCOUNT_DB; i++){
    	strIn1 = (char *)(ST_Accounts_Array[i]).primaryAccountNumber;
        if (	!(strcmp(strIn1, strIn2))	){
        	return i;
        }
    }
    return -1;
}


/***************************************************************
* Service Name:       isValidAccount
* Parameters (in):    cardData, pointer to struct
* Return value:       EN_serverError_t, OK_SERVER or ACCOUNT_NOT_FOUND error
* Description:        Function to search PAN Card on Server DB API
*					  It checks if the PAN exists or not in the server's database (ST_accountsDB_t AccountsDB[]).
*					  If the PAN doesn't exist will return ACCOUNT_NOT_FOUND,
*					  else will return OK_SERVER
*					  using Linear Search Algorithm
****************************************************************/
EN_serverError_t isValidAccount(ST_cardData_t *cardData){
	uint8_t *PANno = cardData->primaryAccountNumber;
	g_index_DB = LinearSearch(AccountsDB, PANno);
	if(g_index_DB >= 0){

		return OK_SERVER;
	}
	else {
		return ACCOUNT_NOT_FOUND;
	}
}


/***************************************************************
* Service Name:       isAmountAvailable
* Parameters (in):    termData, pointer to struct
* Return value:       EN_serverError_t, OK_SERVER or LOW_BALANCE error
* Description:        Function to take terminal data and validate these data.
* 					  this API checks if the transaction's amount is available or not.
* 					  If the transaction amount is greater than the balance in the database
* 					  will return LOW_BALANCE, else will return OK_SERVER API
****************************************************************/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
	float Amount = termData->transAmount;
	if(Amount > AccountsDB[g_index_DB].balance){
		return LOW_BALANCE;
	}
	else {
		return OK_SERVER;
	}

}


/***************************************************************
* Service Name:       getTransaction
* Parameters (in):    transactionSequenceNumber- variable of uint32_t
* 					  transData- pointer to struct of ST_transaction_t type
* Return value:       EN_serverError_t, OK_SERVER or TRANSACTION_NOT_FOUND error
* Description:        Function to search transaction Sequence Number in Transaction DataBase
* 					  this API checks if the transactionSequenceNumber is exists in transDB array.
* 					  If the transactionSequenceNumber is existing in transData_Array OK_SERVER,
* 					  else will return TRANSACTION_NOT_FOUND API
*					  using binary search Algorithm is used, due to the transactionSequenceNumber is sorted in ascending order
****************************************************************/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData_Array){
	uint8_t i = 0; /* index of Transaction DataBase */
	for(i=0 ; i<MAX_ACCOUNT_DB ; i++){
		if(((transData_Array[i]).transactionSequenceNumber) == transactionSequenceNumber){
			g_TSN = i;
			return OK_SERVER;
		}
	}
	return TRANSACTION_NOT_FOUND;
}


/***************************************************************
* Service Name:       saveTransaction
* Parameters (in):    transData- pointer to struct of ST_transaction_t type to save the following:
* Parameters (out):	  .transState- transaction state on transaction DB with values= "APPROVED or DECLINED"
* 					  .cardHolderData- contains all CardData (cardExpirationDate, cardHolderName, and PAN)
* 					  .terminalData- contains all terminalData (transAmount, maxTransAmount, and transactionDate)
* 					  .transactionSequenceNumber- gives transactionSequenceNumber to a transaction, which is
* 					                              incremented once at each process on the server side.
* Return value:       EN_serverError_t, OK_SERVER, SAVING_FAILED error
* Description:        Function to save all transaction data into the transactions database.
* 					  this API gives transactionSequenceNumber to a transaction,
* 					  which is incremented once at each process on the server side.
* 					  g_TSN incremented once every transaction process
****************************************************************/
EN_serverError_t saveTransaction(ST_transaction_t *transData){
	if ((NULL==(transData[g_TSN]).cardHolderData.primaryAccountNumber) || (0>=(transData[g_TSN]).terminalData.transAmount)){
		return SAVING_FAILED;
	}
	else{
		strcpy((char *)(transData[g_TSN]).cardHolderData.cardExpirationDate  	,  (char *)g_cardData.cardExpirationDate);
		strcpy((char *)(transData[g_TSN]).cardHolderData.cardHolderName 	 	,  (char *)g_cardData.cardHolderName);
		strcpy((char *)(transData[g_TSN]).cardHolderData.primaryAccountNumber   ,  (char *)g_cardData.primaryAccountNumber);

		(transData[g_TSN]).terminalData.maxTransAmount = g_termData.maxTransAmount;
		(transData[g_TSN]).terminalData.transAmount = g_termData.transAmount;
		 strcpy((char *)(transData[g_TSN]).terminalData.transactionDate			,  (char *)g_termData.transactionDate);

		(transData[g_TSN]).transactionSequenceNumber = g_TSN;
		g_TSN++;
		return OK_SERVER;
	}
}


/***************************************************************
* Service Name:       recieveTransactionData
* Parameters (in):    transData, pointer to struct
* Return value:       EN_terminalError_t - APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD,
* 										   or INTERNAL_SERVER_ERROR error
* Description:        Function to It checks the account details, isValidAccount, and isAmountAvailable API
*					  If the account is not Valid return DECLINED_STOLEN_CARD,
*					  if the amount is not available will return DECLINED_INSUFFECIENT_FUND,
*					  if a transaction can't be saved will return INTERNAL_SERVER_ERROR
*					  and will not save the transaction,
*					  else returns APPROVED.
*					  then go to update the DB with the new balance
****************************************************************/
EN_transState_t recieveTransactionData(ST_transaction_t *transData){
	if(ACCOUNT_NOT_FOUND == isValidAccount(&g_cardData)){
		return DECLINED_STOLEN_CARD;
	}
	else if (LOW_BALANCE == isAmountAvailable(&g_termData)){
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (TRANSACTION_NOT_FOUND == (getTransaction(g_TSN, transDB))) {
		/* Saving Data */
		if ( OK_SERVER == saveTransaction(transData)){
			/* Updating balance of the account */
			(AccountsDB[g_index_DB]).balance = (AccountsDB[g_index_DB]).balance - g_termData.transAmount;
			return APPROVED;
		}
		else if(SAVING_FAILED == saveTransaction(transData)){
			return INTERNAL_SERVER_ERROR;
		}
	}
	return APPROVED;
}

