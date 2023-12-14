cmake_minimum_required(VERSION 3.26)
# Configurando o padrão c++
set(CMAKE_CXX_STANDARD 17)

# INIT NO SCREEN BUGFIX
# Em alguns casos, o programa pode não renderizar a tela. Por isso temos
# as seguintes linhas. Caso encontre algum problema, comente-as.
set(CMAKE_SKIP_RPATH ON)
set(CMAKE_SKIP_RPATH ON CACHE BOOL "Skip RPATH" FORCE)
# END NO SCREEN BUGFIX
####### DO NOT EDIT ABOVE

# Configurando o nome e executável do projeto
set(PROJECT_NAME "BrazilStrikers")
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME}
        Source/Main.cpp
        Source/Math.cpp
        Source/Random.cpp
        Source/Actors/Actor.cpp
        Source/Components/Component.cpp
        Source/Game.cpp
        Source/Components/DrawComponents/DrawComponent.cpp
        Source/Components/DrawComponents/DrawComponent.h
        Source/Components/RigidBodyComponent.cpp
        Source/Components/RigidBodyComponent.h
        Source/Components/ColliderComponents/CircleColliderComponent.cpp
        Source/Components/ColliderComponents/CircleColliderComponent.h
        Source/Json.h
        Source/Components/DrawComponents/DrawSpriteComponent.cpp
        Source/Components/DrawComponents/DrawSpriteComponent.h
        Source/Components/DrawComponents/DrawPolygonComponent.cpp
        Source/Components/DrawComponents/DrawPolygonComponent.h
        Source/Components/ColliderComponents/AABBColliderComponent.cpp
        Source/Components/ColliderComponents/AABBColliderComponent.h
        Source/Components/DrawComponents/DrawAnimatedComponent.cpp
        Source/Components/DrawComponents/DrawAnimatedComponent.h
        Source/Actors/Spawner.cpp
        Source/Actors/Spawner.h
        Source/Actors/Field.cpp
        Source/Actors/Field.h
        Source/Actors/Ball.cpp
        Source/Actors/Ball.h
        Source/Actors/Ball.h
        Source/Actors/Ball.h
        Source/Actors/Ball.h
        Source/Actors/Characters/Character.cpp
        Source/Actors/Characters/Character.h
        Source/Collision.cpp
        Source/Collision.h
        Source/Actors/Wall.cpp
        Source/Actors/Wall.h
        Source/Components/DrawComponents/DrawTileComponent.cpp
        Source/AudioSystem.h
        Source/AudioSystem.cpp
        Source/AudioSystem.h
        Source/AudioSystem.cpp
        Source/GameClock.cpp
        Source/GameClock.h
        Source/Actors/ScoreBoard.cpp
        Source/Actors/ScoreBoard.h
        Source/Components/DrawComponents/DrawFontComponent.cpp
        Source/Components/DrawComponents/DrawFontComponent.h
        Source/AudioSystem.cpp
)

####### DO NOT EDIT BELLOW
find_package(SDL2 2.28.2 EXACT REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
#find_library(SDL2_mixer SDL2_mixer)
#find_library(SDL2TTF_LIBRARIES SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf ${SDL2TTF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)
