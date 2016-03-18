#include "globals.h"
#include "synth.h"
#include "notes.h"
#include "tutorialData.h"

void setup()
{
  Serial.begin(9600);
//  synthTest2();
//  playSingleVoice(TEST_NOTES);
//  playSong(SCORE_1, SCORE_1_SUBSONG_LIST);
//  playSingleVoice(SIMPLE_MELODY);  
//  playSingleVoice(CONSTANT_VOLUME_NOTES);  
//  playSingleVoice(CLARINET_NOTES);
//  playSingleVoice(FUNKY_NOTES);
//  playSong(SONG_ALL, SUBSONG_LIST);
  playSong(ROUND_ALL, ROUND_SUBSONG_LIST);
}

void loop() {
  if (playingSong) {
    songTick();
  }
}

