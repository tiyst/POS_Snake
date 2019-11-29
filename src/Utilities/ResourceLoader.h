//
// Created by tiyst on 16/11/2019.
//

#ifndef SNAKERINO_RESOURCELOADER_H
#define SNAKERINO_RESOURCELOADER_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <iostream>
#include "NonCopyable.hpp"
#include "NonMovable.hpp"

//Singleton
class ResourceLoader : public NonCopyable , NonMovable {
public:
	static ResourceLoader& getInstance() {
		static ResourceLoader instance; // Created on stack, initialised once, and sure to be destroyed
		return instance;
	}

	void initResourceLoader() {
		try {
			defaultFont = new sf::Font();
			defaultFont->loadFromFile("../res/Engine/Roboto-Thin.ttf");
//			defaultSound.loadFromFile("../res/Engine/");

			defaultTexture = new sf::Texture();
			defaultTexture->loadFromFile("../res/Engine/texture.png");
		} catch (const std::out_of_range& exc) {
			std::cerr << "Missing Engine mandatory files.\n";
		}
	}

	sf::Font* addFont(const std::string& key, const std::string& filePath) {
		sf::Font* font = new sf::Font();
		if(font->loadFromFile(filePath)) {
			fontsMap.insert(std::make_pair(key, font));
		} else {
			fontsMap.insert(std::make_pair(key, defaultFont));
		}
		return font;
	}

	sf::SoundBuffer* addSound(const std::string& key, const std::string& filePath) {
		sf::SoundBuffer* sb = new sf::SoundBuffer();
		if(sb->loadFromFile(filePath)) {
			soundBufferMap.insert(std::make_pair(key, sb));
		} else {
			soundBufferMap.insert(std::make_pair(key, defaultSound));
		}
		return sb;

	}

	sf::Texture* addTexture(const std::string& key, const std::string& filePath) {
		sf::Texture* txt = new sf::Texture();
		if(txt->loadFromFile(filePath)) {
			texturesMap.insert(std::make_pair(key, txt));
		} else {
			texturesMap.insert(std::make_pair(key, defaultTexture));
		}
		return txt;
	}

	sf::Font* getFont(const std::string& key) {
		try {
			return fontsMap.at(key);
		} catch (const std::out_of_range& exc) {
			return defaultFont;
		}
	}

	sf::SoundBuffer* getSoundBuffer(const std::string& key) {
		sf::SoundBuffer snd;
		try {
			return soundBufferMap.at(key);
		} catch (const std::out_of_range& exc) {
			return defaultSound;
		}
	}

	sf::Texture* getTexture(const std::string& key) {
		try {
			return texturesMap.at(key);
		} catch (const std::out_of_range& exc) {
			return defaultTexture;
		}
	}

	sf::Font* getDefaultFont() {
		return defaultFont;
	}

	sf::Texture* getDefaultTexture() {
		return defaultTexture;
	}

	sf::SoundBuffer* getDefaultSoundBuffer() {
		return defaultSound;
	}

	std::unordered_map<std::string, sf::Texture*> getTextures() {
		return texturesMap;
	}

	std::unordered_map<std::string, sf::SoundBuffer*> getSoundBuffers() {
		return soundBufferMap;
	}

	std::unordered_map<std::string, sf::Font*> getFonts() {
		return fontsMap;
	}

private:
	sf::Font* defaultFont;
	sf::SoundBuffer* defaultSound;
	sf::Texture* defaultTexture;
	std::unordered_map<std::string, sf::Texture*> texturesMap;
	std::unordered_map<std::string, sf::SoundBuffer*> soundBufferMap;
	std::unordered_map<std::string, sf::Font*> fontsMap;
};

#endif //SNAKERINO_RESOURCELOADER_H
