//
//  Matrix4x4.h
//
//  Created by 渡部 心 on 11/08/22.
//  Copyright (c) 2014年 渡部 心. All rights reserved.
//

#ifndef __SLR_Matrix4x4_h__
#define __SLR_Matrix4x4_h__

#include "../defines.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Point3.h"

#ifdef SLR_Defs_MSVC
#   undef near
#   undef far
#endif

namespace SLR {
    template <typename RealType>
    struct SLR_API Matrix4x4Template {
        union {
            struct { RealType m00, m10, m20, m30; };
            Vector4Template<RealType> c0;
        };
        union {
            struct { RealType m01, m11, m21, m31; };
            Vector4Template<RealType> c1;
        };
        union {
            struct { RealType m02, m12, m22, m32; };
            Vector4Template<RealType> c2;
        };
        union {
            struct { RealType m03, m13, m23, m33; };
            Vector4Template<RealType> c3;
        };
        
        Matrix4x4Template() : c0(Vector4Template<RealType>::Zero), c1(Vector4Template<RealType>::Zero), c2(Vector4Template<RealType>::Zero), c3(Vector4Template<RealType>::Zero) { }
        Matrix4x4Template(RealType array[16]) :
        m00(array[ 0]), m10(array[ 1]), m20(array[ 2]), m30(array[ 3]),
        m01(array[ 4]), m11(array[ 5]), m21(array[ 6]), m31(array[ 7]),
        m02(array[ 8]), m12(array[ 9]), m22(array[10]), m32(array[11]),
        m03(array[12]), m13(array[13]), m23(array[14]), m33(array[15]) { }
        Matrix4x4Template(const Vector3Template<RealType> &col0, const Vector3Template<RealType> &col1, const Vector3Template<RealType> &col2) : c0(col0, 0.0f), c1(col1, 0.0f), c2(col2, 0.0f), c3(Vector4Template<RealType>::Ew) { }
        CONSTEXPR_CONSTRUCTOR Matrix4x4Template(const Vector4Template<RealType> &col0, const Vector4Template<RealType> &col1, const Vector4Template<RealType> &col2, const Vector4Template<RealType> &col3) :
        c0(col0), c1(col1), c2(col2), c3(col3)
#ifdef SLR_Defs_MSVC
        ,// without these extra initialization, an error occurs at least with VS2015.
        m00(col0.x), m10(col0.y), m20(col0.z), m30(col0.w),
        m01(col1.x), m11(col1.y), m21(col1.z), m31(col1.w),
        m02(col2.x), m12(col2.y), m22(col2.z), m32(col2.w),
        m03(col3.x), m13(col3.y), m23(col3.z), m33(col3.w)
#endif
        { }
        
        Matrix4x4Template operator+() const { return *this; }
        Matrix4x4Template operator-() const { return Matrix4x4Template(-c0, -c1, -c2, -c3); }
        
