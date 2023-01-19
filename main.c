#include "lib/include.h"

//Experimento 3
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 500Hz , utilizando el uart se enviara dato desde interfaz de simulink ****
 * para controlar la intensidad luminosa usando un led RGB externa 
 */
 

    //Declaración de variables
    //Variables para colores
    volatile uint8_t color_rojo = 82; //tipo volatil para ir modificando su valor, 82 por su valor en ASCII de R 
    volatile uint8_t color_verde = 71; //Valor en ascii de G
    volatile uint8_t color_azul = 66; //Valor en ascii de B


    volatile uint16_t color;

int main(void)
{
    Configurar_PLL(_20MHZ);  //configuracion de velocidad de reloj
    Configurar_UART0();
    Configura_Reg_PWM1(8);

    //Para probar primero conectar tiva y después abrir simulink 

    while (1)
    {
        color = readChar();
        
        switch (color)
        {
            //COLOR SELECCIONADO AZUL
            case 'B':
                while (color_azul == 66)
                {
                    //Se lee el valor mandado por el UART para cambiar el ciclo de trabajo -> intensidad del led
                    color_azul = (int)readChar();
                }

                //Se hace la conversión para modificar el ciclo de trabajo del PWM -> intensidad del led
                //       PE4  40000:total de cuentas,  int_rojo: valor enviado por UART, las 16,000 cuentas equivalen al 40% de las cuentas
                PWM0->_2_CMPA = 40000-((int)(color_azul*16000)/40); 
                color_azul = 66;
            break;

            //COLOR SELECCIONADO VERDE
            case 'G':
                while (color_verde == 71)
                {
                    color_verde = (int)readChar();
                }

                //Se hace la conversión para modificar el ciclo de trabajo del PWM -> intensidad del led
                //       PB7  40000:total de cuentas,  int_rojo: valor enviado por UART, las 16,000 cuentas equivalen al 40% de las cuentas
                PWM0->_0_CMPB = 40000-((int)(color_verde*16000)/40); //PB7 (G)
                color_verde = 71;
            break;

            //COLOR SELECCIONADO ROJO
            case 'R':
                while (color_rojo == 82)
                {
                    color_rojo = (int)readChar(); //recibe el % del uart para calcular el dc%
                }

                //Se hace la conversión para modificar el ciclo de trabajo del PWM -> intensidad del led
                //       PB4  40000:total de cuentas,  int_rojo: valor enviado por UART, las 16,000 cuentas equivalen al 40% de las cuentas 
                PWM0->_1_CMPA = 40000-((int)(color_rojo*16000)/40); //PB4 (R)
                color_rojo = 82;
            break;

        }   
    }
}

