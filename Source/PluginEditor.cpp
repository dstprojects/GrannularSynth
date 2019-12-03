/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioLupeAudioProcessorEditor::AudioLupeAudioProcessorEditor (AudioLupeAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    auto& params = processor.getParameters();
    //AudioParameterBool* open = (AudioParameterBool*)params.getUnchecked(0);
    
    addAndMakeVisible (openButton);
    openButton.setButtonText ("Open...");
    
    openButton.onClick = [this] { processor.openButtonClicked(); };
    
    //addAndMakeVisible (clearButton);
    //clearButton.setButtonText ("Clear");
    //clearButton.onClick = [this] { processor.clearButtonClicked(); };
}

AudioLupeAudioProcessorEditor::~AudioLupeAudioProcessorEditor()
{
}

//==============================================================================
void AudioLupeAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void AudioLupeAudioProcessorEditor::resized()
{
    openButton .setBounds (10, 10, getWidth() - 20, 20);
    clearButton.setBounds (10, 40, getWidth() - 20, 20);
}
