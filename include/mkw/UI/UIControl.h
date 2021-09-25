#pragma once
#include <rvl/types.h>

namespace UI
{

class UIControl;

struct UIControlCollection {
    UIControlCollection();
    ~UIControlCollection();

    void init(UIControl* parent, int count);
    void insert(int index, UIControl* control);

    UIControl** m_children;
    UIControl** m_childrenSorted;
    UIControl* m_parent;
    UIControl* m_root;
    int m_count;
};

struct UIControlPosition {
    UIControlPosition() : x(0), y(0), z(0), xScale(1), yScale(1), alpha(0xFF) {}

    f32 x;
    f32 y;
    f32 z;
    f32 xScale;
    f32 yScale;
    u8 alpha;
    u8 fill[3];
};

class UIControl
{
public:
    UIControl();
    virtual ~UIControl();

    virtual void init();
    virtual void calc();
    virtual void draw();
    virtual void initInternal() {}
    virtual void calcInternal() {}
    virtual void _20() {}
    virtual void _24() {}
    virtual void _28() {}
    virtual const char* getKindString();
    virtual void _30() {}
    virtual void _34() {}

    UIControlPosition m_basePos;   // code position
    UIControlPosition m_layoutPos; // layout position
    UIControlPosition m_somePos;
    UIControlPosition m_realPos;

    UIControlCollection* m_parent;
    UIControlCollection m_children;

    f32 m_7C;
    bool m_invisible;
    u32 m_84;
    bool m_useSlideAnim;
    f32 m_slideDelay;
    s32 m_slideInSound;
    s32 m_slideOutSound;
};

} // namespace UI