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

    WeatherData data;
    
    printf("<!DOCTYPE html><html><head>");
    printf("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
    printf("<style>");
    
    
    printf("body { margin: 0; min-height: 100vh; display: flex; justify-content: center; align-items: center; font-family: 'Segoe UI', sans-serif; transition: background 1s ease; overflow: hidden; position: relative; }");
    printf(".warm-bg { background: linear-gradient(135deg, #f093fb 0%%, #f5576c 100%%); }");
    printf(".cold-bg { background: linear-gradient(135deg, #5ee7df 0%%, #b490ca 100%%); }");
    
    
    printf(".glass-card { background: rgba(255, 255, 255, 0.2); backdrop-filter: blur(15px); -webkit-backdrop-filter: blur(15px); ");
    printf("border-radius: 30px; border: 1px solid rgba(255, 255, 255, 0.3); padding: 40px; color: white; text-align: center; box-shadow: 0 8px 32px rgba(0,0,0,0.2); width: 90%%; max-width: 450px; z-index: 10; }");
    
    
    printf(".rain { position: absolute; background: white; width: 2px; height: 15px; opacity: 0.4; top: -20px; animation: fall 1s linear infinite; }");
    printf(".snow { position: absolute; background: white; border-radius: 50%%; width: 8px; height: 8px; opacity: 0.8; top: -10px; animation: fall 4s linear infinite; }");
    printf("@keyframes fall { to { transform: translateY(100vh); } }");
    
    printf(".sun-glow { position: absolute; width: 300px; height: 300px; background: radial-gradient(circle, rgba(255,255,255,0.4) 0%%, transparent 70%%); border-radius: 50%%; top: -50px; right: -50px; animation: pulse 4s ease-in-out infinite; }");
    printf("@keyframes pulse { 0%%, 100%% { transform: scale(1); opacity: 0.4; } 50%% { transform: scale(1.2); opacity: 0.7; } }");

    printf(".temp-main { font-size: 80px; font-weight: 800; margin: 10px 0; }");
    printf(".forecast-row { display: flex; justify-content: space-between; margin-top: 30px; gap: 10px; }");
    printf(".day-item { background: rgba(255, 255, 255, 0.15); padding: 15px 10px; border-radius: 15px; flex: 1; font-size: 14px; }");
    printf(".back-btn { display: inline-block; margin-top: 25px; color: white; text-decoration: none; font-weight: 600; opacity: 0.8; }");
    printf("</style></head>");

    if (get_weather(city, &data)) {
        const char *bg = (data.daily[0].temp > 25) ? "warm-bg" : "cold-bg";
        printf("<body class='%s'>", bg);
        
        
        if (strstr(data.daily[0].icon, "09") || strstr(data.daily[0].icon, "10")) {
            for(int i=0; i<30; i++) printf("<div class='rain' style='left: %d%%; animation-delay: 0.%ds;'></div>", i*3, i%10);
        } else if (strstr(data.daily[0].icon, "13")) {
            for(int i=0; i<20; i++) printf("<div class='snow' style='left: %d%%; animation-delay: %ds;'></div>", i*5, i%4);
        } else if (strstr(data.daily[0].icon, "01")) {
            printf("<div class='sun-glow'></div>");
        }

        time_t now = time(NULL) + data.timezone;
        struct tm *t = gmtime(&now);

        printf("<div class='glass-card'>");
        printf("<div style='opacity: 0.9;'>%02d:%02d | %s</div>", t->tm_hour, t->tm_min, data.city);
        printf("<h1>%s</h1>", data.city);
        printf("<img src='http://openweathermap.org/img/wn/%s@4x.png' style='width: 150px; margin: -20px 0;'>", data.daily[0].icon);
        printf("<div class='temp-main'>%.0f&deg;</div>", data.daily[0].temp);

        printf("<div class='forecast-row'>");
        for(int i=1; i<5; i++) {
            printf("<div class='day-item'>");
            printf("Day %d<br>", i);
            printf("<img src='http://openweathermap.org/img/wn/%s.png' style='width: 40px;'><br>", data.daily[i].icon);
            printf("<b>%.0f&deg;</b>", data.daily[i].temp);
            printf("</div>");
        }
        printf("</div>");
        printf("<a href='/' class='back-btn'>&larr; Search Different City</a>");
        printf("</div>");
    } else {
        printf("<body class='cold-bg'><div class='glass-card'><h1>City Not Found</h1><a href='/' class='back-btn'>Go Back</a></div>");
    }

    printf("</body></html>");
    return 0;
}