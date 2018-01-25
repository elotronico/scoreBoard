/*changelog
0.01 primera version
0.02 añadido punto para indicar quien saca, empezando siempre por el equipo de la linea superior
0.03 añadida una pantalla previa para jugar el punto de saque y así determinar si empieza sacando el equipo A (linea superior) o el equipo B (linea inferior)
0.04 cambio en el código. Añadir y quitar puntos son funciones ahora y no están a saco en la sentencia loop
*/

#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include <Button.h>

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
#define DISPLAYS_BPP 1
#define WHITE 0xFF
#define BLACK 0

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN, DISPLAYS_BPP);


// Global variables

int          POINT_A = 0;                // Actual game points player A 
int          POINT_B = 0;                // Actual game points player B
int          GAME1_A = 0;
int          GAME2_A = 0;
int          GAME3_A = 0;
int          GAME1_B = 0;
int          GAME2_B = 0;
int          GAME3_B = 0;
int          SET = 1;                   // Set 1, 2 or 3
int          START = 0;                 //USED TO START BALL
int          tA = 0;
int          tB = 0;
int          i = 0;                     //declared global in the for iteration in order to not enter each time inside loop
boolean      tb_saque = false;          //necessary to determine who is starting during tie break
boolean      tie = false;               //may be not necessary to be global variable, but from here to the end if you are a programmer your eyes will burn....I am not ;)
char         STR_PT_A[3]="00";
char         STR_PT_B[3]="00";
boolean      system_useSpeaker = true;

Button       BTN_A = Button(A5, BUTTON_PULLUP);
Button       BTN_B = Button(A4, BUTTON_PULLUP);
Button       BTN_C = Button(A3, BUTTON_PULLUP);
Button       BTN_D = Button(A2, BUTTON_PULLUP);
int          PINS_BUZZER = A0;


/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}


//Increase game of player A depending on wich set we are
void increase_gameA(){
  if(SET == 1){GAME1_A ++;}
  else if (SET == 2){GAME2_A ++;}
  else {GAME3_A ++;}
}

//Increase game of player B depending on wich set we are
void increase_gameB(){
  if(SET == 1){GAME1_B ++;}
  else if (SET == 2){GAME2_B ++;}
  else {GAME3_B ++;}
}

//beeps the buzzer
void buzzer_beep(int time){
    analogWrite(PINS_BUZZER, 255); 
    delay(time); 
    analogWrite(PINS_BUZZER, 0);
}

