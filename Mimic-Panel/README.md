# Manage up to 4 Fleischmann Turnout

## Key Features
* DCC decoded input on Arduino Pin 2
* Support 4 buttons to use in standalone
  * Arduino Pin D4 to D7
* Support 2 leds per turnouts
  * 4 pins
  * Arduino Pin D8 to D11
* Signal up to 4 5V relay like SONGLE SRD-05VDC-SL-C
  * use the same Arduino output pin than the LED

## Layout

### Turnouts
| Turnout # | Button Pin | LED and Relay Pin |
|---|---|---|
| 1 | D7 | D9 |
| 2 | D6 | D10 |
| 3 | D5 | D8 |
| 4 | D4 | D11 |

### DCC in
see DCC decoder information in its directory

| Pin # | Function |
|---|---|
| 1 | 5V DC to power the DCC decoder |
| 2 | Signal RX to receive DCC info |
| 3 | GND to align the DCC decoder |

## Pictures

![MimicPanelPCB](Mimic-Panel/images/PCB_PCB_Mimic-Panel_2025-11-19.png?raw=true)