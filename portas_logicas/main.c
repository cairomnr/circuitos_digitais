/**
 * Constantes
 */
const byte LED1 = 13;
const byte LED2 = 12;
const byte LEDRESP = 7;

/**
 * Cabeçalho de funções.
 */
bool condNao(int);
bool condE(int, int);
bool condOu(int, int);
bool condNaoE(int, int);
bool condNaoOu(int, int);
bool condOuExclusivo(int, int);
bool condNaoOuExclusivo(int, int);

/**
 * Responsável pela configuração inicial do arduino.
 */
void setup()
{
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LEDRESP, OUTPUT);
}

/**
 * Laço principal de execução.
 */
void loop()
{
  int entradas[4][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
  portaLogicaE(entradas);
  portaLogicaOu(entradas);
  portaLogicaNaoE(entradas);
  portaLogicaNaoOu(entradas);
  portaLogicaOuExclusico(entradas);
  portaLogicaNaoOuExclusico(entradas);
}

/**
 * Acende os leds de acordo com a porta lógica "E".
 *
 * @param int entradas[][]
 */
void portaLogicaE(int entradas[][2]) {
  int i;
  
  for (i = 0; i < 4; i++) {
    int led1 = entradas[i][0];
    int led2 = entradas[i][1];
    int ledResp = condE(led1, led2);

    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);
    digitalWrite(LEDRESP, ledResp);
    delay(2000);
  }
}

/**
 * Acende os leds de acordo com a porta lógica "OU".
 *
 * @param int entradas[][]
 */
void portaLogicaOu(int entradas[][2]) {
  int i;
  
  for (i = 0; i < 4; i++) {
    int led1 = entradas[i][0];
    int led2 = entradas[i][1];
    int ledResp = condOu(led1, led2);

    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);
    digitalWrite(LEDRESP, ledResp);
    delay(2000);
  }
}

/**
 * Acende os leds de acordo com a porta lógica "NÃO E".
 *
 * @param int entradas[][]
 */
void portaLogicaNaoE(int entradas[][2]) {
  int i;
  
  for (i = 0; i < 4; i++) {
    int led1 = entradas[i][0];
    int led2 = entradas[i][1];
    int ledResp = condNaoE(led1, led2);

    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);
    digitalWrite(LEDRESP, ledResp);
    delay(2000);
  }
}

/**
 * Acende os leds de acordo com a porta lógica "NÃO E".
 *
 * @param int entradas[][]
 */
void portaLogicaNaoOu(int entradas[][2]) {
  int i;
  
  for (i = 0; i < 4; i++) {
    int led1 = entradas[i][0];
    int led2 = entradas[i][1];
    int ledResp = condNaoOu(led1, led2);

    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);
    digitalWrite(LEDRESP, ledResp);
    delay(2000);
  }
}

/**
 * Acende os leds de acordo com a porta lógica "OU EXCLUSIVO".
 *
 * @param int entradas[][]
 */
void portaLogicaOuExclusico(int entradas[][2]) {
  int i;
  
  for (i = 0; i < 4; i++) {
    int led1 = entradas[i][0];
    int led2 = entradas[i][1];
    int ledResp = condOuExclusivo(led1, led2);

    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);
    digitalWrite(LEDRESP, ledResp);
    delay(2000);
  }
}


/**
 * Acende os leds de acordo com a porta lógica "NÃO OU EXCLUSIVO".
 *
 * @param int entradas[][]
 */
void portaLogicaNaoOuExclusico(int entradas[][2]) {
  int i;
  
  for (i = 0; i < 4; i++) {
    int led1 = entradas[i][0];
    int led2 = entradas[i][1];
    int ledResp = condNaoOuExclusivo(led1, led2);

    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);
    digitalWrite(LEDRESP, ledResp);
    delay(2000);
  }
}

/**
 * Realiza a verificação da condição "NAO" lógica.
 *
 * @param int entrada1
 * @param int entrada2
 * @return int
 */
bool condNao(int entrada1) {
	return entrada1 == 0;
}

/**
 * Realiza a verificação da condição "E" lógica.
 *
 * @param int entrada1
 * @param int entrada2
 * @return int
 */
bool condE(int entrada1, int entrada2) {
	return (entrada1 * entrada2) == 1;
}

/**
 * Realiza a verificação da condição "OU" lógica.
 *
 * @param int entrada1
 * @param int entrada2
 * @return int
 */
bool condOu(int entrada1, int entrada2) {
	return (entrada1 + entrada2) > 0;
}

/**
 * Realiza a verificação da condição "NAO E" lógica.
 *
 * @param int entrada1
 * @param int entrada2
 * @return int
 */
bool condNaoE(int entrada1, int entrada2) {
	return condNao((entrada1 * entrada2) == 1);
}

/**
 * Realiza a verificação da condição "NAO OU" lógica.
 *
 * @param int entrada1
 * @param int entrada2
 * @return int
 */
bool condNaoOu(int entrada1, int entrada2) {
	return condNao((entrada1 + entrada2) > 0);
}

/**
 * Realiza a verificação da condição "OU EXCLUSIVO" lógica.
 *
 * @param int entrada1
 * @param int entrada2
 * @return int
 */
bool condOuExclusivo(int entrada1, int entrada2) {
	return entrada1 != entrada2;
}

/**
 * Realiza a verificação da condição "NÃO OU EXCLUSIVO" lógica.
 *
 * @param int entrada1
 * @param int entrada2
 * @return int
 */
bool condNaoOuExclusivo(int entrada1, int entrada2) {
	return condNao(entrada1 != entrada2);
}