//TIEBREAK
void tiebreak(int SET){
  dmd.clearScreen( BLACK );
  tA = 0; tB = 0; 
  tie = true;
  int temp = 1;  
  if (((GAME1_A + GAME2_A + GAME3_A + GAME1_B + GAME2_B + GAME3_B + START)%2) == 0){
      dmd.drawBox(19, 5, 20, 6, WHITE);
      tb_saque = true;}
  else {dmd.drawBox(19, 14, 20, 15, WHITE); tb_saque = false;
  }
  print_matrix();
  while (tie == true){
    if(BTN_A.uniquePress()){tA ++;buzzer_beep(200); temp = temp++;
      if((tA >= 7 || tB >= 7) && (abs(tA - tB) >= 2) && (abs(tA - tB) == (tA - tB))) {print_matrix(); delay(2000); if (SET == 1){GAME1_A++; SET++; tie = false;} else if (SET == 2){GAME2_A++; SET++; tie = false;} else if (SET == 3){GAME3_A++; SET++; tie = false;}} 
      else if((tA >= 7 || tB >= 7) && (abs(tA - tB) >= 2) && (abs(tA - tB) == (tB - tA))){print_matrix(); delay(2000); if (SET == 1){GAME1_B++; SET++; tie = false;} else if (SET == 2){GAME2_B++; SET++; tie = false;} else if (SET == 3){GAME3_B++; SET++; tie = false;}}
      if (temp == 2) {tb_saque = !tb_saque; temp =0;}
      print_matrix();
    }  
    if(BTN_B.uniquePress()){tB ++;buzzer_beep(350); temp = temp++;
      if((tA >= 7 || tB >= 7) && (abs(tA - tB) >= 2) && (abs(tA - tB) == (tA - tB))) {print_matrix(); delay(2000); if (SET == 1){GAME1_A++; SET++; tie = false;} else if (SET == 2){GAME2_A++; SET++; tie = false;} else if (SET == 3){GAME3_A++; SET++; tie = false;}}
      else if((tA >= 7 || tB >= 7) && (abs(tA - tB) >= 2) && (abs(tA - tB) == (tB - tA))){print_matrix(); delay(2000); if (SET == 1){GAME1_B++; SET++; tie = false;} else if (SET == 2){GAME2_B++; SET++; tie = false;} else if (SET == 3){GAME3_B++; SET++; tie = false;}}
      if (temp == 2) {tb_saque = !tb_saque; temp =0;}
      print_matrix();
    }
    if(BTN_C.uniquePress()){tA --; if(temp==0){temp=1; tb_saque=!tb_saque;}
      if((tA >= 7 || tB >= 7) && (abs(tA - tB) >= 2) && (abs(tA - tB) == (tA - tB))) {print_matrix(); delay(2000); if (SET == 1){ GAME1_A++; SET++; tie = false;} else if (SET == 2){ GAME2_A++; SET++; tie = false;} else if (SET == 3){ GAME3_A++; SET++; tie = false;}}
      else if((tA >= 7 || tB >= 7) && (abs(tA - tB) >= 2) && (abs(tA - tB) == (tB - tA))){print_matrix(); delay(2000); if (SET == 1){ GAME1_B++; SET++; tie = false;} else if (SET == 2){ GAME2_B++; SET++; tie = false;} else if (SET == 3){ GAME3_B++; SET++; tie = false;}}
      else {print_matrix();}
    }
    if(BTN_D.uniquePress()){tB --; if(temp==0){temp=1; tb_saque=!tb_saque;}
      if((tA >= 7 || tB >= 7) && (abs(tA - tB) >= 2) && (abs(tA - tB) == (tA - tB))) {print_matrix(); delay(2000); if (SET == 1){GAME1_A++; SET++; tie = false;} else if (SET == 2){GAME2_A++; SET++; tie = false;} else if (SET == 3){GAME3_A++; SET++; tie = false;}}
      else if((tA >= 7 || tB >= 7) && (abs(tA - tB) >= 2) && (abs(tA - tB) == (tB - tA))){print_matrix(); delay(2000); if (SET == 1){GAME1_B++; SET++; tie = false;} else if (SET == 2){GAME2_B++; SET++; tie = false;} else if (SET == 3){GAME3_B++; SET++; tie = false;}}
      else {print_matrix();}
    }   
  }
}

void add_point_a(){
//SUMAR PUNTO EQUIPO A....TATATATATATATAAAAAA
  POINT_A ++; buzzer_beep(200);
  if((POINT_A > 3 || POINT_B > 3) && (abs(POINT_A - POINT_B) >= 2)) {
    if (abs(POINT_A - POINT_B) == (POINT_A - POINT_B)) { increase_gameA(); POINT_A = 0; POINT_B = 0; buzzer_beep(100);}
    else {increase_gameB(); POINT_A = 0; POINT_B = 0; buzzer_beep(100);}
  }
  if(SET == 1){ 
    if (GAME1_A >= 6 && ((GAME1_A - GAME1_B) >= 2)){ SET ++; }
    else if (GAME1_B >= 6 && ((GAME1_B - GAME1_A) >= 2)){ SET ++;}
    else if ((GAME1_A == 6) && (GAME1_B == 6)){ tiebreak(SET);}
  }  
  if(SET == 2){ 
    if (GAME2_A >= 6 && ((GAME2_A - GAME2_B) >= 2)){ SET ++;}
    else if (GAME2_B >= 6 && ((GAME2_B - GAME2_A) >= 2)){ SET ++;}
    else if ((GAME2_A == 6) && (GAME2_B == 6)){ tiebreak(SET);}
  }
  if(SET == 3){ 
    if (GAME3_A >= 6 && ((GAME3_A - GAME3_B) >= 2)){ SET ++;}
    else if (GAME3_B >= 6 && ((GAME3_B - GAME3_A) >= 2)){ SET ++;}
    else if ((GAME3_A == 6) && (GAME3_B == 6)){ tiebreak(SET);}
  }  
  print_matrix();
  delay(300);
}

