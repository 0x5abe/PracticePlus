#include "CCArray.hpp"
#include <hooks/PlayLayer.hpp>
#include <hooks/cocos2d/CCObject.hpp>
#include <hooks/CheckpointObject.hpp>

using namespace geode::prelude;

template <class T>
void PPCCArray::load(InputStream& i_stream) {
	removeAllObjects();
	unsigned int l_size;
	i_stream >> l_size;
	T* l_objects = reinterpret_cast<T*>(malloc(l_size*sizeof(T)));
	//geode::log::info("CCARRAY SIZE in: {}", l_size);
	for (int i = 0; i < l_size; i++) {
		reinterpret_cast<T*>(l_objects)->load(i_stream); 
		addObject(l_objects);
		l_objects++;
	}
}

template <class T>
void PPCCArray::save(OutputStream& o_stream) {
	unsigned int l_size = count();
	o_stream << l_size;
	//geode::log::info("CCARRAY SIZE out: {}", l_size);
	for (int i = 0; i < l_size; i++) {
	   reinterpret_cast<T*>(objectAtIndex(i))->save(o_stream); 
	}
}

template <>
void PPCCArray::load<GradientTriggerObject>(InputStream& i_stream) {
	removeAllObjects();
	unsigned int l_size;
	i_stream >> l_size;
	PlayLayer* l_playLayer = PlayLayer::get();
	//geode::log::info("CCARRAY GradientTriggerObject SIZE in: {}", l_size);
	for (int i = 0; i < l_size; i++) {
		int l_objectIndex;
		i_stream >> l_objectIndex;
		
		if (l_playLayer && l_objectIndex != -1) {
			//geode::log::info("CCARRAY GradientTriggerObject ObjectIndex in: {}", l_objectIndex);
			addObject(PlayLayer::get()->m_objects->objectAtIndex(l_objectIndex));
		}
	}
}

template <>
void PPCCArray::save<GradientTriggerObject>(OutputStream& o_stream) {
	unsigned int l_size = count();
	o_stream << l_size;
	//geode::log::info("CCARRAY GradientTriggerObject SIZE out: {}", l_size);
	for (int i = 0; i < l_size; i++) {
		int l_objectIndex = -1;
		if (!objectAtIndex(i)) {
			//log::info(" no game object?? @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		} else {
			PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
			if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(static_cast<GameObject*>(objectAtIndex(i)));
			//geode::log::info("CCARRAY GradientTriggerObject ObjectIndex out: {}", l_objectIndex);
		}
		o_stream << l_objectIndex;
	}
}

template <class T>
void PPCCArray::loadOne(InputStream& i_stream) {
	T* l_object = reinterpret_cast<T*>(malloc(sizeof(T)));
	reinterpret_cast<T*>(l_object)->load(i_stream); 
	addObject(l_object);
}

template <>
void PPCCArray::loadOne<PPCheckpointObject>(InputStream& i_stream) {
	CheckpointObject* l_object = CheckpointObject::create();
	reinterpret_cast<PPCheckpointObject*>(l_object)->load(i_stream); 
#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	geode::log::info("Loaded startpoints:");
	reinterpret_cast<PPCheckpointObject*>(l_object)->describe();
#endif
}

// template <>
// void PPCCArray::load<PPCheckpointObject>(InputStream& i_stream) {
// 	removeAllObjects();
// 	unsigned int l_size;
// 	i_stream >> l_size;
// 	//geode::log::info("CCARRAY CheckpointObject SIZE in: {}", l_size);
// 	PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
// 	if (!l_playLayer) return;
// 	CheckpointObject* l_object;
// 	for (int i = 0; i < l_size; i++) {
// 		l_object = CheckpointObject::create();
// 		reinterpret_cast<PPCheckpointObject*>(l_object)->load(i_stream); 
// 	}
// #if defined(PP_DEBUG) && defined(PP_DESCRIBE)
// 	geode::log::info("Loaded startpoints:");
// 	this->describe<PPCheckpointObject>();
// #endif
// }

template <>
void PPCCArray::save<PPCheckpointObject>(OutputStream& o_stream) {
	unsigned int l_size = count();
	geode::log::info("SIZE SPS: {}", l_size);
	o_stream << l_size;
	if (l_size == 0) return;
#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	geode::log::info("Startpoints to be saved:");
	this->describe<PPCheckpointObject>();
#endif
	//geode::log::info("CCARRAY CheckpointObject SIZE out: {}", l_size);
	for (int i = 0; i < l_size; i++) {
		reinterpret_cast<PPCheckpointObject*>(objectAtIndex(i))->save(o_stream); 
	}
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
// template <>
// void PPCCArray::describe<PPCheckpointObject>() {
// 	int l_size = this->count();
// 	log::info("[PPCCArray CheckpointObject - describe] count(): {}", l_size);
// 	for (int i = 0; i < l_size; i++) {
// 		log::info("[PPCCArray CheckpointObject - describe] this[{}]:", i);
// 		reinterpret_cast<PPCheckpointObject*>(objectAtIndex(i))->describe();
// 	}
// } 

template <>
void PPCCArray::describe<GradientTriggerObject>() {
	int l_size = this->count();
	log::info("[PPCCArray GradientTriggerObject - describe] count(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		int l_objectIndex = -1;
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(static_cast<GameObject*>(objectAtIndex(i)));
		log::info("[PPCCArray GradientTriggerObject - describe] l_objectIndex[{}]: {}", i, l_objectIndex);
	}
}
#endif