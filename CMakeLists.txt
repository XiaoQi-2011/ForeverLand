cmake_minimum_required(VERSION 3.28)
project(ForeverLand)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(ForeverLand main.cpp
        Data.h
        library.h
        Base64.h
        Event/Event.h
        Event/InventoryEvent.h
        Event/Setting.h
        Event/Fighting.h
        Event/Fuben.h
        ConstDatas.h
        Event/Producer.h
        Event/Mine.h
        Event/Trade.h
        Event/Fuben/Adventure.h
        Event/Fuben/InfiniteTower.h
        Event/Fuben/TrainingBot.h
        Event/Fuben/InfiniteTrials.h
        Event/Fuben/WorldBoss.h
        Event/WorkArea.h
        resources.rc
)

