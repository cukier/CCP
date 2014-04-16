#include <18F252.h>

#FUSES HS

#use delay(clock=8MHz)
#use rs232(xmit=PIN_C6, baud=9600)

short ctrl = FALSE;
int cont = 10;
int duty = 0;
long tempoAux = 0;

int main(void) {

   setup_ccp1(CCP_PWM);
   setup_timer_2(T2_DIV_BY_1, 255, 1);
   set_pwm1_duty(127);

   while (TRUE) {
         duty = (int) cont * 2.55;
         set_pwm1_duty(duty);
         printf("\n\rduty: %d, cont: %d", duty, cont);
         cont = !ctrl ? cont + 10 : cont - 10;
         if (cont == 90)
            ctrl = TRUE;
         else if (cont == 10)
            ctrl = FALSE;
         delay_ms(300);
   }

   return 0;
}
