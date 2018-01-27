
uint16_t GeneraID( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (y * Nfilas) + x;
  }

  else if( kMatrixSerpentineLayout == true) {

    //si es fila impar
    if( y & 0x01) {        
      // filas impares run backwards
      uint8_t reverseX = (Nfilas - 1) - x;
      i = (y * Ncol) + reverseX;
    }

    //si es fila par
    else {
      // Even rows run forwards
      i = (y * Ncol) + x;
    }
}
  
  return i;
}

