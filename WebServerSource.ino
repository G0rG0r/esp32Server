#include <WiFi.h>
#include "lwip/sockets.h"


// THIS STEP IS NOT REQUIRED BUT , INORDER TO SET A STATIC IP , OTHERWISE I DONT KNOW ...
IPAddress local_IP(192, 168, 100, 200);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

int s;
struct sockaddr_in address, client;
// THE ESP32 HAS WIFI BUILT IN SO YOU NEED TO ADD IN THE SSID + PASSWORD COMBO 
void setup() {
  Serial.begin(115200);
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.begin("SSID", " wifi passwrod");
  while (WiFi.status() != WL_CONNECTED) delay(10);

  s = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(80);
  socklen_t Addrlen = sizeof(address);
  bind(s,(struct sockaddr*)&address,Addrlen);
  listen(s,100);

}
// HERE IS THE RECIEVING BUFFER WHICH IS USELESS BECAUSE ITS A STATIC WEB PAGE 
char buffer[1024];

//HERE IS THE HTTP HEADER RESPONSE FOR CORRECT CONNECTION
const char* resp = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
// HERE IS THE HTML CODE 
const char* site = R"=====(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Web Server</title>
    <style>
        :root {
            --primary-accent: #ffffff;
            --bg-color: #121212;
            --card-bg: #1e1e1e;
        }
        body {
            margin: 0;
            padding: 20px;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: var(--bg-color);
            background-image: linear-gradient(rgba(0,0,0,0.7), rgba(0,0,0,0.7)), 
                              url("https://m.media-amazon.com/images/I/61MDW+U+rvL._AC_UF1000,1000_QL80_.jpg");
            background-size: 300px;
            color: #e0e0e0;
            display: flex;
            justify-content: center;
        }
        #content {
            max-width: 800px;
            background: var(--card-bg);
            border: 1px solid var(--primary-accent);
            border-radius: 15px;
            padding: 40px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.5);
            line-height: 1.6;
        }
        h1 {
            color: var(--primary-accent);
            text-align: center;
            font-size: 2.5em;
            margin-bottom: 0.5em;
            text-transform: uppercase;
            letter-spacing: 2px;
            border-bottom: 2px solid var(--primary-accent);
            padding-bottom: 10px;
        }
        .intro {
            font-size: 1.2em;
            color: #fff;
            text-align: center;
            margin-bottom: 30px;
        }
        ul {
            list-style: none;
            padding: 0;
        }
        li {
            background: rgba(255, 255, 255, 0.05);
            margin: 10px 0;
            padding: 15px;
            border-left: 4px solid var(--primary-accent);
            border-radius: 4px;
            transition: transform 0.2s;
        }
        li:hover {
            transform: translateX(10px);
            background: rgba(255, 255, 255, 0.08);
        }
        strong {
            color: var(--primary-accent);
        }
        .warning {
            margin-top: 30px;
            
            color: #ff5555;
            text-align: center;
            border: 1px dashed #ff5555;
            padding: 10px;
        }
    </style>
</head>
<body>
    <div id="content">
        <h1>ESP32 Web Server</h1>
        <p class="intro">Hello, I'm <strong>GorGor</strong>, and this is my Server Project.</p>
        <ul>
            <li>Powered by the infamous <strong>ESP32 Microcontroller</strong>.</li>
            <li><strong>Dual-Core Performance</strong> Running at a whopping 240 MHz.</li>
            <li><strong>Connectivity</strong> Integrated Wi-Fi and Bluetooth (BT) stacks.</li>
            <li><strong>Packet Crafting</strong> Specialized NIC access for customized networking.</li>
            <li><strong>Radio Analysis</strong> 2.4GHz radio wave capture for wireless packet sniffing.</li>
        </ul>
        <div class="warning">
            The capabilities of this 3cm x 5cm chip are ASTONISHING. 
            Improper use of these devices poses significant security risks.
        </div>
        <h5>pls dont DOS my server :)</h4>
    </div>
</body>
</html>)=====";

socklen_t addresslen = sizeof(address);
void loop(){
    // LOOP THROUGH REQUESTS, ACCEPT AND SEND THE HEADER + SITE AND CLOSE CONNECTION IMMIEDIATLY
    int clientsock = accept(s, (struct sockaddr*)&address, &addresslen);
    if(clientsock > 0){
    recv(clientsock,buffer,sizeof(buffer),0);
    memset(buffer, 0 , sizeof(buffer));
    send(clientsock,resp,strlen(resp),0);
    send(clientsock,site,strlen(site),0);
    delay(25);
    closesocket(clientsock);
    }
    
}