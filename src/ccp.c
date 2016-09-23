#include <16F877A.h>

#fuses HS

#use delay(clock=20MHz)

#define ccp_nr 60000

short ctrl1;
int cont = 0;
long count;

long read(int canal) {
	set_adc_channel(canal);
	delay_us(100);
	return read_adc();
}

#int_ccp1
void ccp1_isr() {
	clear_interrupt(INT_CCP1);

	if (!ctrl1) {
		setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
		set_timer1(0);
		cont++;
	} else {
		setup_ccp1(CCP_COMPARE_SET_ON_MATCH);
		set_timer1(0);
	}

	CCP_1 = ccp_nr;
	ctrl1++;

	if (cont == 7) {
		cont = 0;
		disable_interrupts(INT_CCP1);
		enable_interrupts(INT_CCP2);
		set_timer0(0);
		setup_ccp2(CCP_CAPTURE_RE);
	}
}

#int_ccp2
void ccp2_isr() {
	clear_interrupt(INT_CCP2);
}

#zero_ram
int main(void) {

	ctrl1 = TRUE;

	set_timer1(0);
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);

	setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
	CCP_1 = ccp_nr;

	clear_interrupt(INT_CCP1);
	enable_interrupts(INT_CCP1);
	enable_interrupts(GLOBAL);

	while (TRUE) {

	}

	return 0;
}

