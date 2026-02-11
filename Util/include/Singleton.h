#pragma once

namespace Util
{
	template<class T>
	class Singleton
	{

	protected:
		Singleton() = default;

	public:
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;
		static T& Get()
		{
			static T instance;
			return instance;
		}
	};
#define	THIS_IS_SINGLETON friend class Singleton
}
