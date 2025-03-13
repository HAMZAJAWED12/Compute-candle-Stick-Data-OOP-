#include "CandlestickPlot.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm> // Required for std::min_element and std::max_element

void plotCandlestickData(const std::vector<Candlestick>& candlesticks) {
    // Find global min and max for dynamic scaling
    double globalLow = 1e9, globalHigh = -1e9;
    for (const auto& candle : candlesticks) {
        globalLow = std::min(globalLow, candle.low);
        globalHigh = std::max(globalHigh, candle.high);
    }

    double scale = 50.0 / (globalHigh - globalLow); // Scale to fit 50-character width
    int plotWidth = std::max(60, static_cast<int>(candlesticks.size() * 1.2)); // Adjust width dynamically

    std::cout << "\nCandlestick Plot (L = Low, H = High, [ = Open, ] = Close):\n";
    std::cout << std::setw(10) << "Year" << std::setw(10) << "Open" << std::setw(10) << "High"
              << std::setw(10) << "Low" << std::setw(10) << "Close" << "     Plot\n";
    std::cout << std::string(plotWidth, '-') << "\n";

    for (const auto& candle : candlesticks) {
        std::cout << std::setw(10) << candle.date << std::setw(10) << std::fixed << std::setprecision(2) << candle.open
                  << std::setw(10) << candle.high << std::setw(10) << candle.low << std::setw(10) << candle.close
                  << "     ";

        // Compute scaled positions
        int lowPoint = static_cast<int>((candle.low - globalLow) * scale);
        int highPoint = static_cast<int>((candle.high - globalLow) * scale);
        int openPoint = static_cast<int>((candle.open - globalLow) * scale);
        int closePoint = static_cast<int>((candle.close - globalLow) * scale);

        // Create the plot
        std::string plot(50, ' '); // Initialize a blank plot of 50 characters

        // Place Low and High markers and vertical stalk
        for (int i = lowPoint; i <= highPoint; ++i) {
            plot[i] = '-';
        }
        plot[lowPoint] = 'L'; // Low marker
        plot[highPoint] = 'H'; // High marker

        // Place Open and Close markers without overlap
        if (openPoint <= closePoint) {
            plot[openPoint] = '['; // Open marker
            plot[closePoint] = ']'; // Close marker
        } else {
            plot[closePoint] = ']'; // Close marker
            plot[openPoint] = '['; // Open marker
        }

        std::cout << plot << "\n";

        // Add horizontal separator for readability
        std::cout << std::string(plotWidth, '-') << "\n";
    }

    // Highlight the highest and lowest candlestick
    std::cout << "\nKey Highlights:\n";
    auto minCandle = *std::min_element(candlesticks.begin(), candlesticks.end(),
                                       [](const Candlestick& a, const Candlestick& b) { return a.low < b.low; });
    auto maxCandle = *std::max_element(candlesticks.begin(), candlesticks.end(),
                                       [](const Candlestick& a, const Candlestick& b) { return a.high > b.high; });
    std::cout << "Lowest Candlestick: " << minCandle.date << " (Low = " << minCandle.low << ")\n";
    std::cout << "Highest Candlestick: " << maxCandle.date << " (High = " << maxCandle.high << ")\n";
}