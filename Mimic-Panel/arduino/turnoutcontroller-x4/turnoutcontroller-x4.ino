// Include NMRA DCC lib
#include <NmraDcc.h>

// constant
#define RELAI_THRESHOLD 1000

// PIN assign
// Turnout #1 input and output
#define T1_BUTTON_PIN 7
#define T1_LED_RELAY_PIN 9
// Turnout #2 input and output
#define T2_BUTTON_PIN 6
#define T2_LED_RELAY_PIN 10
// Turnout #3 input and output
#define T3_BUTTON_PIN 5
#define T3_LED_RELAY_PIN 8
// Turnout #4 input and output
#define T4_BUTTON_PIN 4
#define T4_LED_RELAY_PIN 11
// DCC decoder input
#define DCC_INPUT_PIN 2
// #define DCC_ACK_PIN   3

// DCC constant
#define DECODER_ADDR  40

// Turnout structure
struct Turnout {
  uint8_t buttonPin;
  uint8_t relayLedPin;
  int buttonState;
  int relayState;
  unsigned long timestamp;
};

// Default and starting values of the turnouts
Turnout turnouts[4] = [
  { T1_BUTTON_PIN, T1_LED_RELAY_PIN, HIGH, LOW, 0 },
  { T2_BUTTON_PIN, T2_LED_RELAY_PIN, HIGH, LOW, 0 },
  { T3_BUTTON_PIN, T3_LED_RELAY_PIN, HIGH, LOW, 0 },
  { T4_BUTTON_PIN, T4_LED_RELAY_PIN, HIGH, LOW, 0 },
];

// NMRA DCC lib Singleton
NmraDcc  Dcc;

void notifyDccAccTurnoutOutput(uint16_t Addr, uint8_t Direction, uint8_t OutputPower) {
  // Get the current decoder address
  uint16_t myAddress = Dcc.getAddr();
  int turnoutIdx = myAddress - Addr;

  if (turnoutIdx >= 0 && turnoutIdx < 4) {
    if(Direction == 0) {
      turnouts[turnoutIdx].relayState = LOW;
    } else {
      turnouts[turnoutIdx].relayState = HIGH;
    }
    Serial.print(turnoutIdx);
    Serial.print(" -- DCC Turnout toggling to ");
    Serial.println(Direction);
    digitalWrite(turnouts[turnoutIdx].relayLedPin, turnouts[turnoutIdx].relayState);
  }

}

void notifyCVResetFactoryDefault() {
  // Reset requested, set default address...
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_LSB, DECODER_ADDR & 0xFF);
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_MSB, DECODER_ADDR >> 8);  
}

// void notifyCVAck(void) {
//   digitalWrite(DCC_ACK_PIN, HIGH);
//   delay(8);  
//   digitalWrite(DCC_ACK_PIN, LOW);
// }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // init the pin for each turnout
  for (int turnoutIdx=0; i<4; i++) {
    pinMode(turnouts[turnoutIdx].buttonPin, INPUT);
    digitalWrite(turnouts[turnoutIdx].buttonPin, HIGH); // Write the button is HIGH when released, make test the LOW in the loop() for pressed
    pinMode(turnouts[turnoutIdx].relayLedPin, OUTPUT);
  }
  // pinMode(DCC_ACK_PIN, OUTPUT);

  // init the NMRA DCC library
  Dcc.pin(digitalPinToInterrupt(DCC_INPUT_PIN), DCC_INPUT_PIN, 1);
  Dcc.init(MAN_ID_DIY, 1, FLAGS_MY_ADDRESS_ONLY | FLAGS_DCC_ACCESSORY_DECODER, 0);
}

void loop() {
  unsigned long now = millis();

  // call the NMRA DCC singleton process
  Dcc.process();

  // for each turnout, read the button
  for (int turnoutIdx=0; turnoutIdx<4; turnoutIdx++) {
    if (turnouts[turnoutIdx].timestamp + RELAI_THRESHOLD < now) {
      turnouts[turnoutIdx].buttonState = digitalRead(turnouts[turnoutIdx].buttonPin);
      if (turnouts[turnoutIdx].buttonState == LOW) {
        // change the state of the relay and the led
        turnouts[turnoutIdx].timestamp = now;
        Serial.print(turnoutIdx);
        Serial.println(" -- Turnout toggling");
        turnouts[turnoutIdx].relayState = (turnouts[turnoutIdx].relayState == LOW) ? HIGH : LOW;
        digitalWrite(turnouts[turnoutIdx].relayLedPin, turnouts[turnoutIdx].relayState);
      }
    }
  }

}
