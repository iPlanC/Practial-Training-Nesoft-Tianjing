/*
 * DHT11.h
 *
 * Updated on: 28.06.2020
 * Created on: 24.03.2019
 *     Author: Admin
 */

#ifndef DHT11_H_
#define DHT11_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "..\Lib\CMSIS\stm32f10x.h"

// -----------------------------------------------
// public struct
// -----------------------------------------------
typedef struct {
	uint8_t humidity;
	uint8_t temperature;
} DHT11_TypeDef;
// -----------------------------------------------

// -----------------------------------------------
// public functions
// -----------------------------------------------
uint8_t DHT_read(DHT11_TypeDef *dht11);
// -----------------------------------------------

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DHT11_H_ */
