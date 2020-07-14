# Winsplit
It seems that windows does not offer a simple way to evenly fill the monitor with more than 2 windows. 
As most people know, dragging one window to the side of the screen allows you to perfectly fill your screen with 2 separate windows, each taking half the screen.
While this is nice, people with ultra wide monitors will know that this doesn't go far enough. This is how Winsplit was born.

The project is open source and the project files can be found here:
* [Winsplit Source](https://github.com/Merlotec/winsplit/).
* [Winsplit Release](https://github.com/Merlotec/space_render/blob/master/shaders/src/atmosphere.frag.glsl).

### What is Winsplit
Winsplit is a tool that allows you to split your desktop evenly into an arbitrary number of windows (3 by default). 
It is programmed to be lightning fast, simple, and as unintrusive as possible. There's nothing I hate more than poorly performing, clunky bloatware.
Winsplit is programmed in pure C, the entire program consisting of only 124 lines of code.

### How to Use
Winsplit is compiled into a standalone executable (.exe) which can be run from anywhere.
There is no installer included, because there's basically nothing to install.
**For ease of use, I would recommend pinning the application to your taskbar.**
You can do this by right-clicking `winsplit.exe` and clicking 'Pin to Taskbar'.

Winsplit orders the windows from right to left by their current 'layer/depth', going from closest to farthest. This means, the most recent window you've clicked on will be on the left, the second most recent in the middle, and the third most recent on the right (for 3 way split). This is because as you click onto a new window, it has the new closest depth since it's at the front.

So, when performing a 3 way split, click on the windows in order of right fist, middle second, and left last.
After doing this, simply run the winsplit application either by clicking on the taskbar icon, double clicking the .exe or launching it via the command line.

### More that 3 Windows?

To split the desktop into more than 3 windows, you must pass the number of divides you wish to make as the first command line argument when executing `winsplit.exe`. E.g. to the number of splits you wish to make. E.g. `winsplit.exe 5` would split the desktop into 5 windows. (Note, if there are less than the specified number of windows, winsplit will split the desktop into the number of windows available).

### Some Things to Note
Because of window dimensions and padding, it may sometimes seem as if the windows are not completely touching/filling the screen.
Unfortunately the window size seems to include some padding around the window used for the resize handle, and expanding the windows to remove this removes the ability to resize the windows, which is just more annoying. In addition, this 'padding' value seems to be different with different windows, so it's impossible to get an accurate value for this.
