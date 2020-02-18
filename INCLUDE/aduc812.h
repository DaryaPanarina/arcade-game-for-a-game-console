#ifndef __ADUC812__H
#define __ADUC812__H

/*  BYTE Register  */
__sfr __at ( 0x84 )  DPP      ;
__sfr __at ( 0x88 )  TCON     ;
__sfr __at ( 0x89 )  TMOD     ;
__sfr __at ( 0x8A )  TL0      ;
__sfr __at ( 0x8B )  TL1      ;
__sfr __at ( 0x8C )  TH0      ;
__sfr __at ( 0x8D )  TH1      ;
__sfr __at ( 0xA8 )  IE       ;
__sfr __at ( 0x9A )  I2CDAT   ;
__sfr __at ( 0x9B )  I2CADD   ;
__sfr __at ( 0xE8 )  I2CCON   ;

/* BIT Register..... */
/* TCON */
__sbit __at ( 0x8F ) TF1      ;
__sbit __at ( 0x8E ) TR1      ;
__sbit __at ( 0x8D ) TF0      ;
__sbit __at ( 0x8C ) TR0      ;
__sbit __at ( 0x8B ) IE1      ;
__sbit __at ( 0x8A ) IT1      ;
__sbit __at ( 0x89 ) IE0      ;
__sbit __at ( 0x88 ) IT0      ;

/* IE */                  
__sbit __at ( 0xAF ) EA       ;
__sbit __at ( 0xAE ) EADC     ;
__sbit __at ( 0xAD ) ET2      ;
__sbit __at ( 0xAC ) ES       ;
__sbit __at ( 0xAB ) ET1      ;
__sbit __at ( 0xAA ) EX1      ;
__sbit __at ( 0xA9 ) ET0      ;
__sbit __at ( 0xA8 ) EX0      ;

/* I2CCON */              
__sbit __at ( 0xEF ) MDO      ;
__sbit __at ( 0xEE ) MDE      ;
__sbit __at ( 0xED ) MCO      ;
__sbit __at ( 0xEC ) MDI      ;
__sbit __at ( 0xEB ) I2CM     ;
__sbit __at ( 0xEA ) I2CRS    ;
__sbit __at ( 0xE9 ) I2CTX    ;
__sbit __at ( 0xE8 ) I2CI     ;

/* FPGA */
#define KB 			0x0
#define DATA_IND 	0x1
#define C_IND 		0x6
#define SV 			0x7

#endif //__ADUC812_H