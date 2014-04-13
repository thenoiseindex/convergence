/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ConvergenceVstAudioProcessor::ConvergenceVstAudioProcessor()
{
    ttsChannel.setVoice(0);
    ttsChannel.initialize();
    ttsChannel.addChangeListener(this);
    twitterHandler.init();
    twitterHandler.updateTrends();
    twitterHandler.updateTweets();
    
}

ConvergenceVstAudioProcessor::~ConvergenceVstAudioProcessor()
{
}

void ConvergenceVstAudioProcessor::generateText(){
    ttsChannel.addText("Hello");
}

void ConvergenceVstAudioProcessor::setMaxTweetInterval(int interval){
    ttsChannel.setNextTweetTimeMax(interval);
}

void ConvergenceVstAudioProcessor::changeListenerCallback (ChangeBroadcaster* source){
    if(source == &ttsChannel){
        ttsChannel.setVoice(Random::getSystemRandom().nextInt(4));
        ttsChannel.addText(twitterHandler.getRandomTweet());
    }
}

//==============================================================================
const String ConvergenceVstAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int ConvergenceVstAudioProcessor::getNumParameters()
{
    return 0;
}

float ConvergenceVstAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void ConvergenceVstAudioProcessor::setParameter (int index, float newValue)
{
}

const String ConvergenceVstAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String ConvergenceVstAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String ConvergenceVstAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String ConvergenceVstAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool ConvergenceVstAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool ConvergenceVstAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool ConvergenceVstAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ConvergenceVstAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ConvergenceVstAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double ConvergenceVstAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ConvergenceVstAudioProcessor::getNumPrograms()
{
    return 0;
}

int ConvergenceVstAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ConvergenceVstAudioProcessor::setCurrentProgram (int index)
{
}

const String ConvergenceVstAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void ConvergenceVstAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ConvergenceVstAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ConvergenceVstAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void ConvergenceVstAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
   
    ttsChannel.getNextAudioBlock(buffer);
    /*
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);

        // ..do something to the data...
    }
    */
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool ConvergenceVstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ConvergenceVstAudioProcessor::createEditor()
{
    return new ConvergenceVstAudioProcessorEditor (this);
}

//==============================================================================
void ConvergenceVstAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ConvergenceVstAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ConvergenceVstAudioProcessor();
}
