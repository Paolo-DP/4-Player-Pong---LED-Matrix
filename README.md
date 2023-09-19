# **4-Player-Pong---LED-Matrix**

## A 4 player pong game running on a _PIC16F877A_ microcontroller.  
It supports 2 players on its own but has a companion app on windows to support an additional 2 players.

The main gaming device features a dot matrix display to play pong with two players. A PIC microcontroller runs the games logic and displayes the game on the dot matrix with the support of a decade counter to drive all of the LEDs. the game device and stand on it's own but it does support an additional 2 players with a companion app.

![Prototype](/images/PrototypeBoard.png)

The Pong companion app runs separately on a computer which serves as the display and controls for the 3rd and 4th players. The program only serves to capture the player's inputs and sends it back to the main gaming device. All the game logic still happens on the PIC microcontroller. The companion app receives the display information then replicates the dot matrix LEDs on the laptop screen.

## _Watch the Demo [here](https://www.youtube.com/watch?v=203vcCY0gcY)_
![Game Demo](/images/GameDemo.png)

## Simulation
The prototype can also be simulated using [Proteus](https://www.labcenter.com/). This was done during the initial development to test the code on both the microcontroller and the companion app before the prototype was fabricated. Hex for the PIC MCU can be imported into Proteus. A virtual COM port lets the simulated MCU communicate with the companion app running on another IDE.

![schematic](/images/CircuitDiagram.png)

## In Partial fulfillment of LBYCP1D EQ T2SY2017-2018
### DLSU BS Computer Engineering
#### Authors:
- Bhuller, Jashan  
- Dela Peña, Paolo  
- Espiritu, Danielle  
- Isobe, Takeshi  
- Simeon, Julio