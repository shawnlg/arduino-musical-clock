/*************************************************************************

Tutorial for creating music

Introduction
This tutorial explains how to define songs that can be played on the arduino synthesizer (synth).
The synth is capable of playing 4 notes simultaneously.  Note wave, duration, and volume shape can be
defined.  The song definition is fairly easy as there are simple symbols defined to make the song data
easy to understand.

Concepts:  These will be used throughout the tutorial
 - note:  This is represented by a note number (midi note number) or
   a symbol such as C1 (note C, octave 1 or the lowest C on the piano) or ES4 (E sharp, octave 4).  The note numbers range from 21 to 108
   which are the notes on a piano keyboard.  Not all 127 midi notes can
   be played.
 - BEAT:  The shurtest time duration needed to represent note timings in
   a song.  For example, if you have 4 quarter notes to a mesure, but your
   song has eighth notes, you would actually have 8 beats per measure.
   BEAT numbers are used to represent note durations and rest durations.
 - TICK:  This is the smallest time you can specify when defining your song.
   By default, it is set at 1/100 of a second.  That can be changed by
   redefining a macro variable.
 - BEAT_DURATION:  This is the number of ticks that are the length of a single
   beat.  It defines the temp of the song.  If you set BEAT_DURATION to 10,
 - voice:  The synth can play 4 notes simultaneously.  You define the
   notes and notes and rests one voice at a time.  When the song is
   played, all 4 voices play together.  If you do not need four voices,
   you can define some of them to play nothing.
   nothing in the song can happen faster than every 10 ticks or 1/10 second.
 - REST:  This defines the number of beats that the synth will wait befoore
   playing the next note.  Notes can be playing during a rest, but no new
   notes will start.  
 - REST_UNTIL:  This defines when the synth will start playing again 
   in terms of the song's beat number.  A song starts with beat 1 and 
   it continues increasing until the song is over.  BEAT_UNTIL is used
   when you want to wait until a particular part of the song is over before
   resuming on another voice.  
 - NOTE_LENGTH:  This is the number of beats a note takes to play.  The
   note may start out loud and gradually get softer, it may play at the
   same volume, or it may have other properties, but it ends when this
   number of beats occurs.  A NOTE_LENGTH does not determine a rest.

   For example, if you wanted to play a note that was 3 beats long, have
   one beat of silence, and then play another note, you would define a
   NOTE_LENGTH of 3, then the note to be played, then a 4-beat rest.

   When a NOTE_LENGTH is specified, all notes after the length will have the
   same length until a new length is specified.  This works well for songs
   where all the notes have the same length, like the sound of a xylophone.
 - volume level:  A note being played has a volume level throughout the time it is
   playing.  The maximum volume level of a note is 255.  If a note starts out loud and
   gradually decays as it is playing, it's volume level will start out at 255 and gradully
   decrease to 0 as the note is played.

   The maximum volume level that can be played by this synth is 255.  If more than one
   voice is playing a note at the same time, it's possible for the volumes of the two notes
   to be greater than 255.  In fact, if all 4 voices are playing a note at maximum volume, the
   total volume would be 1020, much higher than can be played by this synth.

   To stay within the maximum volume, the synth divides the volume of each voice by 4 before
   playing them together.  This will prevent too high of a volume which will greatly distort the
   sound.  You can manually change the volume by specifying three volume levels
   * VOLUME_NORMAL divides the volume of each voice by 4, so it is safe to use with all 4 voices playing
   * VOLUME_HIGH divides the volume of each voice by 2, so it is safe to use when 2 voices are playing
   * VOLUME_XHIGH does not divide the volume of the voices playing, so it is only safe while 1 voice is playing
   If you know that only a certain number of notes will ever be playing at the same time, it may
   be safe to manually change the volume.  However, if you do exceed the volume at any time,
   the distortion will be very evident.  The sounds produced can be interesting, and it does not
   hurt to experimenting with overflowing the volume.
 - NOTE_PRESET:  In most songs, notes may be held for different lengths and
   there are certain rests that go with the note.  Instead of specifying a
   note length, the note, and a rest value for each note of the song, it is
   more convenient to make up a number of presets for the common values that
   are used in the song.  A preset lets you define a number of characteristics
   of a note to be played.  These include
   * the type of sound (WAVE) which is used to make the note
   * The length of the note in ticks
   * A rest associated with this note in beats
   * The envelope (loudness shape) of the note.
   Presets can be defined for each type of note such as quarter notes,
   half notes, notes that need emphosis, etc.  Once these presets are defined,
   the song can consist mainly of notes and their note presets.
- ENVELOPE:  This defines how a note's loudness is over time.  A note that
  sounds like a xylophone would start out loud and gradually get softer until
  the end of a note.  A note that resembled a trumpet might start off loud
  and stay loud for a certain amount of time.  A note that resembles a bowed
  instrument might have a fast but gradual increase in volume which is held
  for a certain amount of time and then quickly but gradually get softer at
  the end of the note.  Defining envelopes lets you define the shape of the
  note.

The Song

This tutorial will take you through creating a 4-voice song.  It is a simple
song that children sing in my church.  It can be sung in rounds.  This will
demonstrate using different voices, different sound types, and the other
items discussed above.  We will go through it step by step.

Define a Melody

We start out with defining the notes and rests needed to make a melody.  All
notes will be of the same type, so the song will consist of notes and
rests.

Songs are stored in pieces, and each piese is stored in a byte array in flash memory.  For this
example, we will define a song piece that contains the notes and rests of the melody.  Look in
tutorialData.h for the bye array called SIMPLE_MELODY.

Note that a byte array starts with this:
  const byte PROGMEM SIMPLE_MELODY [] = {
And ends with this:
  };

Each byte array needs to have a different name.  Look at the song piece SIMPLE_MELODY.  
Note the following:
 - The song data starts with a BEAT_DURATION 16.  This means each beat of the song is 16/100
   second long.
 - The song data ends with END_DATA.  This signifies that there is no more song data to read.
   A song piece must end with this, or the synth will keep attempting to read song data after
   the end of the data, and the results will be unpredictable.
 - In this song, there are notes and rests.  Since each note has the same length when being
   played, this works.

Playing the Song

To play a single voice, you call the function playSingleVoice, passing it the
name of the song piece.  This can go in the setup() function.  To play the voice we
just looked at, put the following in your setup() function:
  playSingleVoice(SIMPLE_MELODY);  

It is necessary to call the song player repeatedly in the loop() function.  The song
player is the function that reads the song data, calculates when to play the notes, and
calls the sound generator to make the sounds.  You loop function would look like this:
void loop() {
  if (playingSong) {
    songTick();
  }
}

To hear the song, connect a speaker between pins 3 and 11.  The synth should be loud enough to drive a
normal speaker, and the PWM waveform that drives the speaker should prevent too much current from flowing
to the speaker for a long period of time.

Debugging the Song

If you enter song data and it doesn't sound right, you can put the synth in debug mode.  Instead of playing
the song, it prints the song data to the serial monitor.  To place the synth in debug mode, uncomment this
line in globals.h:
  //#define PRINT_SONG_DATA

The data is printed as if the synth were playing the song.  All envelopes generated from presets are
also printed, showing how the volume level changes over time.

Changing Note Lengths

In the song piece SIMPLE_MELODY, all notes were at the same length.  There were different delays after
each note (the REST command), but that only affected when the next note was played.  It did not affect
the sound of the note in any way.  We will now learn how to change the sound of the notes.  We start with
the note length.

Look at song piece CONSTANT_VOLUME_NOTES.  We use sound presets to define envelopes and note lengths.
To use this feature, you define all possible note sounds before the song.  In this song, we have three
types of notes:  Notes that are 3 beats long, notes that are 2 beats long, and notes that are 1 beat long.
Actually, the notes are slightly shorter than that, or they would run into the next note.  So, for a 3
beat note, the rest after the note is 3 beats, but the note itself is slightly shorter than 3 beats.

All the sound presets are in a single group that starts with the START_PRESETS command and ends with the
END_PRESETS command.  Each preset within that list ends with the END_PRESET command.  The commands that
make up a preset are as follows:
 - length of note (in ticks, not beats)
   Notice that when we define the preset for a 1-beat note, we define the note length to be 14.
   One beat is 16 ticks, so the note will be slightly shorter than that, allowing you to hear a
   slight rest between the end of the note and the start of the next note.
 - rest associated with the note (in beats)
   This is how long the synth will automatically rest after playing the note before playing the next note.
   You can set this to 0 and define the rests yourself with the REST command if desired.  This might be
   useful for complex music where a note of a certain length is not always followed by a certain length
   rest.  You can also have both.  You can define a rest associated with a note, but if you want a longer
   rest, you can also define additional time with a REST command after the note.
 - starting note volume
   This is how loud the note starts playing.  It can be any number between 0 and 255.  You might start it
   at 0 if you wanted to gradually increase the volume as the note was playing.  In the case of this song,
   we start the volume off at the loudest possible level, 255.
 - The next part of the preset is optional, and it is not used for this example.  It consists of two pairs
   of numbers that define the time to the next volume level, and the next volume level.  We will discuss this
   more later on when we create more complex notes.  For now, just understand that the notes start out
   at a volume of 255 and stay at that volume throughout the entire note.

Play this song by changing the playSingleVoice function in setup().  Specify the song piece CONSTANT_VOLUME_NOTES.
Notice that this song sounds worse than the last one.  This is because there is no dynamic range in the
notes.  The previous song used the default note sound which starts out loud and gradually gets softer.

You can play this song in debug mode and observe the envelopes.  You will see the shape of the envelopes
that are default when the song starts.  You see how they volume is high and decreases.  There are 4
envelopes because the synth can play 4 voices at once, and each voice has its own envelope.  We are still
usiing just one voice.

Adding Changing Volume Level to Notes

It is common to express the sound level of a note with the term ADSR.  This stands for attack, decay,
sustain, and release.  Here is what these mean:
 - Attack is the volume level a note has when it first starts and how quickly it gets there.  A piano
   would have a high volume that gets there almost instantly, since the string is hit with a hammer and
   quickly gets to its loudest level.
 - Decay is how quickly the volume decreases and to what level it decreases after the attack.
   For a piano, the volume of a held-in note decays slowly to zero.  A piano nnote that is released before
   it decays to zero would decay to a louder volume and then would drop off quickly to zero when the note
   is released.
 - Sustain defines how long the note plays after it reaches its decay level.  This is how long the note
   is played.  Some notes, like a bell, do not have a sustain.  They decay to zero at the same length
   of time. 
 - Release is how quickly a note falls to a volume level of 0 after the sustain period.  Most instruments
   do not have a release time of 0.  In our last example, no release was defined, so it was 0, which gives
   it a beeping quality.

Look at song piece CLARINET_NOTES.  This is an example of changing volume as notes are played.
 - We see a new command, OCTAVE_UP_ONE.  This allows us to change the octave but use the same
   melody.  This will be important later when we break a song up into several reusable parts.
 - As before, there are 3 presets, each having the same note length and beats as before.
 - The first command in preset 1 is the starting note volume.  This time we start out at the
   quietest volume, 1.  It is not allowed to start out at 0.  The volume is already at 0
   when a note is about to play.
 - This time the preset data continues.  It consists of pairs of numbers
   - time to next volume
   - next volume
   These can be repeated as many times as desired.  The time in this case is not ticks or
   beats.  Instead, it is in 1/128 of the entire note.  This makes things a little more
   difficult, because as notes get longer, if you want the start of the note to have the same
   volume change time, the time gets smaller.

   Here is an example:
   Suppose you want a note to take 1 beat to increase in volume, then play at that volume,
   and then take one beat to decrease down to zero.  The timings would be different depending
   on how many beats the note is in length.
   - for a 2-beat note, one beat would be taken going up in volume, one beat would be taken
     going down in volume, and there would be no time left to stay at the high volume.
     So we would use 64 as the time to rise in volume and 64 as the time to fall in volume.
   - Now for a 3-beat note, 1 beat would be for rising volume, one for falling volume, and
     one in the middle for playing the note at the high volume.  You would have to divide
     your 128 note pieces in thirds to make this work.

You might be wondering why we didn't just use times in ticks instead of dividing the note
into 128 pieces.  The Arduino processor is quite slow, and if we used times, we would have to
calculate ratios which needs division.  The processor does not do division very fast, so it
could affect the sound being produced as the processor calculated the volume envelope every
time a preset were used.

Dividing Up the Song

We now show how to divide the song into multiple pieces.  To do this, we need to start using
the real synth player function.  This lets you play all 4 voices at once and lets you define
various pieces for your song.

Look at the section of data that starts with MULTIPLE PART SONG.  
 - The first piece of data is a subsong called SONG_MELODY.  You can define up to 
   50 subsongs, and they can be used anywhere in the main song.  The next subsong is
   called SONG_PRESETS_A.  There are 2 more subsongs with more presets.
 - Next comes the list of subsongs in the song.  The list is called SUBSONG_LIST.
   It can be called anything, as long as it has a unique name.  It lists ever song piece
   that is a subsong.  In our case, we have 4 subsongs in the list.
 - Next we define the main song for voice 1.  It is called SONG_VOICE_1.  See how it calls
   the various subsongs.  It plays the melody 3 times, each time with a different list of
   preset sounds.
 - Finally, we must define the list of all 4 voices that we pass to the synth.
   It is defined in data SONG_ALL.  In this case, the first voice is song piece SONG_VOICE_1 
   and the rest of the voices are song piece EMPTY_VOICE.  This song piece is defined in the 
   globals.h file, and it's just a song piece with an END_DATA command in it.  
   This is used because we are only using 1 voice for now.

To play a song, you pass the list of 4 voice pieces and the list of subsongs to the function
playSong().  In the case of this song, you would call it like this:
playSong(SONG_ALL, SUBSONG_LIST);

The Final Song

The last song in the tutorial shows how to use all 4 voices.  It uses different presets,
envelope shapes, and octaves to make the voices sound differen from  each other.  We will
go over each piece that makes up this song.
 - The first section of data defines groups of presets.  As before, the presets are put into
   subsongs so that they can be reused.  In the case of this song, we have presets A and B.
   Presets A define the sounds for the melody, and presets B define the sounds for the
   base part.  As before, the melody is played with varying length notes and volumes.  The
   bass part is played with simpler sounds.  They start loud and decay at the same rate.
 - Next we define subsongs which contain actual notes to play.  We have one preset that plays
   the melody and one that plays the bass part.
 - After the subsongs are defined, we need to put them in a list to pass to the synth.
   The data called ROUND_SUBSONG_LIST lists each subsong that will be available to all
   voice tracks in the song.  There can be up to 50 of them.
 - Next we define 4 pieces of data, one for each voice.  Since these are more complex than
   in previous songs, we will discuss them individually.
 - The first voice is defined with data ROUND_VOICE_1.  As in previous songs, it defines a
   beat duration and reads in a subsong that defines preset sounds.  We now define a
   wave shape for the notes.  In this case, we have a ramp wave called WAVE_RAMP.  You can
   see the different wave shapes defined in globals.h.  The shape of the wave defines the
   type of sound produced.  You can try the different waves to see their effect on the sound.
   Finally, voice 1 plays the melody twice.
 - the second voice is defined in data ROUND_VOICE_2.  It has the same beat duration, but it
   uses a different set of sound presets.  This is so the bass part can sound differently
   than the melody.  It also uses a different wave shape.  It then plays the bass part.
   After playing the base part which lasts the entire melody, it plays the melody again but
   1/4 of the verse later than voice 1.  This is part of the round where all 4 voices will
   play the melody together.  Notice that is changes prersets and envelope shape back to the
   melody one, but it uses a different octave.
 - The third voice is used to play the melody, but it waits until the first voice has played
   the melody once and then half of the second melody.  It uses the same preset sounds as
   voice 1, but it uses the WAVE_SINE shape for its wave shape.
 - The last voice is similar to the third voice, but it waits even longer to start playing
   the melody.  It also plays at a low octave and uses a different wave shape.
 - The final piece of the song data is the list of the 4 voice tracks that gets passed to
   the synth.  In this song, we call it ROUND_ALL.  It always contains 4 entries, one for
   each synth voice.

 To play this song, you pass the voice list and subsong list to the synth like this:
  playSong(ROUND_ALL, ROUND_SUBSONG_LIST);

It is not necessary to divide up a song.  If each voice of the song plays something totally
unique, everything can be placed in the data for that voice.  This includes sound presets.
However, it is easier to keep track of the pieces of the song if they are in separate, 
smaller sections.

Remember that when testing a single piece of the song using the playSingleVoice() function,
there is no way to pass in the sound presets as a separate piece of data, and there is no
way to pass in the list of subsongs.  This function is just there to help you easily test
notes and durations before you combine it with other parts of the song.  You will need to
put preset data in the voice track while using the function.  Once the voice is the way you
like it, you can break up that data into separate subsongs.

 *************************************************************************/

