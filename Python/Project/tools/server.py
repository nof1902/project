import http.server
import socketserver

# Define the server configuration
host = 'localhost'
port = 8000

# Create a request handler class
class RequestHandler(http.server.SimpleHTTPRequestHandler):
    # Override the do_GET method to handle GET requests
    def GET(self):
        # Send a response header
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        # Send the response content
        #message = "Hello World!"
        #self.wfile.write(message.encode())
        self.wfile.write(self.path[1:].encode()) #print what the client writes


def main():
    # Create a server instance
    server = socketserver.TCPServer((host, port), RequestHandler)

    # Start the server
    print(f"Server running on {host}:{port}")
    server.serve_forever()


if __name__ == '__main__':
    main()