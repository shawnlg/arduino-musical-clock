#ifndef _GLOBALS
#define _GLOBALS

// debug flags
//#define PRINT_SONG_DATA  // print instead of play

// synth constants
#define DIFF 1
#define CHB 3

#define SINE     0
#define TRIANGLE 1
#define SQUARE   2
#define SAW      3
#define RAMP     4
#define NOISE    5

#define ENVELOPE0 0
#define ENVELOPE1 1
#define ENVELOPE2 2
#define ENVELOPE3 3

#define CLOCK_FREQ 16000000.0  // clock speed
#define FS 20000.0 // Sample rate (NOTE: must match tables.h)

// bit twiddlers
#define SET(x,y) (x |=(1<<y))                //-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))             // |
#define CHK(x,y) (x & (1<<y))                 // |
#define TOG(x,y) (x^=(1<<y))                  //-+

// player constants
#define NUM_VOICES 4  // max number of simultaneous voices
#define TICK_DURATION 10  // tick is one hundredth of a second

// default values
#define DEFAULT_BEAT_DURATION 25  // 4 beats per second
#define DEFAULT_WAVE 3
#define DEFAULT_ENVELOPE 3
#define DEFAULT_NOTE_LENGTH 80
#define DEFAULT_NOTE_MOD 64  // no mod

// voice data stream commands
#define END_DATA 0  // end of voice data
#define END_SUBSONG 255  // end of subsong data - back to voice data
#define BEAT_DURATION 1  // length of beat for a stream in ticks
#define START_PRESETS 2  // start of list of presets
#define END_PRESET 0  // end of single preset
#define END_PRESETS 0  // end of list of presets
#define VOLUME_NORMAL 4  // all 4 voices can play without clipping
#define VOLUME_HIGH 5  // 2 voices can play without clipping
#define VOLUME_XHIGH 6  // 1 voice can play without clipping
#define WAVE_FIRST 7  // command for wave 0
#define WAVE_SINE 7  // command for wave 0
#define WAVE_TRIANGLE 8  // command for wave 1
#define WAVE_SQUARE 9  // command for wave 2
#define WAVE_SAW 10  // command for wave 3
#define WAVE_RAMP 11  // command for wave 4
#define WAVE_NOISE 12  // command for wave 5
#define WAVE_LAST 12  // command for wave 5
#define OCTAVE_DOWN_2 13  // key change down 2 octives
#define OCTAVE_DOWN_1 14  // key change down 1 octive
#define OCTAVE_NORMAL 15  // key change back to original key
#define OCTAVE_UP_1 16  // key change up 1 octive
#define OCTAVE_UP_2 17  // key change up 2 octives
#define NOTE_FIRST 21  // command for midi note 21
#define NOTE_LAST 108  // command for midi note 108
#define PRESET_FIRST 115  // preset 1
#define PRESET_1 115  // preset 1
#define PRESET_2 116  // preset 2
#define PRESET_3 117  // preset 3
#define PRESET_4 118  // preset 4
#define PRESET_5 119  // preset 5
#define PRESET_6 120  // preset 6
#define PRESET_7 121  // preset 7
#define PRESET_8 122  // preset 8
#define PRESET_9 123  // preset 9
#define PRESET_10 124  // preset 10
#define PRESET_LAST 124  // preset 10
#define REST_0 149  // command for delay beats - low range - 1
#define REST_1 150
#define REST_2 151
#define REST_3 152
#define REST_4 153
#define REST_5 154
#define REST_6 155
#define REST_7 156
#define REST_8 157
#define REST_9 158
#define REST_10 159
#define REST_11 160
#define REST_12 161
#define REST_13 162
#define REST_14 163
#define REST_15 164
#define REST_16 165
#define REST_17 166
#define REST_18 167
#define REST_19 168
#define REST_20 169
#define REST_21 170
#define REST_22 171
#define REST_23 172
#define REST_24 173
#define REST_25 174
#define REST_26 175
#define REST_27 176
#define REST_28 177
#define REST_29 178
#define REST_30 179
#define REST_31 180
#define REST_32 181
#define REST_33 182
#define REST_34 183
#define REST_35 184
#define REST_36 185
#define REST_37 186
#define REST_38 187
#define REST_39 188
#define REST_40 189
#define REST_41 190
#define REST_42 191
#define REST_43 192
#define REST_44 193
#define REST_45 194
#define REST_46 195
#define REST_47 196
#define REST_48 197
#define REST_49 198
#define REST_50 199
#define REST_MAX 199  // command for delay beats - high range
#define SUBSONG_FIRST 200
#define SUBSONG_1 200
#define SUBSONG_2 201
#define SUBSONG_3 202
#define SUBSONG_4 203
#define SUBSONG_5 204
#define SUBSONG_6 205
#define SUBSONG_7 206
#define SUBSONG_8 207
#define SUBSONG_9 208
#define SUBSONG_10 209
#define SUBSONG_11 210
#define SUBSONG_12 211
#define SUBSONG_13 212
#define SUBSONG_14 213
#define SUBSONG_15 214
#define SUBSONG_16 215
#define SUBSONG_17 216
#define SUBSONG_18 217
#define SUBSONG_19 218
#define SUBSONG_20 219
#define SUBSONG_21 220
#define SUBSONG_22 221
#define SUBSONG_23 222
#define SUBSONG_24 223
#define SUBSONG_25 224
#define SUBSONG_26 225
#define SUBSONG_27 226
#define SUBSONG_28 227
#define SUBSONG_29 228
#define SUBSONG_30 229
#define SUBSONG_31 230
#define SUBSONG_32 231
#define SUBSONG_33 232
#define SUBSONG_34 233
#define SUBSONG_35 234
#define SUBSONG_36 235
#define SUBSONG_37 236
#define SUBSONG_38 237
#define SUBSONG_39 238
#define SUBSONG_40 239
#define SUBSONG_41 240
#define SUBSONG_42 241
#define SUBSONG_43 242
#define SUBSONG_44 243
#define SUBSONG_45 244
#define SUBSONG_46 245
#define SUBSONG_47 246
#define SUBSONG_48 247
#define SUBSONG_49 248
#define SUBSONG_50 249
#define SUBSONG_LAST 249


boolean playingSong = false;

const byte PROGMEM EMPTY_VOICE [] = {
  END_DATA
};

const byte *EMPTY_SUBSONG_LIST [] = {
};

#endif

