#pragma once

namespace Command
{
	enum class Operator:char
	{
		Who,
		Level,
		Delete,
		Add,
		List,
        Help,
		Authorize,
		Unauthorize,
		Load,
		Run,
        Quit,
		Terminate,
		Owns,
		Filter,
		Update

	};
	enum class Target :char
	{
		User,
		Table,
		Record,
		Log,
		All
	};
	class CommandCentre
	{
		
	};
}
