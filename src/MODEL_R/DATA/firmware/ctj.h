#pragma once

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "constants.h"
#include "classes.h"

// Set the maximum number of columns in the CSV string
const int MAX_COLUMNS = 256;

// Set the maximum length of each column
const int MAX_COLUMN_LENGTH = 5;

// Set the size of the JSON buffer
const int JSON_BUFFER_SIZE = JSON_OBJECT_SIZE(MAX_COLUMNS);

int splitString(const String& inputString, char separator, String outputArray[], int maxColumns) {
  char charArray[inputString.length() + 1];
  inputString.toCharArray(charArray, sizeof(charArray));

  char* token = strtok(charArray, &separator);
  int arrayIndex = 0;
  while (token != nullptr && arrayIndex < maxColumns) {
    outputArray[arrayIndex++] = String(token);
    token = strtok(nullptr, &separator);
  }
  return arrayIndex;
}

String processCSVData(const String& csvData) {
  // Create a JSON buffer
  DynamicJsonDocument jsonBuffer(JSON_BUFFER_SIZE);

  // Create a JSON array to hold the CSV data
  JsonArray jsonArray = jsonBuffer.to<JsonArray>();

  // Split the CSV data into rows
  String rows[MAX_COLUMNS];
  int numRows = sizeof(rows) / sizeof(rows[0]) - 1;

  // Extract column names from the first row
  String columnNames[MAX_COLUMNS];
  int numColumns = splitString(rows[0], ',', columnNames, MAX_COLUMNS);

  // Process each row starting from the second row
  for (int i = 1; i < numRows; i++) {
    // Split the row into columns
    String columns[MAX_COLUMNS];
    char* token = strtok(rows[i].c_str(), ",");
    int numColumns = 0;
    while (token != nullptr) {
      columns[numColumns++] = token;
      token = strtok(nullptr, ",");
    }

    // Create a JSON object for each row
    JsonObject jsonObject = jsonBuffer.createNestedObject();

    // Add the columns to the JSON object
    for (int j = 0; j < numColumns; j++) {
      jsonObject[columnNames[j]] = columns[j];
    }

    // Add the JSON object to the JSON array
    jsonArray.add(jsonObject);
  }

  // Serialize the JSON data to a string
  String jsonString;
  serializeJson(jsonArray, jsonString);

  // Print the JSON string
  return (jsonString);
}

int splitString(String inputString, char separator, String outputArray[]) {
  int arrayIndex = 0;
  int stringIndex = 0;

  while (stringIndex < inputString.length()) {
    int separatorIndex = inputString.indexOf(separator, stringIndex);

    if (separatorIndex == -1) {
      separatorIndex = inputString.length();
    }

    outputArray[arrayIndex] = inputString.substring(stringIndex, separatorIndex);
    stringIndex = separatorIndex + 1;
    arrayIndex++;
  }

  return arrayIndex;
}
