//
// Created by Lucas on 21-05-2024.
//

#include "Pathtracer.h"
#include "Util/BS_thread_pool.hpp"
#include <thread>

Pathtracer::Pathtracer() {
    m_image = std::make_shared<Image>(1, 1);

    Resize(128, 128);
}

void Pathtracer::Render(std::string outputFile) {
    m_camera->CalculateValues(m_width, m_height);

    float pixelSamplesScale = 1.0f / samplesPerPixel;

    std::cout << "Running on " << threadCount << " threads" << std::endl;

    BS::thread_pool pool(threadCount);

    for (int x = 0; x < m_width; x += batchSize) {
        for (int y = 0; y < m_height; y += batchSize) {
            auto _ = pool.submit_task([x, y, this, pixelSamplesScale, outputFile] {
                for (int dx = 0; dx < batchSize; dx++) {
                    for (int dy = 0; dy < batchSize; dy++) {
                        if (x + dx >= m_width || y + dy >= m_height)
                            continue;

                        Vector3 color;

                        for (int i = 0; i < samplesPerPixel; i++) {
                            Ray ray = m_camera->GetRay(x + dx, y + dy);
                            color += m_camera->RayColor(*m_scene, ray, maxDepth);
                        }

                        color *= pixelSamplesScale;

                        m_image->SetPixel(x + dx, y + dy, color);
                    }
                }
            });
        }
    }

    pool.wait();

    if (!outputFile.empty())
        m_image->Save(outputFile);
}

void Pathtracer::Resize(int width, int height) {
    m_width = width;
    m_height = height;

    m_image->Resize(width, height);
}
