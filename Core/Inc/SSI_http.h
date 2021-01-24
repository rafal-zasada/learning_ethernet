/*
 * SSI_http.h
 *
 *  Created on: Jan 24, 2021
 *      Author: Rafal
 */

#ifndef INC_SSI_HTTP_H_
#define INC_SSI_HTTP_H_

#define numSSItags 2
u16_t mySSIHandler(int iIndex, char *pcInsert, int iInsertLen);
void mySSIinit(void);

#endif /* INC_SSI_HTTP_H_ */
