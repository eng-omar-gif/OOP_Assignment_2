#pragma once

#include "PlayerGui.h"
#include <JuceHeader.h>

#include <vector>

/*
 * MainComponent.h
 * -----------------------------
 * This is the main container of the application.
 *
 * - It holds the main layout of the app.
 * - It creates and displays PlayerGUI (the visual part of the player).
 * - It can contain multiple PlayerGUI components (for Task 4 bonus).
*/

class MainComponent : public juce::AudioAppComponent,
                      public juce::Button::Listener,
                      public juce::Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    // Audio
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // GUI
    void paint(juce::Graphics& g) override;
    void resized() override;

    // Event handlers
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // Audio
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    // GUI Controls
    juce::TextButton loadButton { "Load Files" };
    juce::TextButton restartButton { "Restart" };
    juce::TextButton stopButton { "Stop" };
    juce::Slider volumeSlider;

    //void loadTrack(const juce::File& file);
    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};