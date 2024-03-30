#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <hooks/PlayLayer.hpp>
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
}

// int getPlayerGameMode(PlayerObject* p) {
// 	if (p->m_isShip) {
// 		return 1;
// 	}
// 	if (p->m_isBall) {
// 		return 2;
// 	}
// 	if (p->m_isBird) {
// 		return 3;
// 	}
// 	if (p->m_isDart) {
// 		return 4;
// 	}
// 	if (p->m_isRobot) {
// 		return 5;
// 	}
// 	if (p->m_isSpider) {
// 		return 6;
// 	}
// 	if (p->m_isSwing) {
// 		return 7;
// 	}
// 	return 0;
// }

// Speed getPlayerSpeed(PlayerObject* p) {
// 	if (p->m_playerSpeed == 0.7f) {
// 		return Speed::Slow;
// 	}
// 	if (p->m_playerSpeed == 0.9f) {
// 		return Speed::Normal;
// 	}
// 	if (p->m_playerSpeed == 1.1f) {
// 		return Speed::Fast;
// 	}
// 	if (p->m_playerSpeed == 1.3f) {
// 		return Speed::Faster;
// 	}
// 	if (p->m_playerSpeed == 1.6f) {
// 		return Speed::Fastest;
// 	}
// 	return Speed::Normal;
// }

// class $modify(PlayerObject) {
// 	public:
// 		void pushButton(PlayerButton p0) {
// 			PlayerObject::pushButton(p0);
// 			if (p0 != PlayerButton::Jump || this->m_isDead) {
// 				return;
// 			}
// 			PracticePlusPlayLayer* playLayer = static_cast<PracticePlusPlayLayer*>(PlayLayer::get());
// 			if (playLayer) {
				
// 				int sizeofNode = sizeof(CCNode);
// 				int sizeofCPO = sizeof(CheckpointObject);
// 				int sizeofPC = sizeof(PlayerCheckpoint);
// 				log::info("SIZEOF NODE: {}", sizeofNode);
// 				log::info("SIZEOF CPO: {}", sizeofCPO);
// 				log::info("SIZEOF PC: {}", sizeofPC);
// 				if (playLayer->m_fields->m_isPlusMode) {
// 					CheckpointObject *checkpointObject = playLayer->createCheckpoint();
// 					//CC_SAFE_RETAIN(checkpointObject);
// 					log::info("POS X: {}", checkpointObject->m_physicalCheckpointObject->getPositionX());
// 					log::info("POS Y: {}", checkpointObject->m_physicalCheckpointObject->getPositionY());

// 					GameObject* newphysicalCPO = GameObject::createWithFrame("square_01_001.png");
// 					CC_SAFE_RETAIN(checkpointObject->m_physicalCheckpointObject);
// 					newphysicalCPO->setID("Test");
// 					newphysicalCPO->setPosition(this->getPosition());
// 					CC_SAFE_RELEASE(checkpointObject->m_physicalCheckpointObject);
// 					checkpointObject->m_physicalCheckpointObject = newphysicalCPO;
					
// 					playLayer->addStartpoint(checkpointObject);
// 				}

// 				// StartPosObject* startPos = StartPosObject::create();

// 				// int mode = getPlayerGameMode(this);
// 				// log::info("mode: {}", mode);
// 				// startPos->m_levelSettings->m_startMode = mode;
// 				// startPos->m_levelSettings->m_isFlipped = this->m_isUpsideDown;
// 				// startPos->m_levelSettings->m_startSpeed = getPlayerSpeed(this);
// 				// //startPos->m_levelSettings->m_startMini = this->m_
// 				// log::info("speed: {}", this->m_playerSpeed);
// 				// //startPos->m_levelSettings->m_startMode = mode;
// 				// startPos->m_levelSettings->m_startMode = mode;
// 				// startPos->setPosition(this->getPosition());
// 				// playLayer->addObject(startPos);
// 				// //playLayer->m_objectLayer->addChild(startPos);
// 			}
// 		}
// };