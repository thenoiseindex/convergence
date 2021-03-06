/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ConvergenceVstAudioProcessorEditor::ConvergenceVstAudioProcessorEditor (ConvergenceVstAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    // This is where our plugin's editor size is set.
    setSize (400, 300);
    addAndMakeVisible(generateText = new TextButton("Go"));
    addAndMakeVisible(tweetUpdateInterval = new Slider("Tweet update interval"));
    generateText->setBounds(2, 2, 80, 20);
    tweetUpdateInterval->setBounds(2, 24, getWidth()/2, 20);
    tweetUpdateInterval->setRange(5, 30, 1);
    tweetUpdateInterval->setValue(30);
    tweetUpdateInterval->hideTextBox(true);
    tweetUpdateInterval->setSliderStyle(Slider::SliderStyle::LinearBar);
    tweetUpdateInterval->setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    tweetUpdateInterval->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);

    generateText->addListener(this);
    tweetUpdateInterval->addListener(this);
}

ConvergenceVstAudioProcessorEditor::~ConvergenceVstAudioProcessorEditor()
{
}

//==============================================================================
void ConvergenceVstAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

}

void ConvergenceVstAudioProcessorEditor::buttonClicked (Button *button){
    if (button == generateText) {
        static_cast<ConvergenceVstAudioProcessor*>(getAudioProcessor())->generateText();
    }
}

void ConvergenceVstAudioProcessorEditor::sliderValueChanged (Slider *slider){
    if (slider == tweetUpdateInterval) {
        static_cast<ConvergenceVstAudioProcessor*>(getAudioProcessor())->setMaxTweetInterval(slider->getValue());
    }
}
