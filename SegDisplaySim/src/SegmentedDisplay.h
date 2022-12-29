#pragma once
#include <string>

namespace segdisp {

	struct signalMappingHub {
		uint8_t binaryMapping;
		char stringMapping[7];
	};

	class SegmentedDisplay {
	private:
		typedef struct segmentSignals {
			bool light_on;	// Is this segment on or off?
			char debug_segment_char;	// What character is this segment denoted by? { A - G }
		} seg_sig_t;

		const seg_sig_t SEG_SIGS[7] = {
			{false, 'A'},
			{false, 'B'},
			{false, 'C'},
			{false, 'D'},
			{false, 'E'},
			{false, 'F'},
			{false, 'G'}
		};

	public:
		SegmentedDisplay();
		~SegmentedDisplay();
		void setMappings(uint8_t digit);
		static uint8_t getBinaryMapping(uint8_t& digit);
		static std::string mappingToString(uint8_t& binaryMapping);
	};
}