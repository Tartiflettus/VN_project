# VN_project
A VN project. Mostly for fun
The scenario format is a text file, that allows anyone to edit it as he wants.
Because our lives are difficult, a scenario editor is available, but perhaps difficult to handle currently.


Current state of the project:
- Compiles without problem on windows platform, but doesn't work at all. A use of gdb tells us that the program is starting, but no other messages are displayed.
- todo : background handlers, save functions, route choices.


HOW TO USE THIS SOFTWARE:

Simply run the program to access the game mode. Use space or enter to go to the next scene, until there isn't any left.


Run the program with the option "edit" to run the edit mode.
Currently, 4 parameters are editable:
- Characters
- Text
- Voice
- Music

To switch between modes, use the numpad keys 1 -> 4.

Character edit mode: left and right arrow keys to select another slot to place your character.
	Then press up to select a file. Enter it in the window and press "enter".
	Going to the left if there is no more slot will suppress the last slot.
	Going to the right if there is no ore slot will add a slot.

Text edit mode: simply enter your text

Voice edit mode: select a file just like for the characters.

Music edit mode: select a file just like for the characters.

To switch between editors, use - / +.

When you're done, press escape and enter a fileName.

