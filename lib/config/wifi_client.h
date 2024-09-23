#pragma once
#include <vector>

void setupWiFi();
String getIPAddress();

void setupNTP();
String getFormattedTime();

std::vector<String> fetchCurrentWeatherData();