        Matrix4x4Template operator+(const Matrix4x4Template &mat) const { return Matrix4x4Template(c0 + mat.c0, c1 + mat.c1, c2 + mat.c2, c3 + mat.c3); }
        Matrix4x4Template operator-(const Matrix4x4Template &mat) const { return Matrix4x4Template(c0 - mat.c0, c1 - mat.c1, c2 - mat.c2, c3 - mat.c3); }
        Matrix4x4Template operator*(const Matrix4x4Template &mat) const {
            const Vector4Template<RealType> r[] = {row(0), row(1), row(2), row(3)};
            return Matrix4x4Template(Vector4Template<RealType>(dot(r[0], mat.c0), dot(r[1], mat.c0), dot(r[2], mat.c0), dot(r[3], mat.c0)),
                                     Vector4Template<RealType>(dot(r[0], mat.c1), dot(r[1], mat.c1), dot(r[2], mat.c1), dot(r[3], mat.c1)),
                                     Vector4Template<RealType>(dot(r[0], mat.c2), dot(r[1], mat.c2), dot(r[2], mat.c2), dot(r[3], mat.c2)),
                                     Vector4Template<RealType>(dot(r[0], mat.c3), dot(r[1], mat.c3), dot(r[2], mat.c3), dot(r[3], mat.c3)));
        }
        Vector3Template<RealType> operator*(const Vector3Template<RealType> &v) const {
            return Vector3Template<RealType>(dot((Vector3Template<RealType>)row(0), v), dot((Vector3Template<RealType>)row(1), v), dot((Vector3Template<RealType>)row(2), v));
        }
        Vector4Template<RealType> operator*(const Vector4Template<RealType> &v) const { return Vector4Template<RealType>(dot(row(0), v), dot(row(1), v), dot(row(2), v), dot(row(3), v)); }
        Point3Template<RealType> operator*(const Point3Template<RealType> &p) const {
            Vector4Template<RealType> ph{p.x, p.y, p.z, 1.0f};
            Vector4Template<RealType> pht = Vector4Template<RealType>(dot(row(0), ph), dot(row(1), ph), dot(row(2), ph), dot(row(3), ph));
            if (pht.w != 1.0f)
                pht /= pht.w;
            return Point3Template<RealType>(pht.x, pht.y, pht.z);
        }
        Matrix4x4Template operator*(RealType s) const { return Matrix4x4Template(c0 * s, c1 * s, c2 * s, c3 * s); }
        Matrix4x4Template operator/(RealType s) const { return Matrix4x4Template(c0 / s, c1 / s, c2 / s, c3 / s); }
        friend inline Matrix4x4Template operator*(RealType s, const Matrix4x4Template &mat) { return Matrix4x4Template(s * mat.c0, s * mat.c1, s * mat.c2, s * mat.c3); }
        
        Matrix4x4Template &operator+=(const Matrix4x4Template &mat) { c0 += mat.c0; c1 += mat.c1; c2 += mat.c2; c3 += mat.c3; return *this; }
        Matrix4x4Template &operator-=(const Matrix4x4Template &mat) { c0 -= mat.c0; c1 -= mat.c1; c2 -= mat.c2; c3 -= mat.c3; return *this; }
        Matrix4x4Template &operator*=(const Matrix4x4Template &mat) {
            const Vector4Template<RealType> r[] = {row(0), row(1), row(2), row(3)};
            c0 = Vector4Template<RealType>(dot(r[0], mat.c0), dot(r[1], mat.c0), dot(r[2], mat.c0), dot(r[3], mat.c0));
            c1 = Vector4Template<RealType>(dot(r[0], mat.c1), dot(r[1], mat.c1), dot(r[2], mat.c1), dot(r[3], mat.c1));
            c2 = Vector4Template<RealType>(dot(r[0], mat.c2), dot(r[1], mat.c2), dot(r[2], mat.c2), dot(r[3], mat.c2));
            c3 = Vector4Template<RealType>(dot(r[0], mat.c3), dot(r[1], mat.c3), dot(r[2], mat.c3), dot(r[3], mat.c3));
            return *this;
        }
        Matrix4x4Template &operator*=(RealType s) { c0 *= s; c1 *= s; c2 *= s; c3 *= s; return *this; }
        Matrix4x4Template &operator/=(RealType s) { c0 /= s; c1 /= s; c2 /= s; c3 /= s; return *this; }
        
        bool operator==(const Matrix4x4Template &m) const { return c0 == m.c0 && c1 == m.c1 && c2 == m.c2 && c3 == m.c3; }
        bool operator!=(const Matrix4x4Template &m) const { return c0 == m.c0 || c1 != m.c1 || c2 != m.c2 || c3 != m.c3; }
        
        Vector4Template<RealType> &operator[](unsigned int c) {
            SLRAssert(c < 4, "\"c\" is out of range [0, 3].");
            return *(&c0 + c);
        }
        
        Vector4Template<RealType> operator[](unsigned int c) const {
            SLRAssert(c < 4, "\"c\" is out of range [0, 3].");
            return *(&c0 + c);
        }
        
        const Vector4Template<RealType> &column(unsigned int c) const {
            SLRAssert(c < 4, "\"c\" is out of range [0, 3].");
            return *(&c0 + c);
        }
        Vector4Template<RealType> row(unsigned int r) const {
            SLRAssert(r < 4, "\"r\" is out of range [0, 3].");
            switch (r) {
                case 0:
                    return Vector4Template<RealType>(m00, m01, m02, m03);
                case 1:
                    return Vector4Template<RealType>(m10, m11, m12, m13);
                case 2:
                    return Vector4Template<RealType>(m20, m21, m22, m23);
                case 3:
                    return Vector4Template<RealType>(m30, m31, m32, m33);
                default:
                    return Vector4Template<RealType>::Zero;
            }
        }
        
