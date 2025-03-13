#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

std::vector<std::vector<std::string>> CSVReader::readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);  // Push each cell into the current row
        }

        data.push_back(row);  // Push the completed row into the data vector
    }

    return data;
}
