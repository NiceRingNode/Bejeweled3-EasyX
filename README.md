# Bejeweled3-EasyX
A rough application mocking classic game Bejeweled3 using C++ and Easyx
## This is a visual studio project, which was written and run using VS2019.
First you should install Easyx, a highly encapsulated graphics library. See more about this library [here](https://easyx.cn/).
Then double click file **Bejeweled3.sln**(recommended using VS2019 to open it). Set the C++ standard to C++14(or higher).
Then just click the **build** option and the game will be successfully run.
## Notice that this can only be run on Windows, for it uses some library that uniquely belong to Windows.
The master logic is in the file ***bejewled_board.hpp***, some algorithms are used such as BFS in the game, yet some functions are not implemented.
The game can play music and adjust volume, which is implemented using MCI apis.
