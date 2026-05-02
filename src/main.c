#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/weather.h"

int main() {
    
    printf("Content-type: text/html\n\n");

    
    char *query = getenv("QUERY_STRING"); 
    char city[50] = "Dhaka"; 

    if (query && strncmp(query, "city=", 5) == 0) {
        strcpy(city, query + 5);
    }

    WeatherData data;
    
    printf("<html><head><title>C Weather</title>");
    printf("<style>body{font-family:sans-serif; text-align:center; background:#f4f4f4;} .card{background:white; padding:20px; display:inline-block; border-radius:10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1);}</style>");
    printf("</head><body>");
    printf("<h1>C-Powered Weather Station</h1>");

    if (get_weather(city, &data)) {
        
        printf("<div style='background: white; border-radius: 15px; padding: 20px; box-shadow: 0 4px 6px rgba(0,0,0,0.1); display: inline-block;'>");
        printf("<h2 style='color: #333;'>Weather Report</h2>");
        printf("<h3 style='color: #007bff;'>%s</h3>", data.city);
        printf("<p style='font-size: 48px; font-weight: bold; margin: 10px 0;'>%.1f&deg;C</p>", data.temp);
        printf("<p style='color: #666;'>Data fetched via C-Backend</p>");
        printf("</div>");
    } else {
        printf("<p>Error fetching data for %s</p>", city);
    }

    printf("<br><br><a href='/'>Back to Search</a>");
    printf("</body></html>");

    return 0;
}