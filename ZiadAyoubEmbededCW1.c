/*

  Ziad Ayoub CU1900705
  Coursework 1 Code
  Embedded System Design and Development
  2021 - 2022
  Version: V2

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
  ANSELC = 0;                     // Configure PORTC pins as digital
  ANSELD = 0;
  ANSELE = 0;


  TRISA=0b11111111;
  TRISD=0b11111111;
  TRISE=0;

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

  else if (LDRButton == 1){
      UART1_Write_Text("LDR Readings are ON! ");
      UART1_Write_Text("The room is: ");
  
      if (LDR >= 4000){
        UART1_Write_Text("very bright!");
      }

      else if (LDR >= 2200){
        UART1_Write_Text("bright!");
      }
      
      else if (LDR >= 1200){
        UART1_Write_Text("dim!");
      }
      
      else{
        UART1_Write_Text("dark!");
      }
      
      UART1_Write(13);
      UART1_Write(10);
    }


  UART1_Write_Text("The light level due to the variable resistor is: ");

  if (VarRis >= 2600){
    UART1_Write_Text("bright!");
    PORTE = 0b00000111;
  }

  else if (VarRis >= 1900){
    UART1_Write_Text("dim!");
    PORTE = 0b00000011;
  }
  
  else{
    UART1_Write_Text("low/OFF!");
    PORTE = 0b00000001;
  }
  

  UART1_Write(13);
  UART1_Write(10);
  UART1_Write_Text(" ");
  UART1_Write(13);
  UART1_Write(10);
  }
}