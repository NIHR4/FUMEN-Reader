#include <iostream>
#include <fstream>
#include <vector>
#include "format14.h"
#include  "fumentypes.h"
#define TO_BYTEPTR(val) (char*)&val

int main(int argc, char** argv) {
	

	std::cout << "Introduce path to FUMEN file: ";
	std::string filename;
	if (argc <= 1) std::getline(std::cin, filename);
	else filename = argv[1];

	std::ifstream binarystream(filename, std::ifstream::binary);
	
	if (binarystream.is_open() == false) { 
		std::cerr << "Could not open file\n";
		return 0; 
	}

	binarystream.seekg(0, binarystream.end);
	size_t fileLen = binarystream.tellg();
	binarystream.seekg(0x208, binarystream.beg);
	

	std::vector<std::pair<LE::FumenBar, std::vector<LE::FumenNote>>>FumenData;

	while (binarystream.tellg() < fileLen) {
		LE::FumenBar tBar;
		binarystream.read(TO_BYTEPTR(tBar), sizeof(LE::FumenBar));
		std::vector<LE::FumenNote>notes;
		for (int i = 0; i < tBar.totalNotes; i++) {
			LE::FumenNote note;
			binarystream.read(TO_BYTEPTR(note), sizeof(LE::FumenNote));
			notes.push_back(note);
			if (note.drum == 6 || note.drum == 9) binarystream.seekg((size_t)binarystream.tellg() + 8, std::ios_base::beg);
		}


		binarystream.seekg((size_t)binarystream.tellg() + 16, std::ios_base::beg);
		FumenData.push_back({ tBar,notes });
	}
	std::ofstream outstream(filename + ".txt");
	
	for(int barIndex = 0; barIndex < FumenData.size();barIndex++){
		outstream << string_format(
			"Fumen Bar #%i{\nBPM = %f\n Offset = %f\n GogoTime = %i\n ShowBarline = %i\n TotalNotes = %i\n HS = %f\n }\n\n",
			barIndex,
			FumenData[barIndex].first.bpm,
			FumenData[barIndex].first.offset,
			FumenData[barIndex].first.gogotime,
			FumenData[barIndex].first.barlineVisible,
			FumenData[barIndex].first.totalNotes,
			FumenData[barIndex].first.hs
		);

		for (int noteIndex = 0; noteIndex < FumenData[barIndex].second.size(); noteIndex++) {
			outstream << string_format(
				"Bar #%i + Note #%i{\n Drum = %i\n Offset = %f\n InitialItem = %i\n PointDistribution = %i\n DrumrollDuration = %f\n };\n\n",
				barIndex,
				noteIndex,
				FumenData[barIndex].second[noteIndex].drum,
				FumenData[barIndex].second[noteIndex].offset,
				FumenData[barIndex].second[noteIndex].initial_item,
				FumenData[barIndex].second[noteIndex].point_distribution,
				FumenData[barIndex].second[noteIndex].drumroll_duration
			);
		}
		outstream << "====END-OF-BAR===\n\n";
	}
	std::cout << "Done!\n";
	return 0;
}