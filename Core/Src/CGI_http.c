/*
 * CGI_http.c
 *
 *  Created on: Jan 24, 2021
 *      Author: Rafal
 */

#include <string.h>
#include "main.h"
#include "lwip/apps/httpd.h"
#include "CGI_http.h"

/**** CGI handler for controlling the LEDs ****/
// the function pointer for a CGI script handler is defined in httpd.h as tCGIHandler
const char * LedCGIhandler111(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
	uint32_t i=0;
	// index of the CGI within the theCGItable array passed to http_set_cgi_handlers
	// Given how this example is structured, this may be a redundant check.
	// Here there is only one handler iIndex == 0
	if (iIndex == 0)
	{
		// turn off the LEDs
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
		// Check the cgi parameters, e.g., GET /leds.cgi?led=1&led=2
		for (i=0; i<iNumParams; i++)
		{
			//if pcParmeter contains "led", then one of the LED check boxes has been set on
			if (strcmp(pcParam[i], "led") == 0)
			{
				//see if checkbox for LED 1 has been set
				if(strcmp(pcValue[i], "1") == 0)
				{
					// switch led 1 ON if 1
					HAL_GPIO_WritePin(LD3_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
				}
				//see if checkbox for LED 2 has been set
				else if(strcmp(pcValue[i], "2") == 0)
				{
					// switch led 2 ON if 2
					HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
				}
			} //if
		} //for
	} //if
	//uniform resource identifier to send after CGI call, i.e., path and filename of the response

	return "/index.shtml";
//	return NULL;  // it will cause browser to display 404 page. How to stop page refreshing after CGI handler?
} //LedCGIhandler

// this structure contains the name of the LED CGI and corresponding handler for the LEDs
const tCGI LedCGI={"/leds.cgi", LedCGIhandler111};
//table of the CGI names and handlers
tCGI theCGItable[1];

// Initialize the CGI handlers
void myCGIinit(void)
{
	//add LED control CGI to the table
	theCGItable[0] = LedCGI;
	//give the table to the HTTP server
	http_set_cgi_handlers(theCGItable, 1);
} //myCGIinit
