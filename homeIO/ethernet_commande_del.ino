#include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>

//déterminer l'adresse mac et ip
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; 
byte ip[] = { 192, 168, 1, 177};

//port de communication      
EthernetServer server(80);

//déclaration de la del sur la sortie n°8

int del = 8;

//durée de transmission de la chaîne de caractères en ms
String readString = String(30);

//mettre la del à l'état LOW au démarrage

boolean LEDON8 = false;

void setup(){
  Ethernet.begin(mac, ip);
  pinMode(del, OUTPUT);  
  Serial.begin(9600);
}

void loop(){  
  EthernetClient client = server.available();
  if (client) //tester s'il y a une requête client
  {
    while (client.connected()) // si le client est connecté
    {
      if (client.available()) //si tout est OK pour démarrer
      {
        char c = client.read(); //LEGGI I SINGOLI CARATTERI INVIATI
        if (readString.length() < 100) 
        {
          readString += c; //CONCATENA I CARATTERI
        }  
        if (c == '\n') //VEDE SE C'E' IL CARATTERE DI FINE STRINGA, PER INDIVIDUARE CHE E' FINITA
        {
          if(readString.indexOf("LED=1") > 0) //IMPOSTA UNA VARIABILE DI TIPO BOLEANA (VERO-FALSO) PER GLI STATI DEL LED
          {
            LEDON8 = true;
          } 
          
          else if(readString.indexOf("LED=0") > 0)
          {
            LEDON8 = false;
          }           
          //créer la page HTML
          
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html><head>""</head><body>");
          client.println("<h1><FONT color=red>Commander une del via le reseau local</FONT></h1>");//titre en rouge
                   
          //afficher un sous titre DEL
          client.println("<h2>DEL</h2>");

          //afficher l'état ON d'une lampe 
          if (LEDON8) { 
            digitalWrite(del, HIGH);   
            client.println("etat: ON<br>");
          } 
          else {

            //afficher l'état OFF d'une lampe  
            digitalWrite(del, LOW ); 
            client.println("etat: OFF<br>"); 
          }

          //CREA I PULSANTI RELATIVI A LED1    
          client.println("<a href='?LED=0'>ETEINDRE</a>");
          client.println("<a href='?LED=1'>ALLUMER</a>");       
      
        
           //SEPARATEUR
          client.println("<br>______________________________<br>");
  
         //balise fin de page HTML
          client.println("</body></html>");

          //SI PREPARA PER UNA NUOVA ISTRUZIONE
          readString="";

          //arrêter la connexion
          client.stop();
        }
      }
    }
  } }


