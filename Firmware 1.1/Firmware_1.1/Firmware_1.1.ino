// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      600

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
int Nfilas = 20;
int Ncol = 30;
int matriz_R[20][30]= {{},{}};



void setup() {

  Serial.begin(9600);
  Serial.println("iniciado");
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  Serial.println("fin Setup");
}



void loop() {

  setPixel();
  Serial.println("fin setPixel");
  programa3();
  Serial.println("fin programa 2");
  delay(500);

}



void setPixel(void){

    matriz_R[1][1]=255;
    matriz_R[3][3]=255;
  
}


void programa2(void){
//valido para matriz 1 dimension
  for(int i=0; i<NUMPIXELS; i++){
      
      pixels.setPixelColor(i, pixels.Color(0,matriz_R[i],0)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).
  }
  
}







//valido para matriz 2 dimensiones
void programa3(void){

  int contadorPix = 0;
  Serial.println("inicio Programa 3");
  
  for(int fila=0; fila<Nfilas; fila++){
        
        for(int col=0; col<Ncol; col++){
            
            pixels.setPixelColor(contadorPix, pixels.Color(0,matriz_R[col][fila],0)); // Moderately bright green color.
            pixels.show(); // This sends the updated pixel color to the hardware.
      
            //delay(delayval); // Delay for a period of time (in milliseconds).
            contadorPix++;
            Serial.println("Pix: " + (String)contadorPix);
            Serial.println("Pos: " + (String)fila + "-" + (String)col );
            
        }
  }

    Serial.println("Salimos Programa 3");
}



void programa1(void){

  
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,matriz_R[i],0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  
}

