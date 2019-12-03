/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AudioLupeAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TextButton openButton;
    TextButton clearButton;
    
    AudioLupeAudioProcessorEditor (AudioLupeAudioProcessor&);
    ~AudioLupeAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    
    AudioLupeAudioProcessor& processor;
   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioLupeAudioProcessorEditor)
};
