/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/RotarySliderWithLabels.h"

struct ResponseCurveComponent;

/**
*/
class SimpleEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleEQAudioProcessor& audioProcessor;
    
    RotarySliderWithLabels peakFreqSlider, peakGainSlider, peakQualitySlider,
    lowCutFreqSlider, highCutFreqSlider,
    lowCutSlopeSlider, highCutSlopeSlider;
    
    std::unique_ptr<ResponseCurveComponent> responseCurveComponentPtr;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;
    
    
    Attachment peakFreqSliderAttachment, peakGainSliderAttachment, peakQualitySliderAttachment,
    lowCutFreqSliderAttachment, highCutFreqSliderAttachment,
    lowCutSlopeSliderAttachment, highCutSlopeSliderAttachment;
    
    juce::ToggleButton lowcutBypassButton, peakBypassButton, highcutBypassButton, analyzerEnabledButton;
    
    using ButtonAttachment = APVTS::ButtonAttachment;
    ButtonAttachment lowcutBypassButtonAttachment, peakBypassButtonAttachment, highcutBypassButtonAttachment, analyzerEnabledButtonAttachment;
    
    std::vector<juce::Component*> getComps();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessorEditor)
};
