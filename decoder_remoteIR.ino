#include <IRremote00.h>

#define DELAI 200

   #define RECV_PIN 3   //recepteur ir sur entrée 3 numérique

   IRrecv irrecv(RECV_PIN);
   decode_results results;

   const int LED = 13; //led sur pin13


   void setup()
   {
     pinMode(LED, OUTPUT);
     irrecv.enableIRIn(); // Start receiver
     Serial.begin(9600);
   }


   void loop() {
       digitalWrite(LED, LOW);
  
     // si message ir
   if (irrecv.decode(&results)) {
   Serial.println(results.value, HEX); //ecrire code
   digitalWrite(LED, HIGH); //allumer led
   delay(DELAI);
   irrecv.resume(); // attente prochaine commande
     }
   }
