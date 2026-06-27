cmake_minimum_required(VERSION 3.28)
project(ForeverLand)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(ForeverLand main.cpp
        Lib/Data.h
        Lib/library.h
        Lib/Base64.h
        Event/Event.h
        Event/InventoryEvent.h
        Event/Setting.h
        Event/Fighting.h
        Event/Fuben.h
        Lib/ConstDatas.h
        Event/Producer.h
        Event/Mine.h
        Event/Trade.h
        Event/Fuben/Adventure.h
        Event/Fuben/Adventure.cpp
        Event/Fuben/InfiniteTower.h
        Event/Fuben/InfiniteTower.cpp
        Event/Fuben/TrainingBot.h
        Event/Fuben/InfiniteTrials.h
        Event/Fuben/InfiniteTrials.cpp
        Event/Fuben/WorldBoss.h
        Event/WorkArea.h
        Lib/WorldData.h
        Lib/StrData.h
        Lib/Item.h
        Lib/Player.h
        Lib/Entity.h
        Event/Fighting.cpp
        Lib/Data.cpp
        Event/Mine.cpp
        Event/InventoryEvent.cpp
        Event/Producer.cpp
        Event/Trade.cpp
        Event/WorkArea.cpp
        Event/Setting.cpp
)

