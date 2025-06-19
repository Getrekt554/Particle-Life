# Particle-Life
A very simple particle life simulation made in c++

DEPENDENCIES:
Raylib(installed with vcpkg)
(if your raylib.dll + glfw.dll isnt installed at C:/vcpkg/installed/x64-windows/bin then you will have to update CMakeLists.txt accordingly)
Cmake
MinGW (or any generator, ive only tested MinGW though)

HOW TO INSTALL:
1. Download the Repository as a zip file, then unzip it.
2. Open cmd and cd into the folder where the unzipped repo is stored (EX: C:/users/yourname/particle life)
3. run this command "mkdir build" followed by "cd build"
4. open your file explorer and go to the location in which your raylib.dll and your glfw.dll files are stored (for me its C:/vcpkg/installed/x64-windows/bin)
5. copy the 2 files and paste them into the build folder we just created
6. open the terminal again and move into the build directory again run 'cmake .. -G "MinGW Makefiles"' ("cmake .. -G Ninja" for ninja)
7. then run "mingw32-make" (if you're using ninja just run "ninja")
8. run 'main'