        Matrix4x4Template &swapColumns(unsigned int ca, unsigned int cb) {
            if (ca != cb) {
                Vector4Template<RealType> temp = column(ca);
                (*this)[ca] = (*this)[cb];
                (*this)[cb] = temp;
            }
            return *this;
        }
        
        Matrix4x4Template &swapRows(unsigned int ra, unsigned int rb) {
            if (ra != rb) {
                Vector4Template<RealType> temp = row(ra);
                setRow(ra, row(rb));
                setRow(rb, temp);
            }
            return *this;
        }
        
        Matrix4x4Template &setRow(unsigned int r, const Vector4Template<RealType> &v) {
            SLRAssert(r < 4, "\"r\" is out of range [0, 3].");
            c0[r] = v[0]; c1[r] = v[1]; c2[r] = v[2]; c3[r] = v[3];
            return *this;
        }
        Matrix4x4Template &scaleRow(unsigned int r, RealType s) {
            SLRAssert(r < 4, "\"r\" is out of range [0, 3].");
            c0[r] *= s; c1[r] *= s; c2[r] *= s; c3[r] *= s;
            return *this;
        }
        Matrix4x4Template &addRow(unsigned int r, const Vector4Template<RealType> &v) {
            SLRAssert(r < 4, "\"r\" is out of range [0, 3].");
            c0[r] += v[0]; c1[r] += v[1]; c2[r] += v[2]; c3[r] += v[3];
            return *this;
        }
        
        Matrix4x4Template& transpose() {
            auto swap = [](RealType* v0, RealType* v1) {
                RealType temp = *v0;
                *v0 = *v1;
                *v1 = temp;
            };
            swap(&m10, &m01); swap(&m20, &m02); swap(&m30, &m03);
            swap(&m21, &m12); swap(&m31, &m13);
            swap(&m32, &m23);
            return *this;
        }
        
        Matrix4x4Template &invert() {
            SLRAssert_NotImplemented();
            return *this;
        }
        
        bool isIdentity() const {
            typedef Vector4Template<RealType> V4;
            return c0 == V4::Ex && c1 == V4::Ey && c2 == V4::Ez && c3 == V4::Ew;
        }
        bool hasNaN() const { return c0.hasNaN() || c1.hasNaN() || c2.hasNaN() || c3.hasNaN(); }
        bool hasInf() const { return c0.hasInf() || c1.hasInf() || c2.hasInf() || c3.hasInf(); }
        
        static const Matrix4x4Template Identity;
        static const Matrix4x4Template Zero;
        static const Matrix4x4Template One;
        static const Matrix4x4Template Inf;
        static const Matrix4x4Template NaN;
    };
    template <typename RealType>
    const Matrix4x4Template<RealType> Matrix4x4Template<RealType>::Identity = Matrix4x4Template<RealType>(Vector4Template<RealType>(1, 0, 0, 0),
                                                                                                          Vector4Template<RealType>(0, 1, 0, 0),
                                                                                                          Vector4Template<RealType>(0, 0, 1, 0),
                                                                                                          Vector4Template<RealType>(0, 0, 0, 1));
    template <typename RealType>
    const Matrix4x4Template<RealType> Matrix4x4Template<RealType>::Zero = Matrix4x4Template<RealType>(Vector4Template<RealType>(0),
                                                                                                      Vector4Template<RealType>(0),
                                                                                                      Vector4Template<RealType>(0),
                                                                                                      Vector4Template<RealType>(0));
    template <typename RealType>
    const Matrix4x4Template<RealType> Matrix4x4Template<RealType>::One = Matrix4x4Template<RealType>(Vector4Template<RealType>(1),
                                                                                                     Vector4Template<RealType>(1),
                                                                                                     Vector4Template<RealType>(1),
                                                                                                     Vector4Template<RealType>(1));
    template <typename RealType>
    const Matrix4x4Template<RealType> Matrix4x4Template<RealType>::Inf = Matrix4x4Template<RealType>(Vector4Template<RealType>(std::numeric_limits<RealType>::infinity()),
                                                                                                     Vector4Template<RealType>(std::numeric_limits<RealType>::infinity()),
                                                                                                     Vector4Template<RealType>(std::numeric_limits<RealType>::infinity()),
                                                                                                     Vector4Template<RealType>(std::numeric_limits<RealType>::infinity()));
    template <typename RealType>
    const Matrix4x4Template<RealType> Matrix4x4Template<RealType>::NaN = Matrix4x4Template<RealType>(Vector4Template<RealType>(std::numeric_limits<RealType>::quiet_NaN()),
                                                                                                     Vector4Template<RealType>(std::numeric_limits<RealType>::quiet_NaN()),
                                                                                                     Vector4Template<RealType>(std::numeric_limits<RealType>::quiet_NaN()),
                                                                                                     Vector4Template<RealType>(std::numeric_limits<RealType>::quiet_NaN()));
    
    
    template <typename RealType>
    SLR_API Matrix4x4Template<RealType> transpose(const Matrix4x4Template<RealType> &m);
    
