#include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>

//déterminer l'adresse mac et ip
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; 
byte ip[] = { 192, 168, 1, 177};

//port de communication      
EthernetServer server(80);

//correspondance broches entrées/sorties
int lampesalon1 = 4; 
int lampesalon2 = 5;
int lampesdb = 6;
int lampecuisine = 7;
int lampechambre1 = 8;
int lampechambre2 = 9;
int lampeterrasse = 3;


int pincapteur=0;
int valeurlue=0;
float temperature=0;

//LUNGHEZZA DELLA STRINGA INVIATA
String readString = String(30);

//IMPOSTA ALL'AVVIO I LED SPENTI
boolean LEDON3 = false; 
boolean LEDON4 = false;
boolean LEDON5 = false; 
boolean LEDON6 = false;
boolean LEDON7 = false;
boolean LEDON8 = false;
boolean LEDON9 = false;




void setup(){
  Ethernet.begin(mac, ip);
  pinMode(lampesalon1, OUTPUT);  
  pinMode(lampesalon2, OUTPUT);
  pinMode(lampesdb, OUTPUT); 
  pinMode(lampecuisine, OUTPUT); 
  pinMode(lampechambre1, OUTPUT); 
  pinMode(lampechambre2, OUTPUT); 
  pinMode(lampeterrasse, OUTPUT);
  pinMode(pincapteur, INPUT); 
  Serial.begin(9600);

}

