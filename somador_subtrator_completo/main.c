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
bool getSaida(bool, bool, bool, bool);
bool getTrasposicaoSaida(bool, bool, bool, bool);

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
  	lcd.print("SOM/SUB COMPLETO");
  	delay(10);
}

/**
 * Loop principal.
 */
void loop()
{
  int i, entradaA, entradaB, resposta = 0;
  bool transpSaida = 0;
  byte DIP1Portas[] = {DIP1_1, DIP1_2, DIP1_3, DIP1_4};
  byte DIP2Portas[] = {DIP2_1, DIP2_2, DIP2_3, DIP2_4};
  bool DIP1[NU_BITS], DIP2[NU_BITS], M, RESP[NU_BITS + 1];

  M = digitalRead(DIP_M);
  
  for (i = 0; i < NU_BITS; i++) {
  	DIP1[i] = digitalRead(DIP1Portas[i]);
  	DIP2[i] = digitalRead(DIP2Portas[i]);
  }
  
  for (i = 0; i < NU_BITS; i++) {
   	int pos = NU_BITS - i - 1;
  	RESP[i] = getSaida(M, DIP1[pos], DIP2[pos], transpSaida);
    transpSaida = getTrasposicaoSaida(M, DIP1[pos], DIP2[pos], transpSaida);
  }
 
  RESP[4] = getSaida(M, 0, 0, transpSaida);
 
  entradaA = converteBoolParaInteiro(DIP1);
  entradaB = converteBoolParaInteiro(DIP2);
  
  if (RESP[4]) resposta += 16;
  if (RESP[3]) resposta += 8;
  if (RESP[2]) resposta += 4;
  if (RESP[1]) resposta += 2;
  if (RESP[0]) resposta += 1;
  
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(entradaA);
  
  if (M) {
    lcd.print(" - ");
    
    if(entradaA < entradaB) {
    	resposta -= 32;
    }
  } else {
    lcd.print(" + ");
  }
  
  lcd.print(entradaB);
  
  lcd.setCursor(1, 1);
  lcd.print(resposta);
  
  delay(1000);
}

/**
 * Recupera a saída final para a operação.
 *
 * @params boolean M, A, B, Te
 * @return boolean
 */
bool getSaida(bool M, bool A, bool B, bool Te) {
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
bool getTrasposicaoSaida(bool M, bool A, bool B, bool Te) {
  return (B && Te)
    || (!M && A && B)
    || (!M && A && Te)
    || (M && !A && B)
    || (M && !A && Te);
}

/**
 * Converte de valores booleanos para um valor inteiro.
 *
 * @param bool *valores
 * @return int
 */
int converteBoolParaInteiro(bool *valores) {
  int resp = 0;
  
  if (valores[0]) resp += 8;
  if (valores[1]) resp += 4;
  if (valores[2]) resp += 2;
  if (valores[3]) resp += 1;
  
  return resp;
}
