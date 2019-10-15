/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), openButton("Open"), playButton("Play"), stopButton("Stop"),  state(Stopped)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 300);
    formatManager.registerBasicFormats();
    
    openButton.onClick = [this] {openButtonClicked();};
    addAndMakeVisible(&openButton);
    
    playButton.onClick = [this] {playButtonClicked();};
    playButton.setColour(TextButton::buttonColourId, Colours::green);
    playButton.setEnabled(true);
    addAndMakeVisible(&playButton);
    
    stopButton.onClick = [this] {stopButtonClicked();};
    stopButton.setColour(TextButton::buttonColourId, Colours::red);
    stopButton.setEnabled(false);
    addAndMakeVisible(&stopButton);
    
    
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor:: openButtonClicked(){
    
    //DBG("CLICKED");
    
    //chose a file
    FileChooser chooser("Choose a Wave or AIFF File", File::getSpecialLocation(File::userDesktopDirectory), "*.wav", true, false, nullptr);

    //if the user chooses a file
    if (chooser.browseForFileToOpen()){
        
        File myFile;
        
        //what did the user choose?
        myFile = chooser.getResult();
        //read the file
        AudioFormatReader* reader = formatManager.createReaderFor(myFile);
        //get the file ready to play
        std:: unique_ptr<AudioFormatReaderSource> tempSource (new AudioFormatReaderSource(reader, true));
        playSource.reset(tempSource.release());
        
        
        DBG(reader -> getFormatName());
        
    }
    
}


void SynthAudioProcessorEditor:: playButtonClicked(){
    
    
    
}

void SynthAudioProcessorEditor:: stopButtonClicked(){
    
    
    
}


void SynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void SynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    openButton.setBounds(10, 10, getWidth() - 20, 30);
    playButton.setBounds(10, 50, getWidth() - 20, 30);
    stopButton.setBounds(10, 90, getWidth() - 20, 30);
}

