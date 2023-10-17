# Lamp Movement API

## Setup
- **install the Boost.Beast library:** "sudo apt-get install g++ cmake libboost-all-dev"
- **compile the server:** "g++ -o http_server http_server.cpp -lboost_system -lboost_thread -lboost_date_time -lpthread"

## Endpoints
**POST /location**
- *Description*: Send coodinates for the lamp to move to.
- *Request Body (required)* : "x_location=num & y_location=num"
- *Response Body*: "Received x_location: num
                    Received y_location: num "
