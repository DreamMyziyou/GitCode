//
// Created by WeslyChen on 2024/1/20.
//

#include "Application.h"

#include "Core/Geometry/MeshComponent.h"

using namespace std;

Application::Application()
{
    auto world = World::GetWorld();
    auto entity = world->create();

    MeshComponent mesh;
    mesh.vertices = {{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}}, {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}, {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
    world->emplace<MeshComponent>(entity, std::move(mesh));
}

Application::~Application() {}