#pragma once
#include <vector>
#include <string>
namespace Util
{
	class Util
	{
		using indexes = std::vector<int>;
		using string = std::string;
		using substring = std::vector<string>;
		static indexes FastSplitString(const string& str, char delim);
		static substring SplitString(const string& str, char delim);
		static void FastSplitString(indexes& result, const string& str, char delim);
		static void SplitString(substring& result,const string& str, char delim);
	};
}