    template <typename RealType>
    SLR_API Matrix4x4Template<RealType> invert(const Matrix4x4Template<RealType> &m);
    
    template <typename RealType>
    SLR_API Matrix4x4Template<RealType> lookAt(const Point3Template<RealType> &eye, const Point3Template<RealType> &tgt, const Vector3Template<RealType> &up);
    
    template <typename RealType>
    inline Matrix4x4Template<RealType> lookAt(RealType ex, RealType ey, RealType ez, RealType tx, RealType ty, RealType tz, RealType ux, RealType uy, RealType uz) {
        return lookAt(Point3Template<RealType>(ex, ey, ez), Point3Template<RealType>(tx, ty, tz), Vector3Template<RealType>(ux, uy, uz));
    }
    
    template <typename RealType>
    inline Matrix4x4Template<RealType> scale(const Vector3Template<RealType> &s) {
        return Matrix4x4Template<RealType>(s.x * Vector4Template<RealType>::Ex,
                                           s.y * Vector4Template<RealType>::Ey,
                                           s.z * Vector4Template<RealType>::Ez,
                                           Vector4Template<RealType>::Ew);
    }
    
    template <typename RealType>
    inline Matrix4x4Template<RealType> scale(RealType sx, RealType sy, RealType sz) {
        return scale(Vector3Template<RealType>(sx, sy, sz));
    }
    
    template <typename RealType>
    inline Matrix4x4Template<RealType> scale(RealType s) {
        return scale(Vector3Template<RealType>(s, s, s));
    }
    
    template <typename RealType>
    inline Matrix4x4Template<RealType> translate(const Vector3Template<RealType> &t) {
        return Matrix4x4Template<RealType>(Vector4Template<RealType>::Ex,
                                           Vector4Template<RealType>::Ey,
                                           Vector4Template<RealType>::Ez,
                                           Vector4Template<RealType>(t, 1.0f));
    }
    
    template <typename RealType>
    inline Matrix4x4Template<RealType> translate(RealType tx, RealType ty, RealType tz) {
        return translate(Vector3Template<RealType>(tx, ty, tz));
    }
    
    template <typename RealType>
    SLR_API Matrix4x4Template<RealType> rotate(RealType angle, const Vector3Template<RealType> &axis);
    
    template <typename RealType>
    inline Matrix4x4Template<RealType> rotate(RealType angle, RealType ax, RealType ay, RealType az) {
        return rotate(angle, Vector3Template<RealType>(ax, ay, az));
    }
    
    template <typename RealType>
    inline Matrix4x4Template<RealType> rotateX(RealType angle) { return rotate(angle, Vector3Template<RealType>::Ex); }
    template <typename RealType>
    inline Matrix4x4Template<RealType> rotateY(RealType angle) { return rotate(angle, Vector3Template<RealType>::Ey); }
    template <typename RealType>
    inline Matrix4x4Template<RealType> rotateZ(RealType angle) { return rotate(angle, Vector3Template<RealType>::Ez); }
    
    template <typename RealType>
    SLR_API Matrix4x4Template<RealType> camera(RealType aspect, RealType fovY, RealType near, RealType far);
}

#endif
