# EELE 465 Final Project
*ESP32 LED Array Control via Wireless Web App Interface*

**From Proposal:**

"The idea I had was to create and operate a cheap chainable led array from amazon that is controlled by an MSP430FR2310, but the user can control from their phone (utilizing a raspberry pi hotspot which also hosts a server for array control). After getting recommended to the ESP32 from you [Trevor Vannoy] I switched away from the thought of using a raspberry pi; this will be helpful for both power and space. The goal is to make it a mobile setup; then possibly put it on my cap for graduation. For the sake of having values to display, either over LED array or LCD, I’ll also hook up a temperature sensor and real-time-clock. Hopefully I can lean into my Computer Science background with the ESP32 while maintaining a footing within the realm of Microcontroller Applications."

# Final Project Circuit Design
*Altered slightly from proposal, but still maintains I2C master/slave topology*

![System Circuit Design](docs/planning/Final_Project_Diagrams-final_circuit_diagram.png)

# Final Project Flowchart
*Note concurrent processes of the main loop and Led Array Control (LAC) loop!*

![System Circuit Design](docs/planning/Final_Project_Diagrams-System_Flowchart.png)

[Backup Demo Youtube Link](https://youtu.be/YtcjxF9x2d8)
