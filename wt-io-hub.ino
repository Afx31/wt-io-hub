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
    
    Serial.println("Example: Write to CAN");

    // External trigger button
    pinMode(3, INPUT_PULLUP);
}

// External trigger button
//int buttonState = 0;
int buttonState = HIGH;

void loop() {
    int pinValue = digitalRead(3);
    delay(100); // quick and dirty debounce filter
    
    // TODO: Attempt1 - logic wasn't right
    // if (buttonState != pinValue) {
    //   buttonState = pinValue;
    //   Serial.println(buttonState);
    // }

    // TODO: Attempt2 - Working
    if (buttonState == HIGH && pinValue == LOW) {
        Serial.println("Button Pressed");
        mcp2515.sendMessage(&canMsgEnableDatalogging);
    }
    buttonState = pinValue;
}