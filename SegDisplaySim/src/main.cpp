#include <iostream>
#include "SegmentedDisplay.h"

int main(void) {
	std::cout << "Hello world" << std::endl;

	// structure:
	// create a window
	// have buttons on the side
		// choose the "number to display"
	// display that number in the form of a seven segment digit

	segdisp::SegmentedDisplay seg;

	uint8_t digit = 1;
	bool on = true;
	uint8_t mapping = seg.getBinaryMapping(digit);
	std::cout << seg.mappingToString(mapping) << std::endl;
		

	// renderScreen
	// renderGUI
	// segmentLogic
	return 0;
}