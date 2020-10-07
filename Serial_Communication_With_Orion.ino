/*-------------------------------------------------------------------------------
* Projeto: Integrar estação meteorológica a Orion via comunicação serial
* Saiba mais: https://elcereza.com/conectar-a-estacao-meteorologica-com-a-orion/
* Disponibilizado por: https://elcereza.com
* Autor: Gustavo Cereza
---------------------------------------------------------------------------------*/

void setup() {
    Serial.begin(115200);                                                                       // Escolha o baudrate de 115200 ou 9600
}

void loop() {
  
    /*
      Os valores acima podem ser tanto como valores do tipo inteiro quanto do tipo flutuante
      a Orion trabalha com valores de ponto flutuante mas é exibido valores inteiros quando 
      está > 10 e > -10.
    */
    
    Serial.print("tmp:"); Serial.println(random(-150, 150));                                   // Temperatura Ambiente
    Serial.print("hum:"); Serial.println(random(0, 100));                                      // Umidade Relativa
    Serial.print("wid:"); Serial.println(random(0, 300));                                      // Velocidade do Vento
    Serial.print("wdc:"); Serial.println(random(0, 16));                                       // Direção do Vento
    Serial.print("bar:"); Serial.println(random(300, 1100));                                   // Pressão Atmosférica
    Serial.print("plv:"); Serial.println(random(0, 2000));                                     // Índice Pluviométrico
    Serial.print("ruv:"); Serial.println(random(0, 11));                                       // Índice Ultra Violeta

      /*
    Todas as variaveis acima por mais que você não tenha, devaram ser enviados com valor
    ZERO e desativados nas configurações do software Orion. 
    Saiba mais em: https://elcereza.com/settings-sorion/
  */
    delay(1000);                                                                               // Esse atraso é fundamental e não deve passar dos 1s
}
