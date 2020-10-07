/*-------------------------------------------------------------------------------
* Projeto: Integrar estação meteorológica a Orion via Firebase
* Saiba mais: https://elcereza.com/conectar-a-estacao-meteorologica-com-a-orion/
* Disponibilizado por: https://elcereza.com
* Autor: Gustavo Cereza
---------------------------------------------------------------------------------*/

#include <WiFi.h>
#include "FirebaseESP32.h"

#define FIREBASE_HOST "https://(seu-projeto).firebaseio.com/"                              // Link do teu projeto Realtime Database no Firebase
#define FIREBASE_AUTH "sua autentificação"                                                 // Autentificação do teu projeto no Firebase 

/*
  Caso tenha alguma duvida de como obter o link (path) e a autentificação (auth)
  do firebase, acesse: https://elcereza.com/obtendo-a-path-e-auth-do-firebase/
*/

#define WIFI_SSID "SSID"                                                                   // Nome da tua rede WiFi
#define WIFI_PASSWORD "Senha"                                                              // Senha da tua rede WiFi

FirebaseData firebaseData;
String path = "orion/rx/";                                                                 // A string path deve permanecer do jeito que está ou haverá erros na Orion.
void getNode(String &key);



void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conectando");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("conectado: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                            
  Firebase.reconnectWiFi(true);                                                             
  Firebase.setReadTimeout(firebaseData, 1000 * 60);                                         
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  if(Firebase.getShallowData(firebaseData, "/")){
    Serial.println(firebaseData.payload());
  }
}

void loop() {

  /*
    Esta serie de variáveis que são armazenados valores randomicos são apenas para 
    simulação e não devem ser considerados a não ser para testes. 
  */
  
  int temp = random(-150, 150);                                                             // Temperatura Ambiente
  int hum  = random(0, 100);                                                                // Umidade Relativa
  int wind = random(0, 300);                                                                // Velocidade do Vento
  int wd   = random(0, 16);                                                                 // Direção do Vento
  int bar  = random(300, 1100);                                                             // Pressão Atmosférica
  int pluv = random(0, 2000);                                                               // Índice Pluviométrico
  int uv   = random(0, 11);                                                                 // Índice Ultra Violeta

  /*
    Os valores acima podem ser tanto como valores do tipo inteiro quanto do tipo flutuante
    a Orion trabalha com valores de ponto flutuante mas é exibido valores inteiros quando 
    está > 10 e > -10.
  */

  Firebase.setInt(firebaseData, path + "temp_out", temp);                                   // Atribui o valor de temp a temp
  Firebase.setInt(firebaseData, path + "hum_out", hum);                                     
  Firebase.setInt(firebaseData, path + "wind", wind);                                       
  Firebase.setInt(firebaseData, path + "wd", wd);                                           
  Firebase.setInt(firebaseData, path + "bar", bar);                                         
  Firebase.setInt(firebaseData, path + "pluv", pluv);                                       
  Firebase.setInt(firebaseData, path + "uv", uv);                                           

  /*
    Todas as variaveis acima por mais que você não tenha, devaram ser enviados com valor
    ZERO e desativados nas configurações do software Orion. 
    Saiba mais em: https://elcereza.com/settings-sorion/
  */

  delay(1000);                                                                              // Esse atraso é fundamental e não deve passar dos 1s
}
