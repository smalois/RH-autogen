# What is this

A C program to auto-generate simple patterns for Rhythm Horizon. It works by
defining a simple mapping between the player's current foot position, and any
comfortable next steps (See `void initialize_easy_steps`). It then selects a
random next step from the set of next comfortable step (as defined by a
collection of 9 bits representing the arrow receptors).

To use it, you simply provide the number of steps you wish to generate, and it
writes a newline delimited steps to stdout. You'll want to redirect to a file
if planning on using AHK to input them to the game editor. By default the
output is the default RH editor bindings (zaqxswedc).

You then run the autogen.ahk script against the output of the autogen program.
It gives you 2 seconds to shift focus over to the game client before it sends
all of the keypresses.

Note that this is all just a quick hack to get some stamina songs created for
RH. I'm not likely to support this in the future, and this may not be helpful
to people that aren't me.

## Building: 
(Should be portable to any platform, but I've only tried building in Linux (WSL))

```bash
gcc autogen.c -o autogen
```

## Usage:

```bash
./autogen [number of steps to generate]
```
Don't give weird inputs to [number of steps to generate]. I don't do any checks
for the quality of the input. Any number between 0 and UINT_MAX should work.

By default, output is sent to stdout. I redirect to a file that can be read by
the AutoHotkey script like so:

```bash
./autogen [number of steps to generate] > out.txt
```

### Running the AHK script

You'll have to open the autogen.ahk file and replace <FILE PATH TO AUTOGEN
OUTPUT GOES HERE> with the filepath to the out.txt file you generated in the
step above.

Assuming AHK is already installed, you should be able to just double click
autogen.ahk script to run it. It gives you 2 seconds to click on the RH window
to focus it.

Make sure you set your quantization to your desired value before running the
script and have "auto-advance" disabled. If you want 16ths stream, have your
quantization set to 16ths.

## What's next

I had plans to define some "rules" to restrict how next steps could be
determined, but that functionality is unfinished.
