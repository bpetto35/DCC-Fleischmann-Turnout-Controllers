# Turnout Controler Sink

## Definition
Power a turnout motor with a relay and control the direction from an Arduino signal.

## Key Features
Use a RJ45 cable to port
* an AC 16V power from the accessories power supply (model 670601) labelled
  * 16ACLine
  * 16ACBack
* a 5V DCC and GND from the Arduino
* a Signal (5V/GND) to make the relay switch

## Fleischmann turnout wires
| Color |Function |
|----------|-----------------|
| Red   | Turn* |
| Green | Straight* |
| Black | Common  |

\* still to experiment

## RJ-45 special pin layout

| RJ45 Pin Sink | Type   | Color (T568B)   |  RJ45 Pin Source |
|:-----------:|----------|-----------------|:----------------:|
| 8           | 16ACLine | Brown           | 8 |  
| 7           | 16ACBack | White/Brown     | 7 |
| 4           | 5Vcc     | Blue            | 4 |
| 5           | GND      | White/Blue      | 5 |
| 3           | Signal   | White/Orange    | 1 |

## Pictures

![TurnoutRelayPCB](/Turnout-Sink/images/PCB_PCB_Turnout-Relay-Sink_2025-11-19.png?raw=true)

![TurnoutRelay3D](/Turnout-Sink/images/turnout-relay-sink.png?raw=true)
