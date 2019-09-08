
#include "audio/AudioFader.h"

#include <iostream>

namespace ProjectSpace
{
	AudioFader::AudioFader(sf::Music& music, float startVolume, float endVolume, float durationInMilliseconds)
		: music{&music}, startVolume{ startVolume }, endVolume{ endVolume }, durationInMilliseconds{ durationInMilliseconds },
		elapsedMilliseconds{ 0 }, doUpdate{false}, easingFunction{ Easing::sine_easeIn }
	{
		this->music->setVolume(startVolume);
	}

	void AudioFader::update(sf::Time time)
	{
		if (!doUpdate)
			return;

		elapsedMilliseconds += time.asMilliseconds();
		if (elapsedMilliseconds >= durationInMilliseconds)
		{
			doUpdate = false;
			elapsedMilliseconds = 0;
			music->setVolume(endVolume);
			return;
		}

		music->setVolume(easingFunction(elapsedMilliseconds, startVolume, endVolume - startVolume, durationInMilliseconds));
	}

	void AudioFader::start()
	{
		doUpdate = true;
		
		if (music->getStatus() != sf::SoundSource::Status::Playing)
		{
			music->play();
		}
	}

	void AudioFader::setMusic(sf::Music& music)
	{
		this->music = &music;
	}

	void AudioFader::setStartVolume(float startVolume)
	{
		this->startVolume = startVolume;
	}

	void AudioFader::setEndVolume(float endVolume)
	{
		this->endVolume = endVolume;
	}

	void AudioFader::setEasingFunction(Easing::EasingFunction easingFunction)
	{
		this->easingFunction = easingFunction;
	}
}