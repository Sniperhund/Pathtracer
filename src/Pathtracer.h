//
// Created by Lucas on 14-05-2024.
//

#include "Image.h"
#include "Objects/Scene.h"
#include "Objects/Camera.h"
#include "GlobalSettings.h"
#include "ThreadPool.h"

class Pathtracer {
public:
    Pathtracer() {
        if (GlobalSettings::width == -1 || GlobalSettings::height == -1 || GlobalSettings::samplesPerPixel == -1 || GlobalSettings::maxDepth == -1) {
            throw std::runtime_error("Remember to set all the Global Settings variables before constructing the Pathtracer class");
        }

        m_image = Image(GlobalSettings::width, GlobalSettings::height);
    }

    void Render(std::string outputFile) {
        m_camera->CalculateValues();

        float pixelSamplesScale = 1.0f / GlobalSettings::samplesPerPixel;

        for (int x = 0; x < GlobalSettings::width; x++) {
            for (int y = 0; y < GlobalSettings::height; y++) {
                Vector3 color;

                for (int i = 0; i < GlobalSettings::samplesPerPixel; i++) {
                    Ray ray = m_camera->GetRay(x, y);
                    color += m_camera->RayColor(*m_scene, ray, GlobalSettings::maxDepth);
                }

                color *= pixelSamplesScale;

                m_image.SetPixel(x, y, color);
            }
        }

        m_image.Save(outputFile);
    }

    std::shared_ptr<Scene> GetScene() { return m_scene; }
    std::shared_ptr<Camera> GetCamera() { return m_camera; }
private:
    Image m_image = Image(0, 0);
    std::shared_ptr<Scene> m_scene = std::make_shared<Scene>();
    std::shared_ptr<Camera> m_camera = std::make_shared<Camera>();
};