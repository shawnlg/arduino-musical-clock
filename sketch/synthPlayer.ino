synth player;

void synthOn() {
  playingSong = true;
  player.begin();    //Differential - use pins 3 and 11
  // Set up the voices to the default values
  // setupVoice( voice[0-3] , waveform[SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE] , pitch[0-127], envelope[ENVELOPE0-ENVELOPE3], length[0-127], mod[0-127, 64=no mod])
  player.setupVoice(0, DEFAULT_WAVE, 0, DEFAULT_ENVELOPE, DEFAULT_NOTE_LENGTH, DEFAULT_NOTE_MOD);
  player.setupVoice(1, DEFAULT_WAVE, 0, DEFAULT_ENVELOPE, DEFAULT_NOTE_LENGTH, DEFAULT_NOTE_MOD);
  player.setupVoice(2, DEFAULT_WAVE, 0, DEFAULT_ENVELOPE, DEFAULT_NOTE_LENGTH, DEFAULT_NOTE_MOD);
  player.setupVoice(3, DEFAULT_WAVE, 0, DEFAULT_ENVELOPE, DEFAULT_NOTE_LENGTH, DEFAULT_NOTE_MOD);

}

void synthTest() {
  for(int i=49;i<57;i++) {
    player.mTrigger(0,i);
//    player.mTrigger(1,i);
    delay(300);

    player.setLength(3,30);
    player.mTrigger(3,i);
    delay(150);

    player.mTrigger(2,i);
    player.setLength(3,20);
    player.mTrigger(3,i);
    delay(150);
  } // for
}

void synthTest2() {
    player.begin();    //Differential - use pins 3 and 11
    player.setupVoice(0,RAMP,0,ENVELOPE3,100,64);
    player.mTrigger(0,72); // note number
}

void synthOff() {
  player.suspend();
  playingSong = false;
}

// variables needed to keep track of song as it's playing
unsigned long voiceResumeTick[NUM_VOICES];  // delay reading song data until this time
byte voiceBeatDuration[NUM_VOICES];  // each voice's beat duration in ticks
char voiceTranspose[NUM_VOICES];  // how much to transpose notes in voice
byte presetNoteRest[NUM_VOICES];  // played note has this rest associated with it
const byte *voiceCursor[NUM_VOICES];  // current position in voice data
const byte *oldVoiceCursor[NUM_VOICES];  // voice cursor before going to subsong
const byte **subsongs;
unsigned int songTickNumber;  // increments every one hundredth of a second
unsigned long lastTick;  // time of last tick

#define NUM_PRESETS 10  // max number of presets per voice
const byte *pPresets[NUM_VOICES * NUM_PRESETS];  // holds pointers to preset data

// an array of streams is passed to the player, one for each voice
void playSong(const byte **voiceData, const byte **subsongData) {
  songTickNumber = 0;  // reset tick count
  lastTick = millis();  // when last tick happens
  for (byte i=0; i<NUM_VOICES; i++) {
    voiceCursor[i] = voiceData[i];
    voiceResumeTick[i] = 0;  // no dealy, start reading data immediately
    voiceTranspose[i] = 0;  // do not transpose voice
    presetNoteRest[i] = 0;  // no rest associated with notes
  }
  subsongs = subsongData;
  synthOn();
}

// simple player tracks
const byte *_simplePlayerSong [] = {
  EMPTY_VOICE,
  EMPTY_VOICE,
  EMPTY_VOICE,
  EMPTY_VOICE
};
void playSingleVoice(const byte *songData) {
  _simplePlayerSong[0] = songData;
  playSong(_simplePlayerSong, EMPTY_SUBSONG_LIST);
}

