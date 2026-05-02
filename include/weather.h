#ifndef WEATHER_H
#define WEATHER_H

typedef struct {
    char date[20];
    float temp;
    char icon[10];
} Forecast;

typedef struct {
    char city[50];
    long timezone;
    Forecast daily[5];
} WeatherData;

int get_weather(const char *city_name, WeatherData *out_data);

#endif