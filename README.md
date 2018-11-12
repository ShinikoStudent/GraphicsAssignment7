# GraphicsAssignment7
Class assignment for Graphics

# Dealing with Directories and Libraries
Make sure to leave the files/paths for each respective computer user to reach glew/sd/glm folders. It will not interfere with one another, its ok if its a long list. The files for Debug do not have to be reinserted. 

DOUBLE CHECK PATHS, SOME REQUIRE A WHOLE FOLDER OTHERS GO VERY FAR IN DEPTH THROUGH THE FILE IN TERMS OF PATHS.


## Pulling from Github
When I first pulled I had to set up my VS to work with the code, such as targeting the right files.

Just a warning, when I first opened up "Properties" look at the top where it says:

"
**Configuration: Active(Debug)** 


**Platform: Win32**


**Config Man Button**
"

Make sure it says what I just put and then make your changes. What happened on my computer was that it was set to "x64" for some reason and it gave me a lot of problems. **SO MAKE SURE IT SAYS YOU ARE USING Win32!!!**


## Getting Sound to Work
Download the Developement Libraries for Visual C++ here:


https://www.libsdl.org/projects/SDL_mixer/

Open up Visual Studio and right click on your project folder -> Properties -> VC++ Directories -> Add in Library Directory and Include Directory from the SDL_mixer folder. (for the Library Directory choose the "x86" file)

For the .dll files go to your file explorer and into where the SDL_Mixer folder lives in -> lib -> x86 -> copy the file "SDL2_mixer.dll" -> paste this file into this project's Debug folder with the other .dll files. (Make sure you put it in the right Debug!)

All of this should be similar to how you did the GLEW and SDL stuff.

Once again go back to your VS properties -> Linker -> Command Line and copy/paste this inside:

"opengl32.lib glu32.lib glew32s.lib SDL2main.lib SDL2.lib SDL2_mixer.lib" (Without the quotes)

So you are including the library.


Music should work now! :D
