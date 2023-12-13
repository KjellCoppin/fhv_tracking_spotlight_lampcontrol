# Lamp Movement API

## Setup
### Setup MH-X25 Lamp
- **Set lamp into slave mode**
  ```
  press mode untill you see "NASL" ->
  press enter ->
  press up untill you see "SLAv" ->
  press enter
  ```
### Hardware connections
- **Enttecc opendmx ethernet** <br>
  -> Connect to the lamp with a XLR 5-pin male to XLR 3-pin female cable <br>
  -> Connect to the linux machine with an ethernet cable
### Run project on linux machine
- **make sure the ethernetport of your machine has the right ip address**
   ```linux
   sudo ip addr flush dev eth0
   ```
   ```linux
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
