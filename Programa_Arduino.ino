#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 200);

// IP donde se encuentra el servidor
const char * udpAddress = "192.168.1.103";
// Puerto donde se reciben los datos
const int udpPort = 30000;

EthernetUDP Udp; // Instancia Socket UDP

// Buffer para recibir los datos
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; 

float conversion =0;
char buffer[5];

void setup() {
  pinMode(5, OUTPUT);   
  digitalWrite(5,LOW );
  pinMode(6, OUTPUT);   
  digitalWrite(6,LOW );
  pinMode(7, OUTPUT);   
  digitalWrite(7,LOW );
  pinMode(8, OUTPUT);   
  digitalWrite(8,LOW );
   
   if (Ethernet.begin(mac) == 0) {
    Serial.println("No puedo configurar Ethernet usando DHCP");
  }
  //Ethernet.begin(mac, ip); // Configura Ethernet con IP fija
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  // Todo OK con la placa de RED?
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println(F("ERROR en la placa Ethernet("));
    while (true) {
      delay(1); 
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println(F("El cable de red no esta conectado."));
  }
  Udp.begin(udpPort);  // Inicia el socket UDP
}

void loop(){
 int packetSize = Udp.parsePacket();
  if(packetSize){ 
   // Lee el paquete desde el buffer  
   Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE); 
   // Discrimina el comando enviado desde la red
   switch(packetBuffer[0]){ 
   case '1':{
        digitalWrite(5, HIGH);
        break;
      }
   case '2':{
        digitalWrite(5, LOW);  
        break;
      }
      case '3':{
        digitalWrite(6, HIGH);
        break;
      }
   case '4':{
        digitalWrite(6, LOW);  
        break;
      }
   case '5':{
        digitalWrite(7, HIGH);
        break;
      }
   case '6':{
        digitalWrite(7, LOW);  
        break;
      }
    case '7':{
        digitalWrite(8, HIGH);
        break;
      }
   case '8':{
        digitalWrite(8, LOW);  
        break;
      }   
   }
  }
  conversion = analogRead(A0);
  conversion = (conversion *5.0)/1024;
  sprintf(buffer, "%d.%02d", (int)conversion, abs((int)(conversion*100)%100));
  Udp.beginPacket(udpAddress, udpPort);  // Conecta con el servidor
  Udp.print(buffer);  // Envía el canal A/D
  Udp.endPacket();    // Fin de transacción
  delay(200);
}


