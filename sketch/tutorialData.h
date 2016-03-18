// define a simple melody

const byte PROGMEM TEST_NOTES [] = {
  BEAT_DURATION, 16,
  START_PRESETS,
    // 1-beat note - PRESET_1
    254, // length of note in ticks - almost 1 beat
    100,  // rest associated with note - 1 beat
    255, // starting note volume
    END_PRESET,
  END_PRESETS,

  // the melody
  PRESET_1, D5,
  END_DATA
};

const byte PROGMEM SIMPLE_MELODY [] = {
  BEAT_DURATION, 16,
  REST_6, D4, REST_2, // pickup measure
  FS4, REST_3, G4, REST_1, FS4, REST_2, E4, REST_2, // measure 1
  D4, REST_2, E4, REST_2, FS4, REST_2, FS4, REST_2, // measure 2
  A4, REST_3, B4, REST_1,  A4, REST_2, G4, REST_2, // measure 3
  FS4, REST_2, G4, REST_2, A4, REST_2, A4, REST_2, // measure 4
  D4, REST_1, D4, REST_1, D4, REST_1, D4, REST_1, D4, REST_2, E4, REST_2, // measure 5
  D4, REST_2, E4, REST_2, FS4, REST_2, A4, REST_2, // measure 6
  D5, REST_3, B4, REST_1, A4, REST_2, G4, REST_2, // measure 7
  FS4, REST_2, E4, REST_2, D4, REST_2, // measure 8
  END_DATA
};

const byte PROGMEM CONSTANT_VOLUME_NOTES [] = {
  BEAT_DURATION, 16,
  START_PRESETS,
    // 1-beat note - PRESET_1
    14, // length of note in ticks - almost 1 beat
    1,  // rest associated with note - 1 beat
    255, // starting note volume
    END_PRESET,
    // 2-beat note - PRESET_2
    28, // length of note in ticks - almost 2 beats
    2,  // rest associated with note - 2 beats
    255, // starting note volume
    END_PRESET,
    // 3-beat note - PRESET_3
    42, // length of note in ticks - almost 3 beats
    3,  // rest associated with note - 3 beats
    255, // starting note volume
    END_PRESET,
  END_PRESETS,

  // the melody
  REST_6, PRESET_2, D4, // pickup measure
  PRESET_3, FS4, PRESET_1, G4, PRESET_2, FS4, E4, // measure 1
  D4, E4, FS4, FS4, // measure 2
  PRESET_3, A4, PRESET_1, B4, PRESET_2, A4, G4, // measure 3
  FS4, G4, A4, A4, // measure 4
  PRESET_1, D4, D4, D4, D4, PRESET_2, D4, E4, // measure 5
  D4, E4, FS4, A4, // measure 6
  PRESET_3, D5, PRESET_1, B4, PRESET_2, A4, G4, // measure 7
  FS4, E4, D4, // measure 8
  END_DATA
};

const byte PROGMEM CLARINET_NOTES [] = {
  BEAT_DURATION, 16, OCTAVE_UP_1,
  START_PRESETS,
    // 1-beat note - PRESET_1
    14, // length of note in ticks - almost 1 beat
    1,  // rest associated with note - 1 beat
    1, // starting note volume
    20, // time to next volume
    255, // next volume
    98, // time to next volume
    200, // next volume
    10, // time to last volume
    0, // last volume
    END_PRESET,
    // 2-beat note - PRESET_2
    28, // length of note in ticks - almost 2 beats
    2,  // rest associated with note - 2 beats
    1, // starting note volume
    10, // time to next volume
    255, // next volume
    113, // time to next volume
    200, // next volume
    5, // time to last volume
    0, // last volume
    END_PRESET,
    // 3-beat note - PRESET_3
    42, // length of note in ticks - almost 3 beats
    3,  // rest associated with note - 3 beats
    1, // starting note volume
    7, // time to next volume
    255, // next volume
    118, // time to next volume
    200, // next volume
    3, // time to last volume
    0, // last volume
    END_PRESET,
  END_PRESETS,

  // the melody
  REST_6, PRESET_2, D4, // pickup measure
  PRESET_3, FS4, PRESET_1, G4, PRESET_2, FS4, E4, // measure 1
  D4, E4, FS4, FS4, // measure 2
  PRESET_3, A4, PRESET_1, B4, PRESET_2, A4, G4, // measure 3
  FS4, G4, A4, A4, // measure 4
  PRESET_1, D4, D4, D4, D4, PRESET_2, D4, E4, // measure 5
  D4, E4, FS4, A4, // measure 6
  PRESET_3, D5, PRESET_1, B4, PRESET_2, A4, G4, // measure 7
  FS4, E4, D4, // measure 8
  END_DATA
};

