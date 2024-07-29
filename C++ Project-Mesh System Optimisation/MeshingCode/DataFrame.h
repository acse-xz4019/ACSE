//
// Created by Zhang, Xiaoye on 13/03/2024.
//

#ifndef ADVANCED_PROGRAMMING_ASSESSMENT_2_ACSE_XZ4019_DATAFRAME_H
#define ADVANCED_PROGRAMMING_ASSESSMENT_2_ACSE_XZ4019_DATAFRAME_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct DataFrame {
    std::vector<std::string> column_names; // store column names
    std::vector<std::vector<double>> data; // use a 2D vector to store data

    // read data from a CSV file
    std::vector<std::vector<double>> readCSV(const std::string& filename, char delimiter = ',', bool hasColumnNames = true) {
        std::ifstream file(filename);
        std::string line;

        if (!hasColumnNames) {
            // read data directly
            while (getline(file, line)) {
                std::vector<double> row;
                std::istringstream sstream(line);
                std::string cell;
                while (getline(sstream, cell, ',')) {
                    double value = std::stod(cell); // convert string to double
                    row.push_back(value); // add the value to the row
                }
                data.push_back(row);
            }
        } else {
            // read column names
            if (getline(file, line)) {
                std::istringstream sstream(line);
                std::string cell;
                while (getline(sstream, cell, ',')) {
                    column_names.push_back(cell); // add the column name to the vector
                }
            }

            // read data
            while (getline(file, line)) {
                std::vector<double> row;
                std::istringstream sstream(line);
                std::string cell;
                while (getline(sstream, cell, ',')) {
                    double value = std::stod(cell); // convert string to double
                    row.push_back(value); // add the value to the row
                }
                data.push_back(row); // add the row to the data
            }
        }
        return data;
    }

    // display the data
    void display() const {
        for (const auto& name : column_names) {
            std::cout << name << "\t";
        }
        std::cout << std::endl;
        for (const auto& row : data) {
            for (const auto& cell : row) {
                std::cout << cell << "\t";
            }
            std::cout << std::endl;
        }
    }
};
#endif //ADVANCED_PROGRAMMING_ASSESSMENT_2_ACSE_XZ4019_DATAFRAME_H
