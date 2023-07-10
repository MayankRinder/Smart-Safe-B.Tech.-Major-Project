#include <ESP8266WiFi.h>                            // Include the Wi-Fi library
#include <ESP_Notify.h> 


#define ssid  "Mayank's Galaxy M33 5G"              // The name of the Wi-Fi network that will be created
#define password  "strange0"                        // The password required to connect to it, leave blank for an open network
#define server ""
#define port ""
#define DEVICE_ID "fEYOnNjY3wI:APA91bFM1qe9mFIkDB7BwrD_WyYoECzS-14Q6q3lKnSbk81p_hSCogpusS_br8WvVfbg63zmv73-vF8yk9u15EsG5rvFilnONuz3oiRhFuTniM6I-BSe3I6lR9APVBm9FrJ3XdTwqy2p"
boolean objPresent = false;
long duration;
int distance;

ESP_Notify notifier;   

int status = WL_IDLE_STATUS;
                                                                                                      
WiFiClient client;                                  // Initialize the client library

void setup() 
{
    Serial.begin(115200);
  // connect to wifi.
  WiFi.begin(ssid, password);
  Serial.print("\n\nconnecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nconnected: ");
  Serial.println(WiFi.localIP());

  // Send notification
  notifier.sendNotification(DEVICE_ID, "Hello World!", "Stuff, Stuff!");
      Serial.println("connected");
    
   
    Serial.begin(9600);                             // sensor buart rate
    pinMode(0, INPUT);                              // to read value from IR sensor
    pinMode(5, OUTPUT);                             // relay pin connected to D1
    pinMode(4, OUTPUT);                             // buzzer pin connected to D2
    
}

void loop() 
{
    int sensorStatus=analogRead(A0);                // IR Sensor output pin connected to A0  
    Serial.println(sensorStatus);                   // See the Value In Serial Monitor     
    delay(100);  
    if(sensorStatus < 900 )
    {
        
        if(objPresent== false)
        {    //Alert
             digitalWrite(5, HIGH);                 // turn on relay
             digitalWrite(4, HIGH);                 // turn on buzzer
                                                    
            tone(4, 4000, 500);                     // (pin, frequency, duration)           
            
            // send notification    
            if(objPresent == false)
            {    
                 notifier.sendNotification(port,"Alert!","'objPresent'" "Your treasure is being taken away.");
            }
         }
    }
    else
    {
        objPresent = true;
        digitalWrite(5, LOW);
    }
 
     if(!objPresent)
     {
       Serial.println("Notification Sent");
       return;
     }
     else
     {
      Serial.println("Notification sending failed");
      return;
     }
     
}
