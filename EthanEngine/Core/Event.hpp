// ==================================================
//      _____
//   __|___  |__    __    __   _  ____    ____   _
//  |   ___|    | _|  |_ |  |_| ||    \  |    \ | |
//  |   ___|    ||_    _||   _  ||     \ |     \| |
//  |______|  __|  |__|  |__| |_||__|\__\|__/\____|
//     |_____|
//                   Game Engine
// ==================================================
//
// Github : https://github.com/zZnghialamZz/Ethan
// License: MIT License (See LICENSE for details)
//
// ---
// EthanEngine/Core/Event.hpp

#ifndef ETHANENGINE_EVENT_H
#define ETHANENGINE_EVENT_H

#include "Utilities/UtilString.hpp"

namespace Ethan
{
#define EVENT_CLASS(name)                              \
	virtual const char* GetName() const override       \
	{                                                  \
		return #name;                                  \
	}                                                  \
	virtual const EventID& GetEventID() const override \
	{                                                  \
		if (EID == 0)                                  \
		{                                              \
			EID = LibString::Hash(GetName());          \
		}                                              \
		return EID;                                    \
	}

	// ---------------------------------------------------------------------------
	// Event interface for other event children classes to derive from.
	//
	// Usage:
	//     class KeyboardEvent : public IEventBase
	//     {
	//     public:
	//         EVENT_CLASS(KeyboardEvent)
	//         ...
	//     };
	// ---------------------------------------------------------------------------
	using EventID = unsigned long;

	class IEventBase
	{
	public:
		explicit IEventBase()
			: EID(0)
			, Handled(false) {}
		virtual ~IEventBase() = default;

		EAPI_NODISCARD virtual const char* GetName() const = 0;
		EAPI_NODISCARD virtual const EventID& GetEventID() const = 0;

		bool IsHandled() const { return Handled; }
		void SetHandled(const bool Value) { Handled = Value; }

	protected:
		EventID EID;

	private:
		bool Handled;
	};
} // namespace Ethan

#endif // ETHANENGINE_EVENT_H
