#include "WiFi.h"
#define WIFI_CONNECT_TIMEOUT 15

const char* ssid1 = "AP";
const char* password1 =  "12345678";
float a;
int i;
void setup() 
  {
  Serial.begin(9600);
   WiFi.mode(WIFI_STA);
  a=0; 
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
      }
    
    else
        for (i=0;i<=49;i++) {
        delay(200);
        float rssi = WiFi.RSSI();
        a=a+rssi;
        Serial.println();
       
       
        Serial.println(rssi);
        
      }
      
  a=a/50.0;
  Serial.println();
        Serial.println("rssi trung binh:");  Serial.print(a,4);
}
void loop() {

}
