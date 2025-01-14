//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include "Image.h"
#include "Objects/Scene.h"
#include "Objects/Camera.h"
#include "Util/Property.h"
#include <thread>

class Pathtracer {
public:
    Pathtracer();

    void Render(std::string outputFile = "");

    void Resize(int width, int height);

    std::shared_ptr<Scene> GetScene() { return m_scene; }
    std::shared_ptr<Camera> GetCamera() { return m_camera; }
    std::shared_ptr<Image> GetImage() { return m_image; }
    int GetWidth() { return m_width; }
    int GetHeight() { return m_height; }

    Property<int> samplesPerPixel = 1;
    Property<int> maxDepth = 2;
    Property<int> threadCount = std::thread::hardware_concurrency();
    Property<bool> antialias = Property(true, std::function<void(bool)>(std::bind(&Pathtracer::AntialiasCallback, this, std::placeholders::_1)));
private:
    std::shared_ptr<Image> m_image = std::make_shared<Image>(0, 0);
    std::shared_ptr<Scene> m_scene = std::make_shared<Scene>();
    std::shared_ptr<Camera> m_camera = std::make_shared<Camera>();

    void AntialiasCallback(bool value) {
        m_camera->antialias = value;
    }

    int m_width, m_height;
};