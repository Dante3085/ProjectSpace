
#include "Animation.h"

namespace ProjectSpace
{
	Animation::Animation(std::string spriteSheetPath, int frameWidth, int frameHeight, int yRow, int xColumn, 
		int numFrames, float frameDelay)
		: spriteSheet{spriteSheet}, frameDelay{frameDelay}, frames{std::vector<sf::IntRect>{}}
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
			std::cout << "@Animation::setFrameDelay(" << frameDelay << "): Invalid frameDelay." << std::endl;
			return;
		}
		this->frameDelay = frameDelay;
	}

	sf::IntRect const& Animation::operator[](int index) const
	{
		if (index < 0 || index >= frames.size())
			std::cout << "@Animation::operator[" << index << "]: Invalid Index." << std::endl;
		return frames[index];	
	}
}