void add_point_b(){
//SUMAR PUNTO EQUIPO B
  POINT_B ++; buzzer_beep(350);
  if((POINT_A > 3 || POINT_B > 3) && (abs(POINT_A - POINT_B) >= 2)) {
    if (abs(POINT_A - POINT_B) == (POINT_A - POINT_B)) { increase_gameA(); POINT_A = 0; POINT_B = 0; buzzer_beep(200);}
    else {increase_gameB(); POINT_A = 0; POINT_B = 0; buzzer_beep(200);}
  }
  if(SET == 1){ 
    if (GAME1_A >= 6 && ((GAME1_A - GAME1_B) >= 2)){ SET ++; }
    else if (GAME1_B >= 6 && ((GAME1_B - GAME1_A) >= 2)){ SET ++;}
    else if ((GAME1_A == 6) && (GAME1_B == 6)){ tiebreak(SET);}
  }  
  if(SET == 2){ 
    if (GAME2_A >= 6 && ((GAME2_A - GAME2_B) >= 2)){ SET ++;}
    else if (GAME2_B >= 6 && ((GAME2_B - GAME2_A) >= 2)){ SET ++;}
    else if ((GAME2_A == 6) && (GAME2_B == 6)){ tiebreak(SET);}
  }
  if(SET == 3){ 
    if (GAME3_A >= 6 && ((GAME3_A - GAME3_B) >= 2)){ SET ++;}
    else if (GAME3_B >= 6 && ((GAME3_B - GAME3_A) >= 2)){ SET ++;}
    else if ((GAME3_A == 6) && (GAME3_B == 6)){ tiebreak(SET);}
  }  
  delay(300);
  print_matrix();
}

void subs_point_a(){
//QUITA PUNTO EQUIPO A
if(POINT_A > 0){  POINT_A --;}
  else if(SET == 1 && GAME1_A != 0){ GAME1_A --; POINT_A = 3; POINT_B= 3;}
  else if(SET == 2 && GAME2_A != 0){ GAME2_A --; POINT_A = 3; POINT_B= 3;}
  else if(SET == 2 && GAME2_A == 0){ SET = 1; GAME1_A = 5; GAME1_B = 5; POINT_A = 3; POINT_B = 3;}
  else if(SET == 3 && GAME3_A != 0){ GAME3_A --; POINT_A = 3; POINT_B= 3;}
  else if(SET == 3 && GAME3_A == 0){ SET = 2; GAME2_A = 5; GAME2_B = 5; POINT_A = 3; POINT_B = 3;}
  if((POINT_A > 3 || POINT_B > 3) && (abs(POINT_A - POINT_B) >= 2)) {
    if (abs(POINT_A - POINT_B) == (POINT_A - POINT_B)) { increase_gameA(); POINT_A = 0; POINT_B = 0; buzzer_beep(200);}
    else {increase_gameB(); POINT_A = 0; POINT_B = 0; buzzer_beep(200);}
  }
  if(SET == 1){ 
    if (GAME1_A >= 6 && ((GAME1_A - GAME1_B) >= 2)){ SET ++; }
    else if (GAME1_B >= 6 && ((GAME1_B - GAME1_A) >= 2)){ SET ++;}
    else if ((GAME1_A == 6) && (GAME1_B == 6)){ tiebreak(SET);}
  }  
  if(SET == 2){ 
    if (GAME2_A >= 6 && ((GAME2_A - GAME2_B) >= 2)){ SET ++;}
    else if (GAME2_B >= 6 && ((GAME2_B - GAME2_A) >= 2)){ SET ++;}
    else if ((GAME2_A == 6) && (GAME2_B == 6)){ tiebreak(SET);}
  }
  if(SET == 3){ 
    if (GAME3_A >= 6 && ((GAME3_A - GAME3_B) >= 2)){ SET ++;}
    else if (GAME3_B >= 6 && ((GAME3_B - GAME3_A) >= 2)){ SET ++;}
    else if ((GAME3_A == 6) && (GAME3_B == 6)){ tiebreak(SET);}
  }  
  delay(300);
  print_matrix();
}

