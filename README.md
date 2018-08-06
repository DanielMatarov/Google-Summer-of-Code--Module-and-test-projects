# Google Summer of Code, Module and test projects

#             **MIDI support for Godot Engine**  

This repository contains all the code I have wrote for this year's Google Summer of Code. 

My project, Midi Support for Godot Engine involved integrating an existing MIDI library in the game engine Godot. 

The library I used for this project is called TinySoundFont (https://github.com/schellingb/TinySoundFont). It is a very basic MIDI library that includes all of MIDI's basic functions which might be needed in a game engine without any dependencies which made it ideal for integration in a big project such as Godot. 

The feature works with SoundFont and MIDI files which the user can import or load using a GDScript function. A SoundFont file is a library of samples which are called with MIDI messages. In order to use this feature the user will need to create their own SoundFonts, which is fairly easy to do with the free software Polyphone(https://www.polyphone-soundfonts.com/en/). SoundFonts can contain loads of samples which means that a user can have all the sounds they would like to use for their Godot project in a single AudioStreamPlayer node, with a loaded SoundFont as a stream property. 

Since my project is to include a new feature in Godot, after discussion with my mentors we decided that the best way to approach it is to include the library and my code as a custom module for the engine. This means that in order to see my code working, all that needs to be done is to simply copy the TSF folder from this repository into the modules folder of Godot and then compile the engine.



## How does the code work?

The main class for this project is called MidiStream. It inherits AudioStream which is the base class for audio in Godot, while also adding functions from the TinySoundFont library. TSF however does not have any playback on its own, it only stores data to a buffer which can be read by an audio driver. For this purpose there is a MidiStreamPlayback class which inherits AudioStreamPlayback. In this class there is a mix function which reads the audio data and sends it to Godot's AudioFrame. 

The way TSF deals with data is by storing it on a pointer which stores the soundfont data and is used in every function. At the end a render function is called to write the data to a buffer. For this project the render function is called inside the mix function of MidiStreamPlayback. 

To be able to play anything however, a soundfont(.sf2) file needs to be loaded. There are two ways of doing this. One is through a public function that can be called through GDScript. The function, `set_filename(constString&filename)`takes the name of a .sf2 file in a Godot project's directory and loads it to `tsf_pointer` , then checks if the pointer has been loaded and sets TSF's output settings, which are number of channels(stereo or mono), sample rate and gain.

The other way of loading .sf2 files happens by using a ResourceImporterSfont class, which inherits ResourceImporter. This class has an import function which calls on some of Godot's `FileAccess` functions. It also creates an instance of `MidiStream` and calls on a `set_data` function that uses a TSF function(`tsf_load_memory`) to load sound data from memory and assigns it to the`tsf_pointer` .

Using MIDI files is also a part of this feature. Similarly to .sf2 files, .mid files can be loaded in two ways, script and a `ResouceImpoterMidi` class. The script function for loading .mid files is called `midi_load_filename`.  Just like with .sf2 files, .mid file data is stored on a pointer called `midi_pointer`. Once the pointer is loaded, the `MidiStreamPlayback` class' mix function checks if it's loaded properly and and calls on a `midi_file_playback`function before calling the render function and sending the data to Godot's audio server. 

The way `midi file playback` works is by counting the samples which need to be processed and then looping through all MIDI messages up until the current playback time, by checking the type of each message and calling on the correct TSF function. 

Loading MIDI files through `ResourceImpoterMIDI` works slightly different than it does with .sf2 files. They have a separate Resource class called `MidiFileReader` which handles the loading of the files with `set_data` and `get_data` functions by using `tml_load_memory` to load the data to a pointer. The pointer is then called in MidiStream through a set_midi_file function and assigned to midi_pointer in MIDI stream. The idea of this  is to be able to load the .mid files through the editor, so these functions are added as an inspector property for MidiStream. 



