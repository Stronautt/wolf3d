# Wolf3D

Represantation of old Wolfenstein3D (1992). Project fully written in C. Myself I had added some interestion feateres like:
 - Console
 - MLG Effect if you pick Doritos chips package
 - High resolution textures
 - Simple map managment

Truly, it's simply engine on which you can build own game, you can replace textures files and rebuild levels with text editor.
Also, you can replace music files with your own soundtracks.

You can add some new high resolution sprites to make enemies more horrible and detailed.
All resources you can find in `resources` folder.

### Controls:
 - WASD - Movement
 - [hold] LSHIFT - Sprint
 - SPACE - Shoot
 - ENTER - Open Command Line
 - TAB - Enter Full Screen Mode
 - ESC - EXIT
 
##### Avalible commands:
 - raisethesun - Heals you
 - godmode - Gives you immortality
 - goto [level_number] - Sends you to choosen level
 - displaymap - Shows map of the level
 - exit - EXIT

### Map Format:
<pre>
[height] [width]
[player_position_x] [player_position_y]
[cell] ... [cell]
 ....  ...  ....
[cell] ... [cell]
</pre>

#### Cell Format:
It's `hex` number, each digit belongs to texture number, except last one.</br>
Max-lenght og the cell number - 8 digits, e.g. `1ACB67FE`.</br>
In square brackets index number of each digit.</br>
<b>[1] [2] [3] [4] [5] [6] [7] [8]</b>

<pre>
if (`[8]` || `[7]` || `[6]` || `[5]`)
    This cell is a wall
else if (`[2]` && `[1]`)
    This is a sprite through which you can not pass

`[3]` - Floor texture number.
`[4]` - Ceil texture number.
</pre>



### Build:
You need:
 - Xcode
 - Make
 - Clang

If you have these packages, run `make` command in project folder, it will compile whole project

###### Project created and tested on MacOS High Sierra 10.13
###### Copyrights CoZZ © 2018
