# Chickenkiller

Chickenkiller will be a game made by the 2DAsylumEngine inspired by [TheCherno's Hazel Engine](https://www.youtube.com/user/TheChernoProject).

### Getting Started

- Get the code:
	- `git clone --recursive https://github.com/NullJupiter/Chickenkiller`

#### Windows:

- `cd` into the project directory and run the `GenerateProjectFiles.bat` file. There will be a Visual Studio project generated for you.

#### MacOS:

- `cd` into the project directory and run the `GenerateProjectFiles.sh` file. If this doesn't work try creating the correct privileges with `chmod +x GenerateProjectFiles.sh`.
- You need to tweak the Xcode Workspace a bit to compile correctly. First go to `Product > Scheme > Edit Scheme > Options` and set the working directory to the `Chickenkiller` Project folder. (Not the workspace folder!)
- The last tweak would be to set the C++ Standard to C++17 or higher. Go to the project Settings. Then go to `Build Settings` and search for the term `C++ Language Dialect`. There you may change the value to `C++17` or above. Do this for both projects. (Chickenkiller and Asylum-Editor)

Now you are ready to go!
