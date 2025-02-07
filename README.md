 ## Dependencies

 This project requires the SFML (Simple and Fast Multimedia Library) to be installed.

 **Instructions:**

 1.  Download the SFML library for your operating system from the official SFML website: [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)
 2.  Extract the downloaded archive to a directory of your choice (e.g., `SFML-lib` in the project root).
 3.  **For Visual Studio:**
     *   Make sure to link your project to the SFML libraries. This usually involves:
         *   Adding the SFML `include` directory to your project's include paths.
         *   Adding the SFML `lib` directory to your project's library paths.
         *   Specifying the SFML libraries to link with (e.g., `sfml-graphics.lib`, `sfml-window.lib`, `sfml-system.lib`, etc., depending on which SFML modules you use).
     *   Copy the necessary SFML `.dll` files (from the `bin` directory of the SFML distribution) to the directory where your game executable will be built (e.g., `Debug` or `Release` folders).

 Refer to the SFML documentation for more detailed instructions on setting up SFML with your development environment.
