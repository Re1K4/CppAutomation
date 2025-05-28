# CppGameBot

Template for a fast gamebot program in C++ using OpenCV library.


## Visual Studio Setup

### Building with OpenCV Library

To build this project with OpenCV support, follow these steps:

1. **Install OpenCV:**  
   Download and install the pre-built OpenCV binaries for Windows, or build from source as needed.  
   [OpenCV Releases](https://opencv.org/releases/)

2. **Configure Include and Library Directories in Visual Studio:**  
   - Open your project in Visual Studio.
   - Go to **Project > Properties > VC++ Directories**.
     - **Include Directories:** Add the path to your `opencv\build\include` folder.
     - **Library Directories:** Add the path to your `opencv\build\x64\vcXX\lib` folder (replace `vcXX` with your Visual Studio version, e.g., `vc16`).
   - In **Linker > Input > Additional Dependencies**, add the required OpenCV `.lib` files (e.g., `opencv_worldXXX.lib`).

3. **Add OpenCV DLLs to Path:**  
   - Ensure the required OpenCV DLLs (e.g., `opencv_worldXXX.dll`) are available in your system `PATH` or next to your `.exe` at runtime.

### Example Configuration for OpenCV

**OS Environment Variables**

- `Path`  
  Add the following path to your system environment variables:  
  ```
  C:\Program Files\opencv\build\x64\vc16\bin
  ```

**C/C++ Configuration**

- **General > Additional Include Directories**
  ```
  C:\Program Files\opencv\build\include
  ```

**Linker Configuration**

- **General > Additional Library Directories**
  ```
  C:\Program Files\opencv\build\x64\vc16\lib
  ```
- **Input > Additional Dependencies**  
  For Debug build:
  ```
  opencv_world4100d.lib
  Gdi32.lib
  ```
  For Release build:
  ```
  opencv_world4100.lib
  Gdi32.lib
  ```

### Building with Interception Driver

To use keyboard and mouse emulation via Interception:

1. **Download Interception SDK:**  
   - Get the [Interception SDK](https://github.com/oblitum/Interception) and extract it.

2. **Include SDK in Your Project:**  
   - Add the path to the Interception SDK `include` directory to your project’s **Include Directories**.
   - Add the path to the Interception SDK `library` directory to your **Library Directories**.
   - In **Linker > Input > Additional Dependencies**, add `interception.lib`.

3. **Driver Installation:**  
   - The Interception driver must be installed on your system for runtime use.  
   - Use the official installer from the [Interception GitHub Releases](https://github.com/oblitum/Interception/releases).

4. **Administrator Privileges:**  
   - Running and installing the Interception driver requires administrator privileges.

### Example Configuration for Interception Driver

**C/C++ Configuration**

- **Additional Include Directories**
  ```
  C:\Interception\library
  ```

**Linker Configuration**

- **Additional Library Directories**
  ```
  C:\Interception\library\x64
  ```
- **Input > Additional Dependencies**
  ```
  interception.lib
  ```

**Adding the DLL to the Project**

- Add the Interception DLL to your project.  
  In Visual Studio, right-click the DLL in Solution Explorer, select **Properties > General > Item Type**, and choose `"Copy if newer"` (or `"Copy"` depending on your Visual Studio version) to ensure the DLL is copied to your output directory on build.

## Author
[![Twitter: ReekerZrZr](https://img.shields.io/twitter/follow/ReekerZrZr?style=social)](https://x.com/ReekerZrZr)