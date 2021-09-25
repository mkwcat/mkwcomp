#pragma once
#include <rvl/types.h>

namespace UI
{

/* I don't know how this is actually done but this works! */
class EventBase
{
public:
    virtual void call(void* arg1, void* arg2) = 0;
};

template <class BaseT, class Arg1T, class Arg2T> class Event : public EventBase
{
public:
    Event(BaseT* object, void (BaseT::*function)(Arg1T, Arg2T))
        : m_object(object), m_function(function)
    {
    }

    void call(void* arg1, void* arg2)
    {
        (m_object->*m_function)(reinterpret_cast<Arg1T>(arg1),
                                reinterpret_cast<Arg2T>(arg2));
    }

private:
    BaseT* m_object;
    void (BaseT::*m_function)(Arg1T, Arg2T);
};

} // namespace UI