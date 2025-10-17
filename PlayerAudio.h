#pragma once
#include <JuceHeader.h>


/*
 * PlayerAudio.h
 * -----------------------------
 * Handles the AUDIO logic (backend) of the player.
 */

class PlayerAudio {
private:


    // Audio
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)
public:
    PlayerAudio();
    ~PlayerAudio();
    //Audio

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    bool loadFile(const juce::File& file);
    void play();
    void stop();
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition() const;
    double getLength() const;





};
