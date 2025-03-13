#include "CandlestickMain.h"
#include "CandlestickPlot.h"
#include "CandlestickMenu.h"
#include <iostream>

int main() {
    try {
        // Initialize and start the menu-driven application
        CandlestickMenu app("weather_data_EU_1980-2019_temp_only.csv");
        app.init();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
