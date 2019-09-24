
#include "utility/Util.h"

#include <math.h>

namespace ProjectSpace
{
	std::vector<sf::String> addTextWrapping(sf::String const& original, int lineLength, float textHeight, float lineHeight)
	{
		int writer = 0;
		int counter = 0;
		int numberLines = textHeight / lineHeight - 1;
		sf::String text = original;
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
		std::vector<sf::String> refinedText;
		counter = 0;
		writer = 0;
		for (int i = 0; i < text.getSize(); i++)
		{
			if (text[i] == '\n') ++counter;
			if (counter > numberLines)
			{
				refinedText.push_back(text.substring(writer, (i - writer +1)));
				if ((i + 1) < text.getSize())
				{
					writer = i + 1;
				}
				else
				{
					writer = i;
				}
				counter = 0;
			}
		}
		if (writer < text.getSize()-1)
		{
			refinedText.push_back(text.substring(writer, (text.getSize() - writer)));
		}
		return refinedText;
	}

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
		void drawPoint(sf::Vector2f const& point, Scene& scene)
		{
			sf::VertexArray* array = new sf::VertexArray{ sf::PrimitiveType::Points };
			array->append(sf::Vertex{ point, sf::Color::Blue });

			scene.addDrawable(array);
		}

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