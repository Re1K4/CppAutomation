# Name 
CppAutomation

## Overview
C++ template for automation with OpenCV library. 
It is very fast and can automate most operations.

## Requirement
OpenCV - [OpenCV Releases](https://opencv.org/releases/)

Interception - [Interception](https://github.com/oblitum/Interception)

## Usage
This is a template, and the process must be written and built in the while loop in main.cpp according to the process you wish to automate.
The initial main.cpp contains test code for each function.

## Build setup using Visual Studio

### OpenCV configuration

1. **Install OpenCV:**  
   Download and install [OpenCV](https://opencv.org/releases/) (for Windows).

2. **Configure Visual Studio:**  
   - Open your project in Visual Studio.
   - Go to **Project > Properties > C/C++ > General**.
     - **Additional Include Directories:** Add the path to your `opencv\build\include` folder.
      ```
      C:\Program Files\opencv\build\x64\vc16\bin
      ```
   - Go to **Linker > General**.
     - **Additional library directory:** Add the path to your `opencv\build\x64\vcXX\lib` folder (replace `vcXX` with your Visual Studio version, e.g., `vc16`).
      ```
      C:\Program Files\opencv\build\x64\vc16\lib
      ```
   - Go to **Linker > Input**.
     - **Additional dependency file:** 
        - For Debug build:
        ```
        opencv_world4100d.lib
        ```
        - For Release build:
        ```
        opencv_world4100.lib
        ```   

3. **Setting OS Path environment variables:**  
   - Add the path to your `opencv\build\x64\vcXX\bin` folder (replace `vcXX` with your Visual Studio version, e.g., `vc16`).
    ```
    C:\Program Files\opencv\build\x64\vc16\bin
    ```

### Building with Interception Driver

To use keyboard and mouse emulation via interception.

1. **Install Interception:**  
   - Download and install [Interception](https://github.com/oblitum/Interception).

2. **Configure Visual Studio:**  
   - Open your project in Visual Studio.
   - Go to **Project > Properties > C/C++ > General**.
     - **Additional Include Directories:** Add the path to your `Interception\library` folder.
      ```
      C:\Interception\library
      ```
   - Go to **Linker > General**.
     - **Additional library directory:** Add the path to your `Interception\library\x64` folder.
      ```
      C:\Interception\library\x64
      ```
   - Go to **Linker > Input**.
     - **Additional dependency file:** add `interception.lib`.

3. **Add DLLs to your project:**  
   - From the DLL file properties, go to “General > Item Type >” and select “Copy File”.

### If build errors occur, please also set the following additional dependencies

**Linker > Input**

- **Additional dependency file**  
  ```
  Gdi32.lib
  ```

## Author
[![Twitter: ReekerZrZr](https://img.shields.io/twitter/follow/ReekerZrZr?style=social)](https://x.com/ReekerZrZr)

## Licence
[MIT](https://opensource.org/licenses/mit-license.php)