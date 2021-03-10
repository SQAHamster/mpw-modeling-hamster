#ifndef DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_GAMESTRINGIFIER_H
#define DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_GAMESTRINGIFIER_H

#include <memory>
#include <string>

#include "HamsterGame.h"

namespace util {

/**
 * Helper class to serialize / deserialize HamsterGame to / from Strings
 */
class GameStringifier {
public:
    GameStringifier() = delete;

    /**
     * Creates a HamsterGame from the given String. The game will not be started.
     * @param map Encoded game, which uses the following characters
     *            '#' for a Wall
     *            '*' for one grain (note: multiple grains have to be placed with TerritoryBuilder separately
     *            '<' '^' '>' 'v' for the default Hamster in the related direction
     *            ';' for the end of a row
     */
    static std::shared_ptr<hamster::HamsterGame> createFromString(const std::string& map);

    /**
     * Creates a HamsterGame from the given String and starts the game.
     * @param map Encoded game, which uses the following characters
     *            '#' for a Wall
     *            '*' for one grain (note: multiple grains have to be placed with TerritoryBuilder separately
     *            '<' '^' '>' 'v' for the default Hamster in the related direction
     *            ';' for the end of a row
     */
    static std::shared_ptr<hamster::HamsterGame> createFromStringStarted(const std::string& map);

    /**
     * Converts the given game to a simple String.
     *            '#' for a Wall
     *            '*' for one grain (note: multiple grains have to be placed with TerritoryBuilder separately
     *            '<' '^' '>' 'v' for the default Hamster in the related direction
     *            ';' for the end of a row
     * Note: the amount of grains on a field is ignored. If it is relevant, use {@link grainsOnTerritoryToString}.
     * @return the encoded String for the game.
     */
    static std::string toString(const hamster::HamsterGame& game);

    /**
     * Creates a String which states the number of grain on each tile.
     * ';' is used to mark the end of a row.
     * @return the encoded String which contains the number for each tile.
     */
    static std::string grainsOnTerritoryToString(const hamster::HamsterGame& game);
};

}


#endif //DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_GAMESTRINGIFIER_H
