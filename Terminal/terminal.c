/******************************************************************************
* Module: terminal
*
* File Name: terminal.c
*
* Description: Source file for terminal Tasks.
*
* Author: Mohamed Sayed Gedan
******************************************************************************/

#include "terminal.h"
#include <stdlib.h>

/***************************************************************
* Service Name:       GetAllCardData
* Parameters (in/out):InputCardData, pointer to struct and storing new data entry
* Return value:       void
* Description:        Function to get All Card Date and storing it in ST_cardData_t type API
* 					  ask user about Holder Name, Expire Date, and PAN
****************************************************************/
void GetAllCardData(ST_cardData_t *InputCardData){
	while(WRONG_NAME == getCardHolderName(InputCardData));

	while(WRONG_EXP_DATE == getCardExpiryDate(InputCardData));

	while(WRONG_PAN == getCardPAN(InputCardData));
}

/***************************************************************
* Service Name:       getTransactionDate
* Parameters (in):    termData, pointer to struct
* Return value:       EN_terminalError_t, OK or WRONG_DATE error
* Description:        Function to ask for the transaction data and store it in terminal data API
*					  Transaction date is 10 characters string in the format DD/MM/YYYY, e.g 25/06/2022.
*					  If the transaction date is NULL, less than 10 characters or wrong format will
*					  return WRONG_DATE error, else return OK.
****************************************************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
	char chArr[9];

	/* time_t type definition for the time, which defined as long */
	time_t currentDate;

	/* time is a function returns the time since
	 * the Epoch (00:00:00 UTC, January 1, 1970), measured in seconds */
	time(&currentDate);

	/* _strdate function to convert into string on Format: MM/DD/YY */
	strcpy(chArr, _strdate((char *)&currentDate));

	/* Converting date into format: DD/MM/YYYY as follows */

	/* DD */
	termData->transactionDate[0] = chArr[3];
	termData->transactionDate[1] = chArr[4];
	termData->transactionDate[2] = '/';

	/* MM */
	termData->transactionDate[3] = chArr[0];
	termData->transactionDate[4] = chArr[1];
	termData->transactionDate[5] = '/';

	/* YY** */
	termData->transactionDate[6] = '2';
	termData->transactionDate[7] = '0';

	/* **YY */
	termData->transactionDate[8] = chArr[6];
	termData->transactionDate[9] = chArr[7];

	/* string termination */
	termData->transactionDate[10]= '\0';

	if(NULL == (termData->transactionDate) ){     /*DD/MM/YYYY*/
		return WRONG_DATE;
	}
	else if(10 == (strlen((char *)termData->transactionDate))){
		return OK_TERM;
	}
	else{
		return WRONG_DATE;
	}
}

/***************************************************************
* Service Name:       isCardExpired
* Parameters (in):    cardData and termData are struct global variables
* Parameters (inout): None
* Parameters (out):   None
* Return value:       EN_terminalError_t, OK_CARD or EXPIRED_CARD error
* Description:        Function to compares the card expire date with the transaction date API
****************************************************************/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
	uint8_t i = 0;
	i = 3;
	while ( i<=4 ){
			if( termData.transactionDate[i+5] > cardData.cardExpirationDate[i] ){
				return EXPIRED_CARD;
			}
			else if(termData.transactionDate[i+5] == cardData.cardExpirationDate[i]){
				i++;
			}
			else{
				return OK_CARD;
			}
	}
	i = 0;
	while( i<=1 ){
			if( termData.transactionDate[i+3] > cardData.cardExpirationDate[i]  ){
				return EXPIRED_CARD;
			}
			else if (termData.transactionDate[i+3] == cardData.cardExpirationDate[i]){
				i++;
			}
			else{
				return OK_CARD;
			}
	}
	return OK_CARD;
}

/***************************************************************
* Service Name:       isValidCardPAN
* Parameters (in):    cardData is pointer to struct
* Parameters (inout): None
* Parameters (out):   None
* Return value:       EN_terminalError_t ---> OK_TERM or INVALID_CARD error
* Description:        Function to check the PAN is valid or not API
* 					  using Luhn algorithm to check sum of PAN number
****************************************************************/
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData){
	if(0 == LuhnNumbechecker( cardData->primaryAccountNumber)){
		return OK_TERM;
	}
	else{
		return INVALID_CARD;
	}
}

/***************************************************************
* Service Name:       getTransactionAmount
* Parameters (in):    termData is pointer to struct
* Parameters (inout): None
* Parameters (out):   None
* Return value:       EN_terminalError_t ---> OK_TERM or INVALID_AMOUNT error
* Description:        Function to asks for the transaction amount and saves it into terminal data API
****************************************************************/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData){
	float Amount_Value = 0.00;
	printf("\nPLZ Enter the Amount = \n");
	scanf("%f", &Amount_Value);
	if(((sint32_t)Amount_Value) <= 0){
		return INVALID_AMOUNT;
	}
	else {
		termData->transAmount = Amount_Value;
		return OK_TERM;
	}
}

/***************************************************************
* Service Name:       isBelowMaxAmount
* Parameters (in):    termData is pointer to struct
* Parameters (inout): None
* Parameters (out):   None
* Return value:       EN_terminalError_t ---> OK_TERM or EXCEED_MAX_AMOUNT error
* Description:        Function to compares the transaction amount with the terminal max amount API
* 					  If the transAmount is larger than the maxTransAmount will return
* 					  EXCEED_MAX_AMOUNT, else return OK_TERM.
* 					  Note: This is the MAX of CARD (Silver, Gold, or Platinum)
****************************************************************/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData){
	if((termData->transAmount) > (termData->maxTransAmount)){
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return OK_TERM;
	}
}

/***************************************************************
* Service Name:       setMaxAmount
* Parameters (in):    termData is pointer to struct
* Return value:       EN_terminalError_t ---> OK_TERM or INVALID_MAX_AMOUNT  error
* Description:        Function to sets the maximum allowed amount into terminal data API
* 					  If the transAmount is larger than the maxTransAmount will return
* 					  EXCEED_MAX_AMOUNT, else return OK_TERM.
****************************************************************/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData){
	float Max_Value = 0.00;
	printf("PLZ Enter the Maximum Allowed Value = \n");
	scanf("%f", &Max_Value);
	if(((sint32_t)Max_Value) <= 0){
		return INVALID_MAX_AMOUNT;
	}
	else{
		return OK_TERM;
	}
}
