#include <string>
#include <optional>

/** Returns the last index of the start-of-packet-marker as defined by the day 6 problem */
std::optional<int> getNumCharactersToPacketMarker(std::string buffer, unsigned int markerLength);
