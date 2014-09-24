#include<18F252.h>
#DEVICE ADC=10

#FUSES HS

#use delay(clock=15MHz)
//#use rs232(xmit=PIN_C6, baud=9600)

#define latencia 200

long cont, read, aux;

int main(void) {

	setup_adc(ADC_CLOCK_INTERNAL);
	setup_adc_ports(AN0);
	set_adc_channel(0);

	setup_timer_2(T2_DIV_BY_1, 0xFF, 1);

	setup_ccp1(CCP_PWM);
	set_pwm1_duty(512);

	while (TRUE) {

		delay_us(10);
		read = read_adc();
		if (aux != read) {
			aux = read;
			set_pwm1_duty(read_adc());
//			printf("pwm: %lu\n\r", read);
		}
	}

	return 0;
}
