#pragma once

#include "NotoSansBold15.h"
#include "NotoSansBold36.h"
#include "NotoSansBold48.h"

// WiFi
#define WIFI_SSID "Treehouse 2.4"
#define WIFI_PASSWORD "MGKMDV2000"

// TFT Screen Manager
#define TFT_MOSI 17
#define TFT_MISO -1
#define TFT_SCLK 23
#define TFT_CS 15
#define TFT_DC 19
#define TFT_RST 18

#define SCREEN_1_CS 33
#define SCREEN_2_CS 32
#define SCREEN_3_CS 25
#define SCREEN_4_CS 26

#define NUM_SCREENS 4
#define SCREEN_SIZE 240
#define TFT_WIDTH SCREEN_SIZE
#define TFT_HEIGHT SCREEN_SIZE

// Dashboards
// 0 - None, 1 - Clock, 2 - Weather, 3 - Music
#define SCREEN_1_DASHBOARD 0
#define SCREEN_2_DASHBOARD 1
#define SCREEN_3_DASHBOARD 2
#define SCREEN_4_DASHBOARD 3

// Clock
#define TIME_24 false

// Weather
// https://www.latlong.net/
#define API_KEY "pYO9LNlynWkrC36DvAx3aC3v7qZnNGQ1"
#define USE_METRIC false
#define USE_LAT_LON true
#define LOCATION ""
#define LATITUDE "39.166592"
#define LONGITUDE "-86.534889"
#define USE_HOURLY_FORECAST false // True for hourly, false for daily

// Rotary Encoder
#define KNOB_CLK_PIN 14
#define KNOB_DT_PIN 12
#define KNOB_SW_PIN 13

// Buttons
#define BUTTON_1_PIN 4
#define BUTTON_2_PIN 2

// Fonts
#define NOTO_BOLD_15 NotoSansBold15
#define NOTO_BOLD_36 NotoSansBold36
#define NOTO_BOLD_48 NotoSansBold48