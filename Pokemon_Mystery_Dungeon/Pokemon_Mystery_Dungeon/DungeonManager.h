#pragma once
#include "config.h"

class PokemonBuilder;
class PokemonPool;

class DungeonManager
{
private:
    // ���� �̸�, ���� ����
    unordered_map<string, DungeonSpawnInfo> dungeonSpawnMap;
    
    PokemonBuilder* builder;
    PokemonPool* pool;

public:
    void Init();
    void LoadDungeonData();
    void EnterDungeon(string dungeonName);
    void ExitDungeon();

    DungeonManager() {};
    virtual ~DungeonManager() {};
};