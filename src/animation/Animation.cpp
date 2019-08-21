
#include "Animation.h"
#include "Log.h"

namespace ProjectSpace
{
	Animation::Animation(std::string const& spriteSheetPath, int frameWidth, int frameHeight, int yRow, int xColumn, 
		int numFrames, float frameDelay)
		: frameDelay{frameDelay}
	{
		spriteSheet.loadFromFile(spriteSheetPath);

		int spriteSheetWidth = spriteSheet.getSize().x;
 		int frame = 0;

 		// Iterate over "numFrames" frames in the SpriteSheet and store each frame as Rectangle in a vector.
 		// These frames will be the Animation. (Bild zum folgenden Algorithmus im ProjectSpace Ordner)
		while(frame++ < numFrames)
		{
			if ((xColumn * frameWidth) == spriteSheetWidth)
			{
				++yRow;
				xColumn = 0;
			}
			frames.push_back(sf::Rect<int>{ xColumn++ * frameWidth, yRow * frameHeight, frameWidth, frameHeight});
		}
	}

	Animation::Animation(std::string const& spriteSheetPath, float frameDelay)
		: frameDelay{frameDelay}
	{
		spriteSheet.loadFromFile(spriteSheetPath);
	}

	void Animation::setAnimation(std::vector<sf::Rect<int>> const& frames, float frameDelay)
	{
		this->frames.clear();
		this->frames = frames;
		frameDelay = frameDelay;
	}

	sf::Texture const& Animation::getSpriteSheet() const
	{
		return spriteSheet;
	}

	int Animation::size() const
	{
		return frames.size();
	}

	float Animation::getFrameDelay() const
	{
		return frameDelay;
	}

	void Animation::setFrameDelay(float frameDelay)
	{
		if (frameDelay <= 0)
		{
			Log::getInstance() << lo::PTC << ll::ERR << lo::TIMESTAMP << "Invalid FrameDelay." << lo::STACKTRACE << lo::END;
			return;
		}
		this->frameDelay = frameDelay;
	}

	sf::IntRect const& Animation::operator[](int index) const
	{
		if (index < 0 || index >= frames.size())
		{
			Log::getInstance() << lo::PTC << ll::ERR << lo::TIMESTAMP << "Invalid Index." << lo::STACKTRACE << lo::END << lo::EXIT;
		}
		return frames[index];	
	}
}