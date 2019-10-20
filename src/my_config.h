/*
 * my_config.h
 *
 * All configurations and customization's go here
 *
 */

#pragma once

// MQTT base name
#define MQTT_BASE "home" // all MQTT topics are prefix with this string, in the format <MQTT_BASE>/<app name>/<topic>

// MQTT general settings
#define MQTT_TOPIC_START "start"
#define MQTT_TOPIC_START_PAYLOAD "start"
#define MQTT_WILL_TOPIC "status"            // for last will & testament topic name
#define MQTT_WILL_ONLINE_PAYLOAD "online"   // for last will & testament payload
#define MQTT_WILL_OFFLINE_PAYLOAD "offline" // for last will & testament payload
#define MQTT_RETAIN false
#define MQTT_KEEPALIVE 60 // 1 minute
#define MQTT_QOS 1

// custom
#define MQTT_TOPIC_RING "ring"

