# Lhg
A mod of Pilzschaf's simple logger.
Tested C++14, runs on Linux and Windows (mac not tested).  

## Changes over vanilla
Adds some extra functionality like using ConsoleTextAttributes for windows users, more different error levels (INFO, DEBUG, WARNING, ERROR, CRITICAL), a toggle for showing path and line before each line and a way to disable all INFO Outputs.  To show INFO outputs set lhg::verbose to true or add the 'LHG_VERBOSE' compile definition. You can display the Level of the Log with the LHG_PRINT_LVL define. The path can also be hidden with LHG_HIDE_PATH.
Also colors can be changed at runtime.  

There are also helpers for logging opbject creation and deletion, output of which, can be toggled by flipping the verbose property.
 * LOG_INIT - [YourObj] initializing...
 * LOG_DEST - destroying [YourObj]...
 * LOG_DEIN - deinitializing [YourObj]...
 * LOG_QUER - querying [Something for Something]...  

These all also have variations for success and failure.
For success add `_OK` Behind any of these 4 defines.
For Failure `_AB`.

Also these are all using LOG_ING, a macro, that lets you customize these outputs a bit further.
__Example:__
code:
```c++
LOG_ING("check", "something");
LOG_ING_OK("check", "something");
```
output:
```
checking something...
checking something... OK
```

## Linux
If you use linux, add the compile definition 'LHG_LINUX', to disable Console attibutes.

## Example
![grafik](https://user-images.githubusercontent.com/60015267/179369867-2b76f557-0fb5-4307-8048-e9e90378948f.png)
![image](https://user-images.githubusercontent.com/60015267/197496778-a99377ae-b6d6-4a72-bff7-f7d756475277.png)

