package main_package;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

/**
 * Main class - entry point for application, launches the server.
 */
@SpringBootApplication
public class Main {
    /**
     * Main function launching Spring Boot server.
     * @param args Command line arguments (unused)
     */
    public static void main(String[] args)
    {
        SpringApplication.run(Main.class, args);
    }
}
