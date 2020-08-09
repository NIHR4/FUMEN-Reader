#pragma once
#include "swappable.h"

namespace LE {
	struct FumenNote {
		int drum;
		float offset;
		int padding[2];
		short initialItem;
		short pointDistribution;
		float drumrollDuration; //length of drum/ballon in ms
	};

	struct FumenBar {
		float bpm;
		float offset;
		bool gogotime;
		bool  barlineVisible;
		short reserved2;
		unsigned char reserved3[24];
		int reserved4;
		int totalNotes;
		float hs; //horizontal  speed
	};
}

namespace BE {
	//TODO: Add structures compatible with WII U FUMEN file format, alongisde endianness swapping methods.
}