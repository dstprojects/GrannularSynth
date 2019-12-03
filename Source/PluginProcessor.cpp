/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioLupeAudioProcessor::AudioLupeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::mono(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  )
#endif
{
    addParameter( open = new AudioParameterBool("open", "Open", false,"Open"));
    //grain = new GrainEnvelope();
    initializeDSP();
}

AudioLupeAudioProcessor::~AudioLupeAudioProcessor()
{
}

//==============================================================================
const String AudioLupeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioLupeAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AudioLupeAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool AudioLupeAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double AudioLupeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioLupeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int AudioLupeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioLupeAudioProcessor::setCurrentProgram (int index)
{
}

const String AudioLupeAudioProcessor::getProgramName (int index)
{
    return {};
}

void AudioLupeAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AudioLupeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    formatManager.registerBasicFormats();
    grain[0]->initializeEnvelope();
    grain[0]->setSampleRate(getSampleRate());
    grain[1]->initializeEnvelope();
    grain[1]->setSampleRate(getSampleRate());
}

void AudioLupeAudioProcessor::releaseResources()
{
    fileBuffer.setSize (0, 0);
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudioLupeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void AudioLupeAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    
    auto numInputChannels = fileBuffer.getNumChannels();
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    if (ready == true){
        
        for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());
        
        for (auto channel = 0; channel < totalNumOutputChannels; ++channel){
            auto *channelData = buffer.getWritePointer(channel);
            const float *fileData = fileBuffer.getReadPointer(channel);
            grain[channel]->process(channelData, fileData, 0.5, 0.5, getBlockSize(), fileBuffer.getNumSamples());
        }
        
        // This is the place where you'd normally do the guts of your plugin's
        // audio processing...
        // Make sure to reset the state if your inner loop is processing
        // the samples and the outer loop is handling the channels.
        // Alternatively, you can process the samples with the channels
        // interleaved by keeping the same state.
        //auto outputSamplesRemaining = buffer.getNumSamples();                                  // [8]
        //auto outputSamplesOffset = buffer.getWritePointer(0);                                    // [9]
        
        /*while (outputSamplesRemaining > 0)
        {
            auto bufferSamplesRemaining = fileBuffer.getNumSamples() - position;                // [10]
            auto samplesThisTime = jmin (outputSamplesRemaining, bufferSamplesRemaining);       // [11]
            
            for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
            {
                
                //buffer.copyFrom(channel, outputSamplesOffset, &fileBuffer , channel%numInputChannels, position, samplesThisTime);
                
                auto* channelData = buffer.getWritePointer(channel%numInputChannels);
                auto* inputData = fileBuffer.getReadPointer(channel%numInputChannels);

                for(int i = 0; i < buffer.getNumSamples(); i++){
                    channelData[i] = inputData[position+i];
                }
            }
            
            outputSamplesRemaining -= samplesThisTime;                                          // [13]
            outputSamplesOffset += samplesThisTime;                                             // [14]
            position += samplesThisTime;                                                        // [15]
            
            if (position == fileBuffer.getNumSamples())
                position = 0;                                                                   // [16]
        }*/
    }
}

//==============================================================================
bool AudioLupeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AudioLupeAudioProcessor::createEditor()
{
    return new AudioLupeAudioProcessorEditor (*this);
}

//==============================================================================
void AudioLupeAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AudioLupeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void AudioLupeAudioProcessor::openButtonClicked()
{
    //DBG(grain->getInterpolatedSample(0.5f));
    
    FileChooser chooser ("Select a Wave file shorter than 2 seconds to play...",
                         {},
                         "*.wav");
    
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        std::unique_ptr<AudioFormatReader> reader (formatManager.createReaderFor (file)); // [2]
        
        if (reader.get() != nullptr)
        {
            auto duration = reader->lengthInSamples / reader->sampleRate;                 // [3]
            
            if (duration < 300)
            {
                fileBuffer.setSize ((int) reader->numChannels, (int) reader->lengthInSamples);  // [4]
                reader->read (&fileBuffer,                                                      // [5]
                              0,                                                                //  [5.1]
                              (int) reader->lengthInSamples,                                    //  [5.2]
                              0,                                                                //  [5.3]
                              true,                                                             //  [5.4]
                              true);                                                            //  [5.5]
                position = 0;                                                                   // [6]
                ready = true;
                DBG("Done reading");
                //setAudioChannels (0, (int) reader->numChannels);                                // [7]
            }
            else
            {
                ready = false;
                DBG("Audio demasiado grande");
                // handle the error that the file is 2 seconds or longer..
            }
        }
    }
}

void AudioLupeAudioProcessor::clearButtonClicked()
{
    
}

void AudioLupeAudioProcessor::initializeDSP(){
    
    grain[0] = new GrainEnvelope();
    grain[1] = new GrainEnvelope();

}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioLupeAudioProcessor();
}
