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
// EthanEngine/Utilities/UtilString.hpp

#ifndef ETHANENGINE_UTILSTRING_H
#define ETHANENGINE_UTILSTRING_H

namespace Ethan
{
	struct LibString
	{
        // See: http://www.cse.yorku.ca/~oz/hash.html
		static unsigned long Hash(const char* Str)
		{
			unsigned long HashValue = 5381;
			while (*Str != 0U)
			{
				HashValue = ((HashValue << 5) + HashValue) ^ *Str++; /* HashValue * 33 + c */
			}
			return HashValue;
		}
	};
} // namespace Ethan

#endif // ETHANENGINE_UTILSTRING_H
