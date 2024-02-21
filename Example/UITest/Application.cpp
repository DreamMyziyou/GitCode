//
// Created by WeslyChen on 2024/1/20.
//

#include "Application.h"

#include "Core/Geometry/MeshComponent.h"
#include "Core/World/World.h"

using namespace std;

Application::Application()
{
    auto world = World::GetWorld();
    auto entity = world->create();

    MeshComponent mesh;
    mesh.vertices = {{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                     {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                     {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
                     {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};
    mesh.indices = {0, 1, 2, 2, 3, 0};
    world->emplace<MeshComponent>(entity, std::move(mesh));
}

Application::~Application() {}