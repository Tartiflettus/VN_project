#include <string>

template <typename T>
T createFromFile(const std::string &file)
{
	T loadAbleObject;

	loadAbleObject.loadFromFile(file);

	return loadAbleObject;
}
