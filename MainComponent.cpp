#include "MainComponent.h"
#include "PlayerGui.h"

/*
 * MainComponent.cpp
 * -----------------------------
 * This file implements MainComponent.
 *
 * - Initialize and display PlayerGUI.
 * - Define how components are drawn (background, layout).
 * - Handle resizing (place the player correctly in the window).
 */

MainComponent::MainComponent()
{
    addAndMakeVisible(player1);

    setSize(600, 400);
    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    player1.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
}

void MainComponent::resized()
{
    player1.setBounds(20, 20, getWidth() - 40, 120);
