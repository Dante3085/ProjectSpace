
#include "scenes/Scene.h"

namespace ProjectSpace
{
	Scene::Scene(sf::RenderWindow& window)
		: window{window}
	{

	}

	void Scene::update(sf::Time time)
	{
		for (Entity* e : entities)
		{
			e->update(time);  
		}
	}

	void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (sf::Drawable* d : drawables)
		{
			target.draw(*d);
		}
	}

	void Scene::addEntity(Entity* e)
	{
		entities.push_back(e);
	}

	void Scene::addEntities(std::vector<Entity*> entities)
	{
		for (Entity* e : entities)
		{
			this->entities.push_back(e);
		}
	}

	void Scene::addDrawable(sf::Drawable* d)
	{
		drawables.push_back(d);
	}

	void Scene::addDrawables(std::vector<sf::Drawable*> drawables)
	{
		for (Drawable* d : drawables)
		{
			this->drawables.push_back(d);
		}
	}
}