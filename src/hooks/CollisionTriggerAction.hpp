#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CollisionTriggerAction.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPCollisionTriggerAction, CollisionTriggerAction) {
protected:
    friend void operator>>(InputStream& i_stream, PPCollisionTriggerAction& o_value);
    friend void operator<<(OutputStream& o_stream, PPCollisionTriggerAction& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);

#ifdef PP_DEBUG
    void describe();
#endif
};