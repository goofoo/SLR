//
//  ModifiedWardDurReflection.cpp
//
//  Created by 渡部 心 on 2015/09/06.
//  Copyright (c) 2015年 渡部 心. All rights reserved.
//

#include "ModifiedWardDurReflection.h"
#include "../BSDFs/ModifiedWardDurBRDF.h"
#include "../Memory/ArenaAllocator.h"
#include "../Core/textures.h"

namespace SLR {
    BSDF* ModifiedWardDurReflection::getBSDF(const SurfacePoint &surfPt, const WavelengthSamples &wls, ArenaAllocator &mem, float scale) const {
        SampledSpectrum R = m_reflectance->evaluate(surfPt, wls);
        float anisoX = m_anisoX->evaluate(surfPt);
        float anisoY = m_anisoY->evaluate(surfPt);
        return mem.create<ModifiedWardDurBRDF>(scale * R, anisoX, anisoY);
    }
}
