import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) {
        String hostname = "localhost"; // Server's hostname or IP address
        int port = 6789; // Port number where the server is listening

        try (Socket socket = new Socket(hostname, port)) {
            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);

            InputStream input = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));

            BufferedReader consoleInput = new BufferedReader(new InputStreamReader(System.in));

            String userInput;
            String serverResponse;

            // Continuous communication loop
            while (true) {
                // Prompt user for input
                System.out.print("Enter your message to the server (type 'bye' to exit): ");
                userInput = consoleInput.readLine();

                // Send the message to the server
                writer.println(userInput);

                // Break the loop if the user types "bye"
                if (userInput.equalsIgnoreCase("bye")) {
                    break;
                }

                // Read the server's response
                serverResponse = reader.readLine();
                System.out.println(serverResponse);
            }

            // Close resources
            System.out.println("Closing connection...");
        } catch (UnknownHostException ex) {
            System.out.println("Server not found: " + ex.getMessage());
        } catch (IOException ex) {
            System.out.println("I/O error: " + ex.getMessage());
        }
    }
}
