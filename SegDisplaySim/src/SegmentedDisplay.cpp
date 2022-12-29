#include "SegmentedDisplay.h"

typedef unsigned char uint8_t;
const uint8_t NUMBER_OF_SEGMENTS = 7;

// Digit to Segment Display mappings for digits 0 - 9 inclusive
const int8_t mappings[10] = {
	0b1111110, // 0
	0b0110000, // 1
	0b1101101, // 2
	0b1111001, // 3
	0b0110011, // 4
	0b1011011, // 5
	0b1011111, // 6
	0b1110000, // 7
	0b1111111, // 8
	0b1111011  // 9
};

namespace segdisp {
	SegmentedDisplay::SegmentedDisplay() {

	}

	SegmentedDisplay::~SegmentedDisplay() {

	}

	void SegmentedDisplay::setMappings(uint8_t digit) {

	}

	uint8_t SegmentedDisplay::getMapping(uint8_t& digit) {
		return 0;
	}

	std::string SegmentedDisplay::mappingToString(uint8_t& mapping) {
		return std::string();
	}
}