// called repeatedly to coordinate the notes of a song
void songTick() {
  // see if it's time for a song tick
  if (millis() < lastTick + TICK_DURATION) {  // not time for a tick yet
    return;
  }

  // time for a tick
  songTickNumber++;
  lastTick += TICK_DURATION;  // update when last tick

  // count how many voices have stopped.  When they all stop, the song is over and the synth can be stopped
  byte voicesStopped = 0;

  // we have to process every voice stream
  for (byte i=0; i<NUM_VOICES; i++) {
    // see if we aren't finished with last delay
    if (songTickNumber < voiceResumeTick[i]) {
      continue;  // not time to read more data
    }

    // we are pointed at the song data where we continue playing
    for (;;) { // loop until we get a delay or end of song
      byte b = pgm_read_byte(voiceCursor[i]++);  // read the command byte
      #ifdef PRINT_SONG_DATA
        if (b != 0) {
          Serial.print('('); Serial.print(b); Serial.print(')');
        }
      #endif

      if (b >= NOTE_FIRST && b <= NOTE_LAST) {  // a midi note command
        b += voiceTranspose[i];  // apply any transpose
        #ifdef PRINT_SONG_DATA
          Serial.print(F(" NOTE ")); Serial.print(b); Serial.print(' ');
        #endif
        #ifndef PRINT_SONG_DATA
          player.mTrigger(i,b);  // play midi note
        #endif

        // if the notes have a preset rest, delay also
        if (presetNoteRest[i] > 0) {
            voiceResumeTick[i] = songTickNumber + presetNoteRest[i] * voiceBeatDuration[i];  // delay until this tick
            #ifdef PRINT_SONG_DATA
              Serial.print(F(" preset note rest: ")); Serial.print(presetNoteRest[i]);
              Serial.print(F(" stop until tick ")); Serial.println(voiceResumeTick[i]); 
            #endif
            goto doneDoingVoice;  // quit reading data
        } // if preset note rest defined
      } else if (b >= REST_1 && b <= REST_MAX) {  // delay short command
        b -= REST_0;  // now b has the duration in beats
        voiceResumeTick[i] = songTickNumber + b * voiceBeatDuration[i];  // delay until this tick
        #ifdef PRINT_SONG_DATA
          Serial.print(F("REST: v")); Serial.print(i); Serial.print(':'); Serial.print(b);
          Serial.print(F(" stop until tick ")); Serial.println(voiceResumeTick[i]); 
        #endif
        goto doneDoingVoice;  // quit reading data
      } else if (b >= PRESET_FIRST && b <= PRESET_LAST) {  // a preset
        b -= PRESET_FIRST;  // now b has the preset number
        #ifdef PRINT_SONG_DATA
          Serial.print(F("\nPRESET ")); Serial.print(b+1);
        #endif
        // point to the right preset data
        const byte *pPreset = *(pPresets + (NUM_VOICES*i + b));
        #ifdef PRINT_SONG_DATA
          Serial.print(F(" preset list address: ")); Serial.print((unsigned int)pPresets); 
          Serial.print(F(" this preset pointer address: ")); Serial.print((unsigned int)(pPresets + (NUM_VOICES*i + b)));
          Serial.print(F(" this preset address: ")); Serial.println((unsigned int)pPreset);
        #endif

        // read the values in the preset and apply them to the synth
        b = pgm_read_byte(pPreset++);  // read note length in ticks
        #ifdef PRINT_SONG_DATA
          Serial.print('('); Serial.print(b); Serial.print(')');
          Serial.print(F(" note length ")); Serial.print(b); Serial.print(' ');
        #endif
        // change note length into synth length that corresponds to this time
        b = pgm_read_byte(NOTE_LENGTH + b);
        #ifdef PRINT_SONG_DATA
          Serial.print('('); Serial.print(b); Serial.print(')');
          Serial.print(F(" synth length: ")); Serial.print(b); Serial.print(' ');
        #endif
        player.setLength(i,b);

        b = pgm_read_byte(pPreset++);  // read rest length in beats
        #ifdef PRINT_SONG_DATA
          Serial.print('('); Serial.print(b); Serial.print(')');
          Serial.print(F(" rest length ")); Serial.print(b); Serial.print(' ');
        #endif
        presetNoteRest[i] = b;  // every note rests this long after being played

        // we now point at the start of the envelope information
        // create envelope out of the following envelope data
        const unsigned char *pEnvelope = createEnvelope(pPreset);
        player.setEnvelopeData(i,pEnvelope);
      } else if (b >= VOLUME_NORMAL && b <= VOLUME_XHIGH) {  // a volume command
        b = 2 - (b - VOLUME_NORMAL);  // now be is volume number
        #ifdef PRINT_SONG_DATA
          Serial.print(F("VOLUME: ")); Serial.print(b); Serial.print(' ');
        #endif
        player.setVolumeDivisor(b);  // change volume in synth
      } else if (b == END_DATA) {  // no more voice data
        voiceCursor[i]--; // continue to point at stop command
        ++voicesStopped;  // this one has stopped
        goto doneDoingVoice;  // quit reading data
      } else if (b == BEAT_DURATION) {  // set the beat duration
        b = pgm_read_byte(voiceCursor[i]++);  // read beat duration byte
        #ifdef PRINT_SONG_DATA
          Serial.print('('); Serial.print(b); Serial.print(')');
          Serial.print(F(" BEAT_DURATION")); Serial.print(b);
        #endif
        voiceBeatDuration[i] = b;
      } else if (b >= WAVE_FIRST && b <= WAVE_LAST) {  // a wave number command
        b -= WAVE_FIRST;  // now b is the wave number
        #ifdef PRINT_SONG_DATA
          Serial.print(F(" WAVE")); Serial.print(b); Serial.print(' ');
        #endif
        player.setWave(i,b);  // change voice in synth
      } else if (b >= OCTAVE_DOWN_2 && b <= OCTAVE_UP_2) {  // transpose
        char t = 12 * (b - OCTAVE_NORMAL);  // how much to transpose - can be negative
        #ifdef PRINT_SONG_DATA
          Serial.print(F(" OCTAVE TRANSPOSE ")); Serial.print((int)t); Serial.print(' ');
        #endif
        voiceTranspose[i] = t;
      } else if (b == START_PRESETS) { // defines list of presets for voice
        #ifdef PRINT_SONG_DATA
          Serial.println(F("\nSTART_PRESETS")); 
        #endif
        // read and store presets until we get to the end
        for (byte p=0; p<NUM_PRESETS; p++) {
          b = pgm_read_byte(voiceCursor[i]++);  // read note length in ticks
          #ifdef PRINT_SONG_DATA
            Serial.print('('); Serial.print(b); Serial.print(')');
          #endif
          if (b == END_PRESETS) {
            #ifdef PRINT_SONG_DATA
              Serial.println(F("END_PRESETS"));
            #endif
            break;  // no more presets
          }
          #ifdef PRINT_SONG_DATA
            Serial.print(F(" preset ")); Serial.print(p+1); Serial.print(F(" address of data: ")); Serial.print((unsigned int)(voiceCursor[i]-1));
          #endif

          // voiceCursor points to one past the start of this preset
          // Store this in the preset list
          pPresets[i*4 + p] = voiceCursor[i]-1;
          #ifdef PRINT_SONG_DATA
            Serial.print(F(" preset pointer index: ")); Serial.println(i*4 + p);
            Serial.print(F(" note length ")); Serial.print(b); Serial.print(' ');
          #endif
          b = pgm_read_byte(voiceCursor[i]++);  // read note length in ticks
          #ifdef PRINT_SONG_DATA
            Serial.print('('); Serial.print(b); Serial.print(')');
            Serial.print(F(" note rest ")); Serial.print(b); Serial.print(' ');
          #endif
          b = pgm_read_byte(voiceCursor[i]++);  // read note length in ticks
          #ifdef PRINT_SONG_DATA
            Serial.print('('); Serial.print(b); Serial.print(')');
            Serial.print(F(" starting volume ")); Serial.print(b); Serial.print(' ');
          #endif

          b = pgm_read_byte(voiceCursor[i]++);  // read note length in ticks
          #ifdef PRINT_SONG_DATA
            Serial.print('('); Serial.print(b); Serial.print(')');
          #endif

          while (b != END_PRESET) {
            #ifdef PRINT_SONG_DATA
              Serial.print(F(" time to next volume ")); Serial.print(b); Serial.print(' ');
            #endif
            b = pgm_read_byte(voiceCursor[i]++);  // read note length in ticks
            #ifdef PRINT_SONG_DATA
              Serial.print('('); Serial.print(b); Serial.print(')');
              Serial.print(F(" next volume ")); Serial.print(b); Serial.print(' ');
            #endif
            b = pgm_read_byte(voiceCursor[i]++);  // read note length in ticks
            #ifdef PRINT_SONG_DATA
              Serial.print('('); Serial.print(b); Serial.print(')');
            #endif
          } // while not end of preset

          #ifdef PRINT_SONG_DATA
            Serial.println(F(" END_PRESET"));
          #endif
        } // read presets
      } else if (b >= SUBSONG_FIRST && b <= SUBSONG_LAST) {  // a subsong number command
        b -= SUBSONG_FIRST;  // now b is the subsong number
        #ifdef PRINT_SONG_DATA
          Serial.print(F("\nSUBSONG")); Serial.println(b+1);
        #endif
        oldVoiceCursor[i] = voiceCursor[i];  // save location in voice data
        voiceCursor[i] = subsongs[b];  // where to start playing
      } else if (b == END_SUBSONG) {  // no more subsong data
        #ifdef PRINT_SONG_DATA
          Serial.println(F("\nEND_SUBSONG")); 
        #endif
        voiceCursor[i] = oldVoiceCursor[i]; // resume playing voice data
      } else {  // unknown command
        #ifdef PRINT_SONG_DATA
          Serial.print(F("\nunknown command ")); Serial.println(b);
        #endif
      } // which command
    } // loop to read stream
    doneDoingVoice: ;  // get out of innter loop when done reading
  } // loop through all voices
  
  // if none of the voices are playing any more, we are done
  if (voicesStopped == NUM_VOICES) {
    #ifdef PRINT_SONG_DATA
      Serial.println(F("synth off"));
    #endif
    synthOff();
  }
} // songTick

