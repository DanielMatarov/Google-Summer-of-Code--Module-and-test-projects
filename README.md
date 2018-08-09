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

## How do I use this feature? 

As mentioned previously, you need SoundFont files to be able to play any audio using MIDI messages. To begin, you need to place a .sf2 file in your project's directory, and that will automatically detect the file and it will show up in the resources panel in Godot's editor, as shown in the image below. 

![https://i.imgur.com/t4moFMc.png]()

You can also see the MIDI file venture.mid in that panel as well. Just like with .sf2 files, all that needs to be done is to simply place them in the project's directory.

Thanks to the ResourceImporter classes for both .sf2 and .mid files 



## What challenges did I encounter? 

When I first applied for this project I was pretty much a beginner in the world of programming, my experience was limited to a couple of years of audio programming at university where I learned a little bit of object based programming. So needless to say I had a lot to learn before and during the coding part of GSOC. 

I started with learning how Godot is structured so I can find out where in the hierarchy my code will fit. With my mentors we decided, as previously mentioned that the code will be a module. Next I tried to learn how to create custom modules for Godot, by following some of the instructions that I found in the engine's documentation web page. I encountered some issues with that however because parts of the documentation were fairly outdated, but with the help of my mentors I managed to understand how most of it works. Needless to say, I also had to learn how to make custom AudioStream modules and learn how audio works in Godot as a whole. 

My first task was to be able to play a MIDI note by pressing a button in a Godot project. That was in my opinion the hardest part of the project because I didn't quite understand how to connect the data from TSF to the engine's AudioFrame. Fortunately, with the help of my mentors I managed to do that after just two weeks of coding and moved on to adding more TSF functions and implementing MIDI file playback. For the first milestone I created a couple of Test projects, one with a Piano roll and another project that played a MIDI file when a button is pressed. 

Being quite new to programming, one of the main issues I encountered was my code being very messy and understanding how to include headers in .h and .cpp files. It wasn't until I tried creating ResourceImporter classes for MIDI files and SoundFont files that these issues became apparent, where my code was mostly correct, but because of my header includes being in the wrong places, my code wouldn't compile, or if it did it simply didn't work. Fortunately I now have a better understanding on that topic and programming as a whole due to participating in the program, however there is a lot more to learn and I will try to continue to contribute to Godot's code throughout the year and potentially apply for Google Summer of Code next year as well!



#### Conclusions and how this project experience will help me in my future professional career

As someone who aspires to work as a freelancer in the game and film audio field, working on this project helped me understand a lot about how audio works in game engines, and also helped me reinforce and learn lots of new programming skills that I likely wouldn't have learned otherwise. 

A big part of the project was working in the context of a bigger project, which is Godot and understanding how to connect my parts to the bigger picture was an interesting experience. If I end up pursuing a career as a freelance programmer, that will often be the case and I feel like this experience will be a very big plus in my future job search, because I now not only have better skills in programming but I have also learned to use git and work in bigger projects which will be sought by future employers. Another useful skill was working in my own time and building the discipline to do it consistently and every day, which is a very important skill for freelancers.

As a whole working for Godot during Google Summer of code was a very positive experience that I believe will be very useful for my future. I am looking forward to next year's GSOC for which I will definitely apply, and quite likely will try to find another Godot project that will suit my skills and interests! 





