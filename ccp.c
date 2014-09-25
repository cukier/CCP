#include<18F252.h>
#DEVICE ADC=10

#include<MATH.H>

#FUSES HS

#use delay(clock=15MHz)
//#use rs232(xmit=PIN_C6, baud=9600)

#define max			24
#define sync_pin	PIN_B0
#define btn_pin		PIN_B1
#define trig_pin	PIN_C0
#define tmr0reg		44701
#define tmr1reg		3285

short sync;
short btn;
short ctlrSync;
short ctrlbtn;

long pwm_cont;

long pwm_duty[max] = { 512, 644, 768, 874, 955, 1006, 1023, 1006, 955, 874, 768,
		644, 512, 379, 256, 150, 68, 17, 1, 17, 68, 150, 256, 379 };

#INT_TIMER2
void isr_timer2() {
	clear_interrupt(INT_TIMER2);
	if (pwm_cont >= max)
		pwm_cont = 0;
	set_pwm1_duty(pwm_duty[pwm_cont++]);
}

#INT_TIMER1
void isr_timer1() {
	clear_interrupt(INT_TIMER1);
	disable_interrupts(INT_TIMER1);
	setup_ccp1(CCP_OFF);
}

#INT_TIMER0
void isr_timer0() {
	clear_interrupt(INT_TIMER0);
	disable_interrupts(INT_TIMER0);
	set_timer1(tmr1reg);
	clear_interrupt(INT_TIMER1);
	enable_interrupts(INT_TIMER1);
	output_low(trig_pin);
	delay_us(10);
	output_high(trig_pin);
}

int main(void) {
	output_high(trig_pin);

	setup_timer_0(T0_INTERNAL | T0_DIV_1);
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
	setup_timer_2(T2_DIV_BY_16, 0xFF, 16);

	setup_ccp1(CCP_OFF);
	set_pwm1_duty(512);

	clear_interrupt(INT_TIMER2);
	clear_interrupt(INT_TIMER1);
	clear_interrupt(INT_TIMER0);

	delay_ms(100);

	while (TRUE) {
		sync = !input(sync_pin);
		btn = !input(btn_pin);

		if (btn && !ctrlbtn) {
			ctrlbtn = TRUE;
			sync = TRUE;
		}

		if (sync && !ctlrSync) {
			ctlrSync = TRUE;
			ctrlbtn = TRUE;
			setup_ccp1(CCP_PWM);
			set_timer0(tmr0reg);
			clear_interrupt(INT_TIMER2);
			clear_interrupt(INT_TIMER0);
			enable_interrupts(INT_TIMER0);
			enable_interrupts(INT_TIMER2);
			enable_interrupts(GLOBAL);
		} else if (!sync && ctlrSync) {
			ctlrSync = FALSE;
		}
	}

	return 0;
}
