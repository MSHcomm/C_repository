/******************************************************************************
* Module: Cards
*
* File Name: card.c
*
* Description: Source file for Card Tasks.
*
* Author: Mohamed Sayed Gedan
******************************************************************************/
#include "card.h"


/***************************************************************
* Service Name:       LuhnNumbechecker
* Parameters (in):    InPAN, pointer to string(array of char terminated by '\0')
* Return value:       uint8_t, (sum modules of 10)
* Description:        Function to ask for PAN and return 0 if it is valid
*					  or return other value if it is not valid.
****************************************************************/
/* Function to check the PAN number is valid according to Luhn Algorithm API*/
uint8_t LuhnNumbechecker(uint8_t *InPAN){
	boolean DoubledFlag = TRUE;
	uint8_t sum = 0;
	uint8_t i = 0 , Digit = 0;
	uint8_t nDigits = strlen((char *)InPAN);
	for(i=0 ; i<nDigits ; i++){
		Digit = InPAN[i] - '0';
		if(TRUE == DoubledFlag){
			Digit= Digit*2;
			sum += (Digit/10);
			sum += (Digit%10);
		}
		else{
			sum += Digit;
		}
		DoubledFlag = !DoubledFlag;
	}
	return (sum % 10);
}


/***************************************************************
* Service Name:       getCardHolderName
* Parameters (in):    cardData, pointer to struct
* Return value:       EN_cardError_t, OK or WRONG_NAME error
* Description:        Function to ask for the cardholder's name and store it into card data API
*					  If the card holder name is NULL, less than 20 characters or more than 24
*					  will return WRONG_NAME error, else return OK.
****************************************************************/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t len = 0, i = 0;
	uint8_t Name[25] = {0};
	puts("\nPLZ Enter the Card Holder Name:");
	gets((char *)Name);

	strcpy((char *)cardData->cardHolderName , (char *) Name);

	if ('\0' == *(cardData->cardHolderName)){
		return WRONG_NAME;
	}

	/* strlen function to determine the sting length  */
	len = strlen((char *) cardData -> cardHolderName);

	if ((len >=20) && (len <= 24)) {
		for(i=0 ; i<len ; i++){
			if(((Name[i]<'A') && (Name[i] != ' ')) || (Name[i]>'z')){
				printf("\n***   NAME must be (letters capital or small) only   ***\n");
				return WRONG_NAME;
			}
		}
		return OK_CARD;
	}
	else {
		return WRONG_NAME;
	}
}


/***************************************************************
* Service Name:       getCardExpiryDate
* Parameters (in):    cardData, pointer to struct
* Parameters (inout): None
* Parameters (out):   None
* Return value:       EN_cardError_t, OK or WRONG_EXP_DATE error
* Description:        Function to ask for the card expiry date and store it in card date API
*					  Card expire date is 5 characters string in the format "MM/YY", e.g "05/25"
*					  If the card expire date is NULL, less or more than 5 characters,
*					  or has the wrong format will return WRONG_EXP_DATE error, else return OK.
****************************************************************/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData){
	uint8_t len = 0, i = 0;
	uint8_t Date[6] = {0};
	puts("\nPLZ Enter the Card Expire Date:");
	gets((char *)Date);
	strcpy((char *)cardData->cardExpirationDate , (char *) Date);
	/* strlen function to determine the sting length  */
	len = strlen((char*) cardData ->cardExpirationDate);

	if (cardData->cardExpirationDate == NULL) {
		return WRONG_EXP_DATE;
	}
	else if (5 == len) {
		for(i=0 ; i<len ; i++){
			if((Date[i]<'/') || (Date[i]>'9')){
				printf("\n***   EXP_DATE must be numbers only   ***\n");
				return WRONG_EXP_DATE;
			}
		}
		return OK_CARD;
	}
	else {
		return WRONG_EXP_DATE;
	}
}


/***************************************************************
* Service Name:       getCardPAN
* Parameters (in):    cardData, pointer to struct
* Return value:       EN_cardError_t, OK or WRONG_PAN error
* Description:        Function to ask for the card's PAN and store it in card data API API
*					  PAN is 20 characters alphanumeric only string 19 character max, and 16 character min.
*					  If the PAN is NULL, less than 16 or more than 19 characters, will return WRONG_PAN error,
*					  else return OK.
****************************************************************/
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	uint8_t len = 0, i = 0;
	uint8_t PANno[20] = {0};
	puts("PLZ Enter PAN:");
	gets((char *)PANno);
	strcpy((char *)cardData->primaryAccountNumber , (char *) PANno);
	/* strlen function to determine the sting length  */
	len = strlen((char*) cardData->primaryAccountNumber);
	if (('\0' == *(cardData->primaryAccountNumber)) || (NULL == cardData->primaryAccountNumber)){
		return WRONG_PAN;
	}
	else if ((len >= 16) && (len <= 19)){ /*16 without spaces, 19 with 3 spaces */
		for(i=0 ; i<len ; i++){
			if((PANno[i]<'0') || (PANno[i]>'9')){
				printf("\n***   PAN must be numbers only   ***\n");
				return WRONG_PAN;
			}
		}
		return OK_CARD;
	}
	else {
		return WRONG_PAN;
	}
}