const byte PROGMEM FUNKY_NOTES [] = {
  BEAT_DURATION, 48, OCTAVE_UP_1,
  START_PRESETS,
    // 1-beat note - PRESET_1
    42, // length of note in ticks - almost 1 beat
    1,  // rest associated with note - 1 beat
    1, // starting note volume
    16, // time to next volume
    255, // next volume
    16, // time to next volume
    0, // next volume
    16, // time to next volume
    255, // next volume
    16, // time to next volume
    0, // next volume
    16, // time to next volume
    255, // next volume
    16, // time to next volume
    0, // next volume
    16, // time to next volume
    255, // next volume
    16, // time to next volume
    0, // next volume
    END_PRESET,
    // 2-beat note - PRESET_2
    84, // length of note in ticks - almost 2 beats
    2,  // rest associated with note - 2 beats
    1, // starting note volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    END_PRESET,
    // 3-beat note - PRESET_3
    126, // length of note in ticks - almost 3 beats
    3,  // rest associated with note - 3 beats
    1, // starting note volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    END_PRESET,
  END_PRESETS,

  // the melody
  REST_6, PRESET_2, D4, // pickup measure
  PRESET_3, FS4, PRESET_1, G4, PRESET_2, FS4, E4, // measure 1
  D4, E4, FS4, FS4, // measure 2
  PRESET_3, A4, PRESET_1, B4, PRESET_2, A4, G4, // measure 3
  FS4, G4, A4, A4, // measure 4
  PRESET_1, D4, D4, D4, D4, PRESET_2, D4, E4, // measure 5
  D4, E4, FS4, A4, // measure 6
  PRESET_3, D5, PRESET_1, B4, PRESET_2, A4, G4, // measure 7
  FS4, E4, D4, // measure 8
  END_DATA
};

// ***************** MULTIPLE PART SONG ************************

const byte PROGMEM SONG_MELODY [] = {
  PRESET_2, D4, // pickup measure
  PRESET_3, FS4, PRESET_1, G4, PRESET_2, FS4, E4, // measure 1
  D4, E4, FS4, FS4, // measure 2
  PRESET_3, A4, PRESET_1, B4, PRESET_2, A4, G4, // measure 3
  FS4, G4, A4, A4, // measure 4
  PRESET_1, D4, D4, D4, D4, PRESET_2, D4, E4, // measure 5
  D4, E4, FS4, A4, // measure 6
  PRESET_3, D5, PRESET_1, B4, PRESET_2, A4, G4, // measure 7
  FS4, E4, D4, // measure 8
  END_SUBSONG
};

const byte PROGMEM SONG_PRESETS_A [] = {
  START_PRESETS,
    // 1-beat note - PRESET_1
    14, // length of note in ticks - almost 1 beat
    1,  // rest associated with note - 1 beat
    255, // starting note volume
    END_PRESET,
    // 2-beat note - PRESET_2
    28, // length of note in ticks - almost 2 beats
    2,  // rest associated with note - 2 beats
    255, // starting note volume
    END_PRESET,
    // 3-beat note - PRESET_3
    42, // length of note in ticks - almost 3 beats
    3,  // rest associated with note - 3 beats
    255, // starting note volume
    END_PRESET,
  END_PRESETS,
  END_SUBSONG
};

