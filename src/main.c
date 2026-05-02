#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/weather.h"

int main() {
    printf("Content-type: text/html; charset=UTF-8\n\n");

    char *query = getenv("QUERY_STRING"); 
    char city[50] = "Dhaka"; 

    if (query && strncmp(query, "city=", 5) == 0) {
        strcpy(city, query + 5);
    }

    // FIX: Declare the data variable BEFORE using it
    WeatherData data;
    
    printf("<!DOCTYPE html><html><head>");
    printf("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
    printf("<style>");
    printf("body{background:#f0f2f5; font-family:sans-serif; margin:0; display:flex; justify-content:center; align-items:center; min-height:100vh;}");
    printf(".container{width:95%%; max-width:600px; background:white; padding:20px; border-radius:20px; box-shadow:0 10px 30px rgba(0,0,0,0.1); text-align:center;}");
    printf(".forecast-grid{display:grid; grid-template-columns: repeat(auto-fit, minmax(100px, 1fr)); gap:10px; margin-top:20px;}");
    printf(".day-card{background:#f8f9fa; padding:15px; border-radius:15px; border:1px solid #eee;}");
    printf("h1, h2{color:#333;} .temp{font-size:48px; font-weight:bold; color:#007bff;}");
    printf("</style></head><body>");

    if (get_weather(city, &data)) {
        time_t now = time(NULL);
       
        now += data.timezone;
        struct tm *t = gmtime(&now);

        printf("<div class='container'>");
        printf("<h1>%s</h1>", data.city);
        printf("<p>%02d:%02d | %d-%02d-%d</p>", t->tm_hour, t->tm_min, t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
        
        printf("<div class='temp'>%.1f&deg;C</div>", data.daily[0].temp);

        printf("<div class='forecast-grid'>");
        for(int i=0; i<5; i++) {
            printf("<div class='day-card'><b>Day %d</b><br>%.1f&deg;C</div>", i+1, data.daily[i].temp);
        }
        printf("</div><br><a href='/' style='text-decoration:none; color:#007bff;'>&larr; New Search</a></div>");
    } else {
        printf("<div class='container'><h1>City Not Found</h1><a href='/'>Go Back</a></div>");
    }

    printf("</body></html>");
    return 0;
}