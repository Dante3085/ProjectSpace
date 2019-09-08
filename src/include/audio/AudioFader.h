
#ifndef AUDIO_FADER_H
#define AUDIO_FADER_H

#include <SFML/Audio/Music.hpp>

#include "scenes/Entity.h"
#include "Easing.h"

namespace ProjectSpace
{
	class AudioFader : public Entity
	{
	public:
		AudioFader(sf::Music& music, float startVolume, float endVolume, float durationInMilliseconds);

		void update(sf::Time time) override;

		void start();
		void setMusic(sf::Music& music);
		void setStartVolume(float startVolume);
		void setEndVolume(float endVolume);
		void setEasingFunction(Easing::EasingFunction easingFunction);

	private:
		sf::Music* music;
		float startVolume;
		float endVolume;
		float durationInMilliseconds;
		float elapsedMilliseconds;
		bool doUpdate;
		Easing::EasingFunction easingFunction;
	};
}

#endif