void loop(){
 
  
  EthernetClient client = server.available();
  if (client) //SE ESISTE UN CLIENTE
  {
    while (client.connected()) // SE IL CLIENTE E' CONNESSO
    {
      if (client.available()) //SE E' TUTTO OK PER INIZIARE
      {
        char c = client.read(); //LEGGI I SINGOLI CARATTERI INVIATI
        if (readString.length() < 100) 
        {
          readString += c; //CONCATENA I CARATTERI
        }  
        if (c == '\n') //VEDE SE C'E' IL CARATTERE DI FINE STRINGA, PER INDIVIDUARE CHE E' FINITA
        {
          if(readString.indexOf("L1=1") > 0) //IMPOSTA UNA VARIABILE DI TIPO BOLEANA (VERO-FALSO) PER GLI STATI DEL LED
          {
            LEDON4 = true;
          } 
          else if (readString.indexOf("L2=1") > 0) 
          {
            LEDON5= true;            
          }
           else if (readString.indexOf("L3=1") > 0) 
          {
            LEDON6= true;            
          }
           else if (readString.indexOf("L4=1") > 0) 
          {
            LEDON7= true;            
          }
           else if (readString.indexOf("L5=1") > 0) 
          {
            LEDON8= true;            
          }
           else if (readString.indexOf("L6=1") > 0) 
          {
            LEDON9= true;            
          }
           else if (readString.indexOf("L7=1") > 0) 
          {
            LEDON3= true;            
          }

          else if(readString.indexOf("L1=0") > 0)
          {
            LEDON4 = false;
          } 
          else if (readString.indexOf("L2=0") > 0) 
          {
            LEDON5 = false;             
          }
          else if (readString.indexOf("L3=0") > 0) 
          {
            LEDON6 = false;             
          }
          else if (readString.indexOf("L4=0") > 0) 
          {
            LEDON7 = false;             
          }
          else if (readString.indexOf("L5=0") > 0) 
          {
            LEDON8 = false;             
          }
          else if (readString.indexOf("L6=0") > 0) 
          {
            LEDON9 = false;             
          }
          else if (readString.indexOf("L7=0") > 0) 
          {
            LEDON3 = false;             
          }
          
          //créer la page HTML
          
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html><head>""</head><body>");
          client.println("<h1><FONT color=red>Ma maison connect&eacutee</FONT></h1>");
             
          
          //SALON
          client.println("<h2>Lampe du salon1</h2>");

          //OPERAZIONI DA FARE QUANDO SI CLICCA PER ATTIVARE LEDON1:  
          if (LEDON4) { 
            digitalWrite(lampesalon1, HIGH);   
            client.println("etat: ON<br>");
          } 
          else {

            //afficher l'état d'une lampe  
            digitalWrite(lampesalon1, LOW ); 
            client.println("etat: OFF<br>"); 
          }

          //CREA I PULSANTI RELATIVI A LED1    
          client.println("<a href='?L1=0'>ETEINDRE</a>");
          client.println("<a href='?L1=1'>ALLUMER</a>");

                    
          client.println("<h2>Lampe du salon2</h2>");

          //OPERAZIONI DA FARE QUANDO SI CLICCA PER ATTIVARE LEDON2:  
          if (LEDON5) { 
            digitalWrite(lampesalon2, HIGH);  
            client.println("etat: ON<br>"); 
          } 
          else { 

            //OPERAZIONI DA FARE QUANDO SI CLICCA PER SPEGNERE LEDON2:    
            digitalWrite(lampesalon2, LOW); 
            client.println("etat: OFF<br>"); 
          } 

          //CREA I PULSANTI RELATIVI A LED2
          client.println("<a href='?L2=0'>ETEINDRE</a>");
          client.println("<a href='?L2=1'>ALLUMEE</a>");

          //SEPARATEUR
          client.println("<br>______________________________<br>");

            //SALLE DE BAINS
          client.println("<h2>Lampe de la salle de bains</h2>");

          //OPERAZIONI DA FARE QUANDO SI CLICCA PER ATTIVARE LEDON1:  
          if (LEDON6) { 
            digitalWrite(lampesdb, HIGH);   
            client.println("etat: ON<br>");
          } 
          else {

            //afficher l'état d'une lampe  
            digitalWrite(lampesdb, LOW ); 
            client.println("etat: OFF<br>"); 
          }

          //CREA I PULSANTI RELATIVI A LED1    
          client.println("<a href='?L3=0'>ETEINDRE</a>");
          client.println("<a href='?L3=1'>ALLUMER</a>");

          
          //SEPARATEUR
          client.println("<br>______________________________<br>");

            //Cuisine
          client.println("<h2>Lampe de la cuisine</h2>");

          //OPERAZIONI DA FARE QUANDO SI CLICCA PER ATTIVARE LEDON1:  
          if (LEDON7) { 
            digitalWrite(lampecuisine, HIGH);   
            client.println("etat: ON<br>");
          } 
          else {

            //afficher l'état d'une lampe  
            digitalWrite(lampecuisine, LOW ); 
            client.println("etat: OFF<br>"); 
          }

          //CREA I PULSANTI RELATIVI A LED1    
          client.println("<a href='?L4=0'>ETEINDRE</a>");
          client.println("<a href='?L4=1'>ALLUMER</a>");

          //SEPARATEUR
          client.println("<br>______________________________<br>");

            //Chambres
          client.println("<h2>Lampe de la chambre1</h2>");

          //OPERAZIONI DA FARE QUANDO SI CLICCA PER ATTIVARE LEDON1:  
          if (LEDON8) { 
            digitalWrite(lampechambre1, HIGH);   
            client.println("etat: ON<br>");
          } 
          else {

            //afficher l'état d'une lampe  
            digitalWrite(lampechambre1, LOW ); 
            client.println("etat: OFF<br>"); 
          }

          //CREA I PULSANTI RELATIVI A LED1    
          client.println("<a href='?L5=0'>ETEINDRE</a>");
          client.println("<a href='?L5=1'>ALLUMER</a>");
          
           client.println("<h2>Lampe de la chambre2</h2>");

          //OPERAZIONI DA FARE QUANDO SI CLICCA PER ATTIVARE LEDON1:  
          if (LEDON9) { 
            digitalWrite(lampechambre2, HIGH);   
            client.println("etat: ON<br>");
          } 
          else {

            //afficher l'état d'une lampe  
            digitalWrite(lampechambre2, LOW ); 
            client.println("etat: OFF<br>"); 
          }

          //CREA I PULSANTI RELATIVI A LED1    
          client.println("<a href='?L6=0'>ETEINDRE</a>");
          client.println("<a href='?L6=1'>ALLUMER</a>");
          
           //SEPARATEUR
          client.println("<br>______________________________<br>");

            //Terrasse
          client.println("<h2>Lampe de la terrasse</h2>");

          //OPERAZIONI DA FARE QUANDO SI CLICCA PER ATTIVARE LEDON1:  
          if (LEDON3) { 
            digitalWrite(lampeterrasse, HIGH);   
            client.println("etat: ON<br>");
          } 
          else {

            //afficher l'état d'une lampe  
            digitalWrite(lampeterrasse, LOW ); 
            client.println("etat: OFF<br>"); 
          }

          //CREA I PULSANTI RELATIVI A LED1    
          client.println("<a href='?L7=0'>ETEINDRE</a>");
          client.println("<a href='?L7=1'>ALLUMER</a>");

         
           //SEPARATEUR
          client.println("<br>______________________________<br>");


       

          //balise fin de page HTML
          client.println("</body></html>");

          //SI PREPARA PER UNA NUOVA ISTRUZIONE
          readString="";

          //TERMINA LE OPERAZIONI CLIENTE
          client.stop();
        }
      }
    }
  } }


