//
// Created by Lucas on 21-05-2024.
//

#include "Pathtracer.h"
#include "Math/Vector3.h"
#include "Util/BS_thread_pool.hpp"
#include <array>
#include <future>
#include <iostream>
#include <omp.h>
#include <thread>
#include <vector>

Pathtracer::Pathtracer() {
    m_image = std::make_shared<Image>(1, 1);

    Resize(128, 128);
}

void Pathtracer::Render(std::string outputFile) {
    m_camera->CalculateValues(m_width, m_height);

    float pixelSamplesScale = 1.0f / samplesPerPixel;

    BS::thread_pool pool(threadCount);
    std::cout << "Running on " << threadCount << " threads" << std::endl;

    std::vector<std::vector<Vector3>> threadSafeColors(threadCount, std::vector<Vector3>(m_width * m_height));

    for (int x = 0; x < m_width; x += batchSize) {
        for (int y = 0; y < m_height; y += batchSize) {
            // _ is never used and is just a way to remove the warning nodiscard
            auto _ = pool.submit_task([x, y, this, pixelSamplesScale, outputFile, &threadSafeColors] {
                for (int dx = 0; dx < batchSize; dx++) {
                    for (int dy = 0; dy < batchSize; dy++) {
                        if (x + dx >= m_width || y + dy >= m_height)
                            continue;

                        Vector3 color;

                        #pragma omp simd
                        for (int i = 0; i < samplesPerPixel; i++) {
                            Ray ray = m_camera->GetRay(x, y);
                            color += m_camera->RayColor(*m_scene, ray, maxDepth);
                        }

                        color *= pixelSamplesScale;

                        int threadIndex = std::hash<std::thread::id>{}(std::this_thread::get_id()) % threadCount;

                        threadSafeColors[threadIndex][y * m_width + x] = color;
                    }
                }
            });
        }
    }

    pool.wait();

    for (int t = 0; t < threadCount; t++) {
        for (int x = 0; x < m_width; x++) {
            for (int y = 0; y < m_height; y++) {
                m_image->SetPixel(x, y, threadSafeColors[t][y * m_width + x]);
            }
        }
    }


    if (!outputFile.empty())
        m_image->Save(outputFile);
}

void Pathtracer::Resize(int width, int height) {
    m_width = width;
    m_height = height;

    m_image->Resize(width, height);
}
