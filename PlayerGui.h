#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"
 
/*

* PlayerGUI.h
* -----------------------------
* Handles the GRAPHICAL USER INTERFACE of the player.
*/

class PlayerGui 
        :public juce::Component,
        public juce::Button::Listener,
        public juce::Slider::Listener
    {
    public:
        PlayerGui();
        ~PlayerGui() override;

        void paint(juce::Graphics& g) override;
        void resized() override;

        // Audio setup
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
        void releaseResources();

    private:
        // GUI controls
        juce::TextButton loadButton { "Load" };
        juce::TextButton playButton { "Play" };
        juce::TextButton stopButton { "Stop" };
        juce::Slider volumeSlider;

        // Audio engine
        juce::AudioTransportSource transportSource;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::AudioFormatManager formatManager;
        std::unique_ptr<juce::FileChooser> fileChooser;

        // Event handlers
        void buttonClicked(juce::Button* button) override;
        void sliderValueChanged(juce::Slider* slider) override;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGui)
};
