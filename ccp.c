#include <18F45K20.h>

//#FUSES H4
#FUSES HS

#use delay(clock=15MHz)
//#use delay(crystal=15MHz, clock=60MHz)
#use rs232(xmit=PIN_C6, baud=9600)

#INT_CCP1
void isr_ccp1() {
	clear_interrupt(INT_CCP1);
	set_timer3(0);
}

int main(void) {

	setup_ccp1(CCP_CAPTURE_FE);
	setup_timer_3(T3_INTERNAL | T3_DIV_BY_1 | T3_CCP1_TO_2);
//	setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
	enable_interrupts(INT_CCP1 | GLOBAL);

	while (TRUE) {
		printf("%lu\r\n", CCP_1);
		delay_ms(1000);
	}

	return 0;
}

/*#INT_CCP1
 void isr_ccp1() {
 clear_interrupt(INT_CCP1);
 cont = get_timer1();
 set_timer1(0);
 }

 int main(void) {

 float angulo;

 setup_ccp1(CCP_CAPTURE_FE);
 setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);

 enable_interrupts(INT_CCP1);
 enable_interrupts(GLOBAL);

 while (TRUE) {

 if (print) {
 print = FALSE;
 angulo = (float) pulsos / 256 * 360;
 if (angulo < 0)
 angulo += 360;
 printf("\fPf: %ld M: %ld", pulsos, max);
 printf("\nA:%.4f %lu");
 }
 }
 }*/
