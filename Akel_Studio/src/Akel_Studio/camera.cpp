// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 23/08/2022
// Updated : 15/05/2023

#include "camera.h"

SceneCamera::SceneCamera(double x, double y, double z, Ak::WindowComponent* window) : Ak::Component("scene_camera"), _up(0, 1, 0)
{
}

void SceneCamera::onAttach()
{
}

void SceneCamera::update()
{
}

void SceneCamera::onEvent(Ak::Input& input)
{
}

void SceneCamera::onRender()
{
}

void SceneCamera::update_view()
{
}
