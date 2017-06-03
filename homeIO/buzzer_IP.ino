#include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>

//déterminer l'adresse mac et ip
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; 
byte ip[] = { 192, 168, 1, 177};

     
EthernetServer server(80);



int alarme = 4;


String readString = String(30);



boolean ALARME4 = false;

void setup(){
  Ethernet.begin(mac, ip);
  pinMode(alarme, OUTPUT);  
  Serial.begin(9600);

}

void loop(){
 
  
  EthernetClient client = server.available();
  if (client) 
  {
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read(); 
      
        if (readString.length() < 100) 
        {
          readString += c; 
        }  
        if (c == '\n') 
        {
          if(readString.indexOf("alarme=1") > 0) 
          {
            ALARME4 = true;
          } 
          
          else if(readString.indexOf("alarme=0") > 0)
          {
            ALARME4 = false;
          } 
         
          
          //créer la page HTML
          
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html><head>""</head><body>");
          client.println("<h1><FONT color=red>Gestion d'une alarme domestique</FONT></h1>");//titre en rouge
             
          
          //afficher un sous titre DEL
          client.println("<h2>Commander un buzzer via le reseau local</h2>");

          //afficher l'état ON d'une lampe 
          if (ALARME4) { 
            tone(alarme, 440);   
            client.println("etat: ON<br>");
          } 
          else {

            //afficher l'état OFF d'une lampe  
          noTone(alarme); 
            client.println("etat: OFF<br>"); 
          }

          //les commandes    
          client.println("<a href='?alarme=0'>ARRETER</a>");
          client.println("<a href='?alarme=1'>DECLENCHER</a>");
            
          

         
           //SEPARATEUR
          client.println("<br>______________________________<br>");
  

          //balise fin de page HTML
          client.println("</body></html>");


          readString="";

          client.stop();
        }
      }
    }
  } }


