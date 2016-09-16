//#include<18F45K22.h>
//#DEVICE ADC=10
#include <16F877A.h>

//#FUSES HSM, PLLEN, CCP2C1
//#FUSES INTRC, PLLEN, CCP2C1
#fuses HS

//#use delay(internal=16MHz)
//#use delay(clock=60MHz, crystal=15MHz)
#use delay(clock=20MHz)
#use rs232(xmit=PIN_C6, baud=9600)

long leitura1;
long leitura2;
short dir;

long read(int canal) {
	set_adc_channel(canal);
	delay_us(100);
	return read_adc();
}

#zero_ram
int main(void) {

	setup_timer_2(T2_DIV_BY_1, 255, 1);
//	setup_timer_4(T4_DIV_BY_1, 255, 1);

//	setup_ccp1(CCP_PWM);
	setup_ccp2(CCP_PWM);

//	setup_adc_ports(sAN0 | sAN1);
//	setup_adc(ADC_CLOCK_INTERNAL);
//	set_adc_channel(0);
//	delay_us(100);
	leitura1 = 0;
	dir = TRUE;

	while (TRUE) {
//		leitura1 = read(0);
//		set_pwm1_duty(leitura1);

//		leitura2 = read(1);
		set_pwm2_duty(leitura1);

		if (dir)
			leitura1++;
		else
			leitura1--;

		if (leitura1 == 0xFF)
			dir = FALSE;
		if (leitura1 == 1)
			dir = TRUE;

//		printf("l1 %4lu - l2 %4lu\n\r", leitura1, leitura2);
//		delay_ms(1);
	}
	return 0;
}

