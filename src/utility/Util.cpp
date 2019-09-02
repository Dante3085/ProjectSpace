
#include "utility/Util.h"

#include <iostream>
#include <math.h>
#include <vector>
#include <string>

namespace ProjectSpace
{
	std::ostream& operator<<(std::ostream& stream, sf::Vector2f const& v)
	{
		stream << "{" << v.x << ", " << v.y << "}";
		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, sf::FloatRect const& r)
	{
		stream << "{{" << r.left << ", " << r.top << "}, {" << r.left + r.width << ", " << r.top <<"}, {"
		<< r.left + r.width << ", " << r.top + r.height << "}, {" << r.left << ", " << r.top + r.height << "}}";
		return stream;
	}

	float vectorLength(sf::Vector2f const& v)
	{
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}

	sf::Vector2f vectorMultScalar(sf::Vector2f const& v, float scalar)
	{
		return sf::Vector2f{ v.x * scalar, v.y * scalar };
	}

	sf::Vector2f operator*(sf::Vector2f const& v, float scalar)
	{
		return sf::Vector2f{ v.x * scalar, v.y * scalar };
	}

	sf::Vector2f operator-(sf::Vector2f const& v1, sf::Vector2f v2)
	{
		return sf::Vector2f{ v1.x - v2.x, v1.y - v2.y };
	}

	float scalarProduct(sf::Vector2f const& v1, sf::Vector2f const& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	sf::Vector2f normalizedVector(sf::Vector2f const& v)
	{
		return vectorMultScalar(v, 1.f / vectorLength(v));
	}

	template <class T>
	std::ostream& operator<<(std::ostream& stream, sf::Vector2<T> v)
	{
		stream << "{" << v.x << ", " << v.y << "}";
		return stream;
	}

	std::string toString(sf::Vector2f const& v)
	{
		std::string str{"{ "};
		str.append(std::to_string(v.x));
		str.append(", ");
		str.append(std::to_string(v.y));
		str.append("}");
		return str;
	}

	template <class T>
	std::ostream& operator<<(std::ostream& stream, std::vector<T> v)
	{
		stream << "{ ";
		for (T& t : v)
		{
			stream << t << " ";
		}
		stream << "}";
		return stream;
	}

	void parseString(sf::String& text, int zeilenlaenge, int zeilenzahl)
	{
		int writer = 0;
		int counter = 0;

		for (int i = 0; i < text.getSize(); i++)
		{
			if (counter < zeilenlaenge - 1)
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
}