void subs_point_b(){
//QUITA PUNTO EQUIPO B
if(POINT_B > 0){  POINT_B --;}
  else if(SET == 1 && GAME1_B != 0){ GAME1_B --; POINT_A = 3; POINT_B= 3;}
  else if(SET == 2 && GAME2_B != 0){ GAME2_B --; POINT_A = 3; POINT_B= 3;}
  else if(SET == 2 && GAME2_B == 0){ SET = 1; GAME1_A = 5; GAME1_B = 5; POINT_A = 3; POINT_B = 3;}
  else if(SET == 3 && GAME3_B != 0){ GAME3_B --; POINT_A = 3; POINT_B= 3;}
  else if(SET == 3 && GAME3_B == 0){ SET = 2; GAME2_A = 5; GAME2_B = 5; POINT_A = 3; POINT_B = 3;}
  if((POINT_A > 3 || POINT_B > 3) && (abs(POINT_A - POINT_B) >= 2)) {
    if (abs(POINT_A - POINT_B) == (POINT_A - POINT_B)) { increase_gameA(); POINT_A = 0; POINT_B = 0; buzzer_beep(200);}
    else {increase_gameB(); POINT_A = 0; POINT_B = 0; buzzer_beep(200);}
  }
  if(SET == 1){ 
    if (GAME1_A >= 6 && ((GAME1_A - GAME1_B) >= 2)){ SET ++; }
    else if (GAME1_B >= 6 && ((GAME1_B - GAME1_A) >= 2)){ SET ++;}
    else if ((GAME1_A == 6) && (GAME1_B == 6)){ tiebreak(SET);}
  }  
  else if(SET == 2){ 
    if (GAME2_A >= 6 && ((GAME2_A - GAME2_B) >= 2)){ SET ++;}
    else if (GAME2_B >= 6 && ((GAME2_B - GAME2_A) >= 2)){ SET ++;}
    else if ((GAME2_A == 6) && (GAME2_B == 6)){ tiebreak(SET);}
  }
  else if(SET == 3){ 
    if (GAME3_A >= 6 && ((GAME3_A - GAME3_B) >= 2)){ SET ++;}
    else if (GAME3_B >= 6 && ((GAME3_B - GAME3_A) >= 2)){ SET ++;}
    else if ((GAME3_A == 6) && (GAME3_B == 6)){ tiebreak(SET);}
  }  
  delay(300);
  print_matrix();
}

