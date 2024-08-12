#include <Servo.h>

/* Declaração das variáveis */
const int btA = 2;
const int btB = 3;
const int btC = 4;
const int btD = 5;
int potA0 = 0;
int potA1 = 0;
int escolha = 0;

/* Definição dos ângulos iniciais dos servos (esses valores podem variar de montagem para montagem) */
int angBase = 90;
int angDir = 90;
int angEsq = 90;
int angGuarra = 90; // Atualize este valor conforme necessário

/* Declaração dos servos */
Servo servo_9;
Servo servo_10;
Servo servo_11;
Servo servo_12;

/* Tempo para atualizar a posição dos servos */
unsigned long previousMillis = 0;
const long interval = 20; // Intervalo de atualização em milissegundos

void setup() {
  /* Configuração do modo de operação das portas para os botões */
  pinMode(btA, INPUT_PULLUP);
  pinMode(btB, INPUT_PULLUP);
  pinMode(btC, INPUT_PULLUP);
  pinMode(btD, INPUT_PULLUP);

  /* Configuração das portas de operação dos servos */
  servo_9.attach(9);
  servo_10.attach(10);
  servo_11.attach(11);
  servo_12.attach(12);

  delay(500);
  /* Define os ângulos inicias dos servos */

  servo_9.write(angBase);
  servo_10.write(angDir);
  servo_11.write(angEsq);
  servo_12.write(angGuarra); // Atualize este valor conforme necessário

  delay(500);
  
  Serial.begin(9600); // Inicializando a comunicação serial
}

void loop() {
  unsigned long currentMillis = millis();

  /* Coleta os valores analógicos dos potenciômetros */
  potA0 = analogRead(A0);
  potA1 = analogRead(A1);

  /* Imprime os valores lidos no monitor serial para depuração */
  Serial.print("potA0: ");
  Serial.print(potA0);
  Serial.print(" | potA1: ");
  Serial.println(potA1);

  /* Identifica qual botão será pressionado */
  if (digitalRead(btA) == LOW) {
    escolha = 1;
  }
  else if (digitalRead(btB) == LOW) {
    escolha = 2;
  }
  else if (digitalRead(btC) == LOW) {
    escolha = 3;
  }
  else if (digitalRead(btD) == LOW) {
    escolha = 4;
  }

  /* Verifica se é hora de atualizar a posição dos servos */
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    /* Após um botão ser pressionado, entrará em um dos quatro modos de operação (A, B, C e D) */
    switch (escolha) {
      case 1:
        /* Se o joystick for deslocado para a esquerda, abrirá a garra. */
        if (potA0 > 700 && angGuarra < 100) {
          angGuarra += 1;
          servo_12.write(angGuarra);
          Serial.print("Garra Abrindo: ");
          Serial.println(angGuarra);
        }
        /* Se o joystick for deslocado para a direita, fechará a garra. */
        if (potA0 < 300 && angGuarra > 60) {
          angGuarra -= 1;
          servo_12.write(angGuarra);
          Serial.print("Garra Fechando: ");
          Serial.println(angGuarra);
        }
        break;

      case 2:
        /* Se o joystick for deslocado para a frente, abaixará o braço. */
        if (potA1 > 700 && angDir < 180) {
          angDir += 1;
          servo_10.write(angDir);
          Serial.print("Braço Abaixando: ");
          Serial.println(angDir);
        }
        /* Se o joystick for deslocado para trás, levantará o braço. */
        if (potA1 < 300 && angDir > 50) {
          angDir -= 1;
          servo_10.write(angDir);
          Serial.print("Braço Levantando: ");
          Serial.println(angDir);
        }
        break;

      case 3:
        /* Se o joystick for deslocado para a direita, o braço girará no sentido horário. */
        if (potA0 < 300 && angBase < 180) {
          angBase += 1;
          servo_9.write(angBase);
          Serial.print("Base Girando Horário: ");
          Serial.println(angBase);
        }
        /* Se o joystick for deslocado para a esquerda, o braço girará no sentido anti-horário. */
        if (potA0 > 700 && angBase > 0) {
          angBase -= 1;
          servo_9.write(angBase);
          Serial.print("Base Girando Anti-Horário: ");
          Serial.println(angBase);
        }
        break;

      case 4:
        /* Se o joystick for deslocado para a frente, levantará o antebraço. */
        if (potA1 > 700 && angEsq < 180) {
          angEsq += 1;
          servo_11.write(angEsq);
          Serial.print("Antebraço Levantando: ");
          Serial.println(angEsq);
        }
        /* Se o joystick for deslocado para trás, abaixará o antebraço. */
        if (potA1 < 300 && angEsq > 90) {
          angEsq -= 1;
          servo_11.write(angEsq);
          Serial.print("Antebraço Abaixando: ");
          Serial.println(angEsq);
        }
        break;
    }
  }
}
