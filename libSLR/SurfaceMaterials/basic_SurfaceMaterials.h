//
//  basic_SurfaceMaterials.h
//
//  Created by 渡部 心 on 2015/09/05.
//  Copyright (c) 2015年 渡部 心. All rights reserved.
//

#ifndef __SLR__basic_SurfaceMaterials__
#define __SLR__basic_SurfaceMaterials__

#include "../defines.h"
#include "../references.h"
#include "../Core/surface_material.h"

namespace SLR {
    class SLR_API DiffuseReflection : public SurfaceMaterial {
        const SpectrumTexture* m_reflectance;
        const FloatTexture* m_sigma;
    public:
        DiffuseReflection(const SpectrumTexture* reflectance, const FloatTexture* sigma) :
        m_reflectance(reflectance), m_sigma(sigma) {}
        
        BSDF* getBSDF(const SurfacePoint &surfPt, const WavelengthSamples &wls, ArenaAllocator &mem, float scale = 1.0f) const override;
    };
    
    
    
    class SLR_API SpecularReflection : public SurfaceMaterial {
        const SpectrumTexture* m_coeffR;
        const SpectrumTexture* m_eta;
        const SpectrumTexture* m_k;
    public:
        SpecularReflection(const SpectrumTexture* coeffR, const SpectrumTexture* eta, const SpectrumTexture* k) :
        m_coeffR(coeffR), m_eta(eta), m_k(k) { }
        
        BSDF* getBSDF(const SurfacePoint &surfPt, const WavelengthSamples &wls, ArenaAllocator &mem, float scale = 1.0f) const override;
    };
    
    
    
    class SLR_API SpecularScattering : public SurfaceMaterial {
        const SpectrumTexture* m_coeff;
        const SpectrumTexture* m_etaExt;
        const SpectrumTexture* m_etaInt;
    public:
        SpecularScattering(const SpectrumTexture* coeff, const SpectrumTexture* etaExt, const SpectrumTexture* etaInt) :
        m_coeff(coeff), m_etaExt(etaExt), m_etaInt(etaInt) { }
        
        BSDF* getBSDF(const SurfacePoint &surfPt, const WavelengthSamples &wls, ArenaAllocator &mem, float scale = 1.0f) const override;
    };
    
    
    
    class SLR_API InverseSurfaceMaterial : public SurfaceMaterial {
        const SurfaceMaterial* m_baseMat;
    public:
        InverseSurfaceMaterial(const SurfaceMaterial* baseMat) :
        m_baseMat(baseMat) { };
        
        BSDF* getBSDF(const SurfacePoint &surfPt, const WavelengthSamples &wls, ArenaAllocator &mem, float scale = 1.0f) const override;
    };
}

#endif /* defined(__SLR__basic_SurfaceMaterials__) */
