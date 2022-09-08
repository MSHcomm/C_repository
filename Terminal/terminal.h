/******************************************************************************
* Module: Terminal
*
* File Name: terminal.h
*
* Description: Source file for terminal Tasks.
*
* Author: Mohamed Sayed Gedan
******************************************************************************/

#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_

/*******************************************************************************
 *                       Header Files & Libraries Includes                   *
 *******************************************************************************/
#include "../Card/card.h"
#include <time.h>

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

 /*
  * ST_terminalData_t to define the transaction info
  */
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

/*
 * EN_terminalError_t to define the transaction error
 */
typedef enum EN_terminalError_t
{
	OK_TERM, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

/*******************************************************************************
 *                Module global variables declared                        *
 *******************************************************************************/
extern ST_terminalData_t g_termData;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

 /* Function to get All Card Date and storing it in ST_cardData_t type */
void GetAllCardData(ST_cardData_t *InputCardData);

 /* Function to ask for the transaction data and store it in terminal data*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

/* Function to compares the card expire date with the transaction date*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);

/* Function to check the PAN valid or not */
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);

/* Function to asks for the transaction amount and saves it into terminal data */
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);

/* Function to compares the transaction amount with the terminal max amount */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

/* Function to sets the maximum allowed amount into terminal data */
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

#endif /* TERMINAL_TERMINAL_H_ */
