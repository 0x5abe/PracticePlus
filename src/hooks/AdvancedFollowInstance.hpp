#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/AdvancedFollowInstance.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPAdvancedFollowInstance, AdvancedFollowInstance) {
protected:
	friend void operator>>(InputStream& i_stream, PPAdvancedFollowInstance& o_value);
	friend void operator<<(OutputStream& o_stream, PPAdvancedFollowInstance& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
#endif
};