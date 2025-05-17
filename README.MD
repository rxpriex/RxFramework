# RxFramework

## Overview
RxFramework is a lightweight C++ framework for building 2D graphical applications using SDL2. It provides a component-based architecture for rendering and managing UI elements, such as labels and sprites, within a windowed frame. The framework supports event handling, collision detection, and basic movement mechanics, making it suitable for simple games or interactive applications.

## Features
- **Component-Based Architecture**: Create reusable components like `RxLabel` for text and `DrawableSprite` for rectangles.
- **Event Handling**: Supports keyboard input and window events via SDL2.
- **Rendering**: Uses SDL2 for hardware-accelerated rendering.
- **Collision Detection**: Built-in support for detecting component collisions.
- **Threading**: Optional detached graphics thread for rendering.
- **Customizable Frame Rate**: Set target FPS for smooth rendering.

## Dependencies
- **SDL2**: For rendering and event handling.
- **SDL2_ttf**: For rendering text (used in `RxLabel`).
- **C++17 or later**: For modern C++ features like `std::shared_ptr`.

## Installation
1. **Install SDL2 and SDL2_ttf**:
   - On Ubuntu:
     ```bash
     sudo apt-get install libsdl2-dev libsdl2-ttf-dev
     ```
   - On macOS (using Homebrew):
     ```bash
     brew install sdl2 sdl2_ttf
     ```
   - On Windows, download development libraries from [SDL2](https://www.libsdl.org/) and [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/).

2. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd RxFramework
   ```

3. **Build the Project**:
   Use cmake to build and install the project
   ```bash
   cmake --build . && cmake --install .
   ```

3. **Include the library**:
   Use cmake to include the library in your project using
   ```cmake
   find_package(SDL_Graph REQUIRED)
   ``` 

## Usage
1. **Create a Frame**:
   ```cpp
   RxFrame frame(800, 600, 60); // 800x600 window, 60 FPS
   frame.initFrame(WAIT_ON_FRAME);
   ```

2. **Add Components**:
   ```cpp
   RxLabel* label = new RxLabel("Hello, World!");
   label->setLocation(100, 100);
   frame.addComponent(label);

   DrawableSprite* sprite = new DrawableSprite(200, 200, 50, 50);
   sprite->setMovementParameters(5, 0); // Move right
   frame.addComponent(sprite);
   ```

3. **Set Event Handlers**:
   ```cpp
   frame.setKeyListener([](SDL_Event event) {
       if (event.key.keysym.sym == SDLK_ESCAPE) {
           exit(0);
       }
   });

   frame.setOnUpdate([]() {
       // Update logic here
   });
   ```

4. **Run the Application**:
   Ensure a font file (e.g., `arial.ttf`) is available for `RxLabel`. Run the compiled binary:
   ```bash
   ./app
   ```

## Project Structure
- **include/**: Header files for the framework.
- **src/**: Source files implementing the framework.
- **RxComponent**: Base class for all components.
- **RxLabel**: Component for rendering text.
- **DrawableSprite**: Component for rendering colored rectangles.
- **RxFrame**: Manages the window and rendering loop.

## Contributing
Contributions are welcome! Please submit pull requests or open issues on the repository.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
