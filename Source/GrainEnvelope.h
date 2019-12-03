/*
  ==============================================================================

    GrainEnvelope.h
    Created: 6 Nov 2019 5:46:25pm
    Author:  Alexis Uriel Guerrero Montoya

  ==============================================================================
*/

#pragma once
#include "Helpers.h"

class GrainEnvelope
{

public:
	GrainEnvelope();
	~GrainEnvelope();

	void process(
		float* currentBlock,
		const float* fileBuffer,
		float duration,
		float position,
		int blockNumSamples,
		int fileNumSamples
	);

	void reset();
	void setSampleRate(int inSampleRate);
	void initializeEnvelope();
	double getInterpolatedSample(float readPosition);
	double getInterpolatedPositionSample(float, float*);


private:

	float mSamplerate;
	float grainBuffer[grainEnvelopeSize];
	int currentPositionInFileBuffer;
	float currentPositionInEnvelope;
    int initialPosition;
    int contador;
};
    

    

