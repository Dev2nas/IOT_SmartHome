/* Projet : Maison intelligente 
   Description :
   Ce code permet de contrôler un relais à 
   partir d'un appareil externe (comme un smartphone) 
   via Bluetooth en envoyant l'une des commandes prédéfinies. 
   Le relais est connecté au GPIO 22 de l'ESP32, et le nom de 
   l'appareil Bluetooth est "Maison_Intelligent@Devnas". Le moniteur 
   série est utilisé pour afficher des messages de démarrage et de notification.

   devnas.inc@gmail.com
   github: dev2nas

   APK disponible sur playStore: Arduino BlueController

   Copyright [void loop Robotech & Automation] & [DEVNAS]

   @2023
*/



#include "BluetoothSerial.h" //Cela inclut la bibliothèque "BluetoothSerial.h" dans le code. Cette bibliothèque permet de gérer la communication Bluetooth sur une carte ESP32.
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED) //C'est une directive conditionnelle du préprocesseur qui vérifie si les macros CONFIG_BT_ENABLED et CONFIG_BLUEDROID_ENABLED sont définies à partir des fichiers de configuration du projet. Ces macros sont généralement utilisées pour activer ou désactiver les fonctionnalités du Bluetooth dans le projet.
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it 
/*Si l'une des macros CONFIG_BT_ENABLED ou CONFIG_BLUEDROID_ENABLED n'est pas définie (ce qui signifie que le Bluetooth n'est pas activé), 
 cette directive générera une erreur lors de la compilation du code. 
 L'erreur affichera le message "Bluetooth is not enabled! Please run make menuconfig to and enable it",
 indiquant à l'utilisateur qu'il doit activer le Bluetooth en utilisant la commande "make menuconfig" dans l'IDE Arduino. 
 L'activation du Bluetooth nécessite généralement de sélectionner les options appropriées dans le menu de configuration du projet.
*/

#endif //FIN SI

#define relais 22 // Numéro de la broche (GPIO) utilisée pour contrôler le relais

String receive = ""; // Variable pour stocker les données reçues via Bluetooth

BluetoothSerial SerialBT; // Objet pour gérer la communication Bluetooth

void setup() {
  Serial.begin(115200); // Initialisation de la communication série
  pinMode(relais, OUTPUT); // Configuration de la broche relais en sortie pour contrôler le relais

  SerialBT.begin("Maison_Intelligent@Devnas"); // Initialisation de la communication Bluetooth avec le nom de l'appareil "Maison_Intelligent@Devnas"
  Serial.println("Le périphérique a démarré, maintenant vous pouvez le coupler via Bluetooth !"); // Affiche un message dans le moniteur série pour indiquer que le périphérique est prêt à être appairé via Bluetooth
}

void loop()
{
  while (SerialBT.available()) // Boucle pour lire les données disponibles depuis la communication Bluetooth
  {
    char string = SerialBT.read(); // Lecture d'un caractère (byte) reçu via Bluetooth
    receive = receive + string; // Ajout du caractère reçu à la fin de la chaîne "receive"
    delay(1); // Pause d'une milliseconde pour permettre de recevoir les autres caractères
  }
  
  // Vérification des commandes Bluetooth reçues et contrôle du relais en fonction des commandes
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