const byte PROGMEM SONG_PRESETS_B [] = {
  START_PRESETS,
    // 1-beat note - PRESET_1
    14, // length of note in ticks - almost 1 beat
    1,  // rest associated with note - 1 beat
    1, // starting note volume
    20, // time to next volume
    255, // next volume
    98, // time to next volume
    200, // next volume
    10, // time to last volume
    0, // last volume
    END_PRESET,
    // 2-beat note - PRESET_2
    28, // length of note in ticks - almost 2 beats
    2,  // rest associated with note - 2 beats
    1, // starting note volume
    10, // time to next volume
    255, // next volume
    113, // time to next volume
    200, // next volume
    5, // time to last volume
    0, // last volume
    END_PRESET,
    // 3-beat note - PRESET_3
    42, // length of note in ticks - almost 3 beats
    3,  // rest associated with note - 3 beats
    1, // starting note volume
    7, // time to next volume
    255, // next volume
    118, // time to next volume
    200, // next volume
    3, // time to last volume
    0, // last volume
    END_PRESET,
  END_PRESETS,
  END_SUBSONG
};

const byte PROGMEM SONG_PRESETS_C [] = {
  START_PRESETS,
    // 1-beat note - PRESET_1
    42, // length of note in ticks - almost 1 beat
    1,  // rest associated with note - 1 beat
    1, // starting note volume
    16, // time to next volume
    255, // next volume
    16, // time to next volume
    0, // next volume
    16, // time to next volume
    255, // next volume
    16, // time to next volume
    0, // next volume
    16, // time to next volume
    255, // next volume
    16, // time to next volume
    0, // next volume
    16, // time to next volume
    255, // next volume
    16, // time to next volume
    0, // next volume
    END_PRESET,
    // 2-beat note - PRESET_2
    84, // length of note in ticks - almost 2 beats
    2,  // rest associated with note - 2 beats
    1, // starting note volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    8, // time to next volume
    255, // next volume
    8, // time to next volume
    0, // next volume
    END_PRESET,
    // 3-beat note - PRESET_3
    126, // length of note in ticks - almost 3 beats
    3,  // rest associated with note - 3 beats
    1, // starting note volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    5, // time to next volume
    255, // next volume
    5, // time to next volume
    0, // next volume
    END_PRESET,
  END_PRESETS,
  END_SUBSONG
};

// define pieces of a song
const byte *SUBSONG_LIST [] = {
  SONG_MELODY,  // subsong 1
  SONG_PRESETS_A,  // subsong 2
  SONG_PRESETS_B,  // subsong 3
  SONG_PRESETS_C   // subsong 4
};

const byte PROGMEM SONG_VOICE_1 [] = {
  BEAT_DURATION, 16,
  SUBSONG_2,  // presets A
  SUBSONG_1,  // play the melody
  SUBSONG_3,  // presets B
  SUBSONG_1,  // play the melody
  SUBSONG_4,  // presets C
  SUBSONG_1,  // play the melody
  END_DATA
};

// voice tracks
const byte *SONG_ALL [] = {
  SONG_VOICE_1,
  EMPTY_VOICE,
  EMPTY_VOICE,
  EMPTY_VOICE
};


// ***************** END OF MULTIPLE PART SONG ************************


// ***************** MULTIPLE PART ROUND ************************

// define the groups of presets as a subsong
const byte PROGMEM ROUND_PRESETS_A [] = {
  START_PRESETS,
    // 1-beat note - PRESET_1
    14, // length of note in ticks - almost 1 beat
    1,  // rest associated with note - 1 beat
    1, // starting note volume
    20, // time to next volume
    150, // next volume
    98, // time to next volume
    150, // next volume
    10, // time to last volume
    0, // last volume
    END_PRESET,
    // 2-beat note - PRESET_2
    28, // length of note in ticks - almost 2 beats
    2,  // rest associated with note - 2 beats
    1, // starting note volume
    10, // time to next volume
    150, // next volume
    113, // time to next volume
    150, // next volume
    5, // time to last volume
    0, // last volume
    END_PRESET,
    // 3-beat note - PRESET_3
    42, // length of note in ticks - almost 3 beats
    3,  // rest associated with note - 3 beats
    1, // starting note volume
    7, // time to next volume
    150, // next volume
    118, // time to next volume
    150, // next volume
    3, // time to last volume
    0, // last volume
    END_PRESET,
  END_PRESETS,
  END_SUBSONG
};

