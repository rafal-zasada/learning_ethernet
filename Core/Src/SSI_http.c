/*
 * SSI_http.c
 *
 *  Created on: Jan 24, 2021
 *      Author: Rafal
 */

#include <string.h>
#include "arch.h" // for u16_t
#include "lwip/apps/httpd.h"
#include "SSI_http.h"

#include "usart.h"

//array of tags for the SSI handler
//these are the tags <!--#tag1--> contained in the shtml file

char const *theSSItags[numSSItags] = {"tag1","tag2"};

// This function is called each time the HTTPD server detects a tag of the form
// <!--#name--> in a .shtml, .ssi or .shtm file
// It won't work if the file has a .html extension.
u16_t mySSIHandler(int iIndex, char *pcInsert, int iInsertLen)
{
	//debug

	 extern char GUI_buffer[200];

	 snprintf(GUI_buffer, sizeof(GUI_buffer), "Test inside mySSIHandler");
	 HAL_UART_Transmit(&huart3, (unsigned char*)&GUI_buffer , strlen(GUI_buffer) + 1, 200);


	// see which tag in the array theSSItags to handle
	if (iIndex == 0) //is “tag1”
	{
		char myStr1[] = "Hello from Tag #1!"; //string to be displayed on web page
		//copy the string to be displayed to pcInsert
		strcpy(pcInsert, myStr1);
		//return number of characters that need to be inserted in html
		return strlen(myStr1);
	}
	else if (iIndex == 1) //is “tag2”
	{
		char myStr2[] = "Hello from Tag #2!"; //string to be displayed on web page
		//copy string to be displayed
		strcpy(pcInsert, myStr2);
		//return number of characters that need to be inserted in html
		return strlen(myStr2);
	}
	return 0;
} //mySSIHandler

/**** Initialize SSI handlers ****/
void mySSIinit(void)
{
	//configure SSI handler function
	//theSSItags is an array of SSI tag strings to search for in SSI-enabled files

	//Note: #define LWIP_HTTPD_SSI 1 must be added in lwipopts.h. It should be possible from STM32CubeIDE but something did not work.
	http_set_ssi_handler(mySSIHandler, (char const **)theSSItags, numSSItags);

} //mySSIinit
