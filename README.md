# Google Summer of Code, Module and test projects

#             **MIDI support for Godot Engine**  

This repository contains all the code I have wrote for this year's Google Summer of Code. 

My project, Midi Support for Godot Engine involved integrating an existing MIDI library in the game engine Godot. 

The library I used for this project is called TinySoundFont (https://github.com/schellingb/TinySoundFont). It is a very basic MIDI library that includes all of MIDI's basic functions which might be needed in a game engine without any dependencies which made it ideal for integration in a big project such as Godot. 

The feature works with SoundFont and MIDI files which the user can import or load using a GDScript function. A SoundFont file is a library of samples which are called with MIDI messages. In order to use this feature the user will need to create their own SoundFonts, which is fairly easy to do with the free software Polyphone(https://www.polyphone-soundfonts.com/en/). SoundFonts can contain loads of samples which means that a user can have all the sounds they would like to use for their Godot project in a single AudioStreamPlayer node, with a loaded SoundFont as a stream property. 

Since my project is to include a new feature in Godot, after discussion with my mentors we decided that the best way to approach it is to include the library and my code as a custom module for the engine. This means that in order to see my code working, all that needs to be done is to simply copy the TSF folder from this repository into the modules folder of Godot and then compile the engine.

![](https://i.imgur.com/sYx4z3m.png)

