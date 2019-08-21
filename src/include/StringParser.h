
#ifndef STRING_PARSER_H
#define STRING_PARSER_H

#include <string>

namespace ProjectSpace
{
    class StringParser
    {
    public:

        static void parseString(std::string& text, int zeilenlaenge, int zeilenzahl)
        {
            int writer = 0;
            int counter = 0;

            for (int i = 0; i < text.size(); i++)
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

    private:
		StringParser();
    };
}

#endif