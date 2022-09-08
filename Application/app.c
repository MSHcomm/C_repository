/******************************************************************************
*
* Module: Application
*
* File Name: App.c
*
* Description: Source file for Application Tasks.
*
* Author: Mohamed Sayed Gedan
******************************************************************************/

#include "app.h"

void appStart(void){


	/******************************************************************************
	*
	* Card module Processes
	*
	******************************************************************************/
	GetAllCardData(&g_cardData);

	/******************************************************************************
	*
	* Terminal module Processes
	*
	******************************************************************************/
	getTransactionDate(&g_termData);
	printf("\nTransAction Date: %s",g_termData.transactionDate);

	if (EXPIRED_CARD == isCardExpired(g_cardData, g_termData)){
		printf("\n * Declined Process *** EXPIRED_CARD * ");
		exit(0);
		printf("\n *** End Process *** ");
	}

	if (INVALID_CARD == isValidCardPAN(&g_cardData)){
		printf("\n * Declined Process *** INVALID CARD or STOLEN CARD * ");
		exit(0);
		printf("\n *** End Process *** ");
	}

	while (INVALID_AMOUNT == getTransactionAmount(&g_termData));

	if (EXCEED_MAX_AMOUNT == isBelowMaxAmount(&g_termData)){
		printf("\n * Declined Process *** AMOUNT EXCEEDING LIMIT * ");
		exit(0);
		printf("\n *** End Process *** ");
	}
	else{
		printf("\n * PLZ WAIT * ");
	}

	/******************************************************************************
	*
	* Server module Processes
	*
	******************************************************************************/
	if (DECLINED_STOLEN_CARD == recieveTransactionData(transDB)){
		printf("\n * Declined Process *** DECLINED_STOLEN_CARD * ");
		exit(0);
		printf("\n *** End Process *** ");
	}
	else if(DECLINED_INSUFFECIENT_FUND == recieveTransactionData(transDB)){
		printf("\n * Declined Process *** DECLINED_INSUFFECIENT_FUND * ");
		exit(0);
		printf("\n *** End Process *** ");
	}
	else if(APPROVED == recieveTransactionData(transDB)){
		printf("\n * APPROVED Process * ");
		exit(0);
		printf("\n *** End Process *** ");
	}
	else {
		printf("\n *** No *** ");
	}


}
