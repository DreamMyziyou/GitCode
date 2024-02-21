//
// Created by WeslyChen on 2024/1/20.
//

#include <gtest/gtest.h>

#include "Core/World/World.h"

TEST(World, ECS)
{
    struct PositionComponent
    {
        int x = 0;
        int y = 0;
    };

    struct MoveComponent
    {
        bool isMovable = false;
    };

    auto world = World::GetWorld();
    auto entity = world->create();
    world->emplace<PositionComponent>(entity, PositionComponent{1, 2});
    world->emplace<MoveComponent>(entity, MoveComponent{true});

    auto positionView = world->view<PositionComponent>();
    for (const auto& [entityKey, position] : positionView.each())
    {
        EXPECT_TRUE(entity == entityKey);
        EXPECT_TRUE(position.x == 1 && position.y == 2);
    }

    auto moveView = world->view<MoveComponent>();
    for (const auto& [entityKey, move] : moveView.each())
    {
        EXPECT_TRUE(entity == entityKey);
        EXPECT_TRUE(move.isMovable);
    }
}