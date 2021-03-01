
#include <SoftwareSerial.h>               

#define RX  10 //ligar no TX do SIM800L
#define TX  11 //ligar no RX do SIM800L

SoftwareSerial GSM(RX, TX);

void setup()
{
  Serial.begin(9600); 
  GSM.begin(9600); 

  GSM.println("AT");
  updateSerial();
  Serial.println("");
  delay(100);
  GSM.println("ATI");
  updateSerial();
  Serial.println("");
  delay(100);
  Serial.print("1. Dados de qualidade de sinal: ");
  SendCommand("CSQ");   //Qualidade do sinal GSM
  Serial.println("");
  Serial.print("2. Número de telefone: ");
  SendCommand("CCID");  //Número do SIM Card
  Serial.println("");
  Serial.print("3. IMEI: ");
  SendCommand("CIMI");  //Mostra número do IMEI
  Serial.println("");
  Serial.print("4. Informações de registro na rede: ");
  SendCommand("CREG?"); //Checa se SIM foi registrado na rede
  Serial.println("");
  Serial.print("5, Dados da rede e operadora: ");
  SendCommand("COPS?"); //Verifica dados da rede, operadora
  Serial.println("");
  Serial.print("6. Status de bateria e tensão de alimentação do SIM800L: ");
  SendCommand("CBC");   //Mostra status de bateria (se houver) e tensão de alimentação do SIM800L
  Serial.println("");

  SendSMS("Testando codigo criado. email: williansalmeida@willcorp.dev.br"); //Enviando mensagem de texto para meu TIM
}

/*
 *          Programa Principal
 */
void loop()
{
  
}
/*
 * Verifica o comando enviado e verifica se tem reposta ao comando pela serial
 * 
 */
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    GSM.write(Serial.read());
  }
  while(GSM.available()) 
  {
    Serial.write(GSM.read());
  }
}

/*
 * Formata comando AT para enviar ao módulo
 * 
 */
void SendCommand (String cmd)
{
  GSM.println("AT+"+cmd);
  updateSerial();
  delay(100); 
}

/*
 * Formata e envia mensagem de texto (SMS) para um outro chip
 * 
 */
void SendSMS (String msg)
{
  SendCommand("CMGF=1");      //Configurando modo texto
  SendCommand("CMGS=\"+5511983046994\""); //Definindo para que número enviará a msg
  GSM.print(msg);
  updateSerial();
  GSM.write(26);
}
