#include "SegmentedDisplay.h"

typedef unsigned char uint8_t;
const uint8_t NUMBER_OF_SEGMENTS = 7;

// Digit to Segment Display mappings for digits 0 - 9 inclusive
// the least significant bit (little-endian) represents A, most significant bit represents G
const int8_t b_mappings[10] = {
	0b0111111, // 0
	0b0000110, // 1
	0b1011011, // 2
	0b1001111, // 3
	0b1100110, // 4
	0b1101101, // 5
	0b1111101, // 6
	0b0000111, // 7
	0b1111111, // 8
	0b1101111  // 9
};

namespace segdisp {
	SegmentedDisplay::SegmentedDisplay() {}

	SegmentedDisplay::~SegmentedDisplay() {}

	void SegmentedDisplay::setMappings(uint8_t digit) {

	}

	uint8_t SegmentedDisplay::getBinaryMapping(uint8_t& digit) {
		return b_mappings[digit];
	}

	std::string SegmentedDisplay::mappingToString(uint8_t& binaryMapping) {
		std::string stringMapping;

		const char empty = '-';
		uint8_t mask = 0x1; // mask out the least significant bit
		for (int sig = 0; sig < NUMBER_OF_SEGMENTS; sig++) {
			
		}
		return std::string();
	}


}

