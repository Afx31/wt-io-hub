#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsgEnableDatalogging;
struct can_frame canMsgChangePage;
MCP2515 mcp2515(10);

void setup() {
    canMsgEnableDatalogging.can_id  = 0x69;
    canMsgEnableDatalogging.can_dlc = 4;
    canMsgEnableDatalogging.data[0] = 0x01;
    canMsgEnableDatalogging.data[1] = 0x01;
    canMsgEnableDatalogging.data[2] = 0x01;
    canMsgEnableDatalogging.data[3] = 0x01;

    canMsgChangePage.can_id  = 0x67;
    canMsgChangePage.can_dlc = 4;
    canMsgChangePage.data[0] = 0x01;
    canMsgChangePage.data[1] = 0x01;
    canMsgChangePage.data[2] = 0x01;
    canMsgChangePage.data[3] = 0x01;
    
    while (!Serial);
    Serial.begin(500000);
    
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp2515.setNormalMode();

    // External trigger button
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
}

// External trigger button
int btn3State = HIGH;
int btn4State = HIGH;
int btn5State = HIGH;

void loop() {
    int pinValue3 = digitalRead(3);
    int pinValue4 = digitalRead(4);
    int pinValue5 = digitalRead(5);
    delay(100); // quick and dirty debounce filter

    // Btn1
    if (btn3State == HIGH && pinValue3 == LOW) {
        Serial.println("Button Pressed - 1");
        mcp2515.sendMessage(&canMsgEnableDatalogging);
    }
    btn3State = pinValue3;

    // Btn2
    if (btn4State == HIGH && pinValue4 == LOW) {
        Serial.println("Button Pressed - 2");
        //mcp2515.sendMessage(&canMsgEnableDatalogging);
    }
    btn4State = pinValue4;

    // Btn3
    if (btn5State == HIGH && pinValue5 == LOW) {
        Serial.println("Button Pressed - 3");
        //mcp2515.sendMessage(&canMsgEnableDatalogging);
    }
    btn5State = pinValue5;
}