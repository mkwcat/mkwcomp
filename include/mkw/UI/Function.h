#pragma once

namespace UI
{

template <class P1, class P2>
class FunctionBase
{
public:
    virtual void call(P1 param1, P2 param2) = 0;
};

template <class P1, class P2>
class Function
{
    FunctionBase<P1, P2>* m_function;

public:
    void operator()(P1 param1, P2 param2)
    {
        m_function->call(param1, param2);
    }

    void set(FunctionBase<P1, P2>* function)
    {
        m_function = function;
    }
};

template <class O, class P1, class P2>
class FunctionImp : public FunctionBase<P1, P2>
{
    O* m_object;
    void (O::*m_function)(P1, P2);

public:
    FunctionImp(O* object, void (O::*function)(P1, P2))
    {
        m_object = object;
        m_function = function;
    }

    virtual void call(P1 param1, P2 param2)
    {
        (m_object->*m_function)(param1, param2);
    }
};

} // namespace UI
