#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "../include/weather.h"
#include "../include/credentials.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, char *data) {
    strncat(data, ptr, size * nmemb);
    return size * nmemb;
}

int get_weather(const char *city_name, WeatherData *out_data) {
    CURL *curl;
    CURLcode res;
    char url[512];
    char encoded_city[200] = ""; 
    char buffer[32768] = ""; 

    int j = 0;
    for (int i = 0; city_name[i] != '\0'; i++) {
        if (city_name[i] == ' ' || city_name[i] == '+') {
            strcat(encoded_city, "%%20"); 
            j += 3;
        } else {
            encoded_city[j++] = city_name[i];
            encoded_city[j] = '\0';
        }
    }

    sprintf(url, "http://api.openweathermap.org/data/2.5/forecast?q=%s&appid=%s&units=metric", encoded_city, API_KEY);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK || strstr(buffer, "\"cod\":\"404\"")) {
            curl_easy_cleanup(curl);
            return 0;
        }

        char *tz_ptr = strstr(buffer, "\"timezone\":");
        if(tz_ptr) sscanf(tz_ptr, "\"timezone\":%ld", &out_data->timezone);
        
        char *name_ptr = strstr(buffer, "\"name\":\"");
        if(name_ptr) sscanf(name_ptr, "\"name\":\"%[^\"]\"", out_data->city);

        char *search_ptr = buffer;
        for(int i = 0; i < 5; i++) {
            search_ptr = strstr(search_ptr, "\"temp\":");
            if(search_ptr) {
                sscanf(search_ptr, "\"temp\":%f", &out_data->daily[i].temp);
                char *icon_ptr = strstr(search_ptr, "\"icon\":\"");
                if(icon_ptr) sscanf(icon_ptr, "\"icon\":\"%[^\"]\"", out_data->daily[i].icon);
                
                for(int k=0; k<8 && search_ptr; k++) {
                    search_ptr = strstr(search_ptr + 1, "\"dt\":");
                }
            }
        }
        curl_easy_cleanup(curl);
        return 1;
    }
    return 0;
}