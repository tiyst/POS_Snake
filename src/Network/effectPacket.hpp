//
// Created by tiyst on 05/01/2020.
//

#ifndef SNAKERINO_PACKET_HPP
#define SNAKERINO_PACKET_HPP


#include <SFML/Network/Packet.hpp>
#include <iostream>

class effectPacket : sf::Packet {
private:
	virtual const void* onSend(std::size_t& size) {
		std::cout << "Received Data with size: " << size << std::endl;
	}

	virtual void onReceive(const void* data, std::size_t size) {
		std::cout << "Received Data: " << data << std::endl;
	}

public:
	int effect, x, y;

	effectPacket(int eff, int xp, int yp) {
		effect = eff;
		x = xp;
		y = yp;
	}
};

sf::Packet& operator <<(sf::Packet& packet, const effectPacket& effectPacket) {
	return packet << effectPacket.effect << effectPacket.x << effectPacket.y;
}

sf::Packet& operator >>(sf::Packet& packet, effectPacket& effectPacket) {
	return packet >> effectPacket.effect >> effectPacket.x >> effectPacket.y;
}


#endif //SNAKERINO_PACKET_HPP
