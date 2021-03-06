//
//  LinearCongruentialRNG.h
//
//  Created by 渡部 心 on 2016/06/17.
//  Copyright (c) 2016年 渡部 心. All rights reserved.
//

#ifndef LinearCongruentialRNG_h
#define LinearCongruentialRNG_h

#include "../defines.h"
#include "../references.h"
#include "../Core/RandomNumberGenerator.h"

namespace SLR {
    template <typename TypeSet>
    class SLR_API LinearCongruentialRNGTemplate : public RandomNumberGeneratorTemplate<TypeSet> {
        typename TypeSet::UInt m_seed;
    public:
        LinearCongruentialRNGTemplate() {
            m_seed = (typename TypeSet::UInt)time(NULL);
        }
        LinearCongruentialRNGTemplate(typename TypeSet::UInt seed) {
            m_seed = seed;
        }
        LinearCongruentialRNGTemplate(const LinearCongruentialRNGTemplate &rng) {
            m_seed = rng.m_seed;
        }
        
        typename TypeSet::UInt getUInt() override;
    };
    
    template <> Types32bit::UInt LinearCongruentialRNGTemplate<Types32bit>::getUInt();
    template <> Types64bit::UInt LinearCongruentialRNGTemplate<Types64bit>::getUInt();
}


#endif /* LinearCongruential_h */
