#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/http/parser.hpp>
#include <string>
#include <thread>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void moveLamp(int x_value, int y_value) {
    std::cout << "Moving lamp to " << x_value << " " << y_value << std::endl;
}


void handle_request(http::request<http::string_body>& request, http::response<http::string_body>& response) {
    if (request.method() != http::verb::post) {
        response.result(http::status::bad_request);
        response.body() = "Invalid request method. Use POST.";
        response.prepare_payload();
        return;
    }

    try {
        // Parse the request body
        auto& body = request.body();
        std::string x_location, y_location;

        // Find the x_location and y_location parameters in the body
        size_t xpos = body.find("x_location=");
        size_t ypos = body.find("y_location=");

        if (xpos != std::string::npos && ypos != std::string::npos) {
            xpos += 11;  // Move past "x_location="
            ypos += 11;  // Move past "y_location="

            // Find the end of the x_location and y_location values
            size_t x_end = body.find('&', xpos);
            size_t y_end = body.find('&', ypos);

            x_location = body.substr(xpos, x_end - xpos);
            y_location = body.substr(ypos, y_end - ypos);
        } else {
            response.result(http::status::bad_request);
            response.body() = "Both x_location and y_location parameters are required.";
            response.prepare_payload();
            return;
        }

        moveLamp(std::stoi(x_location), std::stoi(y_location));
        
        // echoing them back in the response.
        response.result(http::status::ok);
        response.set(http::field::server, "My-Custom-Server");
        response.body() = "Received x_location: " + x_location + "\n";
        response.body() += "Received y_location: " + y_location;
        response.prepare_payload();
    } catch (std::exception const& e) {
        response.result(http::status::internal_server_error);
        response.body() = "Error: " + std::string(e.what());
        response.prepare_payload();
    }
}

int main() {
    net::io_context io;
    tcp::acceptor acceptor(io, {tcp::v4(), 8080});
    
    for (;;) {
        tcp::socket socket(io);
        acceptor.accept(socket);

        try {
            beast::flat_buffer buffer;
            http::request<http::string_body> request;
            http::read(socket, buffer, request);

            http::response<http::string_body> response;
            handle_request(request, response);
            http::write(socket, response);
        } catch (std::exception const& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}

