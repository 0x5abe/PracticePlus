#include <Geode/Geode.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;

void setupKeybinds();

$on_mod(Loaded) {
	setupKeybinds();
}

void setupKeybinds() {
	using namespace keybinds;

	BindManager::get()->registerBindable({
		"place-sp"_spr,
		"Place startpoint",
		"Places a startpoint when in practice mode",
		{ Keybind::create(KEY_C, Modifier::None) },
		Category::PLAY,
	});

	BindManager::get()->registerBindable({
		"remove-sp"_spr,
		"Remove startpoint",
		"Removes the most recently placed startpoint when in practice mode",
		{ Keybind::create(KEY_V, Modifier::None) },
		Category::PLAY,
	});

	BindManager::get()->registerBindable({
		"switch-sp-prev"_spr,
		"Switch to next startpoint",
		"Switches the current startpoint to the previous one in the level when in practice mode",
		{ Keybind::create(KEY_Q, Modifier::None) },
		Category::PLAY,
	});

	BindManager::get()->registerBindable({
		"switch-sp-next"_spr,
		"Switch to previous startpoint",
		"Switches the current startpoint to the next one in the level when in practice mode",
		{ Keybind::create(KEY_E, Modifier::None) },
		Category::PLAY,
	});

	BindManager::get()->registerBindable({
		"toggle-sp-visible"_spr,
		"Toggle show startpoints",
		"Toggles between showing and hiding startpoints",
		{ Keybind::create(cocos2d::KEY_M, Modifier::None) },
		Category::PLAY,
	});

	// TODO REMOVE
	BindManager::get()->registerBindable({
		"test-key-2"_spr,
		"Test 2",
		"Save startpoints",
		{ Keybind::create(KEY_K, Modifier::None) },
		Category::PLAY,
	});
	// ENDTODO
}