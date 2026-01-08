<h2>Result : </h2>
<h3>A working Static Web Server that would accept a request and serve the page and close the connection </h3>
<img src="picture.png">




<h2>Requirements : </h2>
<ul>
<li>ESP32 microcontroller or dev module </li>
<li>Arduino IDE for coding + the required libraries like esp32 , WiFi and lwip/sockets.h </li>
<li>Optional an Antenna for improved Wifi capabilities to ensure consistance network connectivity </li>
</ul>

<h2>Steps : </h2>
<ul>
<li>Download Arduino IDE</li>
<li>Download the provided WebServerSource.ino file </li>
<li>Open the file in the IDE and upload the code into the ESP32 after pluging it in via USB cable </li>
<li>Make sure the change the SSID + Password for your network and change the default gateway and static ip to match the one given by the DHCP</li>
<li>some times the esp32 is not writable and require some windows COM libraries</li>
</ul>
