#include "PlayLayer.hpp"
#include <filesystem>
#include <managers/StartpointManager.hpp>
#include <util/algorithm.hpp>
#include <util/filesystem.hpp>

using namespace geode::prelude;
using namespace persistenceAPI;

void PPPlayLayer::writeSpfHeader() {
	Stream& l_stream = StartpointManager::get().m_stream;
	l_stream.write(s_spfMagicAndVer,sizeof(s_spfMagicAndVer));
	l_stream.writeZero(16-sizeof(s_spfMagicAndVer));
	unsigned int l_levelStringHash = util::algorithm::hash_string(m_level->m_levelString.c_str());
	l_stream << l_levelStringHash;
}

void PPPlayLayer::saveStartpoints() {
	StartpointManager& l_startpointManager = StartpointManager::get();
	//log::info("SaveStartpoints Gets run");
	switch (m_fields->m_startpointSavingState) {
		case SavingState::Setup: {
			//log::info("Goes into beginning");
			m_fields->m_remainingStartpointSaveCount = l_startpointManager.getStartpointCount();
			if (m_fields->m_remainingStartpointSaveCount == 0) {
				m_fields->m_startpointSavingState = SavingState::Ready;
				break;
			}
		
			std::string l_filePath = getStartpointFilePath();
			std::string l_fileDirectory = util::filesystem::getParentDirectoryFromPath(l_filePath);
			if (!std::filesystem::exists(l_fileDirectory) && !std::filesystem::create_directories(l_fileDirectory)) {
				m_fields->m_startpointSavingState = SavingState::Ready;
				break;
			}

			Stream& l_stream = StartpointManager::get().m_stream;
			if (!l_stream.setFile(l_filePath, true)) {
				m_fields->m_startpointSavingState = SavingState::Ready;
				break;
			}

			showSavingIcon(true);
			
			writeSpfHeader();

			l_stream << m_fields->m_remainingStartpointSaveCount;

			m_fields->m_startpointSavingState = SavingState::Started;
			// falls through
		}
		case SavingState::Started: {
			if (m_fields->m_remainingStartpointSaveCount > 0) {
				l_startpointManager.saveOneStartpointToStream(l_startpointManager.getStartpointCount()-m_fields->m_remainingStartpointSaveCount);
				m_fields->m_remainingStartpointSaveCount--;
				//log::info("Remaining save count: {}", m_fields->m_remainingStartpointSaveCount);
				CCScene* l_currentScene = CCScene::get();
				if (l_currentScene) {
					l_currentScene->runAction(
						CCSequence::create(
							CCDelayTime::create(0.0f),
							CCCallFunc::create(
								this,
								callfunc_selector(PPPlayLayer::saveStartpoints)
							),
							nullptr
						)
					);
				}
				break;
			}
			if (m_fields->m_remainingStartpointSaveCount == 0) {
				StartpointManager& l_startpointManager = StartpointManager::get();
				Stream& l_stream = StartpointManager::get().m_stream;
				l_stream.seek(sizeof(s_spfMagicAndVer));
				bool o_finishedSaving = true;
				l_stream.write((char*)&o_finishedSaving,sizeof(bool));
				l_startpointManager.endStream();
				m_fields->m_startpointSavingState = SavingState::Ready;
			}
			// falls through
		}
		case SavingState::Ready: {
			hideSavingIcon();
			break;
		}
	}
}