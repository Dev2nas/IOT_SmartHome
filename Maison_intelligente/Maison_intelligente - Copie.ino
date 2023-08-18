#include "BluetoothSerial.h" 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it 
#endif //FIN SI
#define relais 22 // Numéro de la broche (GPIO) utilisée pour contrôler le relais

String receive = ""; // Variable pour stocker les données reçues via Bluetooth
BluetoothSerial SerialBT; // Objet pour gérer la communication Bluetooth

void setup() {
  Serial.begin(115200); 
  pinMode(relais, OUTPUT);
  SerialBT.begin("Maison_Intelligent@Devnas");
  Serial.println("Le périphérique a démarré, maintenant vous pouvez le coupler via Bluetooth !");
}

void loop()
{
  while (SerialBT.available())
  {
    char string = SerialBT.read(); // Lecture d'un caractère (byte) reçu via Bluetooth
    receive = receive + string; // Ajout du caractère reçu à la fin de la chaîne "receive"
    delay(1); 
  }
  
    if (receive == "A")
  {
    digitalWrite(relais, HIGH); // Allumer le relais
  }
  if (receive == "a")
  {
    digitalWrite(relais,LOW); // Éteindre le relais
  }
  if (receive == "AB")
  {
    digitalWrite(relais, HIGH); // Allumer le relais
  }
  if (receive == "ab")
  {
    digitalWrite(relais, LOW); // Éteindre le relais
  }

  receive = ""; // Effacer la variable "receive" pour pouvoir recevoir de nouvelles commandes Bluetooth
}