void print_matrix(){
  //CADENA STR PARA REPRESENTAR PUNTOS
  dmd.clearScreen(0);
  if(POINT_A == 0){ STR_PT_A[0]='0';STR_PT_A[1]='0';}
  else if (POINT_A == 1){ STR_PT_A[0]='1'; STR_PT_A[1]='5';}
  else if (POINT_A == 2){ STR_PT_A[0]='3'; STR_PT_A[1]='0';}
  else if (POINT_A == 3){ STR_PT_A[0]='4'; STR_PT_A[1]='0';}
  else if ((POINT_A > 3) && (POINT_A == POINT_B)){ STR_PT_A[0]='4'; STR_PT_A[1]='0';}
  else if ((POINT_A > 3) && (POINT_A > POINT_B)){ STR_PT_A[0]='V'; STR_PT_A[1]='E'; STR_PT_B[0]='-'; STR_PT_B[1]='-';}
  
  if(POINT_B == 0){ STR_PT_B[0] = '0';STR_PT_B[1]='0';}
  else if (POINT_B == 1){ STR_PT_B[0]='1'; STR_PT_B[1]='5';}
  else if (POINT_B == 2){ STR_PT_B[0]='3'; STR_PT_B[1]='0';}
  else if (POINT_B == 3 && POINT_A <=3){ STR_PT_B[0]='4'; STR_PT_B[1]='0';}
  else if ((POINT_B > 3) && (POINT_A == POINT_B)){ STR_PT_B[0]='4'; STR_PT_B[1]='0';}
  else if ((POINT_B > 3) && (POINT_A < POINT_B)){ STR_PT_B[0] = 'V'; STR_PT_B[1]='E'; STR_PT_A[0]='-'; STR_PT_A[1]='-';}
  
  if(tie==true){
    char CHAR1_A;
    if(GAME1_A==0){CHAR1_A='0';}
    else if(GAME1_A==1){CHAR1_A='1';}
    else if(GAME1_A==2){CHAR1_A='2';}
    else if(GAME1_A==3){CHAR1_A='3';}
    else if(GAME1_A==4){CHAR1_A='4';}
    else if(GAME1_A==5){CHAR1_A='5';}
    else if(GAME1_A==6){CHAR1_A='6';}
    else if(GAME1_A==7){CHAR1_A='7';}
    char CHAR2_A;
    if(GAME2_A==0){CHAR2_A='0';}
    else if(GAME2_A==1){CHAR2_A='1';}
    else if(GAME2_A==2){CHAR2_A='2';}
    else if(GAME2_A==3){CHAR2_A='3';}
    else if(GAME2_A==4){CHAR2_A='4';}
    else if(GAME2_A==5){CHAR2_A='5';}
    else if(GAME2_A==6){CHAR2_A='6';}
    else if(GAME2_A==7){CHAR2_A='7';}
    char CHAR3_A;
    if(GAME3_A==0){CHAR3_A='0';}
    else if(GAME3_A==1){CHAR3_A='1';}
    else if(GAME3_A==2){CHAR3_A='2';}
    else if(GAME3_A==3){CHAR3_A='3';}
    else if(GAME3_A==4){CHAR3_A='4';}
    else if(GAME3_A==5){CHAR3_A='5';}
    else if(GAME3_A==6){CHAR3_A='6';}
    else if(GAME3_A==7){CHAR3_A='7';}
    char CHAR1_B;
    if(GAME1_B==0){CHAR1_B='0';}
    else if(GAME1_B==1){CHAR1_B='1';}
    else if(GAME1_B==2){CHAR1_B='2';}
    else if(GAME1_B==3){CHAR1_B='3';}
    else if(GAME1_B==4){CHAR1_B='4';}
    else if(GAME1_B==5){CHAR1_B='5';}
    else if(GAME1_B==6){CHAR1_B='6';}
    else if(GAME1_B==7){CHAR1_B='7';}
    char CHAR2_B;
    if(GAME2_B==0){CHAR2_B='0';}
    else if(GAME2_B==1){CHAR2_B='1';}
    else if(GAME2_B==2){CHAR2_B='2';}
    else if(GAME2_B==3){CHAR2_B='3';}
    else if(GAME2_B==4){CHAR2_B='4';}
    else if(GAME2_B==5){CHAR2_B='5';}
    else if(GAME2_B==6){CHAR2_B='6';}
    else if(GAME2_B==7){CHAR2_B='7';}
    char CHAR3_B;
    if(GAME3_B==0){CHAR3_B='0';}
    else if(GAME3_B==1){CHAR3_B='1';}
    else if(GAME3_B==2){CHAR3_B='2';}
    else if(GAME3_B==3){CHAR3_B='3';}
    else if(GAME3_B==4){CHAR3_B='4';}
    else if(GAME3_B==5){CHAR3_B='5';}
    else if(GAME3_B==6){CHAR3_B='6';}
    else if(GAME3_B==7){CHAR3_B='7';}
    
    char CHAR_tA[3];
    itoa(tA, CHAR_tA, 10);
    if (tA < 10) {
        CHAR_tA[1] = CHAR_tA[0];
        CHAR_tA[0] = ' ';
    }
    
    char CHAR_tB[3];
    itoa(tB, CHAR_tB, 10);   
    if (tB < 10) {
        CHAR_tB[1] = CHAR_tB[0];
        CHAR_tB[0] = ' ';
    }
    dmd.drawChar(0, 0, CHAR1_A, WHITE, BLACK);
    dmd.drawChar(6, 0, CHAR2_A, WHITE, BLACK);
    dmd.drawChar(12, 0, CHAR3_A, WHITE, BLACK);
    dmd.drawChar(21, 0, CHAR_tA[0], WHITE, BLACK);
    dmd.drawChar(27, 0, CHAR_tA[1], WHITE, BLACK);
    dmd.drawChar(0, 9, CHAR1_B, WHITE, BLACK);
    dmd.drawChar(6, 9, CHAR2_B, WHITE, BLACK);
    dmd.drawChar(12, 9, CHAR3_B, WHITE, BLACK);
    dmd.drawChar(21, 9, CHAR_tB[0], WHITE, BLACK);
    dmd.drawChar(27, 9, CHAR_tB[1], WHITE, BLACK);
    if (tb_saque == true){
      dmd.drawBox(19, 5, 20, 6, WHITE);}
    else {dmd.drawBox(19, 14, 20, 15, WHITE);
    }
  }  
  else if(tie==false){
    char CHAR1_A;
    if(GAME1_A==0){CHAR1_A='0';}
    else if(GAME1_A==1){CHAR1_A='1';}
    else if(GAME1_A==2){CHAR1_A='2';}
    else if(GAME1_A==3){CHAR1_A='3';}
    else if(GAME1_A==4){CHAR1_A='4';}
    else if(GAME1_A==5){CHAR1_A='5';}
    else if(GAME1_A==6){CHAR1_A='6';}
    else if(GAME1_A==7){CHAR1_A='7';}
    char CHAR2_A;
    if(GAME2_A==0){CHAR2_A='0';}
    else if(GAME2_A==1){CHAR2_A='1';}
    else if(GAME2_A==2){CHAR2_A='2';}
    else if(GAME2_A==3){CHAR2_A='3';}
    else if(GAME2_A==4){CHAR2_A='4';}
    else if(GAME2_A==5){CHAR2_A='5';}
    else if(GAME2_A==6){CHAR2_A='6';}
    else if(GAME2_A==7){CHAR2_A='7';}
    char CHAR3_A;
    if(GAME3_A==0){CHAR3_A='0';}
    else if(GAME3_A==1){CHAR3_A='1';}
    else if(GAME3_A==2){CHAR3_A='2';}
    else if(GAME3_A==3){CHAR3_A='3';}
    else if(GAME3_A==4){CHAR3_A='4';}
    else if(GAME3_A==5){CHAR3_A='5';}
    else if(GAME3_A==6){CHAR3_A='6';}
    else if(GAME3_A==7){CHAR3_A='7';}
    char CHAR1_B;
    if(GAME1_B==0){CHAR1_B='0';}
    else if(GAME1_B==1){CHAR1_B='1';}
    else if(GAME1_B==2){CHAR1_B='2';}
    else if(GAME1_B==3){CHAR1_B='3';}
    else if(GAME1_B==4){CHAR1_B='4';}
    else if(GAME1_B==5){CHAR1_B='5';}
    else if(GAME1_B==6){CHAR1_B='6';}
    else if(GAME1_B==7){CHAR1_B='7';}
    char CHAR2_B;
    if(GAME2_B==0){CHAR2_B='0';}
    else if(GAME2_B==1){CHAR2_B='1';}
    else if(GAME2_B==2){CHAR2_B='2';}
    else if(GAME2_B==3){CHAR2_B='3';}
    else if(GAME2_B==4){CHAR2_B='4';}
    else if(GAME2_B==5){CHAR2_B='5';}
    else if(GAME2_B==6){CHAR2_B='6';}
    else if(GAME2_B==7){CHAR2_B='7';}
    char CHAR3_B;
    if(GAME3_B==0){CHAR3_B='0';}
    else if(GAME3_B==1){CHAR3_B='1';}
    else if(GAME3_B==2){CHAR3_B='2';}
    else if(GAME3_B==3){CHAR3_B='3';}
    else if(GAME3_B==4){CHAR3_B='4';}
    else if(GAME3_B==5){CHAR3_B='5';}
    else if(GAME3_B==6){CHAR3_B='6';}
    else if(GAME3_B==7){CHAR3_B='7';}

    dmd.drawChar(0, 0, CHAR1_A, WHITE, BLACK);
    dmd.drawChar(6, 0, CHAR2_A, WHITE, BLACK);
    dmd.drawChar(12, 0, CHAR3_A, WHITE, BLACK);
    dmd.drawChar(0, 9, CHAR1_B, WHITE, BLACK);
    dmd.drawChar(6, 9, CHAR2_B, WHITE, BLACK);
    dmd.drawChar(12, 9, CHAR3_B, WHITE, BLACK); 
    dmd.drawChar(21, 0, STR_PT_A[0], WHITE, BLACK);
    dmd.drawChar(27, 0, STR_PT_A[1], WHITE, BLACK);
    dmd.drawChar(21, 9, STR_PT_B[0], WHITE, BLACK);
    dmd.drawChar(27, 9, STR_PT_B[1], WHITE, BLACK);
    if (((GAME1_A + GAME2_A + GAME3_A + GAME1_B + GAME2_B + GAME3_B + START)%2) == 0){
      dmd.drawBox(19, 5, 20, 6, WHITE);}
    else {dmd.drawBox(19, 14, 20, 15, WHITE);
    }
  }
}


