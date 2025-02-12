﻿//
// Created by Arwed on 2/12/2025.
//

#include "compare.h"

double calculate_avg_error(const std::vector<double> errorValue); {
    double avgError = 0;
    for (const auto& error : errorValue) {
        avgError += error;
    }
    return avgError / errorValue.size();
}

double calculate_avg_percent(const std::vector<double> percentValue) {
    double avgPercent = 0;
    for (const auto& percent : percentValue) {
        avgPercent += percent;
    }
    return avgPercent / percentValue.size() * 100;
}


void compare_trapez(shunting_yard& function, numeric_functions& numericFunctions, double exact) {
    double trapez = numericFunctions.calculate_trapez_rule(function);
    double trapezError = abs(trapez - exact);
    double trapezPercent = trapezError / exact * 100;
    std::cout << "Trapez: " << trapez << " Error: " << trapezError <<" Prozentual: "<< trapezPercent << std::endl;
}

void compare_simpson(shunting_yard& function, numeric_functions& numericFunctions, double exact) {
    double simpson = numericFunctions.calculate_simpson_rule(function);
    double simpsonError = abs(simpson - exact);
    double simpsonPercent = simpsonError / exact * 100;
    std::cout << "Simpson: " << simpson << " Error: " << simpsonError << "Prozentual: " << simpsonPercent << std::endl;
}
void compare_area_numeric_functions(const std::string& functionString, double lowerLimit, double upperLimit, int iterations, double exact) {
    shunting_yard function = shunting_yard(functionString);
    numeric_functions numericFunctions= numeric_functions(lowerLimit, upperLimit, iterations);
    compare_trapez(function, numericFunctions, exact);
    compare_simpson(function, numericFunctions, exact);
    std::cout << std::endl;
}

std::vector<double> compare_euler(shunting_yard& function, numeric_functions& numericFunctions, double startValue, std::vector<double> xValues, std::vector<double> exactValues, double stepLength) {
    std::vector<double> eulerValues = numericFunctions.calculate_euler_rule(function, stepLength, startValue, xValues);
    std::vector<double> errorValues;
    std::vector<double> percentValues;
    for (int i = 0; i < eulerValues.size(); i++) {
        errorValues[i] = abs(eulerValues[i]-exactValues[i]);
        percentValues[i] = errorValues[i]/exactValues[i] * 100;
        std::cout << "Euler y"<< i << " = " << eulerValues[i] << std::endl;
        std::cout << "Exact y"<< i << " = " << exactValues[i] << std::endl;
        std::cout << "Error: " << errorValues[i] << std::endl;
        std::cout << "Percent:" << percentValues[i] << std::endl;
        std::cout << std::endl;
    }
    std::vector<double> returnValues;
    returnValues.push_back(calculate_avg_error(errorValues));
    returnValues.push_back(calculate_avg_percent(percentValues));
    return returnValues;
}

std::vector<double> compare_mid_point(shunting_yard &function, numeric_functions &numericFunctions, double startValue, std::vector<double> xValues, std::vector<double> exactValues, double stepLength) {
    std::vector<double> midPointValues = numericFunctions.calculate_mid_point_rule(function, stepLength, startValue, xValues);
    std::vector<double> errorValues;
    std::vector<double> percentValues;
    for (int i = 0; i < midPointValues.size(); i++) {
        errorValues[i] = abs(midPointValues[i]-exactValues[i]);
        percentValues[i] = errorValues[i]/exactValues[i] * 100;
        std::cout << "MidPoint y"<< i << " = " << midPointValues[i] << std::endl;
        std::cout << "Exact y"<< i << " = " << exactValues[i] << std::endl;
        std::cout << "Error: " << errorValues[i] << std::endl;
        std::cout << "Percent:" << percentValues[i] << std::endl;
        std::cout << std::endl;
    }
    std::vector<double> returnValues;
    returnValues.push_back(calculate_avg_error(errorValues));
    returnValues.push_back(calculate_avg_percent(percentValues));
    return returnValues;
}

std::vector<double> compare_runge_kutta_4th_order(shunting_yard &function, numeric_functions &numericFunctions, double startValue, std::vector<double> xValues, std::vector<double> exactValues, double stepLength) {
    std::vector<double> rungeValues = numericFunctions.calculate_runge_kutta_4th_order(function, stepLength, startValue, xValues);
    std::vector<double> errorValues;
    std::vector<double> percentValues;
    for (int i = 0; i < rungeValues.size(); i++) {
        errorValues[i] = abs(rungeValues[i]-exactValues[i]);
        percentValues[i] = errorValues[i]/exactValues[i] * 100;
        std::cout << "Runge Kutta y"<< i << " = " << rungeValues[i] << std::endl;
        std::cout << "Exact y"<< i << " = " << exactValues[i] << std::endl;
        std::cout << "Error: " << errorValues[i] << std::endl;
        std::cout << "Percent:" << percentValues[i] << std::endl;
        std::cout << std::endl;
    }
    std::vector<double> returnValues;
    returnValues.push_back(calculate_avg_error(errorValues));
    returnValues.push_back(calculate_avg_percent(percentValues));
    return returnValues;
}


void compare_diff_numeric_functions(const std::string& functionString, const std::string& differentialFunction,
    double lowerLimit, double upperLimit, int iterations, double startValue, double stepLength) {
    shunting_yard function = shunting_yard(functionString);
    shunting_yard diffFunction = shunting_yard(differentialFunction);
    numeric_functions numericFunctions = numeric_functions(lowerLimit, upperLimit, iterations);
    std::vector<double> xValues = numericFunctions.calculate_x_values(stepLength);
    std::vector<double> exactValues;
    for (const auto& x : xValues) {
        exactValues.push_back(diffFunction.calculate(x, 0));
    }
    std::vector<double> eulerResult = compare_euler(function, numericFunctions, startValue, xValues, exactValues, stepLength);
    std::vector<double> midPointResult = compare_mid_point(function, numericFunctions, startValue, xValues, exactValues, stepLength);
    std::vector<double> rungeResult = compare_runge_kutta_4th_order(function, numericFunctions, startValue, xValues, exactValues, stepLength);
}

