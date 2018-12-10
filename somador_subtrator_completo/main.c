#include <LiquidCrystal.h>

#define NU_BITS 4

#define DIP1_1 13
#define DIP1_2 12
#define DIP1_3 11
#define DIP1_4 10

#define DIP2_1 9
#define DIP2_2 8
#define DIP2_3 7
#define DIP2_4 6

#define DIP_M A0

#define LCD_RS 4
#define LCD_Enable 5
#define LCD_D4 0
#define LCD_D5 1
#define LCD_D6 2
#define LCD_D7 3

// Declaração das funções.
bool getSaida(boolean, boolean, boolean, boolean);
bool getTrasposicaoSaida(boolean, boolean, boolean, boolean);

LiquidCrystal lcd(
  LCD_RS,
  LCD_Enable,
  LCD_D4,
  LCD_D5,
  LCD_D6,
  LCD_D7
);

/**
 * Define as configurações das portas.
 */
void setup()
{
   	Serial.begin(9600);
  
  	// DIP 1
  	pinMode(DIP1_1, INPUT);
  	pinMode(DIP1_2, INPUT);
  	pinMode(DIP1_3, INPUT);
  	pinMode(DIP1_4, INPUT);

    // DIP 2
  	pinMode(DIP2_1, INPUT);
  	pinMode(DIP2_2, INPUT);
  	pinMode(DIP2_3, INPUT);
  	pinMode(DIP2_4, INPUT);
  
  	// DIP M
  	pinMode(DIP_M, INPUT);
  
  	// LCD
    lcd.begin(16, 2);
}

/**
 * Loop principal.
 */
void loop()
{
  int i, entradaA, entradaB, resposta;
  boolean transpSaida = 0;
  byte DIP1Portas[] = {DIP1_1, DIP1_2, DIP1_3, DIP1_4};
  byte DIP2Portas[] = {DIP2_1, DIP2_2, DIP2_3, DIP2_4};
  boolean DIP1[NU_BITS], DIP2[NU_BITS], M, RESP[NU_BITS + 1];

  M = digitalRead(DIP_M);
  
  for (i = 0; i < NU_BITS; i++) {
  	DIP1[i] = digitalRead(DIP1Portas[i]);
  	DIP2[i] = digitalRead(DIP2Portas[i]);
  }
  
  for (i = NU_BITS - 1; i > -1; i++) {
  	RESP[i + 1] = getSaida(M, DIP1[i], DIP2[i], transpSaida);
    transpSaida = getTrasposicaoSaida(M, DIP1[i], DIP2[i], transpSaida);
  }
 
  RESP[0] = getSaida(M, 0, 0, transpSaida);
 
  entradaA = converteBoolParaInteiro(DIP1);
  entradaB = converteBoolParaInteiro(DIP2);
  
  if (RESP[0]) resposta += 16;
  if (RESP[1]) resposta += 8;
  if (RESP[2]) resposta += 4;
  if (RESP[3]) resposta += 2;
  if (RESP[4]) resposta += 1;
  
  lcd.clear();
  lcd.display();
  lcd.setCursor(1, 0);
  lcd.print(entradaA);
  lcd.print(" AVBB ");
  lcd.print(entradaB);
  
  lcd.setCursor(1, 1);
  lcd.print(resposta);
  
  delay(10);
}

/**
 * Recupera a saída final para a operação.
 *
 * @params boolean M, A, B, Te
 * @return boolean
 */
bool getSaida(boolean M, boolean A, boolean B, boolean Te) {
	return (A && !B && !Te)
      || (!A && !B && Te)
      || (A && B && Te)
      || (!A && B && !Te);
}

/**
 * Recupera a saída parcial para a operação.
 *
 * @params boolean M, A, B, Te
 * @return boolean
 */
bool getTrasposicaoSaida(boolean M, boolean A, boolean B, boolean Te) {
  return (B && Te)
    || (!M && A && B)
    || (!M && A && Te)
    || (M && !A && B)
    || (M && !A && Te);
}


int converteBoolParaInteiro(boolean *valores) {
  int resp = 0;
  
  if (valores[0]) resp += 8;
  if (valores[1]) resp += 4;
  if (valores[2]) resp += 2;
  if (valores[3]) resp += 1;
  
  return resp;

}
