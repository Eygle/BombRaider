# BombRaider
A 3D bomberman game made with League of Legend and World of Warcraft models

# Prerequisit
Libraries dependencies
* make
* g++
* GL
* glu
* glut

For unbuntu you can run:
```bash
sudo apt-get install make g++ libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev
```

# Setup & Install BombRaider
In BombRaider's root folder run:
```bash
sudo make prepare
```
**or**
Copy all files in libs/bin_x86_64 in the folder /usr/lib (if you use a 32 bit system copy the files in bin_x86 instead)

Run the following commands

```bash
make
./bomberman
```
