/*

  Ziad Ayoub CU1900705
  Coursework 1 Code
  Embedded System Design and Development
  2021 - 2022
  Version: V4

*/


// Initialization of variables
char uart_rd;
int LDR;						  // LDR reading
int VarRis;						  // Potentiometer reading 
int LDRButton;					  // Button staus wether 1 (readings toggeled on) or 0 (readings toggeled off)


void main() {

  UART1_Init(9600);               // Initialize UART module at 9600 bps
  Delay_ms(100);                  // Wait for UART module to stabilize

  UART1_Write_Text("Start");	  // Writes on the UART Terminal the word "Start" for visual confirmation of succesful UART Initialization
  UART1_Write(13);
  UART1_Write(10);


  ANSELA = 0b11111111;			  // Configure PORT A pins as analouge
  ANSELC = 0;                     // Configure PORT C pins as digital
  ANSELD = 0;					  // Configure PORT D pins as digital
  ANSELE = 0;					  // Configure PORT E pins as digital


  TRISA=0b11111111;			   	  // Configure PORT A pins as input
  TRISD=0b11111111;				  // Configure PORT D pins as input
  TRISE=0;						  // Configure PORT E pins as output

  LDRButton = 0;				  // Set LDRButton to 0 which turns readings off by defult,
								  // setting it to 1 would turn readings on.
  

  while(1){						  // Goes into infinite loop

  LDR = ADC_Read(1);			  // Reads LDR value through the analoug to digital converter through pin RA1
  VarRis = ADC_Read(0);			  // Reads Potentiometer value through the analoug to digital converter through pin RA0


  Delay_ms(1000);				  // Time delay of 1 sec between readings 
  
  
  // Checks if buttons RD7 or RD6 are pressed
  // If RD7 is pressed, readings from the LDR are taken
  // If RD6 is pressed, readings for the LDR are switched off 
  if (Button(&PORTD, 7, 10, 1)){LDRButton = 1;}
  if (Button(&PORTD, 6, 10, 1)){LDRButton = 0;}


  // If readings for the LDR are switched off, outputs visual message that it is off
  if (LDRButton == 0){
     UART1_Write_Text("LDR Readings are OFF!");
     UART1_Write(13);
     UART1_Write(10);
  }


  // If readings for the LDR are switched on, outputs visual message that it is on
  // It then takes the reading of the LDR and comapres it to the 4 preassigned ranges to determin the state of the room's brightness level
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


  // Takes the reading from the potentiometer and compares it to the 3 preassigned value
  // Depending on the potentiometer level, 1, 2, or 3, lighs on PORT E turn on
  // A visual message on the terminal is also displayed  
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
  

  // Creates an empty line to seprate between readings
  UART1_Write(13);
  UART1_Write(10);
  UART1_Write_Text(" ");
  UART1_Write(13);
  UART1_Write(10);
  }
}