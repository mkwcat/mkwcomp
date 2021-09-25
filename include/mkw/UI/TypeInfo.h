#pragma once

namespace UI
{

struct TypeInfo {
    const TypeInfo* parent;
};

template <class T> struct AutoTypeInfo : public TypeInfo {
    AutoTypeInfo() { parent = &T::sTypeInfo; }
};

} // namespace UI