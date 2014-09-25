#include<18F252.h>
#DEVICE ADC=10

#FUSES HS

#use delay(clock=15MHz)
//#use rs232(xmit=PIN_C6, baud=9600)

#define max 24

long cont;

long pwm_duty[max] = { 512, 644, 768, 874, 955, 1006, 1023, 1006, 955, 874, 768,
		644, 512, 379, 256, 150, 68, 17, 1, 17, 68, 150, 256, 379 };

#INT_TIMER2
void isr_timer2() {
	clear_interrupt(INT_TIMER2);
	if (cont >= max)
		cont = 0;
	set_pwm1_duty(pwm_duty[cont++]);
}

int main(void) {

	setup_timer_2(T2_DIV_BY_1, 0xFF, 16);

	setup_ccp1(CCP_PWM);
	set_pwm1_duty(512);

	clear_interrupt(INT_TIMER2);
	enable_interrupts(INT_TIMER2);
	enable_interrupts(GLOBAL);

	while (TRUE)
		;

	return 0;
}
