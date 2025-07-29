import os
import platform

# Download and compile raylib if not done yet.
if not os.path.isfile("raylib/src/libraylib.a"):
    os.system("git clone --depth 1 https://github.com/raysan5/raylib.git && cd raylib/src && make")

def build_mac():
    # Build and run the game.
    build = " ".join([
        "g++ main.cpp -std=c++20 -Wall -o main",
        "-Iraylib/src -Lraylib/src raylib/src/libraylib.a",
        "-framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL",
    ])
    os.system(build)
    os.system("./main")
    os.remove("./main")

def build_win():
    # Build and run the game.
    build = " ".join([
        "g++ main.cpp -std=c++20 -Wall -o main.exe",
        "-Iraylib/src -Lraylib/src raylib/src/libraylib.a",
        "-lraylib -lgdi32 -lwinmm",
    ])
    os.system(build)
    os.system("main.exe")
    os.remove("main.exe")

# python build.py
if platform.system() == "Windows":
    build_win()
else:
    build_mac()
