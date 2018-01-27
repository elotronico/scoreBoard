// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#define kMatrixSerpentineLayout true    //tiras conectadas al reves
#include <Adafruit_NeoPixel.h>


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6


int Nfilas = 20;
int Ncol = 30;
int matriz_R[20][30]= { {},{} };

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      600

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second




void setup() {

  Serial.begin(115200);
  Serial.println("\n1 -iniciado    [ok]");
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  //borrar 

  Serial.println( (String)GeneraID(0,1) );
  Serial.println( (String)GeneraID(1,1) );
  Serial.println( (String)GeneraID(2,2) );

  
  //borrar

  pixels.begin(); // This initializes the NeoPixel library.
  Serial.println("2 -Pixels Begin    [ok]");
  delay(5000);
  
  clearMatrix2D();
  actualizaMatriz2D();
  Serial.println("3 - clearMatrix2D   [ok]");
  delay(5000);
}



void loop() {

  setPixel2D();
  Serial.println("fin setPixel");
  
  actualizaMatriz2D();
  Serial.println("fin ciclo # # # # # # # # # # # # # # # # # # # # # # # #");
  delay(5000);

}


/*
escribe valores en la matriz
*/
void setPixel2D(void){

  matriz_R[1][1]=255;
  matriz_R[2][1]=255;
  matriz_R[3][1]=255;
  matriz_R[4][1]=255;
  matriz_R[5][1]=255;
  matriz_R[6][1]=255;
  matriz_R[7][1]=255;
  matriz_R[8][1]=255;
  matriz_R[9][1]=255;
  matriz_R[10][1]=255;
}



void programa1D(void){

  for(int i=0; i<NUMPIXELS; i++){
      
      pixels.setPixelColor(i, pixels.Color(0,matriz_R[i],0)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).
  }
  
}







//valido para matriz 2 dimensiones
void actualizaMatriz2D(void){

  int contadorPix = 0;
  Serial.println("inicio Programa ACTUALIZAR MATRIZ **************");
  
  for(int fila=0; fila<Nfilas; fila++){
        
        for(int col=0; col<Ncol; col++){
            
            pixels.setPixelColor(contadorPix, pixels.Color(0,matriz_R[fila][col],0)); // Moderately bright green color.
                  
            contadorPix++;
         }
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

    Serial.println("Salimos de ACTUALIZAR MATRIZ ************");
    delay(5000);
    
}

/*
parauna matriz 1D
*/
void programa1(void){

  
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,matriz_R[i],0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  
}



/*
matriz 2D
*/
void clearMatrix2D(void){
  
  Serial.println("iniciando borrado de matriz");
  
  for(int fila=0; fila<Nfilas; fila++){
        
        for(int col=0; col<Ncol; col++){

            //Serial.print("Pos: " + (String)fila + "-" + (String)col + " => " +(String)matriz_R[fila][col] + " -> ");
            matriz_R[fila][col] = 0;
            //Serial.println( (String)matriz_R[fila][col] );
            
        }
  }

    Serial.println("borrado de matriz completado"); 
    delay(1000);
  
  }
