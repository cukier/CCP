#include<18F252.h>
#DEVICE ADC=10

#FUSES HS

#use delay(clock=15MHz)
#use rs232(xmit=PIN_C6, baud=9600)

long leitura;

#zero_ram
int main(void) {

	setup_timer_2(T2_DIV_BY_1, 255, 16);

	setup_ccp1(CCP_PWM);

	setup_adc_ports(AN0);
	setup_adc(ADC_CLOCK_INTERNAL);
	set_adc_channel(0);
	delay_us(100);

	while (TRUE) {
		leitura = read_adc();
		set_pwm1_duty(leitura);
		printf("%lu\n\r", leitura);
		delay_ms(750);
	}
	return 0;
}

