#include<18F252.h>

#FUSES HS

#use delay(clock=15MHz)
#use rs232(xmit=PIN_C6, baud=9600)

int main(void) {

	setup_timer_2(T2_DIV_BY_1, 0xFF, 1);

	setup_ccp1(CCP_PWM);
	set_pwm1_duty(512);

	while (TRUE) {



	}

	return 0;
}
