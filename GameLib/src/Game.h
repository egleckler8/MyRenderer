/**
 * @file Game.h
 * @author Elijah Gleckler
 *
 * The active game state. Collection
 * of GameObjects
 *
 * TODO 
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_GAME_H
#define LEARNING_OPENGL_GAMELIB_SRC_GAME_H

#include <vector>

class GameObject;
/**
 * The active game state. Collection
 * of GameObjects
 */
class Game
{
private:

    /// All the loaded game objects in this game
    std::vector<GameObject> mObjects;

public:

    /// Default constructor (disabled)
    Game() = delete;

    /// Copy constructor (disabled)
    Game(const Game &) = delete;

    /// Assignment operator
    void operator=(const Game &) = delete;

    // ****************************************************************

    void AddObject();


};

#endif //LEARNING_OPENGL_GAMELIB_SRC_GAME_H
