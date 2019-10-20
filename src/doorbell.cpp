/*
 * MyESP test
 */

#include "my_config.h"
#include "version.h"
#include <PButton.h>
#include <Arduino.h>

#include <MyESP.h>

// Debugger to telnet
#define myDebug(...) myESP.myDebug(__VA_ARGS__)
#define myDebug_P(...) myESP.myDebug_P(__VA_ARGS__)

bool SettingsCallback(MYESP_FSACTION action, uint8_t wc, const char * setting, const char * value);
bool FSCallback(MYESP_FSACTION action, JsonObject json);


#define WAIT_TIME 50  // wait time in ms (500 is 1/2 a second)

command_t PROGMEM project_cmds[] = {{"info", "show info"}};

// BLUE SIGNAL LED
const uint8_t LED_PIN = 27; // GPIO27

// button
const uint8_t  PButton_PIN             = 25;    // GPIO25
const uint16_t PButton_Debounce        = 40;
const uint16_t PButton_DblClickDelay   = 250;
const uint16_t PButton_LongPressDelay  = 750;
const uint16_t PButton_VLongPressDelay = 3000; // 3 seconds
PButton myPButton(PButton_PIN, HIGH, PButton_Debounce, PButton_DblClickDelay, PButton_LongPressDelay, PButton_VLongPressDelay);

// click types
enum click_t : uint8_t { PRESS_SINGLE_CLICK, PRESS_DOUBLE_CLICK, PRESS_LONG_CLICK, PRESS_VERYLONG_CLICK };
enum click_t click;

// send ring command to HA
void sendRing(click_t clickType) {
    // light up LED
    digitalWrite(LED_PIN, HIGH);

    // send to HA
    // use false so MQTT doesn't keep the message. otherwise restart of HA will fire the trigger each time
    if (clickType == PRESS_SINGLE_CLICK) {
        myESP.mqttPublish(MQTT_TOPIC_RING, "single press");
    } else if (clickType == PRESS_DOUBLE_CLICK) {
        myESP.mqttPublish(MQTT_TOPIC_RING, "double press");
    } else if (clickType == PRESS_LONG_CLICK) {
        myESP.mqttPublish(MQTT_TOPIC_RING, "long press");
    } else if (clickType == PRESS_VERYLONG_CLICK) {
        myESP.mqttPublish(MQTT_TOPIC_RING, "very long press");
    }

    // turn off LED
    delay(1000);
    digitalWrite(LED_PIN, LOW);
}

// button single click
void OnClick(PButton & b) {
    myDebug("Button single click");
    sendRing(PRESS_SINGLE_CLICK);
}

// button double click
void OnDblClick(PButton & b) {
    myDebug("Button double click");
    sendRing(PRESS_DOUBLE_CLICK);
}

// button long press
void OnLongPress(PButton & b) {
    myDebug("Button long press");
    sendRing(PRESS_LONG_CLICK);
}

// button indefinite press
void OnVLongPress(PButton & b) {
    myDebug("Button very long press");
    // sendRing(PRESS_VERYLONG_CLICK);
}


// call back when a telnet client connects or disconnects
// we set the logging here
void TelnetCallback(uint8_t event) {
    if (event == TELNET_EVENT_CONNECT) {
        //ems_setLogging(EMS_SYS_LOGGING_DEFAULT);
    } else if (event == TELNET_EVENT_DISCONNECT) {
        //ems_setLogging(EMS_SYS_LOGGING_NONE);
    }
}

// Init callback, which is used to set functions and call methods when telnet has started
void WIFICallback() {
    myDebug("* wifi init callback");
}

