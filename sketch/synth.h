#ifndef _SYNTH
#define _SYNTH
//*************************************************************************************
//  Arduino synth V4.1
//  Optimized audio driver, modulation engine, envelope engine.
//
//  Dzl/Illutron 2014
//
//*************************************************************************************
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "tables.h"
#include "globals.h"

volatile unsigned int PCW[4] = {0, 0, 0, 0};			//-Wave phase accumolators
volatile unsigned int FTW[4] = {1000, 200, 300, 400};           //-Wave frequency tuning words
volatile unsigned char AMP[4] = {255, 255, 255, 255};           //-Wave amplitudes [0-255]
volatile unsigned int PITCH[4] = {500, 500, 500, 500};          //-Voice pitch
volatile unsigned int WAVE[4];                                  //-Wave table selector [address of wave in memory]
volatile unsigned int EPCW[4] = {0x8000, 0x8000, 0x8000, 0x8000}; //-Envelope phase accumolator
volatile unsigned int EFTW[4] = {10, 10, 10, 10}; //-Envelope speed tuning word
volatile unsigned char voice = 4; //-Sample rate decimator for envelope
volatile unsigned char volumeDivisor = 2;
unsigned char envelopeData[4*128];  // holds current envelope for each voice

//*********************************************************************************************
//  Audio driver interrupt
//*********************************************************************************************

SIGNAL(TIMER1_COMPA_vect)
{
  //-------------------------------
  // Time division
  //-------------------------------
  voice++;
  voice &= 0x03;

  //-------------------------------
  // Volume envelope generator
  //-------------------------------

  if (!(((unsigned char*)&EPCW[voice])[1]&0x80))
    AMP[voice] = *(envelopeData + voice*128 + (((unsigned char*)&(EPCW[voice]+=EFTW[voice]))[1]));
  else
    AMP[voice] = 0;

  //-------------------------------
  //  Synthesizer/audio mixer
  //-------------------------------

  OCR2A = OCR2B = 127 +
    ((
  (((signed char)pgm_read_byte(WAVE[0] + ((unsigned char *)&(PCW[0] += FTW[0]))[1]) * AMP[0]) >> 8) +
    (((signed char)pgm_read_byte(WAVE[1] + ((unsigned char *)&(PCW[1] += FTW[1]))[1]) * AMP[1]) >> 8) +
    (((signed char)pgm_read_byte(WAVE[2] + ((unsigned char *)&(PCW[2] += FTW[2]))[1]) * AMP[2]) >> 8) +
    (((signed char)pgm_read_byte(WAVE[3] + ((unsigned char *)&(PCW[3] += FTW[3]))[1]) * AMP[3]) >> 8)
    ) >> volumeDivisor);

}

class synth
{
private:

public:

  synth()
  {
  }

  //*********************************************************************
  //  Startup 
  //*********************************************************************

  void begin()
  {
    #ifdef PRINT_SONG_DATA
      Serial.println(F("Synth.begin"));
    #endif
    TCCR1A = 0x00;                                  //-Start audio interrupt
    TCCR1B = 0x09;
    TCCR1C = 0x00;
    OCR1A=16000000.0 / FS;			    //-Auto sample rate
    SET(TIMSK1, OCIE1A);                            //-Start audio interrupt
    sei();                                          //-+

    TCCR2A = 0xB3;                                  //-8 bit audio PWM
    TCCR2B = 0x01;                                  // |
    OCR2A = OCR2B = 127;                            //-+
    SET(DDRB, 3);				      //-PWM pin
    SET(DDRD, 3);				      //-PWM pin
  }

  //*********************************************************************
  //  Setup all voice parameters in MIDI range
  //  voice[0-3],wave[0-6],pitch[0-127],envelope[0-4],length[0-127],mod[0-127:64=no mod]
  //*********************************************************************

  void setupVoice(unsigned char v, unsigned char wave, unsigned char pitch, unsigned char env, unsigned char length, unsigned int mod)
  {
    // removed mod from synth
    setWave(v,wave);
    setPitch(v,pitch);
    setEnvelope(v,env);
    setLength(v,length);
  }

  //*********************************************************************
  //  Setup wave [0-6]
  //*********************************************************************

  void setWave(unsigned char v, unsigned char wave)
  {
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.setWave v:")); Serial.print((int)v); Serial.print(' '); Serial.println((int)wave);
    #endif
    switch (wave)
    {
    case TRIANGLE:
      WAVE[v] = (unsigned int)TriangleTable;
      break;
    case SQUARE:
      WAVE[v] = (unsigned int)SquareTable;
      break;
    case SAW:
      WAVE[v] = (unsigned int)SawTable;
      break;
    case RAMP:
      WAVE[v] = (unsigned int)RampTable;
      break;
    case NOISE:
      WAVE[v] = (unsigned int)NoiseTable;
      break;
    default:
      WAVE[v] = (unsigned int)SinTable;
      break;
    }
  }
  //*********************************************************************
  //  Setup Pitch [0-127]
  //*********************************************************************

