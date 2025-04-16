# Crow Telemetry Service

## Overview
A minimal REST API server for collecting and analyzing simple telemetry data.  
Built with C++20, Crow (header-only) and standalone Asio.

## Features
- Store telemetry events (arrays of duration values with timestamps)  
- Compute mean path length with optional time filtering and unit conversion  
- Thread‑safe in‑memory storage using `std::shared_mutex`  
- Lightweight, modular architecture with dependency injection

## Requirements
- C++20‑capable compiler (GCC, Clang, MSVC)  
- CMake ≥ 3.14  
- Internet access (for FetchContent to download Asio and GoogleTest)

## Building & Running

```bash
mkdir build && cd build
cmake ..
cmake --build .
./crow_test       # starts server on port 18080
```

##  Running Tests

```bash
cd build
ctest --output-on-failure
# or directly:
./tests --gtest_color=yes
```

## API Endpoints

### POST /paths/{event}
- **Request**  
  - `Content-Type: application/json`  
  - Body:
    ```json
    {
      "values": [double, …], 
      "date": <unix_timestamp>
    }
    ```
- **Response**  
  - `201 Created` on success  
  - `400 Bad Request` on malformed JSON

### GET /paths/{event}/meanLength
- **Request**  
  - `Content-Type: application/json`  
  - Optional Body:
    ```json
    {
      "resultUnit": "seconds" | "milliseconds",
      "startTimestamp": <unix_timestamp>,
      "endTimestamp": <unix_timestamp>
    }
    ```
- **Response**  
  - `200 OK` + 
    ```json
    { "mean": <double> }
    ```
  - `404 Not Found` + `{"error":"no data"}` if no events in range

## Example

```bash
curl -X POST http://localhost:18080/paths/myEvent \
  -H "Content-Type: application/json" \
  -d '{
    "values": [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0],
    "date": 1680000000
  }'
```

```bash
curl -X GET http://localhost:18080/paths/myEvent/meanLength \
  -H "Content-Type: application/json" \
  -d '{
    "resultUnit": "seconds",
    "startTimestamp": 1679000000,
    "endTimestamp": 1681000000
  }'
```