const byte PROGMEM ROUND_PRESETS_B [] = {
  // this preset makes all notes decay at the same rate, so notes are all the same length.
  // They do define different default rests so that we can have different length notes in the
  // song.
  START_PRESETS,
    // 1-beat note - PRESET_1
    28, // length of note in ticks - almost 2 beats
    1,  // rest associated with note - 1 beat
    255, // starting note volume
    127, // time to next volume
    0, // next volume
    END_PRESET,
    // 2-beat note - PRESET_2
    28, // length of note in ticks - almost 2 beats
    2,  // rest associated with note - 2 beats
    255, // starting note volume
    127, // time to next volume
    0, // next volume
    END_PRESET,
    // 3-beat note - PRESET_3
    28, // length of note in ticks - almost 2 beats
    3,  // rest associated with note - 3 beats
    255, // starting note volume
    127, // time to next volume
    0, // next volume
    END_PRESET,
    // 4-beat note - PRESET_4
    28, // length of note in ticks - almost 2 beats
    4,  // rest associated with note - 4 beats
    255, // starting note volume
    127, // time to next volume
    0, // next volume
    END_PRESET,
  END_PRESETS,
  END_SUBSONG
};

// define pieces of the song notes as subsongs

const byte PROGMEM ROUND_MELODY [] = {
  PRESET_2, D4, // pickup measure
  PRESET_3, FS4, PRESET_1, G4, PRESET_2, FS4, E4, // measure 1
  D4, E4, FS4, FS4, // measure 2
  PRESET_3, A4, PRESET_1, B4, PRESET_2, A4, G4, // measure 3
  FS4, G4, A4, A4, // measure 4
  PRESET_1, D4, D4, D4, D4, PRESET_2, D4, E4, // measure 5
  D4, E4, FS4, A4, // measure 6
  PRESET_3, D5, PRESET_1, B4, PRESET_2, A4, G4, // measure 7
  FS4, E4, D4, // measure 8 except pickup
  END_SUBSONG
};

const byte PROGMEM ROUND_BASS [] = {
  REST_2,  // pickup measure
  PRESET_2, D3, A3, A2, A3, // measure 1
  D3, A3, PRESET_4, A2, // measure 2
  PRESET_2, FS3, A3, CS3, A3, // measure 3
  D3, E3, PRESET_4, FS3, // measure 4
  PRESET_2, D3, FS3, A3, G3, // measure 5
  FS3, G3, PRESET_4, A3, // measure 6
  A2, PRESET_2, A2, G3, // measure 7
  A3, G3, PRESET_4, FS3, // measure 8 except pickup
  
  END_SUBSONG
};

// define list of all subsongs
const byte *ROUND_SUBSONG_LIST [] = {
  ROUND_PRESETS_A,  // subsong 1
  ROUND_PRESETS_B,  // subsong 2
  ROUND_MELODY, // subsong 3
  ROUND_BASS // subsong 4
};

const byte PROGMEM ROUND_VOICE_1 [] = {
  BEAT_DURATION, 16,
  SUBSONG_1,  // presets A
  WAVE_RAMP,
  SUBSONG_3,  // play the melody
  SUBSONG_3,  // play the melody
  END_DATA
};

const byte PROGMEM ROUND_VOICE_2 [] = {
  BEAT_DURATION, 16,
  SUBSONG_2,  // presets B
  WAVE_SAW,
  SUBSONG_4, // play base part
  SUBSONG_1,  // presets A
  WAVE_RAMP,
  OCTAVE_DOWN_1,
  REST_14, // rest quarter verse minus pickup
  SUBSONG_3,  // play the melody
  END_DATA
};

const byte PROGMEM ROUND_VOICE_3 [] = {
  BEAT_DURATION, 16,
  SUBSONG_1,  // presets A
  WAVE_SINE,
  OCTAVE_UP_1,
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  SUBSONG_3,  // play the melody
  END_DATA
};

const byte PROGMEM ROUND_VOICE_4 [] = {
  BEAT_DURATION, 16,
  SUBSONG_1,  // presets A
  WAVE_SAW,
  OCTAVE_DOWN_2,
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  REST_16, // rest quarter verse
  SUBSONG_3,  // play the melody
  END_DATA
};

// voice tracks
const byte *ROUND_ALL [] = {
  ROUND_VOICE_1,
  ROUND_VOICE_2,
  ROUND_VOICE_3,
  ROUND_VOICE_4
};


// ***************** END OF MULTIPLE PART ROUND ************************


