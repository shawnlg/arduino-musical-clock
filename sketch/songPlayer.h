
//-----------------------------------------------
// Start playing a note on a particular channel
//-----------------------------------------------
void playNote (byte voice, byte note) {
  Serial.print("mTrigger ");
  Serial.print(voice);
  Serial.print(" ");
  Serial.println(note);
  player.mTrigger(voice,note);
}

//-----------------------------------------------
// Stop playing a note on a particular channel
//-----------------------------------------------
void stopNote (byte voice) {
}

unsigned long songDelayLength, songDelayStart;  // no more note data until after this time
const byte *songStart = 0;  // start of song data
const byte *songCursor = 0;  // current position in song data

// called to start playing a song
void playSong (const byte *score) {
  songStart = score;
  songCursor = score;
  songDelayLength = 0;  // no dealy, start reading data immediately
  songDelayStart = millis();  // no dealy, start reading data immediately
  synthOn();
}

// info about song data
#define CMD_PLAYNOTE  0x90  /* play a note: low nibble is generator #, note is next byte */
#define CMD_STOPNOTE  0x80  /* stop a note: low nibble is generator # */
#define CMD_RESTART 0xe0  /* restart the score from the beginning */
#define CMD_STOP  0xf0  /* stop playing */
/* if CMD < 0x80, then the other 7 bits and the next byte are a 15-bit big-endian number of msec to wait */

// called repeatedly to coordinate the notes of a song
void songTick() {
  // we are pointed at the song data where we continue playing
  byte cmd, opcode, chan;
  unsigned int duration;

  unsigned long now = millis();  // current time used in song delays
  if (songDelayStart + songDelayLength > now) {
    return;  // not time to read more data
  }

  for (;;) { // loop until we get a delay
    //Serial.print("songCursor "); Serial.println((unsigned int)songCursor - (unsigned int)songStart);
    //Serial.print("readByte "); Serial.println(pgm_read_byte(songCursor), HEX);
    cmd = pgm_read_byte(songCursor++);
    if (cmd < 0x80) { /* wait count in msec. */
      //Serial.print("readByte "); Serial.println(pgm_read_byte(songCursor));
      duration = ((unsigned)cmd << 8) | (pgm_read_byte(songCursor++));
      songDelayLength = duration;  // song delay
      songDelayStart = now;
      //Serial.print("delay "); Serial.println(duration);
      return;
    }

    opcode = cmd & 0xf0;
    chan = cmd & 0x0f;
  
    if (opcode == CMD_STOPNOTE) { /* stop note */
      //Serial.print("stopNote "); Serial.println(chan);
      stopNote (chan);
    } else if (opcode == CMD_PLAYNOTE) { /* play note */
      //Serial.print("readByte "); Serial.println(pgm_read_byte(songCursor), HEX);
      byte note = pgm_read_byte(songCursor++);
      //Serial.print("playNote "); Serial.print(chan); Serial.print(" "); Serial.println(note);
      playNote (chan, note);
    } else if (opcode == CMD_RESTART) { /* restart score */
      //Serial.println("restart");
      songCursor = songStart;
    } else if (opcode == CMD_STOP) { /* stop score */
      //Serial.println("song end");
      synthOff();
      songCursor--;  // stay on the stop command
      return;
    } // which opcode
    
  } // loop forever
} // songTick

