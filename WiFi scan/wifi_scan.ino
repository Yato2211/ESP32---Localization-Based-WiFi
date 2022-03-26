#include "WiFi.h"
#define WIFI_CONNECT_TIMEOUT 15

const char* ssid1 = "AP1";
const char* password1 =  "12345678";
const char* ssid2 = "AP2";
const char* password2 =  "12345678";
const char* ssid3 = "AP3";
const char* password3 =  "12345678";
float a,b,c;
float x,y,z;
int i;
void setup() 
  {
  Serial.begin(115200);
  a=0; b=0; c=0; x=0; y=0; z=0;
  WiFi.begin(ssid1, password1);delay(3000);
  WiFi.begin(ssid2, password2);delay(3000);
  WiFi.begin(ssid3, password3);delay(3000);
  for (i=0;i<=49;i++) 
    {
    WiFi.mode(WIFI_STA);
     delay(500);
    WiFi.begin(ssid1, password1);
    int loop = 0;
    bool recheck_connect_fail = false;
    while (WiFi.status() != WL_CONNECTED) 
      {
      delay(200);
      loop++;
      if ((WiFi.status() == WL_NO_SSID_AVAIL) || (WiFi.status() == WL_CONNECT_FAILED) || (WiFi.status() > WL_DISCONNECTED))
        {
        recheck_connect_fail = true;
        break;
        }
      else
        {
        if (loop >= (WIFI_CONNECT_TIMEOUT)) 
          {
          recheck_connect_fail = true;
          break;
          }
        }
      }

    if (recheck_connect_fail) 
    {
      Serial.println();
      Serial.println("WiFi network connection failed");
      x++;
      }
    
    else
      {
        delay(1000);
        float rssi = WiFi.RSSI();
        a=a+rssi;
        Serial.println();
        Serial.print("RSSI(AP1) lan ");
        Serial.print(i+1);
        Serial.print(":");
        Serial.println(rssi);
      }
     WiFi.mode(WIFI_STA); 
     delay(200);
    WiFi.begin(ssid2, password2);
    loop = 0;
    recheck_connect_fail = false;
    while (WiFi.status() != WL_CONNECTED) 
      {
      delay(1000);
      loop++;
      if ((WiFi.status() == WL_NO_SSID_AVAIL) || (WiFi.status() == WL_CONNECT_FAILED) || (WiFi.status() > WL_DISCONNECTED))
        {
        recheck_connect_fail = true;
        break;
        }
      else
        {
        if (loop >= (WIFI_CONNECT_TIMEOUT)) 
          {
          recheck_connect_fail = true;
          break;
          }
        }
      }

    if (recheck_connect_fail) {Serial.println("WiFi network connection failed");y++;}
    else
      {
        delay(200);
        float rssi = WiFi.RSSI();
        b=b+rssi;
        Serial.print("RSSI(AP2) lan ");
        Serial.print(i+1);
        Serial.print(":");
        Serial.println(rssi);
      }
      WiFi.mode(WIFI_STA);
       delay(200);
      WiFi.begin(ssid3,password3);
    loop = 0;
    recheck_connect_fail = false;
    while (WiFi.status() != WL_CONNECTED) 
      {
      delay(1000);
      loop++;
      if ((WiFi.status() == WL_NO_SSID_AVAIL) || (WiFi.status() == WL_CONNECT_FAILED) || (WiFi.status() > WL_DISCONNECTED))
        {
        recheck_connect_fail = true;
        break;
        }
      else
        {
        if (loop >= (WIFI_CONNECT_TIMEOUT)) 
          {
          recheck_connect_fail = true;
          break;
          }
        }
      }

    if (recheck_connect_fail) {Serial.println("WiFi network connection failed");z++;}
    else
      {
        delay(200);
        float rssi = WiFi.RSSI();
        c=c+rssi;
        Serial.print("RSSI(AP3) lan ");
        Serial.print(i+1);
        Serial.print(":");
        Serial.println(rssi);
      }
     
    }
  a=a/(50.0-x); b=b/(50.0-y); c=c/(50.0-z);
  Serial.println();
  Serial.println("RSSI trung binh:");
  Serial.print("AP1:");
  Serial.println(a,4);
  Serial.print("AP2:");
  Serial.println(b,4);
  Serial.print("AP3:");
  Serial.println(c,4);
}
void loop() {

}
