:Author: vedatoz
:Email: ozturkvedat72@gmail.com
:Date: 25/05/2024
:License: Public Domain

= Project: {Room Metrics Tracker}

An IoT project that uses sensors to monitor environmental parameters, and sends email notifications on exceeded decibel threshold.

== Step 1: Installation

1. Login to Arduino IoT Cloud platform and create a dashboard with variables; Humidity, Temperature, Noise.
2. You can bind this variables to corresponding visualizations on your dashboard. E.g. chart for noise, gauge for temperature, percentage for humidity..
2. Open the project folder on Arduino IoT Cloud platform.
3. Edit arduino_secrets.h file with your Wi-fi credentials and your Arduino IoT Cloud dashboard secret key.
4. Check the rest of the codes in the header files/main code in case of compatibility errors. 

== Step 2: Assemble the circuit

Assemble the circuit following the diagram in IoTProj_circuit.png file.

== Step 3: Load the code

Upload the code contained in the .ino file to your nodeMCU esp8266 board.

=== Folder structure

....
 IotProject_dec28a           => Arduino sketch folder
  ├── IotProject_dec28a.ino       => main Arduino file
  ├── arduino_secrets.h           => header file for credentials
  ├── sketch.json                 => json file for Cloud
  └── thingProperties.h           => header file for binding the Cloud service to the main code
 IotProj_circuit.png         => an image of the circuit diagram
 IotProj.fzz                 => fritzing file of circuit (if you want to edit the circuit on Fritzing software)
 README.md                   => this file 
 sensors.jpg                 => an image of the actual circuit



=== Materials you need for this project

|===
| Arduino nodeMCU esp8266
| DHT-11 Temperature/Humidity Sensor      
| LM-393 Sound Sensor      
| Jumper Cables 
| Resistor (for DHT-11)
|===
