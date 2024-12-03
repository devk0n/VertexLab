# VertexLab

## Overview

VertexLab is a C++ application designed to demonstrate real-time rendering techniques using modern OpenGL. It showcases a simple graphics engine that manages rendering through the use of GLFW, GLEW, and the integration of ImGui for a user-friendly interface.

### Features

- **OpenGL Rendering**: Utilize OpenGL for rendering 3D graphics with support for customizable shaders and camera manipulation.
- **Real-time Performance Monitoring**: Displays FPS and frame time for real-time performance tracking.
- **ImGui Integration**: Provides an interactive graphical user interface enabling user interaction with various rendering settings.
- **Customizable Grid**: Render a dynamic 3D grid to demonstrate basic rendering capabilities.

## Getting Started

### Prerequisites

- **CMake**: Ensure CMake is installed for project configuration.
- **GLFW**: Necessary for creating windows and handling input.
- **GLEW**: Required to manage and load OpenGL extensions.
- **OpenGL**: Make sure an appropriate version of OpenGL is supported by your graphics drivers.
- **GLM**: Used for math operations, particularly for matrix transformations.

### Building the Project

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/devk0n/VertexLab.git
   cd VertexLab
   ```

2. **Configure and Build**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the Application**:
   ```bash
   ./VertexLab
   ```

### Project Structure

- **main.cpp**: Contains the primary application loop and initializes the graphics context.
- **camera.h**: Defines the camera for managing view transformations.
- **utils.h**: Utility functions for initialization and setup.
- **drawing_utils.h**: Contains functions to manage rendering logic.
- **imgui_manager.h**: Handles the setup and rendering of ImGui interfaces.

## Usage

- **Camera Controls**: Navigate the 3D scene using keyboard inputs.
- **FPS Display**: Monitor the application's rendering performance through the FPS and frame time display.
- **ImGui Widgets**: Interact with additional settings and configurations through the ImGui interface.

## Troubleshooting

- Ensure all dependencies are correctly installed and accessible.
- Verify your environment's compatibility with OpenGL.
- Check for error messages and consult logs for more details.

## Contributing

Contributions are welcome! Feel free to submit issues and pull requests to improve VertexLab.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by various real-time rendering tutorials and resources.
- Thanks to the developers of GLFW, GLEW, GLM, and ImGui for their incredible libraries.
