// TEMP: HAS BEEN CONVERTED TO 2-SPACED TABS

#include "lexer.h"

std::vector<ab::lexObj> ab::lexDocument(std::string doc)
{
	std::vector<ab::lexObj> lexObjects;
	std::string cur;
	std::string commentBuf;
	bool spaceFound = false;
	bool inQuotes = false;
	bool commentSearch = false;
	bool inComment = false;

	const std::string OPENING_COMMENT_TAG = "<!--";
	const std::string CLOSING_COMMENT_TAG = "-->";

	for(int i = 0; i < doc.length(); i++)
	{
		if (doc[i] != '\n')
		{
			//// check for Comments ///////////////////
			if (!inQuotes)
			{
				if (doc[i] == '<' || (inComment && doc[i] == '-'))
					commentSearch = true;

				if (commentSearch)
				{
					commentBuf += doc[i];

					if (!inComment)
					{
						if (commentBuf[commentBuf.length() - 1] != OPENING_COMMENT_TAG[commentBuf.length() - 1])
						{
							commentSearch = false;
							commentBuf.clear();
						}
						else if (commentBuf == OPENING_COMMENT_TAG)
						{
							commentSearch = false;
							inComment = true;
							commentBuf.clear();
							cur.clear();
						}
					}
					else
					{
						if (commentBuf[commentBuf.length() - 1] != CLOSING_COMMENT_TAG[commentBuf.length() - 1])
						{
							commentBuf.clear();
						}
						else if (commentBuf == CLOSING_COMMENT_TAG)
						{
							commentSearch = false;
							inComment = false;
							commentBuf.clear();
						}
					}
				}
			}
			///////////////////////////////////////////

			if (!inComment)
			{
				if (doc[i] == ' ')
				{
					if (!spaceFound)
					{
						spaceFound = true;
						cur += doc[i];
					}
				}
				else if ((doc[i] == '<' || doc[i] == '>') && !inQuotes)
				{
					spaceFound = false;

					if (cur[0] == ' ')
						cur.erase(0, 1);
					if (cur[cur.length() - 1] == ' ')
						cur.erase(cur.length() - 1, 1);

					if (doc[i] == '<')
					{
						if (cur.length() > 0)
						{
							lexObjects.push_back(lexObj(Constants::INNER_TEXT, cur));
							cur.clear();
						}
					}
					else if (doc[i] == '>')
					{
						if (cur.length() > 0)
						{
							lexObjects.push_back(lexObj(Constants::TAG, cur));
							cur.clear();
						}
					}
				}
				else
				{
					if (doc[i] == '\"')
					{
						if (inQuotes)
							inQuotes = false;
						else
							inQuotes = true;
					}

					spaceFound = false;
					cur += doc[i];
				}
			}
		}
	}

	return lexObjects;
}

std::vector<std::string> ab::lexAttributes(lexObj &tag)
{
	std::vector<std::string> attributes;
	std::string tagVal = tag.getValue();
	std::string cur;
	bool afterTag = false;
	bool inQuotes = false;

	for(int i = 0; i < tagVal.length(); i++)
	{
		if (!inQuotes)
			if (tagVal[i] >= 65 && tagVal[i] <= 90)
				tagVal[i] = tagVal[i] + 32;

		if (!afterTag && tagVal[i] == ' ')
			afterTag = true;
		else if (afterTag)
		{
			if (tagVal[i] != '=' && tagVal[i] != '\"')
			{
				cur += tagVal[i];
			}
			else if (tagVal[i] == '=')
			{
				if (cur[0] == ' ')
					cur.erase(0, 1);
				if (cur[cur.length() - 1] == ' ')
					cur.erase(cur.length() - 1, 1);

				attributes.push_back(cur);
				cur.clear();
			}
			else if (tagVal[i] == '\"')
			{
				if (inQuotes)
				{
					if (cur[0] == ' ')
						cur.erase(0, 1);
					if (cur[cur.length() - 1] == ' ')
						cur.erase(cur.length() - 1, 1);

					attributes.push_back(cur);
					cur.clear();
					inQuotes = false;
				}
				else
					inQuotes = true;
			}

			tagVal.erase(i, 1);
			i--;
		}
	}

	if (tagVal[tagVal.length() - 1] == ' ')
		tagVal.erase(tagVal.length() - 1, 1);
	tag.setValue(tagVal);

	return attributes;
}
