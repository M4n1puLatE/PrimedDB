#include <Util.h>
#include <istream>
#include <sstream>
namespace Util { 
	Util::indexes Util::FastSplitString(const string& str, char delim)
	{
		if(str.empty())
			return {};
		indexes positions;
		FastSplitString(positions, str, delim);
		return positions;
	}
	Util::substring Util::SplitString(const string& str, char delim)
	{

		substring result;
		SplitString(result, str, delim);
		return result;
	}
	void Util::FastSplitString(indexes& result, const string& str, char delim)
	{
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == delim)
				result.push_back(i);
		}
	}
	void Util::SplitString(substring& result, const string& str, char delim)
	{
		if (!str.empty())
		{
			string token;
			std::istringstream tokenStream(str);
			while (std::getline(tokenStream, token, delim))
			{
				result.push_back(token);
			}
		}
	}
}