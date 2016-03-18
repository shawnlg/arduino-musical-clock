# arduino-musical-clock
A clock that plays a song every hour
# Work In Progress

This code runs on the Arduino Nano and probably any other type of Arduino.  It does not use any special library.

## End Product

The final code will be a digital clock that plays a different song every hour.  It will have the following features
* Uses a real-time-clock module to keep accurate time
* Uses 4 7-segment LED displays connected directly to the Arduino without the need of any driver chips
* Uses a small 8-ohem speaker connected to the Arduino without the need of an amplifier
* Contains a 4-voice synthesizer, allowing complex songs to be created.
* Contains a fairly simple song definition format, allowing song notes and sounds to be defined

## Credits

For the sound synthesizer, I have modified code from this guthob project:
https://github.com/dzlonline/the_synth

# What's Here So Far

## Synth and Player

Code for defining and playing the sound is here.  A sample song is included as demonstration.

## Song Tutorial

A fairly involved tutorial has been included with sample song data.  It walks you through creating songs that will eventually
play on the clock.  The tutorial takes you through
* Creating basic notes and rests
* Defining volume shaping envelopes for more expressive sounds
* Dividing songs into parts for reuse
* Writing for all 4 voices

# Hooking Up the Speaker

A speaker can be connected directly to pins 3 and 11.  These pins produce short pulses of PWM, so they will not burn out.
However, if you are nervous about damaging the I/O pins on your arduino, you can add a 150 ohm resister in line with one of
the speaker leads.
