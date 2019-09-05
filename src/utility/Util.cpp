
#include "utility/Util.h"

#include <math.h>

namespace ProjectSpace
{
	void addLineWrapping(sf::String& text, int lineLength)
	{
		int writer = 0;
		int counter = 0;

		for (int i = 0; i < text.getSize(); i++)
		{
			if (counter < lineLength - 1)
			{
				if (text[i] == ' ')
				{
					writer = i;
				}
				counter++;
			}
			else
			{
				text[writer] = '\n';
				counter = 0;
				i = ++writer;
			}
		}

	}

	namespace DebugDrawing
	{
		void drawLine(sf::Vector2f const& begin, sf::Vector2f const& end, Scene& scene)
		{
			// TODO: Use shared pointer to avoid ressource leak.

			sf::VertexArray* line = new sf::VertexArray{ sf::PrimitiveType::Lines };
			line->append(sf::Vertex{ begin });
			line->append(sf::Vertex{ end });

			scene.addDrawable(line);
		}

		void drawRec(sf::Vector2f const& position, sf::Vector2f const& size, Scene& scene)
		{
			sf::VertexArray* rec = new sf::VertexArray{ sf::PrimitiveType::Quads };
			rec->append(sf::Vertex{ position });
			rec->append(sf::Vertex{ sf::Vector2f{position.x + size.x, position.y} });
			rec->append(sf::Vertex{ sf::Vector2f{position.x + size.x, position.y + size.y} });
			rec->append(sf::Vertex{ sf::Vector2f{position.x, position.y + size.y} });

			scene.addDrawable(rec);
		}
	}
}