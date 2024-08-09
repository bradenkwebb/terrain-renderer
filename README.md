# Terrain Renderer

## Set-up
To build and run this program on Windows, the following tools should be available:

```
gcc --version
g++ --version
gdb --version
```
In order to use the C/C++ debugger on VS Code, I also make sure to open the directory by running the
Developer Command Prompt for VS, navigating to the directory, and running `code .` from within the directory.

### Dependencies
**assimp**

Download and compile the `assimp` library as described [here](https://github.com/assimp/assimp/blob/master/Build.md). I
recommend building it from source. By default this builds a dynamically linked library, so be sure to copy the `.dll`
file to the `lib` directory and the generated `assimp/include/assimp` folder into your `assimp` directory.



I followed [this video](https://www.youtube.com/watch?v=hRInLNR9iRg) to get my setup to actually work.