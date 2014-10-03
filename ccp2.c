#include<18F252.h>
#DEVICE ADC=10

#include<MATH.H>

#FUSES HS

#use delay(clock=16MHz)
//#use rs232(xmit=PIN_C6, baud=9600)

#define max			24
#define btn_pin		PIN_B0

short btn;
short ctrlbtn;

int pwm_cont1 = 8;

long pwm_duty[max] = { 512, 644, 768, 874, 955, 1006, 1023, 1006, 955, 874, 768,
		644, 512, 379, 256, 150, 68, 17, 1, 17, 68, 150, 256, 379 };

#INT_TIMER2
void isr_timer2() {
	clear_interrupt(INT_TIMER2);
	if (pwm_cont1 >= max)
		pwm_cont1 = 0;
	set_pwm1_duty(pwm_duty[pwm_cont1++]);
}

int main(void) {

	setup_timer_2(T2_DIV_BY_16, 0xFF, 16);

	setup_ccp1(CCP_OFF);

	set_pwm1_duty(pwm_duty[pwm_cont1++]);

	clear_interrupt(INT_TIMER2);

	delay_ms(100);

	while (TRUE) {

		btn = !input(btn_pin);

		if (btn && !ctrlbtn) {
			ctrlbtn = TRUE;
			setup_ccp1(CCP_PWM);
			clear_interrupt(INT_TIMER2);
			enable_interrupts(INT_TIMER2);
			enable_interrupts(GLOBAL);
		} else if (!btn && ctrlbtn) {
			ctrlbtn = FALSE;
			setup_ccp1(CCP_OFF);
		}
	}

	return 0;
}