// MQTT Callback to handle incoming/outgoing changes
void MQTTCallback(unsigned int type, const char * topic, const char * message) {
    // we're connected. lets subscribe to some topics
    if (type == MQTT_CONNECT_EVENT) {
        myESP.mqttSubscribe(MQTT_TOPIC_RING);

        // subscribe to a start message and send the first publish
        myESP.mqttSubscribe(MQTT_TOPIC_START);
        myESP.mqttPublish(MQTT_TOPIC_START, MQTT_TOPIC_START_PAYLOAD);
    }

    if (type == MQTT_MESSAGE_EVENT) {
        // handle response from a start message
        // for example with HA it sends the system time from the server
        if (strcmp(topic, MQTT_TOPIC_START) == 0) {
            myDebug("Received boottime: %s", message);
            myESP.setBoottime(message);
            return;
        }
    }
}

// callback for loading/saving settings to the file system (SPIFFS)
bool FSCallback(MYESP_FSACTION action, JsonObject json) {
    bool ok = true;
    if (action == MYESP_FSACTION_LOAD) {
        /*
        // led
        if (json.containsKey("led")) {
            EMSESP_Status.led_enabled = (bool)json["led"];
        } else {
            EMSESP_Status.led_enabled = LED_BUILTIN; // default value
            ok                        = false;
        }
        */

    }

    if (action == MYESP_FSACTION_SAVE) {
       // json["led"]             = EMSESP_Status.led_enabled;

    }

    return ok; // all ok
}

// callback for custom settings when showing Stored Settings
// wc is number of arguments after the 'set' command
// returns true if the setting was recognized and changed
bool SettingsCallback(MYESP_FSACTION action, uint8_t wc, const char * setting, const char * value) {
    bool ok = false;

    if (action == MYESP_FSACTION_SET) {
        // led
    }

    if (action == MYESP_FSACTION_LIST) {
        // myDebug("  led=%s", EMSESP_Status.led_enabled ? "on" : "off");
    }

    return ok;
}

void showInfo() {
    myDebug("Info...");
    //myDebug("> ESP32 Temp = %s C\n", myESP.formatFloat(temperatureRead(), 2, 2).c_str());
    myDebug("> ESP32 Hall sensor = %d", hallRead());
    myDebug("> Switch pin is %d", PButton_PIN);
}

// extra commands options for telnet debug window
// wc is the word count, i.e. number of arguments. Everything is in lower case.
void TelnetCommandCallback(uint8_t wc, const char * commandLine) {
    bool ok = false;
    // get first command argument
    char * first_cmd = strtok((char *)commandLine, ", \n");

    if (strcmp(first_cmd, "info") == 0) {
        showInfo();
        ok = true;
    }
    
    // check for invalid command
    if (!ok) {
        myDebug("Unknown command. Use ? for help.");
    }
}

/*
 * Setup
 */
void setup() {

    // set up myESP for Wifi, MQTT, MDNS and Telnet
    myESP.setTelnet(project_cmds, ArraySize(project_cmds), TelnetCommandCallback, TelnetCallback); // set up Telnet commands
#ifdef WIFI_SSID
    myESP.setWIFI(WIFI_SSID, WIFI_PASSWORD, WIFICallback);
#else
    myESP.setWIFI(NULL, NULL, WIFICallback); // pull the wifi settings from the SPIFFS stored settings
#endif

    // MQTT host, username and password taken from the SPIFFS settings
    myESP.setMQTT(NULL, NULL, NULL, MQTT_BASE, MQTT_KEEPALIVE, MQTT_QOS, MQTT_RETAIN, MQTT_WILL_TOPIC, 
      MQTT_WILL_ONLINE_PAYLOAD, MQTT_WILL_OFFLINE_PAYLOAD, MQTTCallback);

    // custom settings in SPIFFS
    myESP.setSettings(FSCallback, SettingsCallback);

    // start up all the services
    myESP.begin(APP_HOSTNAME, APP_NAME, APP_VERSION);

    // push button
    myPButton.onClick(OnClick);
    myPButton.onDblClick(OnDblClick);
    myPButton.onLongPress(OnLongPress);
    myPButton.onVLongPress(OnVLongPress);

    // LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

}

void loop() {

    myESP.loop();

    // check button press
    myPButton.check();

    // wait
    delay(WAIT_TIME);
}