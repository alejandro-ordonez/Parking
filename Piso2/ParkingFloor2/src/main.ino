#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Carro.h>

const char *ssid = "LAB-AUTOMATIZACION";
const char *password = "sala.ceri";
bool state = false;
int x;
String url ="https://parkingutadeo2019.azurewebsites.net/api/Cars";
String send;
Carro cars[9];
String header;
int x;
void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password); 
  Serial.print("Conectando.. ");
  while (WiFi.status() != WL_CONNECTED) 
  delay(1000);
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi conectado...");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /*pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);*/
  cars[0] = Carro("AJK1", "1", "9", "Sutanito", "2", false);
  cars[1] = Carro("AJK1", "2", "10", "Sutanito", "2", false);
  cars[2] = Carro("AJK1", "3", "11", "Sutanito", "2", false);
  cars[3] = Carro("AJK1", "4", "12", "Sutanito", "2", false);
  cars[4] = Carro("AJK1", "5", "13", "Sutanito", "2", false);
  cars[5] = Carro("AJK1", "6", "14", "Sutanito", "2", false);
  cars[6] = Carro("AJK1", "7", "15", "Sutanito", "2", false);
  cars[7] = Carro("AJK1", "8", "16", "Sutanito", "2", false);
}
void loop()
{
  HTTPClient http;
  
  for (size_t i = 0; i < 8; i++)
  {
    state = digitalRead(i);
    if (state)
    {
      cars[i].setOwner("Whatever");
      cars[i].setLicensePlate("asdf123");
      cars[i].setState(true);
    }
    else
    {
      cars[i].setOwner("Puto");
      cars[i].setLicensePlate("el que lo lea");
      cars[i].setState(false);
    }
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    http.begin("https://parkingutadeo2019.azurewebsites.net/api/Cars");
    http.addHeader("Content-Type", "text/application/json");

    for (size_t i = 0; i < 8; i++)
    {
      send="";
      StaticJsonDocument<200> doc;
      doc["carID"] = cars[i].getCarID();
      doc["placeID"]=cars[i].getPlaceID();
      doc["floorID"]=cars[i].getFloorID();
      doc["owner"]=cars[i].getOwner();
      doc["licensePlate"]=cars[i].getLicensePlate();
      serializeJsonPretty(doc, send);
      int httpResponseCode = http.request(url,'Content-Type: text/plain\r\n',send,x);
      Serial.println();
      Serial.println(send);

    if (httpResponseCode > 0)
    {

      String response = http.getString();
      Serial.println();
      Serial.println();
      Serial.println(httpResponseCode);
      Serial.println();
      Serial.println();
      Serial.println(response);
    }
    else
    {

      Serial.print("Error al enviar la solicitud PUT ");
      Serial.println(httpResponseCode);
      Serial.println();
      Serial.println();
    }

    http.end();
    delay(2000);
    }

    
  }
  else
  {
    Serial.println("Error en la conexión WiFi");
  }
     
}


