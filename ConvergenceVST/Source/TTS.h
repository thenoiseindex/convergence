/*
  ==============================================================================

    TTS.h
    Created: 3 May 2013 11:42:30pm
    Author:  Jordan Hochenbaum & Owen Vallis

  ==============================================================================
*/

#ifndef __TTS_H_ABF67C39__
#define __TTS_H_ABF67C39__

//#define USE_FESTIVAL_SERVER
#define USE_FLITE

#include "flite.h"
#include "JuceHeader.h"
#include <queue>


class TTS : public ChangeBroadcaster, public Timer, public Thread {
public:
	TTS();
    ~TTS();
    
	void initialize();
    
	void addText(String text);
    void setVoice(int voiceToSet);
    void setNextTweetTimeMax(int interval);
	void convertToAudio(String text, int samplingRate);
    
    void getNextAudioBlock (AudioSampleBuffer &bufferToFill);
    void timerCallback();
    
    void run();
    void setOutputChannel(int chan){outputChannel = chan;};
    
private:
    bool bufferReady;
    
	cst_voice *voice;
    
    std::queue <String> texts;

	AudioSampleBuffer ttsBuffer; //ofSoundBuffer soundBuffer;
    AudioSampleBuffer upsampledTTSBuffer;
    int samplesProcessed;
    
    int nextTweetTimeMax;
    
    String textToConvert;
    
    int outputChannel;
};

#endif  // __TTS_H_ABF67C39__
