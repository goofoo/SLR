//
//  Scene.h
//
//  Created by 渡部 心 on 2015/07/11.
//  Copyright (c) 2015年 渡部 心. All rights reserved.
//

#ifndef __SLRSceneGraph__Scene__
#define __SLRSceneGraph__Scene__

#include <libSLR/defines.h>
#include "references.h"

namespace SLRSceneGraph {
    class SLR_SCENEGRAPH_API Scene {
        InternalNodeRef m_rootNode;
        InfiniteSphereNodeRef m_envNode;
        std::unique_ptr<SLR::Scene> m_raw;
    public:
        Scene();
        ~Scene();
        
        InternalNodeRef &rootNode() { return m_rootNode; };
        void setEnvNode(const InfiniteSphereNodeRef &node) { m_envNode = node; };
        
        void build(const SLR::Scene** scene, SLR::ArenaAllocator &mem);
        
        const SLR::Scene* raw() const { return m_raw.get(); }
    };
    
    struct SLR_SCENEGRAPH_API RenderingContext {
        std::unique_ptr<SLR::Renderer> renderer;
        int32_t width;
        int32_t height;
        float timeStart;
        float timeEnd;
        float brightness;
        int32_t rngSeed;
        
        RenderingContext();
        ~RenderingContext();
        
        RenderingContext &operator=(RenderingContext &&ctx);
    };
}

#endif
