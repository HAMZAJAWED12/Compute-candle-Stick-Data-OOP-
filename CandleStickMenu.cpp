#include "CandlestickMenu.h"
#include <iostream>

using namespace std;

CandlestickMenu::CandlestickMenu(const std::string& filename) {
    candlesticks = computeCandlestickData(filename, "GB_temperature");
}

void CandlestickMenu::init() {
    int userOption = 0;
    do {
        printMenu();
        cin >> userOption;
        processUserOption(userOption);
    } while (userOption != 0);
}

void CandlestickMenu::printMenu() {
    cout << "\nCandlestick Management Menu\n";
    cout << "1. View All Candlesticks\n";
    cout << "2. Plot Candlestick Data\n";
    cout << "3. Filter by Temperature Range\n";
    cout << "4. Predict Future Temperature Trends\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void CandlestickMenu::processUserOption(int userOption) {
    switch (userOption) {
        case 1:
            viewAllCandlesticks();
            break;
        case 2:
            plotCandlestickData(candlesticks); // Task 2
            break;
        case 3:
            filterByTemperatureRange();
            break;
        case 4:
            predictFutureTrends();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
    }
}

void CandlestickMenu::viewAllCandlesticks() {
    cout << "\nAll Candlesticks:\n";
    for (const auto& candle : candlesticks) {
        candle.print();
    }
}

void CandlestickMenu::filterByTemperatureRange() {
    double minTemp, maxTemp;
    cout << "Enter minimum temperature: ";
    cin >> minTemp;
    cout << "Enter maximum temperature: ";
    cin >> maxTemp;

    // Use the global function `filterByTemperatureRange` instead of the class member function
    auto filtered = ::filterByTemperatureRange(candlesticks, minTemp, maxTemp);

    if (filtered.empty()) {
        cout << "No candlesticks found in the given range.\n";
    } else {
        cout << "\nFiltered Candlesticks:\n";
        for (const auto& candle : filtered) {
            candle.print();
        }
          // Plot the filtered data
        plotCandlestickData(filtered);
    }
}

void CandlestickMenu::predictFutureTrends() {
    int futureYears;
    cout << "Enter number of future years to predict: ";
    cin >> futureYears;

    auto futureCandlesticks = predictFutureData(candlesticks, futureYears);

    cout << "\nPredicted Candlestick Data:\n";
    for (const auto& pred : futureCandlesticks) {
        pred.print();
    }
      // Plot the predicted data
    plotCandlestickData(futureCandlesticks);
}
