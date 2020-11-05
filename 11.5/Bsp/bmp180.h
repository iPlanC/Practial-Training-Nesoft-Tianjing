#ifndef BMP180_H_
#define BMP180_H_

#include "bsp_i2c.h"
#include "delay.h"

#define BMP180_ADDRESS						0x77

// Preset Meas for Normal mode
#define BMP180_PRESET_CTRL_MEAS_NORMAL		(BMP180_CTRL_MEAS_OSRS_T_X16 | BMP180_CTRL_MEAS_OSRS_P_X16 | BMP180_CTRL_MEAS_MODE_NORMAL)
// Preset Meas for Forced mode
#define BMP180_PRESET_CTRL_MEAS_FORCED		(BMP180_CTRL_MEAS_OSRS_T_X16 | BMP180_CTRL_MEAS_OSRS_P_X16 | BMP180_CTRL_MEAS_MODE_FORCED)
// Preset Config
#define BMP180_PRESET_CONFIG				(BMP180_CONFIG_T_SB_125 | BMP180_CONFIG_FILTER_COEFF_2 | BMP180_CONFIG_SPI3W_OFF)

// ---------------------------------------------

#define BMP180_RESET_VALUE					0xB6

// Register
#define BMP180_REGISTER_ID					0xD0
#define BMP180_REGISTER_RESET				0xE0
#define BMP180_REGISTER_STATUS				0xF3
#define BMP180_REGISTER_CTRL_MEAS			0xF4
#define BMP180_REGISTER_CONFIG				0xF5
#define BMP180_REGISTER_PRESSURE_MSB		0xF7
#define BMP180_REGISTER_PRESSURE_LSB		0xF8
#define BMP180_REGISTER_PRESSURE_XLSB		0xF9
#define BMP180_REGISTER_TEMPERATURE_MSB		0xFA
#define BMP180_REGISTER_TEMPERATURE_LSB		0xFB
#define BMP180_REGISTER_TEMPERATURE_XLSB	0xFC

// Compensation parameter storage
#define BMP180_CAL_AC1           0xAA
#define BMP180_CAL_AC2           0xAC
#define BMP180_CAL_AC3           0xAE
#define BMP180_CAL_AC4           0xB0
#define BMP180_CAL_AC5           0xB2
#define BMP180_CAL_AC6           0xB4
#define BMP180_CAL_B1            0xB6
#define BMP180_CAL_B2            0xB8
#define BMP180_CAL_MB            0xBA
#define BMP180_CAL_MC            0xBC
#define BMP180_CAL_MD            0xBE
#define BMP180_CONTROL           0xF4
#define BMP180_TEMPDATA          0xF6
#define BMP180_PRESSUREDATA      0xF6

/* ------------------------------------------------
 * Register 0xF4 "ctrl_meas"
 * ------------------------------------------------
 * osrs_t[7:5] | Temperature  | Typical temperature
 *             | oversampling | resolution
 * ------------------------------------------------
 *     000     |  skipped     |       -
 *     001     |    x1        | 16 bit / 0.0050 C
 *     010     |    x2        | 17 bit / 0.0025 C
 *     011     |    x4        | 18 bit / 0.0012 C
 *     100     |    x8        | 19 bit / 0.0006 C
 * 101 110 111 |    x16       | 20 bit / 0.0003 C
 * ------------------------------------------------
 */
#define BMP180_CTRL_MEAS_OSRS_T_SKIP		0x00
#define BMP180_CTRL_MEAS_OSRS_T_X1			0x20
#define BMP180_CTRL_MEAS_OSRS_T_X2			0x40
#define BMP180_CTRL_MEAS_OSRS_T_X4			0x60
#define BMP180_CTRL_MEAS_OSRS_T_X8			0x80
#define BMP180_CTRL_MEAS_OSRS_T_X16			0xA0


/* ---------------------------------------------
 * osrs_p[4:2] | Pressure     | Typical pressure
 *             | oversampling | resolution
 * ---------------------------------------------
 *     000     |  skipped     |       -
 *     001     |    x1        | 16 bit / 2.62 Pa
 *     010     |    x2        | 17 bit / 1.31 Pa
 *     011     |    x4        | 18 bit / 0.66 Pa
 *     100     |    x8        | 19 bit / 0.33 Pa
 * 101 110 111 |    x16       | 20 bit / 0.16 Pa
 * ---------------------------------------------
 */
