#include "bmp180.h"
#include <math.h>

int16_t cal_AC1 = 0;
int16_t cal_AC2 = 0;
int16_t cal_AC3 = 0;
uint16_t cal_AC4 = 0;
uint16_t cal_AC5 = 0;
uint16_t cal_AC6 = 0;
int16_t cal_B1  = 0;
int16_t cal_B2  = 0;
int16_t cal_MB  = 0;
int16_t cal_MC  = 0;
int16_t cal_MD  = 0;

uint8_t BMP180_ReadRegister(uint8_t address) {

	uint8_t data[1] = {0};

	BMP180_ReadRegisters(address, data, 1);

	return data[0];
}

void BMP180_ReadRegisters(uint8_t address, uint8_t *data, uint8_t size) {

	uint8_t count = 0;

	// I2C Send
	I2C1_Start();
	I2C1_SendAddress(BMP180_ADDRESS, I2C_TRANSMITTER);
	I2C1_SendData(address);

	// I2C Receive
	I2C1_Start();
	I2C1_SendAddress(BMP180_ADDRESS, I2C_RECEIVER);

	for (count = 0; count < size - 1; ++count ) {
		data[count] = I2C1_ReceiveData(I2C_ACK);
	}

	I2C1_Stop();
	data[count] = I2C1_ReceiveData(I2C_NACK);
}

void BMP180_WriteRegister(uint8_t address, uint8_t data) {

	uint8_t tempdata[1] = {0};
	tempdata[0] = data;

	BMP180_WriteRegisters(address, tempdata, 1);
}

void BMP180_WriteRegisters(uint8_t address, uint8_t *data, uint8_t size) {
	int i = 0;
	// I2C Send
	I2C1_Start();
	I2C1_SendAddress(BMP180_ADDRESS, I2C_TRANSMITTER);
	I2C1_SendData(address);

	for (i = 0; i < size; ++i) {
		I2C1_SendData(data[i]);
	}

	I2C1_Stop();
}

uint8_t BMP180_GetStatus() {

	uint8_t id = 0;
	// I2C Send
	I2C1_Start();
	if (I2C1_SendAddress(BMP180_ADDRESS, I2C_TRANSMITTER) == I2C_ERROR) return 0;
	I2C1_SendData(BMP180_REGISTER_ID);

	// I2C Receive
	I2C1_Start();
	if (I2C1_SendAddress(BMP180_ADDRESS, I2C_RECEIVER) == I2C_ERROR) return 0;
	I2C1_Stop();

	id = I2C1_ReceiveData(I2C_NACK);
	if(id != 0x58) {
		return 0;
	}

	return 1;
}

void BMP180_Init(BMP180_Mode_Type mode) {
	
	int16_t cal_AC1 = BMP180_ReadRegister(BMP180_CAL_AC1);
	int16_t cal_AC2 = BMP180_ReadRegister(BMP180_CAL_AC2);
	int16_t cal_AC3 = BMP180_ReadRegister(BMP180_CAL_AC3);
	uint16_t cal_AC4 = BMP180_ReadRegister(BMP180_CAL_AC4);
	uint16_t cal_AC5 = BMP180_ReadRegister(BMP180_CAL_AC5);
	uint16_t cal_AC6 = BMP180_ReadRegister(BMP180_CAL_AC6);
	int16_t cal_B1  = BMP180_ReadRegister(BMP180_CAL_B1);
	int16_t cal_B2  = BMP180_ReadRegister(BMP180_CAL_B2);
	int16_t cal_MB  = BMP180_ReadRegister(BMP180_CAL_MB);
	int16_t cal_MC  = BMP180_ReadRegister(BMP180_CAL_MC);
	int16_t cal_MD  = BMP180_ReadRegister(BMP180_CAL_MD);

	// Soft reset
	// BMP180_Reset();

	if (mode == BMP180_Normal) {
		BMP180_SetRegisterConfig(BMP180_PRESET_CONFIG);
		BMP180_SetRegisterCtrlMeas(BMP180_PRESET_CTRL_MEAS_NORMAL);
		delay_us(10000);
	}
}

void BMP180_Reset() {
	BMP180_WriteRegister(BMP180_REGISTER_RESET, BMP180_RESET_VALUE);
}

void BMP180_SetRegisterCtrlMeas(uint8_t ctrl_meas) {
	BMP180_WriteRegister(BMP180_REGISTER_CTRL_MEAS, ctrl_meas);
}

