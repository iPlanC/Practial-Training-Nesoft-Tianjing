#ifndef __MAIN_H__
#define __MAIN_H__

// RCC
typedef struct {
	unsigned int CR;
	unsigned int CFGR;
	unsigned int CIR;
	unsigned int APB2RSTR;
	unsigned int APB1RSTR;
	unsigned int AHBENR;
	unsigned int APB2ENR;
	unsigned int APB1ENR;
	unsigned int BDCR;
	unsigned int CSR;
} RCC_typedef;

// GPIOA
typedef struct {
	unsigned int CRL;
	unsigned int CRH;
	unsigned int IDR;
	unsigned int ODR;
	unsigned int BSRR;
	unsigned int BRR;
	unsigned int LCKR;
} GPIOA_typedef;

#define RCC			((RCC_typedef *)	0x40021000)
#define GPIOA		((GPIOA_typedef *)	0x40010800)

#endif
