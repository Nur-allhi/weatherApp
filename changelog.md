
## Changelog

All notable changes to the **Weather Station** project are documented in this file.

### [1.2.0] - 2026-05-02
#### Added
*   **Immersive Weather Effects**: Integrated CSS-based animations (Rain, Snow, Sun Glow) that trigger dynamically based on OpenWeatherMap icon codes.
*   **Persistent Search History**: Implemented `localStorage` logic to save and display the last three searched cities as clickable chips.
*   **Smart Home Screen**: Added a dynamic greeting (Good Morning/Afternoon/Evening) and a real-time local clock using JavaScript.
*   **Quick-Access UI**: Added "Quick-Tap" city chips for popular locations to streamline the user experience.

#### Changed
*   **Modern UI Refresh**: Updated the home screen with a premium gradient background, improved input focus states, and interactive card shadows.
*   **Visual Feedback**: Added a loading spinner to the search form to provide immediate feedback during CGI execution.

---

### [1.1.0] - 2026-04-30
#### Added
*   **Glassmorphism UI**: Redesigned the results page with a semi-transparent frosted glass effect using `backdrop-filter`.
*   **Dynamic Backgrounds**: Implemented C logic to toggle between "Warm" and "Cold" CSS classes based on real-time temperature thresholds.
*   **5-Day Forecast**: Expanded the backend logic to parse and display a multi-day outlook instead of just current weather.
*   **Weather Icons**: Integrated OpenWeatherMap icon set to provide visual weather representations.

#### Fixed
*   **URL Encoding**: Resolved issues with city names containing spaces (e.g., "New York") by implementing a custom percent-encoding loop in `weather_logic.c`.
*   **API Validation**: Added 404 error handling to gracefully manage invalid city searches.

---

### [1.0.0] - 2026-04-15
#### Added
*   **Core C Engine**: Initial implementation of `libcurl` for fetching weather data from the OpenWeatherMap API.
*   **CGI Integration**: Configured the project to run as a compiled binary within the `/usr/lib/cgi-bin/` directory for Apache.
*   **Static Frontend**: Basic HTML form for city input and initial result table.
*   **Modular Architecture**: Separated logic into `weather.h`, `weather_logic.c`, and `main.c` for easier maintenance.

---

### Tech Stack Summary
*   **Backend:** C (CGI)
*   **Networking:** Libcurl
*   **Frontend:** HTML5, CSS3 (Glassmorphism, Flexbox), JavaScript (Vanilla)
*   **API:** OpenWeatherMap 5-Day / 3-Hour Forecast