void BMP180_SetRegisterConfig(uint8_t config) {
	BMP180_WriteRegister(BMP180_REGISTER_CONFIG, config);
}

// --------------------------------------------------
// BMP180_Compensate_Temperature
// --------------------------------------------------
double BMP180_Compensate_Pressure(int32_t adc_T)
{
	int32_t UT;
	int32_t UP = BMP180_GetTemperature();
	int X1, X2, X3, B1, B2, B3, B4, B5, B6, B7, p;
	UT = adc_T;
	X1 = ((UT - cal_AC6) * cal_AC5) >> 15;
	X2 = (((long)cal_MC) << 11) / (X1 + cal_MD);
	B5 = X1 + X2;
	B6 = B5 - 4000;
	X1 = ((long)B2 * (B6 * B6 >> 12)) >> 11;
	X2 = ((long)cal_AC2) * B6 >> 11;
	X3 = X1 + X2;
	B3 = ((((long)cal_AC1) * 4 + X3) + 2) /4;
	X1 = ((long)cal_AC3) * B6 >> 13;
	X2 = (((long)B1) *(B6*B6 >> 12)) >>16;
	X3 = ((X1 + X2) + 2) >> 2;
	B4 = ((long)cal_AC4) * (unsigned long)(X3 + 32768) >> 15;
	B7 = ((unsigned long)UP - B3) * 50000;
	if(B7 < 0x80000000) {
		p = (B7 * 2) / B4;
	}
	else {
		p = (B7 / B4) * 2;
	}
	X1 = (p >> 8) * (p >>8);
	X1 = (((long)X1) * 3038) >> 16;
	X2 = (-7357 * p) >> 16;
	p = p + ((X1 + X2 + 3791) >> 4);
	return 44330 * (1 - pow(((p) / 101325.0), (1.0/5.255)));
}

// --------------------------------------------------
// BMP180_Compensate_Pressure (Pa)
// --------------------------------------------------
double BMP180_Compensate_Temperature(int32_t adc_P)
{
	return 0.0;
}

double BMP180_GetTemperature() {

	int32_t adc_T;
	uint8_t data[3] = {0};

	BMP180_ReadRegisters(BMP180_REGISTER_TEMPERATURE_MSB, data, 3);

	adc_T = (int32_t)((data[0] << 12) | (data[1] << 4) | (data[2] >> 4));

	return BMP180_Compensate_Temperature(adc_T);
}

double BMP180_GetPressure() {

	int32_t adc_P;
	uint8_t data[3] = {0};

	BMP180_ReadRegisters(BMP180_REGISTER_PRESSURE_MSB, data, 3);

	adc_P = (int32_t)((data[0] << 12) | (data[1] << 4) | (data[2] >> 4));

	return BMP180_Compensate_Pressure(adc_P);
}

double BMP180_GetAltitude() {

	int32_t adc_P;
	uint8_t data[3] = {0};

	BMP180_ReadRegisters(BMP180_REGISTER_PRESSURE_MSB, data, 3);

	adc_P = (int32_t)((data[0] << 12) | (data[1] << 4) | (data[2] >> 4));

	return BMP180_Compensate_Pressure(adc_P);
}

void BMP180_GetTemperatureAndPressure(double *temperature, double *pressure) {

	int32_t adc_T, adc_P;
	uint8_t data[6] = {0};

	BMP180_ReadRegisters(BMP180_REGISTER_PRESSURE_MSB, data, 6);

	adc_P = (int32_t)((data[0] << 12) | (data[1] << 4) | (data[2] >> 4));
	adc_T = (int32_t)((data[3] << 12) | (data[4] << 4) | (data[5] >> 4));

	*temperature = BMP180_Compensate_Temperature(adc_T);
	*pressure = BMP180_Compensate_Pressure(adc_P);
}

void BMP180_GetTemperatureAndPressureForced(double *temperature, double *pressure) {

	// 20bit, Forced mode, 125ms, filter 2
	BMP180_SetRegisterConfig(BMP180_PRESET_CONFIG);
	BMP180_SetRegisterCtrlMeas(BMP180_PRESET_CTRL_MEAS_FORCED);

	delay_us(10000);

	*temperature = BMP180_GetTemperature();
	*pressure = BMP180_GetPressure();
}
