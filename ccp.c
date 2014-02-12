#include <18F45K20.h>

#FUSES H4

#use delay(crystal=15MHz, clock=60MHz)
#use rs232(xmit=PIN_C6, baud=9600)

int cont = 0;
int duty = 0;
long tempoAux = 0;
short ctrl = TRUE;
int main(void) {

	setup_ccp1(CCP_PWM);
	setup_timer_2(T2_DIV_BY_1, 255, 1);
	set_pwm1_duty(127);

	while (TRUE) {
//		cont = ctrl ? cont + 10 : cont - 10;
//		if (cont == 30)
//			ctrl = TRUE;
//		else if (cont == 127)
//			ctrl = FALSE;
//		set_pwm1_duty(cont);
//		delay_ms(100);
		if (!input(PIN_B0) && ctrl) {
			ctrl = FALSE;
			delay_ms(300);
			set_pwm1_duty(cont);
			printf("\fduty: %u", cont);
			cont += 8;

		} else if (input(PIN_B0) && !ctrl)
			ctrl = TRUE;
	}

	return 0;
}
