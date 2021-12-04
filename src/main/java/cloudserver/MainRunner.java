/**
 * @file MainRunner.java
 * @author Andrii Dovbush
 * @brief Main runner class for the server
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Main runner class for server.
 */

package cloudserver;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;

@SpringBootApplication
public class MainRunner extends SpringBootServletInitializer {

    public static void main(String[] args) {
        SpringApplication.run(MainRunner.class, args);
    }

}
