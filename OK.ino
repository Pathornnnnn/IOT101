#include <ESP8266WiFi.h>
const char* ssid     = "true_home2G_8hc";
const char* password = "n68q34aK";
const char* host = "sadboyacu.000webhostapp.com";
String url2 = "/button1_proc.php";
String url = url2;
String id = "button1_stat";
String value = "";
const int led = 2;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(2, HIGH);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

String GetField(String str,int fcount){
 int i=0;
 char ch;
 int len=str.length();
 String str2="";
 while(fcount>=1 and i<len)
 {
  ch=str[i];
  //str2+=ch;
  if(ch!=',' & ch!=' ') {
    str2+=ch;
  }
  else
  {
   fcount--;
   if(fcount>0){
    str2="";
   }
  }
    i++;
 }
 return(str2);
}

String stat="OFF";
String line="";
String line2="";

void loop() {
  url=url2;

  if(stat=="ON"){
     digitalWrite(LED_BUILTIN,LOW);
  }
  else if(stat=="OFF"){
     digitalWrite(LED_BUILTIN, HIGH);
  }
  delay(500);
  Serial.println(stat);
  
  value="?";

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // We now create a URI for the request
  url += "?id=" + id;
  url += "&value=" + value;
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  url = url2;
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  
  while (client.available()) {
    line = client.readStringUntil('\n');
    //erial.println(line);
    if(char(line[0])=='>'){
      line.trim();
      line2=line;
    }
  }
  stat=GetField(line2,3);
}
