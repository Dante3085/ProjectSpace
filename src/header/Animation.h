
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <iostream>

namespace ProjectSpace
{
	/**
	 * @brief      Represents a single Animation.
	 */
	class Animation
	{
	public:
		/**
		 * @brief      Constructs an Animation object.
		 *
		 * @param[in]  spriteSheetPath  Path to SpriteSheet.
		 * @param[in]  frameWidth       Width of a single frame in the SpriteSheet.
		 * @param[in]  frameHeight      Height of a single frame in the SpriteSheet.
		 * @param[in]  yRow             Y-Coordinate of the first frame of the Animation in the SpriteSheet.
		 * @param[in]  xColumn          X-Coordinate of the first frame of the Animation in the SpriteSheet.
		 * @param[in]  numFrames        Number of frames in the Animation.
		 * @param[in]  frameDelay       Delay between frames of the Animation in seconds.
		 */
		Animation(std::string spriteSheetPath, int frameWidth, int frameHeight, int yRow, int xColumn, 
			int numFrames, float frameDelay = 0.2f);

		/**
		 * @brief      Gets the SpriteSheet of this Animation.
		 *
		 * @return     The SpriteSheet of this Animation.
		 */
		sf::Texture const& getSpriteSheet() const;

		/**
		 * @brief     Gets the number of frames in this Animation.
		 *
		 * @return    The number of frames in this Animation.
		 */
		int size() const;

		/**
		 * @brief      Gets the frame delay of this Animation.
		 *
		 * @return     The frame delay of this Animation.
		 */
		float getFrameDelay() const;

		/**
		 * @brief      Sets the frame delay of this Animation.
		 *
		 * @param[in]  frameDelay  New frameDelay for this Animation.
		 */
		void setFrameDelay(float frameDelay);

		/**
		 * @brief      Gets frame of this Animation at the given index.
		 *
		 * @param[in]  index  The index. (Maybe throw exception if index is invalid ????)
		 *
		 * @return     frame of this Animation at the given index.
		 */
		sf::IntRect const& operator[](int index) const;

	private:
		sf::Texture spriteSheet; 			// SpriteSheet of the Animation.
		float frameDelay;					// Delay in seconds between each of the Animation's frames.
		std::vector<sf::IntRect> frames; 	// The frames of the Animation.
	};
}

#endif