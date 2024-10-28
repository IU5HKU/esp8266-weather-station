// AMA 28.09.2024 Adapted to use api.open-meteo.com

/**The MIT License (MIT)
 
 Copyright (c) 2020 by Chris Klinger
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once
#include <JsonListener.h>
#include <JsonStreamingParser.h>

typedef struct OpenWeatherMapOneCallCurrentData {
  // "dt":1587216739
  uint32_t dt;
  // "sunrise":1587182465
  uint32_t sunrise;
  // "sunset":1587233389
  uint32_t sunset;
  // "temp": 290.56
  float temp;
  // "feels_like": 290.56
  float feels_like;
  // "pressure": 290.56
  uint16_t pressure;
  // "humidity": 87
  uint8_t humidity;
  //"dew_point": -3.24
  float dew_point;
  // "uvi": 4.5
  float uvi;
  // "clouds": 0
  uint8_t clouds;
  // visibility: 10000
  uint16_t visibility;
  // "wind_speed": 1.5
  float windSpeed;
  // "wind_deg": 0
  float windDeg;
  // "id": 800
  uint16_t weatherId;
  // "main": "Rain"
  String weatherMain;
  // "description": "shower rain"
  String weatherDescription;
  // "icon": "09d"
  String weatherIcon;
  String weatherIconMeteoCon;
  uint8_t is_day; //day or night, for icon selection

} OpenWeatherMapOneCallCurrentData;

typedef struct OpenWeatherMapOneCallHourlyData {
  // "dt":1587216739
  uint32_t dt;
  // "temp": 290.56
  float temp;
  // "precipitation_probability": 0-100
  uint8_t rain_prob;
  // "feels_like": 290.56
  float feels_like;
  // "pressure": 290.56
  uint16_t pressure;
  // "humidity": 87
  uint8_t humidity;
  //"dew_point": -3.24
  float dew_point;
  // "clouds": 0
  uint8_t clouds;
  // "wind_speed": 1.5
  float windSpeed;
  // "wind_deg": 0
  float windDeg;
  // "id": 800
  uint16_t weatherId;
  // "main": "Rain"
  String weatherMain;
  // "description": "shower rain"
  String weatherDescription;
  // "icon": "09d"
  String weatherIcon;
  String weatherIconMeteoCon;
  uint8_t is_day; //day or night, for icon selection

} OpenWeatherMapOneCallHourlyData;

typedef struct OpenWeatherMapOneCallDailyData {
  // "dt":1587216739
  uint32_t dt;
  // "sunrise":1587182465
  uint32_t sunrise;
  // "sunset":1587233389
  uint32_t sunset;
  // "temp": {"day": 17.72}
  float tempDay;
  // "temp": {"min": 17.72}
  float tempMin;
  // "temp": {"max": 17.72}
  float tempMax;
  // "temp": {"night": 17.72}
  float tempNight;
  // "temp": {"eve": 17.72}
  float tempEve;
  // "temp": {"morn": 17.72}
  float tempMorn;
  // "feels_like": {"day": 17.72}
  float feels_likeDay;
  // "feels_like": {"night": 17.72}
  float feels_likeNight;
  // "feels_like": {"eve": 17.72}
  float feels_likeEve;
  // "feels_like": {"morn": 17.72}
  float feels_likeMorn;
  // "pressure": 290.56
  uint16_t pressure;
  // "humidity": 87
  uint8_t humidity;
  //"dew_point": -3.24
  float dew_point;
  // "wind_speed": 1.5
  float windSpeed;
  // "wind_deg": 0
  float windGusts;
  // "wind_gusts": 0
  float windDeg;
  // "id": 800
  uint16_t weatherId;
  // "main": "Rain"
  String weatherMain;
  // "description": "shower rain"
  String weatherDescription;
  // "icon": "09d"
  String weatherIcon;
  String weatherIconMeteoCon;
  // "clouds": 0
  uint8_t clouds;
  // "rain": 5.97
  float rain;
  // "precipitation_probability_max": 0-100
  uint8_t rain_prob;
  // "snow":	0.15
  float snow;
  // "uvi": 4.5
  float uvi;
  
} OpenWeatherMapOneCallDailyData;

typedef struct OpenWeatherMapOneCallData {
  // "lon": 8.54,
  float lon;
  // "lat": 47.37
  float lat;
  // "timezone": "America/Chicago"
  String timezone;
  // "current": {}
  OpenWeatherMapOneCallCurrentData current;
  // "hourly": [...]
  OpenWeatherMapOneCallHourlyData hourly[8];
  // "daily": [...]
  OpenWeatherMapOneCallDailyData daily[8];
} OpenWeatherMapOneCallData;

class OpenWeatherMapOneCall: public JsonListener {
  private:
    const String host = "api.open-meteo.com"; //"api.openweathermap.org";
    const uint8_t port = 80;
    String currentKey = "ROOT";
    String currentParent;
    OpenWeatherMapOneCallData *data;
    uint8_t weatherItemCounter = 0;
    uint8_t dailyItemCounter = 0;
    uint8_t hourlyItemCounter = 0;

    boolean metric = true;
    String language;
    uint8_t maxDailyForecasts = 8; //5;
    uint8_t maxHourlyForecasts = 8; //12;
    // uint8_t *allowedHours;
    // uint8_t allowedHoursCount = 0;
    uint8_t currentForecast;

    void doUpdate(OpenWeatherMapOneCallData *data, String path);
    String buildPath(String appId, float lat, float lon);

  public:
    OpenWeatherMapOneCall();
    void update(OpenWeatherMapOneCallData *data, String appId, float lat, float lon);

    void setMetric(boolean metric) {this->metric = metric;}
    boolean isMetric() { return metric; }
    void setLanguage(String language) { this->language = language; }
    String getLanguage() { return language; }
    
    String getMeteoconIcon(uint16_t weather_code, uint8_t is_day);

    virtual void whitespace(char c);
    virtual void startDocument();
    virtual void key(String key);
    virtual void value(String value);
    virtual void endArray();
    virtual void endObject();
    virtual void endDocument();
    virtual void startArray();
    virtual void startObject();
};