//*******************************************************************************

void setup() {
   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 5000/DISPLAYS_BPP );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( BLACK );   //true is normal (all pixels off), false is negative (all pixels on)
   dmd.selectFont(System5x7);
   pinMode(PINS_BUZZER, OUTPUT);
   
   // imprime texto punto de saque
   dmd.selectFont(System5x7);
   for (byte x=0;x<DISPLAYS_ACROSS;x++) {
     for (byte y=0;y<DISPLAYS_DOWN;y++) {
       dmd.drawString(  2+(32*x),  1+(16*y), "punto", 5, WHITE,BLACK );
       dmd.drawString(  2+(32*x),  9+(16*y), "saque", 5, WHITE,BLACK );
     }
   }
}


void loop() {
//this if plus for instance is a not elegant way to solve that first iteration uniquepress returns value.
if(i == 0){
  for(i = 0; i <= 1; i++){
    if(BTN_A.uniquePress()){ START = START+2;}
    if(BTN_B.uniquePress()){ START = START++;}
    if(BTN_C.uniquePress()){ START = START-2;}
    if(BTN_D.uniquePress()){ START = START--;}
    delay(50);
  }
}
while(START == 0){
  if(BTN_A.uniquePress()){ START = START+2; buzzer_beep(200); print_matrix();}
  if(BTN_B.uniquePress()){ START = START++; buzzer_beep(200); print_matrix();}
}  
if(BTN_A.uniquePress()){add_point_a();}

if(BTN_B.uniquePress()){add_point_b();}

if(BTN_C.uniquePress()){subs_point_a();}
    
if(BTN_D.uniquePress()){subs_point_b();}
    

}
