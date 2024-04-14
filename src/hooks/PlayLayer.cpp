#include "PlayLayer.hpp"
#include <Geode/binding/CheckpointObject.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <managers/StartpointManager.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

using namespace geode::prelude;

// overrides

bool PPPlayLayer::init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects) {
	// reset uniqueID global to save/load GameObjects correctly using their index
	// should look into not having to do this but it's harder than it looks since there's 
	// probably maps with object id as keys, it's not just us saving pointers so I'd have to find those.
	*reinterpret_cast<int*>(geode::base::get()+0x4ea028) = 10;
	m_fields->m_uniqueIdBase = *reinterpret_cast<int*>(geode::base::get()+0x4ea028) + 2;

	if (!PlayLayer::init(i_level, i_useReplay, i_dontCreateObjects)) return false;

	setupKeybinds();
	return true;
}

void PPPlayLayer::resetLevel() {
	m_fields->m_enableArrayHook = true;
 
	PlayLayer::resetLevel();
	m_fields->m_enableArrayHook = false;
}

void PPPlayLayer::togglePracticeMode(bool i_value) {
	togglePlusMode(i_value);

	PlayLayer::togglePracticeMode(i_value);
}

void PPPlayLayer::updateVisibility(float i_unkFloat) {
	PlayLayer::updateVisibility(i_unkFloat);

	if (!isPlusMode()) {
		StartpointManager::get().updatePlusModeVisibility();
	}
}

void PPPlayLayer::onQuit() {
	if (!m_fields->m_onQuitCalled) {
		StartpointManager::get().reset();
		m_fields->m_onQuitCalled = true;
	}
	PlayLayer::onQuit();
}

// custom methods

void PPPlayLayer::createStartpoint() {
	addStartpoint(StartpointManager::get().createStartpoint(createCheckpoint(), m_player1->getPosition()));
}

void PPPlayLayer::addStartpoint(CheckpointObject* i_startpoint, int i_index) {
	PlayLayer::addToSection(i_startpoint->m_physicalCheckpointObject);
	i_startpoint->m_physicalCheckpointObject->activateObject();
}

bool PPPlayLayer::removeStartpoint(int i_index) {
	StartpointManager& l_startpointManager = StartpointManager::get();
	CheckpointObject* l_startpoint = l_startpointManager.getStartpoint(i_index);
	if (!l_startpoint) return false;
	PlayLayer::removeObjectFromSection(l_startpoint->m_physicalCheckpointObject);
	l_startpoint->m_physicalCheckpointObject->removeMeAndCleanup();
	if (l_startpoint == l_startpointManager.getActiveStartpoint()) {
		StartpointManager::get().setActiveStartpointId(l_startpointManager.getActiveStartpointId()-1);
	}
	l_startpointManager.removeStartpoint(i_index);
	return true;
}

bool PPPlayLayer::setActiveStartpointAndReload(int i_index) {
	StartpointManager::get().setActiveStartpointId(i_index);
	reloadFromActiveStartpoint();
	return true;
}

void PPPlayLayer::reloadFromActiveStartpoint() {
	while (m_checkpointArray->count() > 0) {
		PlayLayer::removeCheckpoint(false);
	}
	resetLevel();
}

void PPPlayLayer::togglePlusMode(bool i_value) {
	StartpointManager& l_startpointManager = StartpointManager::get();
	l_startpointManager.togglePlusMode(i_value);
	l_startpointManager.updatePlusModeLogic();
	l_startpointManager.updatePlusModeVisibility();
}

void PPPlayLayer::setupKeybinds() {
	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			if (event->isDown() && isPlusMode()) {
				createStartpoint();
			}
			return ListenerResult::Propagate;
		},
		"place-sp"_spr
	);

	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			if (event->isDown() && isPlusMode()) {
				removeStartpoint();
			}
			return ListenerResult::Propagate;
		},
		"remove-sp"_spr
	);

	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			if (event->isDown() && isPlusMode()) {
				if (StartpointManager::get().prevStartpoint()) {
					reloadFromActiveStartpoint();
				}
			}
			return ListenerResult::Propagate;
		},
		"switch-sp-prev"_spr
	);

	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			if (event->isDown() && isPlusMode()) {
				if (StartpointManager::get().nextStartpoint()) {
					reloadFromActiveStartpoint();
				}
			}
			return ListenerResult::Propagate;
		},
		"switch-sp-next"_spr
	);

	// TodoRemove
	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			if (event->isDown() && isPlusMode()) {
				InputStream l_ifstream = InputStream("./testPlayerCheckpoint.spf");
				StartpointManager::get().loadStartpointsFromStream(l_ifstream);
			}
			return ListenerResult::Propagate;
		},
		"test-key-1"_spr
	);

	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			if (event->isDown() && isPlusMode()) {
				OutputStream l_ofstream = OutputStream("./testPlayerCheckpoint.spf");
				StartpointManager::get().saveStartpointsToStream(l_ofstream);
			}
			return ListenerResult::Propagate;
		},
		"test-key-2"_spr
	);
	// EndTodo
}