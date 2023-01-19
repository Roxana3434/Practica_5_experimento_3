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

//Variable para guardar el ciclo de trabajo enviado por UART y modificar intensidad
volatile uint8_t intensidad = 0;

volatile uint16_t color;  

int main(void)
{
    
    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj
    Configurar_UART0();//se usa UART0
    Configura_Reg_PWM1(8);

    //Para probar primero conectar tiva y después abrir simulink 
    
    while (1)
    {
        //Se lee el valor mandado por el UART para seleccionar el color
        color = readChar(); 

        switch (color)
        {
            //COLOR SELECCIONADO AZUL
            case 'B':
                color_azul = 66;
                while (color_azul == 66)
                {
                    intensidad = (int)readChar();
                    color_azul = 0;
                }

                //Se hace la conversión para modificar el ciclo de trabajo del PWM -> intensidad del led
                //       PE4  40000:total de cuentas,  int_rojo: valor enviado por UART, las 16,000 cuentas equivalen al 40% de las cuentas 
                PWM0 ->_2_CMPA = 40000 - ((int)(intensidad*16000)/40); 
            break;

            //COLOR SELECCIONADO VERDE
            case 'G':
                color_verde = 71;
                while (color_verde == 71)
                {
                    intensidad = (int)readChar();
                    color_verde = 0;
                }

                //Se hace la conversión para modificar el ciclo de trabajo del PWM -> intensidad del led
                //       PB7  40000:total de cuentas,  int_rojo: valor enviado por UART, las 16,000 cuentas equivalen al 40% de las cuentas 
                PWM0 ->_0_CMPB = 40000 - ((int)(intensidad*16000)/40); 
            break;

            //COLOR SELECCIONADO ROJO
            case 'R':
                color_rojo = 82;
                while (color_rojo == 82)
                {
                    //Se lee el valor mandado por el UART para cambiar el ciclo de trabajo -> intensidad del led
                    intensidad = (int)readChar(); 
                    color_rojo = 0;
                }

                //Se hace la conversión para modificar el ciclo de trabajo del PWM -> intensidad del led
                //       PB4  40000:total de cuentas,  int_rojo: valor enviado por UART, las 16,000 cuentas equivalen al 40% de las cuentas 
                PWM0 ->_1_CMPA = 40000 - ((int)(intensidad*16000)/40); 
            break;

        }
        
    }
    
}

