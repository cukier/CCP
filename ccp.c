#include<18F252.h>

#include<STRING.H>

#FUSES HS

#use delay(clock=40MHz)
#use rs232(uart1, baud=9600)

#define ccp_nr 1040

int ctrl;

int comando_ligar[10] = "ligar\r";
int comando_desligar[10] = "desligar\r";
int comando_duty[10] = "dyty\r";
int string_comando[10] = "";

#int_ccp1
void ccp1_isr() {
	clear_interrupt(INT_CCP1);
	ctrl = !ctrl;
	if (ctrl) {
		setup_ccp1(CCP_COMPARE_SET_ON_MATCH);
		set_timer1(0);
		CCP_1 = ccp_nr;
	} else {
		setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
		set_timer1(0);
		CCP_1 = ccp_nr;
	}
}

int main(void) {

	while (TRUE) {
		gets(string_comando);
		if (!strcmp(string_comando, comando_ligar)) {
			setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
			set_timer1(0);
			setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
			CCP_1 = ccp_nr;
			clear_interrupt(INT_CCP1);
			enable_interrupts(INT_CCP1);
			enable_interrupts(GLOBAL);
		} else if (!strcmp(string_comando, comando_desligar)) {
			setup_timer_1(T1_DISABLED);
			set_timer1(0);
			CCP_1 = ccp_nr;
			clear_interrupt(INT_CCP1);
			disable_interrupts(INT_CCP1);
			disable_interrupts(GLOBAL);
		}
	}

	return 0;
}
