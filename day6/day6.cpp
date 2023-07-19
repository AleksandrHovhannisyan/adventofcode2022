#include <map>
#include <iostream>
#include "day6.h"

std::optional<int> getNumCharactersToPacketMarker(std::string buffer, unsigned int markerLength) {
    unsigned int slidingWindowStart = 0;

    while (slidingWindowStart <= buffer.length() - markerLength) {
        auto index = slidingWindowStart;
        std::map<char, unsigned int> seenCharacterIndices {};
        char character;

        // Look at markerLength characters starting from slidingWindowStart
        for (unsigned int i = 0; i < markerLength; i++) {
            index = slidingWindowStart + i;
            character = buffer[index];
            // We've already seen this character
            if (seenCharacterIndices.contains(character)) {
                // We know for a fact that the next legit sequence has to start from at least this index, or else it will
                // once again encounter both seenCharacterIndices[character] and the duplicate we just saw. So we have to discard
                // the first seen instance of that duplicate character and look at the next window.
                slidingWindowStart = seenCharacterIndices[character] + 1;
                break;
            }
            // We haven't seen this character before. Track its index.
            seenCharacterIndices[character] = index;
        }
        // We filled up the map on this pass with markerLength characters without finding a duplicate, so this must be the solution
        if (seenCharacterIndices.size() == markerLength) {
            return index + 1;
        }
    }

    // In the real world, it's not guaranteed that a solution would exist
    return std::nullopt;
}
