/*

  Ziad Ayoub CU1900705
  Coursework 1 Code
  Embedded System Design and Development
  2021 - 2022
  Version: V1
  
*/


char uart_rd;
int LDR;
int VarRis;
int LDRButton;

void main() {

  UART1_Init(9600);               // Initialize UART module at 9600 bps
  Delay_ms(100);                  // Wait for UART module to stabilize

  UART1_Write_Text("Start");
  UART1_Write(13);
  UART1_Write(10);


  ANSELA = 0b11111111;
  ANSELD = 0;
  ANSELC = 0;                     // Configure PORTC pins as digital

  TRISA=0b11111111;
  TRISD=0b11111111;

  LDRButton = 0;

  while(1){

  LDR = ADC_Read(1);
  VarRis = ADC_Read(0);
  
  
  Delay_ms(1000);
  if (Button(&PORTD, 7, 10, 1)){LDRButton = 1;}
  if (Button(&PORTD, 6, 10, 1)){LDRButton = 0;}


  if (LDRButton == 0){
     UART1_Write_Text("LDR Readings are OFF!");
     UART1_Write(13);
     UART1_Write(10);
  }

  else if (LDRButton == 1)
  {
      UART1_Write_Text("LDR Readings are ON!");

      if (LDR>=4000){
        UART1_Write_Text("The room is very bright");
        UART1_Write(13);
        UART1_Write(10);
      }

      else if (LDR>=2200){
        UART1_Write_Text("The room is bright");
        UART1_Write(13);
        UART1_Write(10);
      }
	  
      else if (LDR>=1200){
        UART1_Write_Text("The room is dim");
        UART1_Write(13);
        UART1_Write(10);
      }

      else if (LDR>=0){
        UART1_Write_Text("The room is dark");
        UART1_Write(13);
        UART1_Write(10);
      }
    }
  
  UART1_Write_Text("Variable Resistor Level: ");
  UART1_Write(VarRis);
  UART1_Write(13);
  UART1_Write(10);
  
  }
}