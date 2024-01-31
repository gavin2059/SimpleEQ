/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Processors/Fifo.cpp"
#include "Processors/ChainSettings.h"
#include "Processors/Filters.h"

class SimpleEQAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    SimpleEQAudioProcessor();
    ~SimpleEQAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    /**
        @brief Creates the parameters of this plugin
        @return The parameters created
     */
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts {*this, nullptr, "Parameters", createParameterLayout()};

    using BlockType = juce::AudioBuffer<float>;
    SingleChannelSampleFifo<BlockType> leftChannelFifo {Channel::Left};
    SingleChannelSampleFifo<BlockType> rightChannelFifo {Channel::Right};
    
    private:
    MonoChain leftChain, rightChain;

    /**
        @brief Updates peak filter
        @param chainSettings A reference to the chain settings to update with
     */
    void updatePeakFilter(const ChainSettings& chainSettings);
    
    /**
        @brief Updates low cut filters
        @param chainSettings A reference to the chain settings to update with
     */
    void updateLowCutFilters(const ChainSettings& chainSettings);
    
    /**
        @brief Updates high cut filters
        @param chainSettings A reference to the chain settings to update with
     */
    void updateHighCutFilters(const ChainSettings& chainSettings);
    
    /**
        @brief Updates all filters
     */
    void updateFilters();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessor)
    
};
