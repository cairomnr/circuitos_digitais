#define BCD8 4
#define BCD4 3
#define BCD2 2
#define BCD1 1

#define DisplayB 11
#define DisplayA 10
#define DisplayF 9
#define DisplayG 8
#define DisplayE 7
#define DisplayD 6
#define DisplayC 5

// Define o cabeçalho das funções
void acendeA(bool, bool, bool, bool);
void acendeB(bool, bool, bool, bool);
void acendeC(bool, bool, bool, bool);
void acendeD(bool, bool, bool, bool);
void acendeE(bool, bool, bool, bool);
void acendeF(bool, bool, bool, bool);
void acendeG(bool, bool, bool, bool);

// Configura as portas lógicas.
void setup()
{
  // Inputs
  pinMode(BCD8, INPUT);
  pinMode(BCD4, INPUT);
  pinMode(BCD2, INPUT);
  pinMode(BCD1, INPUT);
  
  // Outputs
  pinMode(DisplayB, OUTPUT);
  pinMode(DisplayA, OUTPUT);
  pinMode(DisplayF, OUTPUT);
  pinMode(DisplayG, OUTPUT);
  pinMode(DisplayE, OUTPUT);
  pinMode(DisplayD, OUTPUT);
  pinMode(DisplayC, OUTPUT);
}

// O Loop principal.
void loop()
{
	bool A = digitalRead(BCD8);
  	bool B = digitalRead(BCD4);
  	bool C = digitalRead(BCD2);
  	bool D = digitalRead(BCD1);
  
  	acendeA(A, B, C, D);
  	acendeB(A, B, C, D);
  	acendeC(A, B, C, D);
  	acendeD(A, B, C, D);
  	acendeE(A, B, C, D);
  	acendeF(A, B, C, D);
  	acendeG(A, B, C, D);
  
  	delay(1);
}

/**
 * Acende o segmento A de acordo com a expressão lógica.
 *
 * @param bool A
 * @param bool B
 * @param bool C
 * @param bool D
 */
void acendeA(bool A, bool B, bool C, bool D) {
	bool isAceso = (!B && !D) || (!A && C) || (B && C) || (A && !B && !C) || (A && !D) || (!A && B && !C && D);
  	digitalWrite(DisplayA, isAceso);
}

/**
 * Acende o segmento B de acordo com a expressão lógica.
 *
 * @param bool A
 * @param bool B
 * @param bool C
 * @param bool D
 */
void acendeB(bool A, bool B, bool C, bool D) {
  	bool isAceso = (!B && !D) || (!B && !C) || (!A && !C && !D) || (!A && C && D) || (A && !C && D);
  	digitalWrite(DisplayB, isAceso);
}

/**
 * Acende o segmento C de acordo com a expressão lógica.
 *
 * @param bool A
 * @param bool B
 * @param bool C
 * @param bool D
 */
void acendeC(bool A, bool B, bool C, bool D) {
  	bool isAceso = (!A && B) || (A && !B) || (!C && D) || (!A && D) || (!A && !C);
  	digitalWrite(DisplayC, isAceso);
}

/**
 * Acende o segmento D de acordo com a expressão lógica.
 *
 * @param bool A
 * @param bool B
 * @param bool C
 * @param bool D
 */
void acendeD(bool A, bool B, bool C, bool D) {
	bool isAceso = (!B && !C && !D) || (A && B && !C) || (B && !C && D) || (!B && C && D) || (B && C && !D) || (!A && C && !D);
  	digitalWrite(DisplayD, isAceso);
}

/**
 * Acende o segmento E de acordo com a expressão lógica.
 *
 * @param bool A
 * @param bool B
 * @param bool C
 * @param bool D
 */
void acendeE(bool A, bool B, bool C, bool D) {
  	bool isAceso = (A && !D) || (A && C) || (A && B) || (C && !D) || (!B && !D);
  	digitalWrite(DisplayE, isAceso);
}

/**
 * Acende o segmento F de acordo com a expressão lógica.
 *
 * @param bool A
 * @param bool B
 * @param bool C
 * @param bool D
 */
void acendeF(bool A, bool B, bool C, bool D) {
	bool isAceso = (!C && !D) || (A && !B) || (A && C) || (B && !D) || (!A && B && !C); 
  	digitalWrite(DisplayF, isAceso);
}

/**
 * Acende o segmento G de acordo com a expressão lógica.
 *
 * @param bool A
 * @param bool B
 * @param bool C
 * @param bool D
 */
void acendeG(bool A, bool B, bool C, bool D) {
  	bool isAceso = (A && D) || (A && C) || (A && !B) || (C && !D) || (!B && C) || (!A && B && !C); 
  	digitalWrite(DisplayG, isAceso);
}

