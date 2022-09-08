/******************************************************************************
* Module: Cards
*
* File Name: card.h
*
* Description: Header file for Card Tasks.
*
* Author: Mohamed Sayed Gedan
******************************************************************************/

#ifndef CARD_CARD_H_
#define CARD_CARD_H_

/*******************************************************************************
 *                       Header Files & Librraries Includes                   *
 *******************************************************************************/
#include "../Services/Std_Types.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/*
 * ST_cardData_t to define the Holder Name, PAN, and Expiration Dateon on the card
 */
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

/*
 * EN_cardError_t to define the return data if it is correct or has an error
 */
typedef enum EN_cardError_t
{
	OK_CARD, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/*******************************************************************************
 *                Module global variables declaritaion                        *
 *******************************************************************************/
extern ST_cardData_t g_cardData;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function to check the PAN number is valid according to Luhn Algorithm API*/
uint8_t LuhnNumbechecker(uint8_t *InPAN);

 /* Function to ask for the cardholder's name and store it into card data API*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

/* Function to ask for the card expiry date and store it in card data API*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

/* Function to ask for the card's PAN and store it in card data API*/

EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif /* CARD_CARD_H_ */
