
#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

#include "Entity.h"

namespace ProjectSpace
{
	/**
	 * @brief      Represents a Scene in the Game (A closed unit with Characters, Backgrounds,...)
	 */
	class Scene : public Entity, public sf::Drawable
	{
	public:
		Scene(sf::RenderWindow& window);

		/**
		 * @brief      Destroys all Entities of this Scene.
		 */
		virtual ~Scene() {}

		/**
		 * @brief      Updates all Entities of this Scene.
		 *
		 * @param[in]  time  The time.
		 */
		virtual void update(sf::Time time) override;

		/**
		 * @brief      Draws all sf::Drawables of this Scene.
		 *
		 * @param      target  The target.
		 * @param[in]  states  The states.
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		/**
		 * @brief      Adds an Entitiy to this Scene.
		 *
		 * @param      e     Entity.
		 */
		void addEntity(Entity* e);

		/**
		 * @brief      Adds several Entities to this Scene.
		 *
		 * @param[in]  entities  The entities.
		 */
		void addEntities(std::vector<Entity*> entities);

		/**
		 * @brief      Adds an sf::Drawable to this Scene.
		 *
		 * @param      d     sf::Drawable.
		 */
		void addDrawable(sf::Drawable* d);

		/**
		 * @brief      Adds several sf::Drawables to this Scene.
		 *
		 * @param[in]  drawables  The drawables.
		 */
		void addDrawables(std::vector<sf::Drawable*> drawables);

	protected:
		sf::RenderWindow& window; // Reference to RenderWindow of the whole Application.

	private:
		std::vector<Entity*> entities; 		  // Entities of this Scene.
		std::vector<sf::Drawable*> drawables; // Drawables of this Scene.
	};
}

#endif