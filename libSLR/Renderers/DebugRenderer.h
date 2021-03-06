//
//  DebugRenderer.h
//
//  Created by 渡部 心 on 2016/02/06.
//  Copyright (c) 2016年 渡部 心. All rights reserved.
//

#ifndef DebugRenderer_h
#define DebugRenderer_h

#include "../defines.h"
#include "../references.h"
#include "../Core/Renderer.h"
#include "../Core/geometry.h"
#include "../Memory/Allocator.h"

namespace SLR {
    enum class ExtraChannel : uint32_t {
        GeometricNormal,
        ShadingNormal,
        ShadingTangent,
        Distance,
        NumChannels
    };
    
    class SLR_API DebugRenderer : public Renderer {
    private:
        struct Job {
            struct DebugInfo {
                SurfacePoint surfPt;
            };
            
            const DebugRenderer* renderer;
            std::array<std::unique_ptr<Image2D, Allocator::DeleterType>, (int)ExtraChannel::NumChannels>* chImages;
            const Scene* scene;
            
            ArenaAllocator* mems;
            IndependentLightPathSampler** pathSamplers;
            
            const Camera* camera;
            float timeStart;
            float timeEnd;
            
            ImageSensor* sensor;
            uint32_t imageWidth;
            uint32_t imageHeight;
            uint32_t numPixelX;
            uint32_t numPixelY;
            uint32_t basePixelX;
            uint32_t basePixelY;
            
            void kernel(uint32_t threadID);
            DebugInfo contribution(const Scene &scene, const WavelengthSamples &initWLs, const Ray &initRay,
                                   IndependentLightPathSampler &pathSampler, ArenaAllocator &mem) const;
        };
        std::array<bool, (int)ExtraChannel::NumChannels> m_channels;

    public:
        DebugRenderer(bool channelFlags[(int)ExtraChannel::NumChannels]);
        void render(const Scene &scene, const RenderSettings &settings) const override;
    };
}

#endif /* DebugRenderer_h */
