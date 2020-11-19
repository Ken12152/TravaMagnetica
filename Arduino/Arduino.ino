#include "config.h"


// Mantém o estado atual dos pinos (HIGH ou LOW)
int pinsStatus[PINS_COUNT];




////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  //Serial.begin(9600);
  Serial.begin(115200);


  /////////////// Configurar pinos ///////////////
  
  // Coloca os pinos que estão ligados os relês como saída
  for(int i = 0; i < PINS_COUNT; i++) {
    pinsStatus[i] = LOW;
    
    int pinNumber = FIRST_PIN + i;
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, pinsStatus[i]);
  }
}






////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  /////////////// tratamento sobre requisicao do servidor ///////////////
  
  // Verifica se há um novo cliente
  if(Serial.available()) {
    //Faz a leitura da requisição
    char* request = readRequest();

    //Se a requisição não for para o favicon
    if(strstr(request, "favicon") == NULL) {
      //Executamos a ação com o valor passado na requisição
      //execute(getAction(request), getValue(request));

      /*------------------------------------------------------------------------------------*/
      String action = getAction(request);
      //String value = getValue(request);

      //if(action == "on" || action == "off") {
      if(action == "on") {
        // Os relês são numerados a partir do 1, max o array começa do 0
        // então tiramos 1
        //int index = value.toInt() - 1;
        
        // O número do pino será o índice mais o número do pino onde os relês
        // começam. Os relês devem estar em sequência a partir do pino inicial (FIRST_PIN)
        //int pinNumber = FIRST_PIN + index;
        
        //int status = action == "on" ? HIGH : LOW;
        
        //digitalWrite(pinNumber, status);
        //pinsStatus[index] = status;

        ///////////////////////////////////////////////////
        //granted(300);   // Open the door lock for 300 ms
        ///////////////////////////////////////////////////
      }
      /*------------------------------------------------------------------------------------*/

      //Envia a resposta ao cliente
      sendResponse();
    }
    else {
      Serial.print(
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Length: 0\r\n"
        "Connection: close\r\n"
        "\r\n"
      );
    }
    Serial.write(127);
  }
}
