#ifndef WEATHER_H
#define WEATHER_H

typedef struct {
    char city[50];
    float temp;
    int humidity;
    char description[100];
} WeatherData;


int get_weather(const char *city_name, WeatherData *out_data);

#endif