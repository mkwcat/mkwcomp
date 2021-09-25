#pragma once

// Mario Kart Wii's UI system implements its own thing similar to the C++
// dynamic_cast, where it can cast down to a derived class from a base class
// like UIPage or UIControl. The base types include a virtual function that
// returns a TypeInfo, which can be used to verify that the cast is valid.

namespace UI
{

struct TypeInfo {
    const TypeInfo* parent;
};

template <class T> struct AutoTypeInfo : public TypeInfo {
    AutoTypeInfo()
    {
        parent = &T::sTypeInfo;
    }
};

} // namespace UI