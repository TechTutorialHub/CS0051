import java.io.*;
import java.net.*;

public class Server {
    public static void main(String[] args) {
        int port = 6789; // Port number where the server will listen

        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);

            while (true) {
                // Wait for a client to connect
                Socket socket = serverSocket.accept();
                System.out.println("New client connected");

                // Handle communication with the client
                new ClientHandler(socket).start();
            }
        } catch (IOException ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}

// Thread to handle each client connection
class ClientHandler extends Thread {
    private Socket socket;

    public ClientHandler(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        try (
            InputStream input = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true)
        ) {
            String text;
            // Continuous communication loop
            while ((text = reader.readLine()) != null) {
                System.out.println("Client says: " + text);

                if (text.equalsIgnoreCase("bye")) {
                    writer.println("Goodbye! Ending the conversation.");
                    break; // End the conversation if the client says "bye"
                }

                // Prompt server operator for a response
                System.out.print("Enter your response to the client: ");
                BufferedReader consoleInput = new BufferedReader(new InputStreamReader(System.in));
                String serverResponse = consoleInput.readLine();

                // Send the server's response to the client
                writer.println("Server says: " + serverResponse);
            }
        } catch (IOException ex) {
            System.out.println("Client handler exception: " + ex.getMessage());
            ex.printStackTrace();
        } finally {
            try {
                socket.close();
                System.out.println("Client disconnected");
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }
}
