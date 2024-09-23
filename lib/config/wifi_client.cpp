#include <WiFi.h>
#include <WiFiUdp.h>
#include "wifi_client.h"
#include "config.h"
#include <NTPClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
const String weatherApiKey = API_KEY;

// NTP setup
const long utcOffsetInSeconds = -14400;
const char *ntpServer = "pool.ntp.org";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, utcOffsetInSeconds);

WiFiClient client;
HTTPClient http;

void setupWiFi()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to ");
    Serial.print(ssid);

    unsigned long startTime = millis();
    unsigned long timeout = 10000;

    while (WiFi.status() != WL_CONNECTED && (millis() - startTime < timeout))
    {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nConnected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        setupNTP();
    }
    else
    {
        Serial.println("\nFailed to connect.");
    }
}

String getIPAddress()
{
    return WiFi.localIP().toString();
}

void setupNTP()
{
    timeClient.begin();
    timeClient.update();
    Serial.println("NTP setup complete");
}

String getFormattedTime()
{
    timeClient.update();
    int hours = timeClient.getHours();
    int minutes = timeClient.getMinutes();
    String formattedTime;
    if (TIME_24)
    {
        formattedTime = String(hours) + ":";
    }
    else
    {
        int displayHour = (hours % 12 == 0) ? 12 : (hours % 12);
        formattedTime = String(displayHour) + ":";
    }

    if (minutes < 10)
    {
        formattedTime += "0";
    }
    formattedTime += String(minutes);
    return formattedTime;
}

std::vector<String> fetchCurrentWeatherData()
{
    String location = USE_LAT_LON ? (String)LATITUDE + "%2C%20" + (String)LONGITUDE : LOCATION;
    String units = USE_METRIC ? "metric" : "imperial";

    String url = "https://api.tomorrow.io/v4/weather/realtime?location=" + location + "&units=" + units + "&apikey=" + weatherApiKey;
    Serial.println("Fetching weather data from: " + url);

    http.begin(url);

    int httpResponseCode = http.GET();
    if (httpResponseCode == 200)
    {
        String response = http.getString();

        // DynamicJsonDocument jsonDoc(8192);
        JsonDocument jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, response);

        if (error)
        {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return std::vector<String>();
        }

        JsonObject dataArray = jsonDoc["data"];

        if (!dataArray.isNull())
        {
            JsonObject firstInterval = dataArray["values"];
            String temperature = firstInterval["temperature"].as<String>();
            String humidity = firstInterval["humidity"].as<String>();
            String precipitation = firstInterval["precipitationProbability"].as<String>();

            std::vector<String> weatherData = {temperature, humidity, precipitation};
            return weatherData;
        }
    }
    else
    {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpResponseCode);
        Serial.println(http.getString());
    }

    http.end();
}