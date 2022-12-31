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

	void SegmentedDisplay::setMappings(uint8_t digit) 
	{
		seg_sig_t* ref = SEG_SIGS;
		consumeBinaryMapping(getBinaryMapping(digit), [&](bool sig_state, int count) -> void { ref[count].debug_segment_char = sig_state; });
	}

	uint8_t SegmentedDisplay::getBinaryMapping(uint8_t& digit)
	{
		return b_mappings[digit];
	}

	std::string SegmentedDisplay::mappingToString(uint8_t binaryMapping)
	{
		std::string stringMapping;
		auto& ref = SEG_SIGS;
		uint8_t index = 0;

		consumeBinaryMapping(binaryMapping, [&](bool sig_state, int count) -> void {
			if (sig_state) stringMapping.push_back(ref[count].debug_segment_char);
			else stringMapping.push_back('-');
		});

		return stringMapping;
	}

	void SegmentedDisplay::consumeBinaryMapping(uint8_t binaryMapping, std::function<void(bool, int)> some_func) 
	{
		uint8_t lsb_mask = 0x1;
		int count = 0;

		while (count < NUMBER_OF_SEGMENTS) {
			bool current_sig_state = binaryMapping & lsb_mask;
			some_func(current_sig_state, count);
			binaryMapping = binaryMapping >> 1;
			count++;
		}
	}


}

