<pre>
  ________            __  ___        _               ____  ____ _____
 /_  __/ /_  ___     /  |/  /___ _  (_)___  _____   / __ )/ __ ) ___/
  / / / __ \/ _ \   / /|_/ / __ `/ / / __ \/ ___/  / __  / __  \__ \
 / / / / / /  __/  / /  / / /_/ / / / /_/ / /     / /_/ / /_/ /__/ /
/_/ /_/ /_/\___/  /_/  /_/\__,_/_/ /\____/_/     /_____/_____/____/
                              /___/

             __  ___        __     __      _______  __ __ 
            /  |/  /__  ___/ /_ __/ /__   / __/ _ \/ //_/
           / /|_/ / _ \/ _  / // / / -_) _\ \/ // / ,<
          /_/  /_/\___/\_,_/\_,_/_/\__/ /___/____/_/|_|
</pre>

Welcome to the Module SDK project for The Major BBS V10. This project can be placed wherever you put your Visual Studio repositories.

Open Visual Studio for Windows (as of this writing, Visual Studio 2022 is the latest that is worked with), and load the MBBS-v10-module-SDK.sln Solution.

Ensure that your Visual Studio is set to x86, not x64!  You should be able then to open src in the solution explorer and Build the V10MOD project.

If Visual Studio is in Debug mode, it will create the V10MOD.dll in the Debug/ folder off the solution root. If you switch it to Release, it will place it in Release/.

To test the module on your Major BBS V10 system:
 - copy the DLL and the files in the V10MOD/Dist folder
 - run the Menu Tree Editor and add MBBS V10 Example Module to your menu
 - start up the system and enter the module

You can use this SDK as a baseline and example to write your own modules. 

Contact us on Discord and let us know how you're doing, or ask questions, in the #development channel.
Our Major BBS Discord is at https://discord.gg/u5qM24gX

Have fun!

Notes:

- The Developers guide can be found in the Doc folder.  This is an excellent guide on the components of MBBS and includes important details such as the architecture, routines, functions, variables and databases that make up the MBBS system and modules. Read it!
- Only the init__modname routine has to be EXPORT, but EXPORT on all the functions will help you parse GALEXCEP.OUT reports on crashes.
- init__modname has to match the module's filename - if the module changed from v10mod to mynewmod, the init would be VOID EXPORT init__mynewmod(VOID)

Finally - thanks to @elwynor and @pheller for their assistance in putting this project together!
