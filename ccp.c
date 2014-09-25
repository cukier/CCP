#include<18F252.h>
#DEVICE ADC=10

#include<MATH.H>

#FUSES HS

#use delay(clock=15MHz)
//#use rs232(xmit=PIN_C6, baud=9600)

#define max 24

long pwm_cont;

long pwm_duty[max] = { 512, 644, 768, 874, 955, 1006, 1023, 1006, 955, 874, 768,
		644, 512, 379, 256, 150, 68, 17, 1, 17, 68, 150, 256, 379 };

long get_sen(int index) {
	double ang = index * 47.1239 / 180;
	double aux = sin(ang);
	long ret = (aux + 1) * 512;
	return ret;
//	return (long) (sin(index * 47.1239 / 180) + 1) * 512;
}

#INT_TIMER2
void isr_timer2() {
	clear_interrupt(INT_TIMER2);
	if (pwm_cont >= max)
		pwm_cont = 0;
//	long teste = get_sen(pwm_cont);
//	long teste2 = pwm_duty[pwm_cont];
	set_pwm1_duty(pwm_duty[pwm_cont++]);
//	set_pwm1_duty(get_sen(pwm_cont++));
}

int main(void) {

	setup_timer_2(T2_DIV_BY_16, 0xFF, 16);

	setup_ccp1(CCP_PWM);
	set_pwm1_duty(512);

	clear_interrupt(INT_TIMER2);
	enable_interrupts(INT_TIMER2);
	enable_interrupts(GLOBAL);

	while (TRUE)
		;

	return 0;
}
