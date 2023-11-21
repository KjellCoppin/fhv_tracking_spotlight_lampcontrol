# Lamp Movement API

## Setup
- **make sure the ethernetport of your machine has the right ip address**
   ```linux
   sudo ip addr flush dev eth0
   sudo ip addr add 192.168.0.1/24 dev eth0
   ```
- **install the Boost.Beast library:**
   ```linux
   sudo apt-get install g++ cmake libboost-all-dev
   ```
- **compile the server:**
   ```linux
   g++ -o http_server http_server.cpp -lboost_system -lboost_thread -lboost_date_time -lpthread
   ```
- **run the server:**
   ```linux
   ./http_server
   ```

## Endpoints
**POST /location**
- *Description*: Send coodinates for the lamp to move to.
- *Request Body (required)* : "x_location=num & y_location=num"
- *Response Body*: "Received x_location: num
                    Received y_location: num "