/**
 * Create envelope from sound information.  The sound information consists of a number of bytes. 
 * A pointer to this information is passed in the first parameter.  The data is stored in program memory.  
 * The format of the sound information is:
 * - starting volume level
 * - the following 2-byte pairs are repeated until a 0 is in the first byte
 *   - time to next volume level (in terms of envelope entries - one note has 128 entries)
 *   - next volume level
 * 
 * Store the resulting envelope in a 128-byte buffer.  A pointer to the buffer is returned by the function.
 */
unsigned char *createEnvelope(const byte *pInfo) {
  static unsigned char buf[128];
  #ifdef PRINT_SONG_DATA
    Serial.print(F("createEnvelope: address of data: ")); Serial.println((unsigned int)pInfo);
  #endif

  // build envelope data
  const byte *p = pInfo;
  byte *e = buf;  // envelope index
  // note - all volumes will be stored as unsigned integers to make calculations more accurate
  byte b = pgm_read_byte(p++);
  #ifdef PRINT_SONG_DATA
    Serial.print(F(" startingVolume: ")); Serial.print(b);
  #endif
  int startingVolume = b << 6;
  *e++ = startingVolume >> 6;  // first volume in envelope
  int currentVolume = startingVolume;
  int nextVolume = startingVolume;
  while (pgm_read_byte(p) != 0) { // not end of envelope information
    byte timeToNextVolume = pgm_read_byte(p++);
    #ifdef PRINT_SONG_DATA
      Serial.print(F(" timeToNextVolume: ")); Serial.print(timeToNextVolume);
    #endif
    nextVolume = pgm_read_byte(p++) << 6;
    #ifdef PRINT_SONG_DATA
      Serial.print(F(" nextVolume: ")); Serial.print(nextVolume >> 6);
    #endif
    int deltaVolume = (nextVolume - currentVolume) / timeToNextVolume;
    for (byte j=0; j<timeToNextVolume; j++) {
      currentVolume += deltaVolume;
      if (e < (buf + 128)) *e++ = currentVolume >> 6;
    } // store volume change over time in envelope data
  } // read through envelope information
  #ifdef PRINT_SONG_DATA
    Serial.println(F("end of envelope information"));
  #endif

  // make sure entire envelope is filled.  Any unfiled bytes get last volume level
  while (e < (buf + 128)) {
    *e++ = nextVolume >> 6;
  }

  return buf;
}

