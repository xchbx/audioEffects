#include <string.h>
#include <stdio.h>
#include <math.h>
#include "effects.h"

using namespace effects;

AudioEffect::~AudioEffect(){

}

void AudioEffect::SetPassThrough(bool passThrough){
	this->passThrough=passThrough;
}

Volume::Volume(){

}

Volume::~Volume(){

}

void Volume::Process(int16_t* inOut, size_t numSamples){
	if(level==1.0f || passThrough){
		return;
	}
	for(size_t i=0;i<numSamples;i++){
		float sample=(float)inOut[i]*multiplier;
		if(sample>32767.0f)
			inOut[i]=INT16_MAX;
		else if(sample<-32768.0f)
			inOut[i]=INT16_MIN;
		else
			inOut[i]=(int16_t)sample;
	}
}

void Volume::SetLevel(float level){
	this->level=level;
	float db;
	if(level<1.0f)
		db=-50.0f*(1.0f-level);
	else if(level>1.0f && level<=2.0f)
		db=10.0f*(level-1.0f);
	else
		db=0.0f;
	multiplier=expf(db/20.0f * logf(10.0f));
    //printf("db = %6f,multiplier = %6f\r\n",db,multiplier);
}

float Volume::GetLevel(){
	return level;
}
