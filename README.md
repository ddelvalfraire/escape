# Collaborators
- David Del Val Fraire Lab 1
- Emily Tran Lab 1
- Elizabeth Hale Lab 1

 # Dependencies
 We used microsoft vcpkg as our package manager. 
 The following are the dependencies needed to run the program.
 
 We simply used the latest versions of all of these as of 4/24/24.
 - tmxlite
 - box2d
 - sfml
 - googletest

# Running the application from visual studio
We recommend you build in release, there seems to be an issue with box2d in our debug builds
The bug seems to be unrelated to our code and does not appear in release builds.

# How to play
Control the the player by using the arrow keys. The up arrow key jumps and is used to climb walls aswell.
E interacts with chests. To interact with chests you must be touching them. 
Sometimes the character gets a little stuck but jumping and wiggling will always work him out of places.
