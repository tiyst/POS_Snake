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

//Singleton
class ResourceLoader {
public:
	static ResourceLoader& getResourceLoader() {
		static ResourceLoader instance; // Guaranteed to be destroyed. Instantiated on first use.
		return instance;
	}

	bool addFont(const std::string& key, const std::string& filePath) {
		sf::Font font;
		if(font.loadFromFile(filePath)) {
			fontsMap.insert(std::make_pair(key, &font));
			return true;
		}
		return false;
	}

	bool addSound(const std::string& key, const std::string& filePath) {
		sf::SoundBuffer sb;
		if(sb.loadFromFile(filePath)) {
			soundBufferMap.insert(std::make_pair(key, &sb));
			return true;
		}
		return false;

	}

	bool addTexture(const std::string& key, const std::string& filePath) {
		sf::Texture txt;
		if(txt.loadFromFile(filePath)) {
			texturesMap.insert(std::make_pair(key, &txt));
			return true;
		}
		return false;
	}

	sf::Font* getFont(const std::string& key) {
		sf::Font* font;
		try {
			font = fontsMap.at(key);
			return font;
		} catch (const std::out_of_range& exc) {
			return &defaultFont;
		}
	}

	sf::SoundBuffer* getSoundBuffer(const std::string& key) {
		sf::SoundBuffer* snd;
		try {
			snd = soundBufferMap.at(key);
			return snd;
		} catch (const std::out_of_range& exc) {
			return &defaultSound;
		}
	}

	sf::Texture* getTexture(const std::string& key) {
		sf::Texture* txt;
		try {
			txt = texturesMap.at(key);
			return txt;
		} catch (const std::out_of_range& exc) {
			return &defaultTexture;
		}
	}

	sf::Font* getDefaultFont() {
		return &defaultFont;
	}

	sf::Texture* getDefaultTexture() {
		return &defaultTexture;
	}

	sf::SoundBuffer* getDefaultSoundBuffer() {
		return &defaultSound;
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
	ResourceLoader() {
		try {
			defaultFont.loadFromFile("../Resources/engine/Roboto-Thin.ttf");
//			defaultSound->loadFromFile("../Resources/engine/");
			defaultTexture.loadFromFile("../Resources/engine/texture.jpg");
		} catch (const std::out_of_range& exc) {
			std::cerr << "Missing engine mandatory files.\n";
		}
	}

	sf::Font defaultFont;
	sf::SoundBuffer defaultSound;
	sf::Texture defaultTexture;
	std::unordered_map<std::string, sf::Texture*> texturesMap;
	std::unordered_map<std::string, sf::SoundBuffer*> soundBufferMap;
	std::unordered_map<std::string, sf::Font*> fontsMap;

public:
	//Apparently deleted functions should be public for better error messages
	//Deleting so we don't accidentally end up with more ResourceLoaders
//	ResourceLoader(ResourceLoader const&) = delete; //WHY NO WORK?
//	void operator=(ResourceLoader const&) = delete;
};


#endif //SNAKERINO_RESOURCELOADER_H
