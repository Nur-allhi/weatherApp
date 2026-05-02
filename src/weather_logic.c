#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../include/weather.h"
#include "../include/credentials.h"


size_t write_data(void *ptr, size_t size, size_t nmemb, char *data) {
    strcat(data, ptr);
    return size * nmemb;
}

int get_weather(const char *city_name, WeatherData *out_data) {
    CURL *curl;
    CURLcode res;
    char url[256];
    char buffer[2048] = ""; 

    
    sprintf(url, "http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric", city_name, API_KEY);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) return 0; 

        
        char *temp_ptr = strstr(buffer, "\"temp\":");
        if (temp_ptr) {
            sscanf(temp_ptr, "\"temp\":%f", &out_data->temp);
            strcpy(out_data->city, city_name);
            return 1; 
        }
    }
    return 0; 
}