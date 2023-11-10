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

namespace Ethan
{
#define EVENT_CLASS(name, category)                          \
	virtual const char* GetName() const override             \
	{                                                        \
		return #name;                                        \
	}                                                        \
	virtual EEventCategory GetCategoryFlags() const override \
	{                                                        \
		return category;                                     \
	}

	// ---------------------------------------------------------------------------
	// Bit field enum class for Event Category. This is a bit hacky since we use
	// operator overload to make the enum class have the bitwise operator.
	//
	// Warning: Currently, we only support | and & operator.
	// See: https://www.sandordargo.com/blog/2022/06/22/bitwise-enums
	// ---------------------------------------------------------------------------
	enum class EEventCategory
	{
		None = 0,
		Application = BIT(1),
		Input = BIT(2),
		Controller = BIT(3),
		Keyboard = BIT(4),
		Mouse = BIT(5),
	};
	ENUM_CLASS_BITWISE(EEventCategory);

	// ---------------------------------------------------------------------------
	// Event interface for other event children classes to derive from.
	//
	// Usage:
	//     class KeyboardEvent : public IEvent
	//     {
	//     public:
	//         EVENT_CLASS(KeyboardEvent, EEventCategory::Input | EEventCategory::Keyboard)
	//         ...
	//     };
	// ---------------------------------------------------------------------------
	class IEvent
	{
	public:
		virtual ~IEvent() = default;

		[[nodiscard]] virtual const char* GetName() const = 0;
		[[nodiscard]] virtual EEventCategory GetCategoryFlags() const = 0;

		void SetHandled(const bool Value) { Handled = Value; }
		[[nodiscard]] bool IsHandled() const { return Handled; }
		[[nodiscard]] bool IsInCategory(const EEventCategory Category) const
		{
			return (GetCategoryFlags() & Category) != EEventCategory::None;
		}

	private:
		bool Handled = false;
	};
} // namespace Ethan

#endif // ETHANENGINE_EVENT_H
