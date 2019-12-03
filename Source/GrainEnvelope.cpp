/*
  ==============================================================================

    GrainEnvelope.cpp
    Created: 6 Nov 2019 5:46:25pm
    Author:  Alexis Uriel Guerrero Montoya

  ==============================================================================
*/

#include "GrainEnvelope.h"
#include "JuceHeader.h"


GrainEnvelope::GrainEnvelope(){
    reset();
    initializeEnvelope();

	currentPositionInFileBuffer = 0;
	currentPositionInEnvelope = 0;
    
    initialPosition = 0;
    contador = 0;
}

GrainEnvelope::~GrainEnvelope(){
    
}

void GrainEnvelope::initializeEnvelope(){
    
    for(int i = 0; i < grainEnvelopeSize; i++){
        grainBuffer[i] = 0.5+0.5* std::sin(my2PI*i/grainEnvelopeSize - myPI/2);
    }
    
}

void GrainEnvelope::reset(){
    zeromem(grainBuffer, sizeof(float)*grainEnvelopeSize);
}

void GrainEnvelope::setSampleRate(int inSampleRate){
    mSamplerate = inSampleRate;
}

double GrainEnvelope::getInterpolatedSample(float readPosition){
    
    if (readPosition >= 0 && readPosition <= grainEnvelopeSize - 1){
        int index_x0 = (int)readPosition;
        int index_x1 = index_x0+1;
        
        float t = readPosition - index_x0;
        
        const float sample_y0 = grainBuffer[index_x0];
        const float sample_y1 = grainBuffer[index_x1];
        
        return lerp(sample_y0, sample_y1, t);
        
    }
}

void GrainEnvelope::process(float *currentBlock, const float *fileBuffer, float duration, float position, int blockNumSamples, int fileNumSamples){
	
	int positionInSamples = position*fileNumSamples;

	int durationInSamples = duration * mSamplerate;

	initialPosition = positionInSamples - durationInSamples / 2;

	float step = (float)grainEnvelopeSize / (float)durationInSamples;

	if (positionInSamples < durationInSamples / 2)
	{
		initialPosition = durationInSamples / 2;

	}

	if (positionInSamples > fileNumSamples - durationInSamples / 2)
	{
		initialPosition = fileNumSamples - durationInSamples / 2; 
	}

	currentPositionInFileBuffer = initialPosition + contador*blockNumSamples;


	for (int i = 0; i < blockNumSamples; i++)
	{
        if(currentPositionInEnvelope < grainEnvelopeSize-1){
            currentBlock[i] = fileBuffer[currentPositionInFileBuffer]*getInterpolatedSample(currentPositionInEnvelope);
            currentPositionInEnvelope += step;
            currentPositionInFileBuffer += 1;
            
        }else{
            currentPositionInEnvelope = 0;
            initialPosition = positionInSamples - durationInSamples / 2;
            currentPositionInFileBuffer = initialPosition;
            contador = 0;
            //DBG("Jalisco");
            break;
        }
	}
    contador++;

};

double GrainEnvelope::getInterpolatedPositionSample(float initPosition, float* fileBuffer) {

		int index_x0 = (int)initPosition;
		int index_x1 = index_x0 + 1;

		float t = initPosition - index_x0;

		const float sample_y0 = fileBuffer[index_x0];
		const float sample_y1 = fileBuffer[index_x1];

		return lerp(sample_y0, sample_y1, t);

	
}


