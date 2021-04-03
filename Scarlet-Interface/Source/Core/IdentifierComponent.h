#pragma once

namespace ScarletInterface {

	struct IdentifierComponent
	{
	public:
		const char* Identifer;

		IdentifierComponent() = default;
		IdentifierComponent(const IdentifierComponent&) = default;
		IdentifierComponent(const char* _Identifier)
		{ Identifer = _Identifier; }
	};

}