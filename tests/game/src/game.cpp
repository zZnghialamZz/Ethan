#include "game.h"

Game::Game() {}

Game::~Game() {}

ethan::Application *ethan::CreateApplication() { return new Game(); }
