/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_63B83F4C__
#define __PLUGINPROCESSOR_H_63B83F4C__

#include "../JuceLibraryCode/JuceHeader.h"
#include "TTS.h"
#include "TwitterHandler.h"


//==============================================================================
/**
*/
class ConvergenceVstAudioProcessor  : public AudioProcessor, public ChangeListener
{
public:
    //==============================================================================
    ConvergenceVstAudioProcessor();
    ~ConvergenceVstAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    
    void generateText();
    void setMaxTweetInterval(int interval);
    void changeListenerCallback (ChangeBroadcaster* source);

private:
    TTS ttsChannel;
    TwitterHandler twitterHandler;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvergenceVstAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_63B83F4C__
