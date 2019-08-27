#ifndef LIBVOLUME_H
#define LIBVOLUME_H

#include <iostream>

namespace effects{

class AudioEffect{
public:
	virtual ~AudioEffect()=0;
	virtual void Process(int16_t* inOut, size_t numSamples)=0;
	virtual void SetPassThrough(bool passThrough);
protected:
	bool passThrough=false;
};

class Volume : public AudioEffect{
public:
	Volume();
	virtual ~Volume();
	virtual void Process(int16_t* inOut, size_t numSamples);
	/**
	* Level is (0.0, 2.0]
	*/
	void SetLevel(float level);
	float GetLevel();
private:
	float level=1.0f;
	float multiplier=1.0f;
};

}

#endif