  void setPitch(unsigned char v,unsigned char MIDInote)
  {
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.setPitch v:")); Serial.print((int)v); Serial.print(' '); Serial.println((int)MIDInote);
    #endif
    PITCH[v]=pgm_read_word(&PITCHS[MIDInote]);
  }

  //*********************************************************************
  //  Setup Envelope [0-4]
  //*********************************************************************

  void setEnvelope(unsigned char v, unsigned char env)
  {
    switch (env)
    {
    case 0:
      memcpy_P((void*)(envelopeData + v*128), (void*)Env0, 128);
      break;
    case 1:
      memcpy_P((void*)(envelopeData + v*128), (void*)Env1, 128);
      break;
    case 2:
      memcpy_P((void*)(envelopeData + v*128), (void*)Env2, 128);
      break;
    case 3:
      memcpy_P((void*)(envelopeData + v*128), (void*)Env3, 128);
      break;
    default:
      memcpy_P((void*)(envelopeData + v*128), (void*)Env0, 128);
      break;
    }
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.setEnvelope v:")); Serial.print((int)v); Serial.print(' '); Serial.println((int)env);
      printEnvelopeData(envelopeData + v*128);
    #endif
  }

  //*********************************************************************
  //  Set Envelope from envelope data
  //*********************************************************************

  void setEnvelopeData(unsigned char v, const unsigned char *data)
  {
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.setEnvelopeData v:")); Serial.println((int)v);
      printEnvelopeData(data);
    #endif
    // memcpy throws a compiler reg pointer allocation error - compiler bug!
//    memcpy(envelopeData + v*128, data, 128);
    for (int i=0; i<128; i++) {
      envelopeData[v*128 + i] = data[i];
    }
  }


  //*********************************************************************
  //  Setup Length [0-128]
  //*********************************************************************

  void setLength(unsigned char v,unsigned char length)
  {
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.setLength v:")); Serial.print((int)v); Serial.print(' '); Serial.println((int)length);
    #endif
    EFTW[v]=pgm_read_word(&EFTWS[length]);
  }

  //*********************************************************************
  //  Midi trigger
  //*********************************************************************

  void mTrigger(unsigned char v,unsigned char MIDInote)
  {
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.mTrigger v:")); Serial.print((int)v); Serial.print(' '); Serial.println((int)MIDInote);
    #endif
    PITCH[v]=pgm_read_word(&PITCHS[MIDInote]);
    EPCW[v]=0;
//asdf    FTW[v] = PITCH[v] + (int)(((PITCH[v]>>6)*(EPCW[v]>>6))/128)*MOD[v];
    FTW[v] = PITCH[v];
  }

  //*********************************************************************
  //  Set frequency direct
  //*********************************************************************

  void setFrequency(unsigned char v,float f)
  {
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.setFrequency v:")); Serial.print((int)v); Serial.print(' '); Serial.println(f);
    #endif
    PITCH[v]=f/(FS/65535.0);

  }

  //*********************************************************************
  //  Set time
  //*********************************************************************

  void setTime(unsigned char v,float t)
  {
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.setTime v:")); Serial.print((int)v); Serial.print(' '); Serial.println(t);
    #endif
    EFTW[v]=(1.0/t)/(FS/(32767.5*10.0));//[s];
  }

  //*********************************************************************
  //  Simple trigger
  //*********************************************************************

  void trigger(unsigned char v)
  {
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.trigger v:")); Serial.println((int)v);
    #endif
    EPCW[v]=0;
    FTW[v]=PITCH[v];
  }

  //*********************************************************************
  //  Set Voice Divisor
  //  This is how much the wave value of each voice is divided in half
  //  This is necessary if several voices are playing simultaneously.  Without
  //  the divisor, the combined value of the voices could be more than the maximum
  //  volume (255).
  //
  // A value of 2 (default) divides each voice wave by 4, so even if all 4 voices are at
  // a maximum value, the total will not overflow (no clipping).  However, the volume
  // can be quiet, especially if less voices are playing at the same time.
  //
  // A value of 1 divides each voice wave by 2.  The volume is twice as loud as above, but it is
  // possible for clipping if more than 2 voices are playing at the same time.
  //
  // A value of 0 does not divide the voice waves, so you get the maximum volume.
  // However, it is much more likely that there will be clipping if more than one voice
  // is playing at the same time.
  //*********************************************************************
  void setVolumeDivisor(unsigned char d) {
    #ifdef PRINT_SONG_DATA
      Serial.print(F("Synth.setVolumeDivisor ")); Serial.println((int)d);
    #endif
    volumeDivisor = d;
  }


  //*********************************************************************
  //  Suspend/resume synth
  //*********************************************************************

  void suspend()
  {
    #ifdef PRINT_SONG_DATA
      Serial.println(F("Synth.suspend"));
    #endif
    CLR(TIMSK1, OCIE1A);                            //-Stop audio interrupt
  }
  void resume()
  {
    #ifdef PRINT_SONG_DATA
      Serial.println(F("Synth.resume"));
    #endif
    SET(TIMSK1, OCIE1A);                            //-Start audio interrupt
  }

};

#endif

