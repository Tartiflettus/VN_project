#ifndef DEF_EDITTYPES_HPP
#define DEF_EDITTYPES_HPP



namespace edit
{
	struct Action
	{
		enum item
		{
			character,
			text,
			voice,
			music,
			background,
			invalidItem
		};

		Action();

		item aItem;

		bool nextPressed;
		bool precPressed;
		bool closeRequest;

		sf::String textBuffer;		

		int h; //left and right keys
		int v; //up and down keys

	};
}



#endif //DEF_EDITTYPES_HPP