#define BMP180_CTRL_MEAS_OSRS_P_SKIP		0x00
#define BMP180_CTRL_MEAS_OSRS_P_X1			0x04
#define BMP180_CTRL_MEAS_OSRS_P_X2			0x08
#define BMP180_CTRL_MEAS_OSRS_P_X4			0x0C
#define BMP180_CTRL_MEAS_OSRS_P_X8			0x10
#define BMP180_CTRL_MEAS_OSRS_P_X16			0x14

/* ------------------
 * mode[1:0] | Mode
 * ------------------
 *     00    | Sleep
 *   01 10   | Forced
 *     11    | Normal
 * ------------------
 */
#define BMP180_CTRL_MEAS_MODE_SLEEP			0x00
#define BMP180_CTRL_MEAS_MODE_FORCED		0x01
#define BMP180_CTRL_MEAS_MODE_NORMAL		0x03

/* --------------------------
 * Register 0xF5 "config"
 * --------------------------
 * t_sb[7:5] | t_standby [ms]
 * --------------------------
 *    000    |  0.5
 *    001    |  62.5
 *    010    |  125
 *    011    |  250
 *    100    |  500
 *    101    |  1000
 *    110    |  2000
 *    111    |  4000
 * --------------------------
 */
#define BMP180_CONFIG_T_SB_0_5				0x00
#define BMP180_CONFIG_T_SB_62_5				0x20
#define BMP180_CONFIG_T_SB_125				0x40
#define BMP180_CONFIG_T_SB_250				0x60
#define BMP180_CONFIG_T_SB_500				0x80
#define BMP180_CONFIG_T_SB_1000				0xA0
#define BMP180_CONFIG_T_SB_2000				0xC0
#define BMP180_CONFIG_T_SB_4000				0xE0


/* ---------------------------------------------------
 * filter[4:2] | Filter      | Samples to reach >=75 %
 *             | coefficient | of step response
 * ---------------------------------------------------
 *     000     | Filter off  |   1
 *     001     |     2       |   2
 *     010     |     4       |   5
 *     011     |     8       |   11
 *     100     |     16      |   22
 * ---------------------------------------------------
 */
#define BMP180_CONFIG_FILTER_OFF			0x00
#define BMP180_CONFIG_FILTER_COEFF_2		0x04
#define BMP180_CONFIG_FILTER_COEFF_4		0x08
#define BMP180_CONFIG_FILTER_COEFF_8		0x0C
#define BMP180_CONFIG_FILTER_COEFF_16		0x10

/* ------------------------------------------
 * spi3w_en[0] | Enables 3-wire SPI interface
 * ------------------------------------------
 *    0        | disable
 *    1        | enable
 * ------------------------------------------
 */
#define BMP180_CONFIG_SPI3W_OFF				0x00
#define BMP180_CONFIG_SPI3W_ON				0x01

typedef enum {
	 BMP180_Sleep  = 0x0,
	 BMP180_Forced = 0x1,
	 BMP180_Normal = 0x3
} BMP180_Mode_Type;

uint8_t BMP180_ReadRegister(uint8_t address);
void BMP180_ReadRegisters(uint8_t address, uint8_t *data, uint8_t size);
void BMP180_WriteRegister(uint8_t address, uint8_t data);
void BMP180_WriteRegisters(uint8_t address, uint8_t *data, uint8_t size);
uint8_t BMP180_GetStatus(void);
void BMP180_Init(BMP180_Mode_Type mode);
void BMP180_Reset(void);
void BMP180_SetRegisterCtrlMeas(uint8_t ctrl_meas);
void BMP180_SetRegisterConfig(uint8_t config);
double BMP180_GetAltitude(void);
double BMP180_Compensate_Temperature(int32_t adc_T);
double BMP180_Compensate_Pressure(int32_t adc_P);
double BMP180_GetTemperature(void);
double BMP180_GetPressure(void);
void BMP180_GetTemperatureAndPressure(double *temperature, double *pressure);
void BMP180_GetTemperatureAndPressureForced(double *temperature, double *pressure);

#endif /* BMP180_H_ */
