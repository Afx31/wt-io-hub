#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsgDatalogging;
struct can_frame canMsgChangePage;
struct can_frame canMsgPlaceholder;
MCP2515 mcp2515(10);

void setup() {
    /* TODO:
     * For now we will just send different can messages
     * Then in near future, we will utilise 1 canMsg,
     * And use the bytes correctly to house everything
     */
    canMsgDatalogging.can_id  = 0x69A;
    canMsgDatalogging.can_dlc = 4;
    canMsgDatalogging.data[0] = 0x01;
    canMsgDatalogging.data[1] = 0x01;
    canMsgDatalogging.data[2] = 0x01;
    canMsgDatalogging.data[3] = 0x01;

    canMsgChangePage.can_id  = 0x69B;
    canMsgChangePage.can_dlc = 4;
    canMsgChangePage.data[0] = 0x01;
    canMsgChangePage.data[1] = 0x01;
    canMsgChangePage.data[2] = 0x01;
    canMsgChangePage.data[3] = 0x01;

    canMsgChangePage.can_id  = 0x69C;
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
        mcp2515.sendMessage(&canMsgDatalogging);
    }
    btn3State = pinValue3;

    // Btn2
    if (btn4State == HIGH && pinValue4 == LOW) {
        Serial.println("Button Pressed - 2");
        mcp2515.sendMessage(&canMsgChangePage);
    }
    btn4State = pinValue4;

    // Btn3
    if (btn5State == HIGH && pinValue5 == LOW) {
        Serial.println("Button Pressed - 3");
        mcp2515.sendMessage(&canMsgPlaceholder);
    }
    btn5State = pinValue5;
}