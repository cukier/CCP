#include <18F45K20.h>

#FUSES H4

#use delay(crystal=15MHz, clock=60MHz)

int duty = 50;

int main(void) {

	setup_ccp1(CCP_PWM);
	setup_timer_2(T2_DIV_BY_1, 255, 1);
	set_pwm1_duty(230);

	while (TRUE)
		;
}
