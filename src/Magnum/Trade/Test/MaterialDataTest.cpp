/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
                2020 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <algorithm>
#include <sstream>
#include <Corrade/Containers/StaticArray.h>
#include <Corrade/TestSuite/Tester.h>
#include <Corrade/TestSuite/Compare/Numeric.h>
#include <Corrade/Utility/DebugStl.h>
#include <Corrade/Utility/String.h>

#include "Magnum/Math/Color.h"
#include "Magnum/Math/Matrix3.h"
#include "Magnum/Trade/MaterialData.h"
#include "Magnum/Trade/PhongMaterialData.h"

namespace Magnum { namespace Trade { namespace Test { namespace {

class MaterialDataTest: public TestSuite::Tester {
    public:
        explicit MaterialDataTest();

        void attributeTypeSize();
        void attributeTypeSizeInvalid();

        void attributeMap();

        void constructAttributeDefault();
        void constructAttributeString();
        void constructAttributeName();
        void constructAttributeTypeErasedString();
        void constructAttributeTypeErasedName();

        template<class T> void constructAttributeStringConstexpr();

        void constructAttributePointer();
        void constructAttributeMutablePointer();
        void constructAttributeStringNameStringValue();
        void constructAttributeNameStringValue();
        void constructAttributeTextureSwizzle();

        void constructAttributeInvalidName();
        void constructAttributeWrongTypeForName();
        void constructAttributeInvalidType();
        void constructAttributeTooLarge();
        void constructAttributeTooLargeString();
        void constructAttributeTooLargeNameString();
        void constructAttributeWrongAccessType();
        void constructAttributeWrongAccessPointerType();
        void constructAttributeWrongAccessTypeString();

        void construct();
        void constructEmptyAttribute();
        void constructDuplicateAttribute();
        void constructFromImmutableSortedArray();

        void constructLayers();
        void constructLayersNotMonotonic();
        void constructLayersOffsetOutOfBounds();

        void constructNonOwned();
        void constructNonOwnedLayers();
        void constructNonOwnedEmptyAttribute();
        void constructNonOwnedNotSorted();
        void constructNonOwnedDuplicateAttribute();
        void constructNonOwnedLayersNotMonotonic();
        void constructNonOwnedLayersOffsetOutOfBounds();

        void constructCopy();
        void constructMove();

        void access();
        void accessPointer();
        void accessString();
        void accessTextureSwizzle();
        void accessOptional();
        void accessOutOfBounds();
        void accessNotFound();
        void accessInvalidAttributeName();
        void accessWrongType();
        void accessWrongPointerType();
        void accessWrongTypeString();

        void accessLayerLayerNameInBaseMaterial();
        void accessLayerEmptyLayer();
        void accessLayerIndexOptional();
        void accessLayerStringOptional();
        void accessLayerOutOfBounds();
        void accessLayerNotFound();
        void accessOutOfBoundsInLayerIndex();
        void accessOutOfBoundsInLayerString();
        void accessNotFoundInLayerIndex();
        void accessNotFoundInLayerString();

        void releaseAttributes();
        void releaseLayers();

        #ifdef MAGNUM_BUILD_DEPRECATED
        void constructPhongDeprecated();
        void constructPhongDeprecatedTextured();
        void constructPhongDeprecatedTexturedTextureTransform();
        void constructPhongDeprecatedTexturedCoordinates();
        void constructPhongDeprecatedTextureTransformNoTextures();
        void constructPhongDeprecatedNoTextureTransformationFlag();
        void constructPhongDeprecatedNoTextureCoordinatesFlag();
        #endif

        void phongAccess();
        void phongAccessDefaults();
        void phongAccessTextured();
        void phongAccessTexturedDefaults();
        void phongAccessTexturedSingleMatrixCoordinates();
        void phongAccessInvalidTextures();

        void debugAttribute();
        void debugTextureSwizzle();
        void debugAttributeType();

        void debugType();
        void debugTypes();
        #ifdef MAGNUM_BUILD_DEPRECATED
        void debugFlag();
        void debugFlags();
        #endif
        void debugAlphaMode();

        #ifdef MAGNUM_BUILD_DEPRECATED
        void debugPhongFlag();
        void debugPhongFlags();
        #endif
};

MaterialDataTest::MaterialDataTest() {
    addTests({&MaterialDataTest::attributeTypeSize,
              &MaterialDataTest::attributeTypeSizeInvalid,
              &MaterialDataTest::attributeMap,

              &MaterialDataTest::constructAttributeDefault,
              &MaterialDataTest::constructAttributeString,
              &MaterialDataTest::constructAttributeName,
              &MaterialDataTest::constructAttributeTypeErasedString,
              &MaterialDataTest::constructAttributeTypeErasedName,

              &MaterialDataTest::constructAttributeStringConstexpr<bool>,
              &MaterialDataTest::constructAttributeStringConstexpr<Float>,
              &MaterialDataTest::constructAttributeStringConstexpr<Deg>,
              &MaterialDataTest::constructAttributeStringConstexpr<Rad>,
              &MaterialDataTest::constructAttributeStringConstexpr<UnsignedInt>,
              &MaterialDataTest::constructAttributeStringConstexpr<Int>,
              &MaterialDataTest::constructAttributeStringConstexpr<UnsignedLong>,
              &MaterialDataTest::constructAttributeStringConstexpr<Long>,
              &MaterialDataTest::constructAttributeStringConstexpr<Vector2>,
              &MaterialDataTest::constructAttributeStringConstexpr<Vector2ui>,
              &MaterialDataTest::constructAttributeStringConstexpr<Vector2i>,
              &MaterialDataTest::constructAttributeStringConstexpr<Vector3>,
              &MaterialDataTest::constructAttributeStringConstexpr<Vector3ui>,
              &MaterialDataTest::constructAttributeStringConstexpr<Vector3i>,
              &MaterialDataTest::constructAttributeStringConstexpr<Vector4>,
              &MaterialDataTest::constructAttributeStringConstexpr<Vector4ui>,
              &MaterialDataTest::constructAttributeStringConstexpr<Vector4i>,
              &MaterialDataTest::constructAttributeStringConstexpr<Matrix2x2>,
              &MaterialDataTest::constructAttributeStringConstexpr<Matrix2x3>,
              &MaterialDataTest::constructAttributeStringConstexpr<Matrix2x4>,
              &MaterialDataTest::constructAttributeStringConstexpr<Matrix3x2>,
              &MaterialDataTest::constructAttributeStringConstexpr<Matrix3x3>,
              &MaterialDataTest::constructAttributeStringConstexpr<Matrix3x4>,
              &MaterialDataTest::constructAttributeStringConstexpr<Matrix4x2>,
              &MaterialDataTest::constructAttributeStringConstexpr<Matrix4x3>,

              &MaterialDataTest::constructAttributePointer,
              &MaterialDataTest::constructAttributeMutablePointer,
              &MaterialDataTest::constructAttributeStringNameStringValue,
              &MaterialDataTest::constructAttributeNameStringValue,
              &MaterialDataTest::constructAttributeTextureSwizzle,

              &MaterialDataTest::constructAttributeInvalidName,
              &MaterialDataTest::constructAttributeWrongTypeForName,
              &MaterialDataTest::constructAttributeInvalidType,
              &MaterialDataTest::constructAttributeTooLarge,
              &MaterialDataTest::constructAttributeTooLargeString,
              &MaterialDataTest::constructAttributeTooLargeNameString,
              &MaterialDataTest::constructAttributeWrongAccessType,
              &MaterialDataTest::constructAttributeWrongAccessPointerType,
              &MaterialDataTest::constructAttributeWrongAccessTypeString,

              &MaterialDataTest::construct,
              &MaterialDataTest::constructEmptyAttribute});

    addRepeatedTests({&MaterialDataTest::constructDuplicateAttribute},
        5*4*3*2);

    addTests({&MaterialDataTest::constructFromImmutableSortedArray,

              &MaterialDataTest::constructLayers,
              &MaterialDataTest::constructLayersNotMonotonic,
              &MaterialDataTest::constructLayersOffsetOutOfBounds,

              &MaterialDataTest::constructNonOwned,
              &MaterialDataTest::constructNonOwnedLayers,
              &MaterialDataTest::constructNonOwnedEmptyAttribute,
              &MaterialDataTest::constructNonOwnedNotSorted,
              &MaterialDataTest::constructNonOwnedDuplicateAttribute,
              &MaterialDataTest::constructNonOwnedLayersNotMonotonic,
              &MaterialDataTest::constructNonOwnedLayersOffsetOutOfBounds,

              &MaterialDataTest::constructCopy,
              &MaterialDataTest::constructMove,

              &MaterialDataTest::access,
              &MaterialDataTest::accessPointer,
              &MaterialDataTest::accessString,
              &MaterialDataTest::accessTextureSwizzle,
              &MaterialDataTest::accessOptional,
              &MaterialDataTest::accessOutOfBounds,
              &MaterialDataTest::accessNotFound,
              &MaterialDataTest::accessInvalidAttributeName,
              &MaterialDataTest::accessWrongType,
              &MaterialDataTest::accessWrongPointerType,
              &MaterialDataTest::accessWrongTypeString,

              &MaterialDataTest::accessLayerLayerNameInBaseMaterial,
              &MaterialDataTest::accessLayerEmptyLayer,
              &MaterialDataTest::accessLayerIndexOptional,
              &MaterialDataTest::accessLayerStringOptional,
              &MaterialDataTest::accessLayerOutOfBounds,
              &MaterialDataTest::accessLayerNotFound,
              &MaterialDataTest::accessOutOfBoundsInLayerIndex,
              &MaterialDataTest::accessOutOfBoundsInLayerString,
              &MaterialDataTest::accessNotFoundInLayerIndex,
              &MaterialDataTest::accessNotFoundInLayerString,

              &MaterialDataTest::releaseAttributes,
              &MaterialDataTest::releaseLayers,

              #ifdef MAGNUM_BUILD_DEPRECATED
              &MaterialDataTest::constructPhongDeprecated,
              &MaterialDataTest::constructPhongDeprecatedTextured,
              &MaterialDataTest::constructPhongDeprecatedTexturedTextureTransform,
              &MaterialDataTest::constructPhongDeprecatedTexturedCoordinates,
              &MaterialDataTest::constructPhongDeprecatedTextureTransformNoTextures,
              &MaterialDataTest::constructPhongDeprecatedNoTextureTransformationFlag,
              &MaterialDataTest::constructPhongDeprecatedNoTextureCoordinatesFlag,
              #endif

              &MaterialDataTest::phongAccess,
              &MaterialDataTest::phongAccessDefaults,
              &MaterialDataTest::phongAccessTextured,
              &MaterialDataTest::phongAccessTexturedDefaults,
              &MaterialDataTest::phongAccessTexturedSingleMatrixCoordinates,
              &MaterialDataTest::phongAccessInvalidTextures,

              &MaterialDataTest::debugAttribute,
              &MaterialDataTest::debugTextureSwizzle,
              &MaterialDataTest::debugAttributeType,

              &MaterialDataTest::debugType,
              &MaterialDataTest::debugTypes,
              #ifdef MAGNUM_BUILD_DEPRECATED
              &MaterialDataTest::debugFlag,
              &MaterialDataTest::debugFlags,
              #endif
              &MaterialDataTest::debugAlphaMode,

              #ifdef MAGNUM_BUILD_DEPRECATED
              &MaterialDataTest::debugPhongFlag,
              &MaterialDataTest::debugPhongFlags
              #endif
              });
}

using namespace Containers::Literals;
using namespace Math::Literals;

void MaterialDataTest::attributeTypeSize() {
    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::Bool), 1);
    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::Deg), 4);
    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::Vector2i), 8);
    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::Vector3), 12);
    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::Vector4ui), 16);
    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::Matrix2x3), 24);
    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::Matrix4x2), 32);
    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::Matrix3x3), 36);
    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::Matrix3x4), 48);
}

void MaterialDataTest::attributeTypeSizeInvalid() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    materialAttributeTypeSize(MaterialAttributeType(0x0));
    materialAttributeTypeSize(MaterialAttributeType(0xfe));
    materialAttributeTypeSize(MaterialAttributeType::String);
    CORRADE_COMPARE(out.str(),
        "Trade::materialAttributeTypeSize(): invalid type Trade::MaterialAttributeType(0x0)\n"
        "Trade::materialAttributeTypeSize(): invalid type Trade::MaterialAttributeType(0xfe)\n"
        "Trade::materialAttributeTypeSize(): string size is unknown\n");
}

void MaterialDataTest::attributeMap() {
    /* Ensure all attribute names are:
        - present in the map,
        - that their translated string name corresponds to the enum value name,
        - that the calculated type size corresponds to the actual type,
        - and that the name together with the type fits.
       This goes through the first 16 bits, which should be enough. Going
       through 32 bits takes 8 seconds, too much. */
    for(UnsignedInt i = 1; i <= 0xffff; ++i) {
        /* Attribute 0 reserved for an invalid value */

        const auto attribute = MaterialAttribute(i);
        #ifdef __GNUC__
        #pragma GCC diagnostic push
        #pragma GCC diagnostic error "-Wswitch"
        #endif
        switch(attribute) {
            #define _c(name_, type) \
                case MaterialAttribute::name_: \
                    CORRADE_COMPARE((MaterialAttributeData{MaterialAttribute::name_, type{}}.name()), #name_); \
                    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::type), sizeof(type)); \
                    CORRADE_COMPARE_AS(sizeof(type) + Containers::arraySize(#name_) + sizeof(MaterialAttributeType), sizeof(MaterialAttributeData), TestSuite::Compare::LessOrEqual); \
                    break;
            #define _ct(name_, typeName, type) \
                case MaterialAttribute::name_: \
                    CORRADE_COMPARE((MaterialAttributeData{MaterialAttribute::name_, type{}}.name()), #name_); \
                    CORRADE_COMPARE(materialAttributeTypeSize(MaterialAttributeType::typeName), sizeof(type)); \
                    CORRADE_COMPARE_AS(sizeof(type) + Containers::arraySize(#name_) + sizeof(MaterialAttributeType), sizeof(MaterialAttributeData), TestSuite::Compare::LessOrEqual); \
                    break;
            #define _cnt(name_, string, typeName, type) \
                case MaterialAttribute::name_: \
                    CORRADE_COMPARE((MaterialAttributeData{MaterialAttribute::name_, type{}}.name()), string); \
                    break;
            #include "Magnum/Trade/Implementation/materialAttributeProperties.hpp"
            #undef _c
            #undef _ct
            #undef _cnt
        }
        #ifdef __GNUC__
        #pragma GCC diagnostic pop
        #endif
    }
}

void MaterialDataTest::constructAttributeDefault() {
    MaterialAttributeData attribute;
    CORRADE_COMPARE(attribute.name(), "");
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType{});

    constexpr MaterialAttributeData cattribute;
    CORRADE_COMPARE(cattribute.name(), "");
    CORRADE_COMPARE(cattribute.type(), MaterialAttributeType{});
}

void MaterialDataTest::constructAttributeString() {
    MaterialAttributeData attribute{"colorTransform", Matrix3::scaling({2.0f, 0.3f})};
    CORRADE_COMPARE(attribute.name(), "colorTransform");
    CORRADE_COMPARE(attribute.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(attribute.name()[attribute.name().size()], '\0');
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType::Matrix3x3);
    CORRADE_COMPARE(attribute.value<Matrix3>(), Matrix3::scaling({2.0f, 0.3f}));
    CORRADE_COMPARE(*reinterpret_cast<const Matrix3*>(attribute.value()), Matrix3::scaling({2.0f, 0.3f}));
}

void MaterialDataTest::constructAttributeName() {
    MaterialAttributeData attribute{MaterialAttribute::DiffuseColor, 0xff3366aa_rgbaf};
    CORRADE_COMPARE(attribute.name(), "DiffuseColor"_s);
    CORRADE_COMPARE(attribute.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(attribute.name()[attribute.name().size()], '\0');
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType::Vector4);
    CORRADE_COMPARE(attribute.value<Color4>(), 0xff3366aa_rgbaf);
    CORRADE_COMPARE(*reinterpret_cast<const Color4*>(attribute.value()), 0xff3366aa_rgbaf);
}

void MaterialDataTest::constructAttributeTypeErasedString() {
    const Vector2i data{37, -458};
    MaterialAttributeData attribute{"millibitsOfInformation", MaterialAttributeType::Vector2i, &data};
    CORRADE_COMPARE(attribute.name(), "millibitsOfInformation");
    CORRADE_COMPARE(attribute.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(attribute.name()[attribute.name().size()], '\0');
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType::Vector2i);
    CORRADE_COMPARE(attribute.value<Vector2i>(), (Vector2i{37, -458}));
}

void MaterialDataTest::constructAttributeTypeErasedName() {
    const Float data = 85.1f;
    MaterialAttributeData attribute{MaterialAttribute::Shininess, MaterialAttributeType::Float, &data};
    CORRADE_COMPARE(attribute.name(), "Shininess");
    CORRADE_COMPARE(attribute.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(attribute.name()[attribute.name().size()], '\0');
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType::Float);
    CORRADE_COMPARE(attribute.value<Float>(), 85.1f);
}

template<class T> struct TypeName {
    static const char* name() { return Math::TypeTraits<T>::name(); }
};
template<> struct TypeName<bool> {
    static const char* name() { return "bool"; }
};
#define _c(type) template<> struct TypeName<type> {                         \
    static const char* name() { return #type; }                             \
};
_c(Deg)
_c(Rad)
_c(Vector2)
_c(Vector2i)
_c(Vector2ui)
_c(Vector3)
_c(Vector3i)
_c(Vector3ui)
_c(Vector4)
_c(Vector4i)
_c(Vector4ui)
_c(Matrix2x2)
_c(Matrix2x3)
_c(Matrix2x4)
_c(Matrix3x2)
_c(Matrix3x3)
_c(Matrix3x4)
_c(Matrix4x2)
_c(Matrix4x3)
#undef _c

template<class T> void MaterialDataTest::constructAttributeStringConstexpr() {
    setTestCaseTemplateName(TypeName<T>::name());

    /* "templateAttrib" is 14 chars, which is the maximum for 48-bit types */
    constexpr MaterialAttributeData attribute{"templateAttrib"_s, T(15)};
    CORRADE_COMPARE(attribute.name(), "templateAttrib");
    CORRADE_COMPARE(attribute.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(attribute.name()[attribute.name().size()], '\0');
    CORRADE_COMPARE(attribute.value<T>(), T(15));
}

constexpr Int SomeData = 3;

void MaterialDataTest::constructAttributePointer() {
    MaterialAttributeData attribute{"pointer!", &SomeData};
    CORRADE_COMPARE(attribute.name(), "pointer!");
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType::Pointer);
    CORRADE_COMPARE(*static_cast<const Int* const*>(attribute.value()), &SomeData);
    CORRADE_COMPARE(attribute.value<const Int*>(), &SomeData);
    /* Any type works */
    CORRADE_COMPARE(attribute.value<const void*>(), &SomeData);

    constexpr MaterialAttributeData cattribute{"pointer!"_s, &SomeData};
    CORRADE_COMPARE(cattribute.name(), "pointer!");
    CORRADE_COMPARE(cattribute.type(), MaterialAttributeType::Pointer);
    CORRADE_COMPARE(*static_cast<const Int* const*>(cattribute.value()), &SomeData);
    CORRADE_COMPARE(cattribute.value<const Int*>(), &SomeData);

    /* Type-erased variant */
    const Int* pointer = &SomeData;
    MaterialAttributeData typeErased{"pointer!", MaterialAttributeType::Pointer, &pointer};
    CORRADE_COMPARE(typeErased.name(), "pointer!");
    CORRADE_COMPARE(typeErased.type(), MaterialAttributeType::Pointer);
    CORRADE_COMPARE(typeErased.value<const Int*>(), &SomeData);
    /* Any type works */
    CORRADE_COMPARE(typeErased.value<const void*>(), &SomeData);
}

void MaterialDataTest::constructAttributeMutablePointer() {
    Float data = 85.1f;

    MaterialAttributeData attribute{"pointer!", &data};
    CORRADE_COMPARE(attribute.name(), "pointer!");
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType::MutablePointer);
    CORRADE_COMPARE(*static_cast<Float* const*>(attribute.value()), &data);
    CORRADE_COMPARE(attribute.value<Float*>(), &data);
    /* Any type works */
    CORRADE_COMPARE(attribute.value<void*>(), &data);

    /* Type-erased variant */
    Float* pointer = &data;
    MaterialAttributeData typeErased{"pointer!", MaterialAttributeType::MutablePointer, &pointer};
    CORRADE_COMPARE(typeErased.name(), "pointer!");
    CORRADE_COMPARE(typeErased.type(), MaterialAttributeType::MutablePointer);
    CORRADE_COMPARE(typeErased.value<Float*>(), &data);
    /* Any type works */
    CORRADE_COMPARE(typeErased.value<void*>(), &data);
}

void MaterialDataTest::constructAttributeStringNameStringValue() {
    /* Explicitly using a non-null-terminated view on input to check the null
       byte isn't read by accident*/
    MaterialAttributeData attribute{"name that's long", "and a value\0that's also long but still fits!!"_s.except(1)};
    CORRADE_COMPARE(attribute.name(), "name that's long");
    CORRADE_COMPARE(attribute.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(attribute.name()[attribute.name().size()], '\0');
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType::String);
    /* Pointer access will stop at the first null byte, but typed access won't */
    CORRADE_COMPARE(static_cast<const char*>(attribute.value()), "and a value"_s);
    CORRADE_COMPARE(attribute.value<Containers::StringView>(), "and a value\0that's also long but still fits!"_s);
    CORRADE_COMPARE(attribute.value<Containers::StringView>().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(attribute.value<Containers::StringView>()[attribute.value<Containers::StringView>().size()], '\0');

    constexpr MaterialAttributeData cattribute{"name that's long"_s, "and a value\0that's also long but still fits!!"_s.except(1)};
    CORRADE_COMPARE(cattribute.name(), "name that's long");
    CORRADE_COMPARE(cattribute.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(cattribute.name()[cattribute.name().size()], '\0');
    CORRADE_COMPARE(cattribute.type(), MaterialAttributeType::String);
    CORRADE_COMPARE(cattribute.value<Containers::StringView>(), "and a value\0that's also long but still fits!"_s);
    CORRADE_COMPARE(cattribute.value<Containers::StringView>().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(cattribute.value<Containers::StringView>()[cattribute.value<Containers::StringView>().size()], '\0');

    /* Type-erased variant */
    const Containers::StringView value = "and a value\0that's also long but still fits!!"_s.except(1);
    MaterialAttributeData typeErased{"name that's long", MaterialAttributeType::String, &value};
    CORRADE_COMPARE(typeErased.name(), "name that's long");
    CORRADE_COMPARE(typeErased.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(typeErased.name()[typeErased.name().size()], '\0');
    CORRADE_COMPARE(typeErased.type(), MaterialAttributeType::String);
    CORRADE_COMPARE(typeErased.value<Containers::StringView>(), "and a value\0that's also long but still fits!"_s);
    CORRADE_COMPARE(typeErased.value<Containers::StringView>().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(typeErased.value<Containers::StringView>()[typeErased.value<Containers::StringView>().size()], '\0');
}

void MaterialDataTest::constructAttributeNameStringValue() {
    /* Explicitly using a non-null-terminated view on input to check the null
       byte isn't read by accident*/

    MaterialAttributeData attribute{MaterialAttribute::LayerName, "a value\0that's long but still fits!!"_s.except(1)};
    CORRADE_COMPARE(attribute.name(), "$LayerName");
    CORRADE_COMPARE(attribute.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(attribute.name()[attribute.name().size()], '\0');
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType::String);
    /* Pointer access will stop at the first null byte, but typed access won't */
    CORRADE_COMPARE(static_cast<const char*>(attribute.value()), "a value"_s);
    CORRADE_COMPARE(attribute.value<Containers::StringView>(), "a value\0that's long but still fits!"_s);
    CORRADE_COMPARE(attribute.value<Containers::StringView>().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(attribute.value<Containers::StringView>()[attribute.value<Containers::StringView>().size()], '\0');

    /* Type-erased variant */
    const Containers::StringView value = "a value\0that's long but still fits!!"_s.except(1);
    MaterialAttributeData typeErased{MaterialAttribute::LayerName, MaterialAttributeType::String, &value};
    CORRADE_COMPARE(typeErased.name(), "$LayerName");
    CORRADE_COMPARE(typeErased.name().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(typeErased.name()[typeErased.name().size()], '\0');
    CORRADE_COMPARE(typeErased.type(), MaterialAttributeType::String);
    CORRADE_COMPARE(typeErased.value<Containers::StringView>(), "a value\0that's long but still fits!"_s);
    CORRADE_COMPARE(typeErased.value<Containers::StringView>().flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(typeErased.value<Containers::StringView>()[typeErased.value<Containers::StringView>().size()], '\0');
}

void MaterialDataTest::constructAttributeTextureSwizzle() {
    MaterialAttributeData attribute{"swizzle", MaterialTextureSwizzle::GBA};
    CORRADE_COMPARE(attribute.name(), "swizzle");
    CORRADE_COMPARE(attribute.type(), MaterialAttributeType::TextureSwizzle);
    CORRADE_COMPARE(*static_cast<const MaterialTextureSwizzle*>(attribute.value()), MaterialTextureSwizzle::GBA);
    CORRADE_COMPARE(attribute.value<MaterialTextureSwizzle>(), MaterialTextureSwizzle::GBA);

    constexpr MaterialAttributeData cattribute{"swizzle"_s, MaterialTextureSwizzle::GBA};
    CORRADE_COMPARE(cattribute.name(), "swizzle");
    CORRADE_COMPARE(cattribute.type(), MaterialAttributeType::TextureSwizzle);
    CORRADE_COMPARE(*static_cast<const MaterialTextureSwizzle*>(cattribute.value()), MaterialTextureSwizzle::GBA);
    CORRADE_COMPARE(cattribute.value<MaterialTextureSwizzle>(), MaterialTextureSwizzle::GBA);

    /* Type-erased variant */
    const MaterialTextureSwizzle swizzle = MaterialTextureSwizzle::GBA;
    MaterialAttributeData typeErased{"swizzle", MaterialAttributeType::TextureSwizzle, &swizzle};
    CORRADE_COMPARE(typeErased.name(), "swizzle");
    CORRADE_COMPARE(typeErased.type(), MaterialAttributeType::TextureSwizzle);
    CORRADE_COMPARE(typeErased.value<MaterialTextureSwizzle>(), MaterialTextureSwizzle::GBA);
}

void MaterialDataTest::constructAttributeInvalidName() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialAttributeData{MaterialAttribute(0x0), 5};
    MaterialAttributeData{MaterialAttribute(0xfefe), 5};
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialAttributeData: invalid name Trade::MaterialAttribute(0x0)\n"
        "Trade::MaterialAttributeData: invalid name Trade::MaterialAttribute(0xfefe)\n");
}

void MaterialDataTest::constructAttributeWrongTypeForName() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialAttributeData{MaterialAttribute::DiffuseColor, Vector3ui{255, 16, 24}};
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialAttributeData: expected Trade::MaterialAttributeType::Vector4 for Trade::MaterialAttribute::DiffuseColor but got Trade::MaterialAttributeType::Vector3ui\n");
}

void MaterialDataTest::constructAttributeInvalidType() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialAttributeData{"bla", MaterialAttributeType(0x0), nullptr};
    MaterialAttributeData{"bla", MaterialAttributeType(0xfe),  nullptr};
    CORRADE_COMPARE(out.str(),
        "Trade::materialAttributeTypeSize(): invalid type Trade::MaterialAttributeType(0x0)\n"
        "Trade::materialAttributeTypeSize(): invalid type Trade::MaterialAttributeType(0xfe)\n");
}

void MaterialDataTest::constructAttributeTooLarge() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialAttributeData{"attributeIsLong", Matrix3x4{}};
    /* Constexpr variant has the same assert, but in the header. It should have
       the same output. */
    /*constexpr*/ MaterialAttributeData{"attributeIsLong"_s, Matrix3x4{}};
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialAttributeData: name attributeIsLong too long, expected at most 14 bytes for Trade::MaterialAttributeType::Matrix3x4 but got 15\n"
        "Trade::MaterialAttributeData: name attributeIsLong too long, expected at most 14 bytes for Trade::MaterialAttributeType::Matrix3x4 but got 15\n");
}

void MaterialDataTest::constructAttributeTooLargeString() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialAttributeData{"attribute is long", "This is a problem, got a long piece of text!"};
    /* Constexpr variant has the same assert, but in the header. It should have
       the same output. */
    /*constexpr*/ MaterialAttributeData{"attribute is long"_s, "This is a problem, got a long piece of text!"_s};
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialAttributeData: name attribute is long and value This is a problem, got a long piece of text! too long, expected at most 60 bytes in total but got 61\n"
        "Trade::MaterialAttributeData: name attribute is long and value This is a problem, got a long piece of text! too long, expected at most 60 bytes in total but got 61\n");
}

void MaterialDataTest::constructAttributeTooLargeNameString() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialAttributeData{MaterialAttribute::LayerName, "This is a problem, got a huge, yuuge value to store"};
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialAttributeData: name $LayerName and value This is a problem, got a huge, yuuge value to store too long, expected at most 60 bytes in total but got 61\n");
}

void MaterialDataTest::constructAttributeWrongAccessType() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialAttributeData{"thing3", Matrix4x3{}}.value<Int>();
    CORRADE_COMPARE(out.str(), "Trade::MaterialAttributeData::value(): improper type requested for thing3 of Trade::MaterialAttributeType::Matrix4x3\n");
}

void MaterialDataTest::constructAttributeWrongAccessPointerType() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    Int a = 3;
    const Float b = 57.0f;

    std::ostringstream out;
    Error redirectError{&out};
    MaterialAttributeData{"thing3", &a}.value<Int>();
    MaterialAttributeData{"boom", &b}.value<Float>();
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialAttributeData::value(): improper type requested for thing3 of Trade::MaterialAttributeType::MutablePointer\n"
        "Trade::MaterialAttributeData::value(): improper type requested for boom of Trade::MaterialAttributeType::Pointer\n");
}

void MaterialDataTest::constructAttributeWrongAccessTypeString() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialAttributeData{"thing3", Matrix4x3{}}.value<Containers::StringView>();
    CORRADE_COMPARE(out.str(), "Trade::MaterialAttributeData::value(): thing3 of Trade::MaterialAttributeType::Matrix4x3 can't be retrieved as a string\n");
}

void MaterialDataTest::construct() {
    int state;
    MaterialData data{MaterialType::Phong, {
        {MaterialAttribute::DoubleSided, true},
        {MaterialAttribute::DiffuseTextureCoordinates, 5u},
        {"highlightColor", 0x335566ff_rgbaf},
        {MaterialAttribute::AmbientTextureMatrix, Matrix3::scaling({0.5f, 1.0f})}
    }, &state};

    CORRADE_COMPARE(data.types(), MaterialType::Phong);
    CORRADE_COMPARE(data.layerCount(), 1);
    CORRADE_VERIFY(!data.layerData());
    CORRADE_COMPARE(data.attributeCount(), 4);
    CORRADE_COMPARE(data.attributeData().size(), 4);
    CORRADE_COMPARE(data.importerState(), &state);

    CORRADE_COMPARE(data.layerName(0), "");
    CORRADE_VERIFY(!data.hasLayer(""));

    /* Verify sorting */
    CORRADE_COMPARE(data.attributeName(0), "AmbientTextureMatrix");
    CORRADE_COMPARE(data.attributeName(1), "DiffuseTextureCoordinates");
    CORRADE_COMPARE(data.attributeName(2), "DoubleSided");
    CORRADE_COMPARE(data.attributeName(3), "highlightColor");

    /* Access by ID */
    CORRADE_COMPARE(data.attributeType(0), MaterialAttributeType::Matrix3x3);
    CORRADE_COMPARE(data.attributeType(1), MaterialAttributeType::UnsignedInt);
    CORRADE_COMPARE(data.attributeType(2), MaterialAttributeType::Bool);
    CORRADE_COMPARE(data.attributeType(3), MaterialAttributeType::Vector4);

    CORRADE_COMPARE(data.attribute<Matrix3>(0), Matrix3::scaling({0.5f, 1.0f}));
    CORRADE_COMPARE(data.attribute<UnsignedInt>(1), 5);
    CORRADE_COMPARE(data.attribute<bool>(2), true);
    CORRADE_COMPARE(data.attribute<Color4>(3), 0x335566ff_rgbaf);

    CORRADE_COMPARE(*static_cast<const Matrix3*>(data.attribute(0)), Matrix3::scaling({0.5f, 1.0f}));
    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.attribute(1)), 5);
    CORRADE_COMPARE(*static_cast<const bool*>(data.attribute(2)), true);
    CORRADE_COMPARE(*static_cast<const Color4*>(data.attribute(3)), 0x335566ff_rgbaf);

    /* Access by name */
    CORRADE_VERIFY(data.hasAttribute(MaterialAttribute::DoubleSided));
    CORRADE_VERIFY(data.hasAttribute(MaterialAttribute::AmbientTextureMatrix));
    CORRADE_VERIFY(!data.hasAttribute(MaterialAttribute::TextureMatrix));

    CORRADE_COMPARE(data.attributeId(MaterialAttribute::DoubleSided), 2);
    CORRADE_COMPARE(data.attributeId(MaterialAttribute::AmbientTextureMatrix), 0);
    CORRADE_COMPARE(data.attributeId(MaterialAttribute::DiffuseTextureCoordinates), 1);

    CORRADE_COMPARE(data.attributeType(MaterialAttribute::AmbientTextureMatrix), MaterialAttributeType::Matrix3x3);
    CORRADE_COMPARE(data.attributeType(MaterialAttribute::DiffuseTextureCoordinates), MaterialAttributeType::UnsignedInt);
    CORRADE_COMPARE(data.attributeType(MaterialAttribute::DoubleSided), MaterialAttributeType::Bool);

    CORRADE_COMPARE(data.attribute<Matrix3>(MaterialAttribute::AmbientTextureMatrix), Matrix3::scaling({0.5f, 1.0f}));
    CORRADE_COMPARE(data.attribute<UnsignedInt>(MaterialAttribute::DiffuseTextureCoordinates), 5);
    CORRADE_COMPARE(data.attribute<bool>(MaterialAttribute::DoubleSided), true);

    CORRADE_COMPARE(*static_cast<const Matrix3*>(data.attribute(MaterialAttribute::AmbientTextureMatrix)), Matrix3::scaling({0.5f, 1.0f}));
    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.attribute(MaterialAttribute::DiffuseTextureCoordinates)), 5);
    CORRADE_COMPARE(*static_cast<const bool*>(data.attribute(MaterialAttribute::DoubleSided)), true);

    /* Access by string */
    CORRADE_VERIFY(data.hasAttribute("DoubleSided"));
    CORRADE_VERIFY(data.hasAttribute("highlightColor"));
    CORRADE_VERIFY(!data.hasAttribute("TextureMatrix"));

    CORRADE_COMPARE(data.attributeId("DoubleSided"), 2);
    CORRADE_COMPARE(data.attributeId("AmbientTextureMatrix"), 0);
    CORRADE_COMPARE(data.attributeId("DiffuseTextureCoordinates"), 1);
    CORRADE_COMPARE(data.attributeId("highlightColor"), 3);

    CORRADE_COMPARE(data.attributeType("AmbientTextureMatrix"), MaterialAttributeType::Matrix3x3);
    CORRADE_COMPARE(data.attributeType("DiffuseTextureCoordinates"), MaterialAttributeType::UnsignedInt);
    CORRADE_COMPARE(data.attributeType("DoubleSided"), MaterialAttributeType::Bool);
    CORRADE_COMPARE(data.attributeType("highlightColor"), MaterialAttributeType::Vector4);

    CORRADE_COMPARE(data.attribute<Matrix3>("AmbientTextureMatrix"), Matrix3::scaling({0.5f, 1.0f}));
    CORRADE_COMPARE(data.attribute<UnsignedInt>("DiffuseTextureCoordinates"), 5);
    CORRADE_COMPARE(data.attribute<bool>("DoubleSided"), true);
    CORRADE_COMPARE(data.attribute<Color4>("highlightColor"), 0x335566ff_rgbaf);

    CORRADE_COMPARE(*static_cast<const Matrix3*>(data.attribute("AmbientTextureMatrix")), Matrix3::scaling({0.5f, 1.0f}));
    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.attribute("DiffuseTextureCoordinates")), 5);
    CORRADE_COMPARE(*static_cast<const bool*>(data.attribute("DoubleSided")), true);
    CORRADE_COMPARE(*static_cast<const Color4*>(data.attribute("highlightColor")), 0x335566ff_rgbaf);
}

void MaterialDataTest::constructEmptyAttribute() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialData{{}, {
        {"DiffuseTexture"_s, 12u},
        MaterialAttributeData{}
    }};
    CORRADE_COMPARE(out.str(), "Trade::MaterialData: attribute 1 doesn't specify anything\n");
}

void MaterialDataTest::constructDuplicateAttribute() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    auto attributes = Containers::Array<MaterialAttributeData>{Containers::InPlaceInit, {
        {MaterialAttribute::DoubleSided, true},
        {MaterialAttribute::DiffuseTextureCoordinates, 5u},
        {"highlightColor", 0x335566ff_rgbaf},
        {MaterialAttribute::AmbientTextureMatrix, Matrix3::scaling({0.5f, 1.0f})},
        {MaterialAttribute::DiffuseTextureCoordinates, 5u}
    }};

    /* Testing that it asserts in all input permutations */
    for(std::size_t i = 0; i != testCaseRepeatId(); ++i)
        std::next_permutation(attributes.begin(), attributes.end(), [](const MaterialAttributeData& a, const MaterialAttributeData& b) {
            return a.name() < b.name();
        });

    std::ostringstream out;
    Error redirectError{&out};
    MaterialData data{{}, std::move(attributes)};
    /* Because with graceful asserts it doesn't exit on error, the assertion
       might get printed multiple times */
    CORRADE_COMPARE(Utility::String::partition(out.str(), '\n')[0], "Trade::MaterialData: duplicate attribute DiffuseTextureCoordinates");
}

void MaterialDataTest::constructFromImmutableSortedArray() {
    constexpr MaterialAttributeData attributes[]{
        {"hello this is first"_s, 1},
        {"yay this is last"_s, Vector4{0.2f, 0.6f, 0.4f, 1.0f}}
    };

    MaterialData data{{}, Containers::Array<MaterialAttributeData>{const_cast<MaterialAttributeData*>(attributes), Containers::arraySize(attributes), [](MaterialAttributeData*, std::size_t) {}}};

    CORRADE_COMPARE(data.attributeCount(), 2);
    CORRADE_COMPARE(data.attributeName(0), "hello this is first");
    CORRADE_COMPARE(data.attributeName(1), "yay this is last");
}

void MaterialDataTest::constructLayers() {
    int state;
    MaterialData data{MaterialType::Phong, {
        {MaterialAttribute::DoubleSided, true},
        {MaterialAttribute::DiffuseTextureCoordinates, 5u},

        /* Layer name gets sorted first by the constructor */
        {"highlightColor", 0x335566ff_rgbaf},
        {MaterialAttribute::AlphaBlend, true},
        {MaterialAttribute::LayerName, "ClearCoat"},

        /* Empty layer here */

        /* Unnamed but nonempty layer */
        {"thickness", 0.015f},
        {MaterialAttribute::NormalTexture, 3u}
    }, {
        2, 5, 5, 7
    }, &state};

    CORRADE_COMPARE(data.types(), MaterialType::Phong);
    CORRADE_COMPARE(data.importerState(), &state);

    CORRADE_COMPARE(data.layerCount(), 4);
    CORRADE_COMPARE(data.layerData().size(), 4);

    CORRADE_COMPARE(data.attributeData().size(), 7);
    CORRADE_COMPARE(data.attributeCount(0), 2);
    CORRADE_COMPARE(data.attributeCount(1), 3);
    CORRADE_COMPARE(data.attributeCount(2), 0);
    CORRADE_COMPARE(data.attributeCount(3), 2);
    CORRADE_COMPARE(data.attributeCount("ClearCoat"), 3);

    /* Layer access */
    CORRADE_COMPARE(data.layerName(0), "");
    CORRADE_COMPARE(data.layerName(1), "ClearCoat");
    CORRADE_COMPARE(data.layerName(2), "");
    CORRADE_COMPARE(data.layerName(3), "");

    CORRADE_VERIFY(data.hasLayer("ClearCoat"));
    CORRADE_VERIFY(!data.hasLayer(""));
    CORRADE_VERIFY(!data.hasLayer("DoubleSided"));

    CORRADE_COMPARE(data.layerId("ClearCoat"), 1);

    /* Verify sorting in each layer */
    CORRADE_COMPARE(data.attributeName(0, 0), "DiffuseTextureCoordinates");
    CORRADE_COMPARE(data.attributeName(0, 1), "DoubleSided");

    CORRADE_COMPARE(data.attributeName(1, 0), "$LayerName");
    CORRADE_COMPARE(data.attributeName(1, 1), "AlphaBlend");
    CORRADE_COMPARE(data.attributeName(1, 2), "highlightColor");

    CORRADE_COMPARE(data.attributeName(3, 0), "NormalTexture");
    CORRADE_COMPARE(data.attributeName(3, 1), "thickness");

    /* Access by layer ID and attribute ID */
    CORRADE_COMPARE(data.attributeType(0, 0), MaterialAttributeType::UnsignedInt);
    CORRADE_COMPARE(data.attributeType(1, 2), MaterialAttributeType::Vector4);
    CORRADE_COMPARE(data.attributeType(3, 1), MaterialAttributeType::Float);

    CORRADE_COMPARE(data.attribute<UnsignedInt>(0, 0), 5);
    CORRADE_COMPARE(data.attribute<Color4>(1, 2), 0x335566ff_rgbaf);
    CORRADE_COMPARE(data.attribute<Float>(3, 1), 0.015f);

    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.attribute(0, 0)), 5);
    CORRADE_COMPARE(*static_cast<const Color4*>(data.attribute(1, 2)), 0x335566ff_rgbaf);
    CORRADE_COMPARE(*static_cast<const Float*>(data.attribute(3, 1)), 0.015f);

    /* Access by layer ID and attribute name */
    CORRADE_VERIFY(data.hasAttribute(0, MaterialAttribute::DiffuseTextureCoordinates));
    CORRADE_VERIFY(!data.hasAttribute(0, MaterialAttribute::AlphaBlend));
    CORRADE_VERIFY(data.hasAttribute(1, MaterialAttribute::AlphaBlend));
    CORRADE_VERIFY(data.hasAttribute(1, MaterialAttribute::LayerName));
    CORRADE_VERIFY(!data.hasAttribute(2, MaterialAttribute::LayerName));
    CORRADE_VERIFY(!data.hasAttribute(2, MaterialAttribute::NormalTexture));
    CORRADE_VERIFY(data.hasAttribute(3, MaterialAttribute::NormalTexture));

    CORRADE_COMPARE(data.attributeId(0, MaterialAttribute::DiffuseTextureCoordinates), 0);
    CORRADE_COMPARE(data.attributeId(1, MaterialAttribute::AlphaBlend), 1);
    CORRADE_COMPARE(data.attributeId(1, MaterialAttribute::LayerName), 0);
    CORRADE_COMPARE(data.attributeId(3, MaterialAttribute::NormalTexture), 0);

    CORRADE_COMPARE(data.attributeType(0, MaterialAttribute::DiffuseTextureCoordinates), MaterialAttributeType::UnsignedInt);
    CORRADE_COMPARE(data.attributeType(1, MaterialAttribute::AlphaBlend), MaterialAttributeType::Bool);
    CORRADE_COMPARE(data.attributeType(1, MaterialAttribute::LayerName), MaterialAttributeType::String);
    CORRADE_COMPARE(data.attributeType(3, MaterialAttribute::NormalTexture), MaterialAttributeType::UnsignedInt);

    CORRADE_COMPARE(data.attribute<UnsignedInt>(0, MaterialAttribute::DiffuseTextureCoordinates), 5);
    CORRADE_COMPARE(data.attribute<bool>(1, MaterialAttribute::AlphaBlend), true);
    CORRADE_COMPARE(data.attribute<Containers::StringView>(1, MaterialAttribute::LayerName), "ClearCoat");
    CORRADE_COMPARE(data.attribute<UnsignedInt>(3, MaterialAttribute::NormalTexture), 3);

    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.attribute(0, MaterialAttribute::DiffuseTextureCoordinates)), 5);
    CORRADE_COMPARE(*static_cast<const bool*>(data.attribute(1, MaterialAttribute::AlphaBlend)), true);
    CORRADE_COMPARE(static_cast<const char*>(data.attribute(1, MaterialAttribute::LayerName)), "ClearCoat"_s);
    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.attribute(3, MaterialAttribute::NormalTexture)), 3);

    /* Access by layer ID and attribute string */
    CORRADE_VERIFY(data.hasAttribute(0, "DoubleSided"));
    CORRADE_VERIFY(!data.hasAttribute(0, "highlightColor"));
    CORRADE_VERIFY(data.hasAttribute(1, "highlightColor"));
    CORRADE_VERIFY(data.hasAttribute(1, "$LayerName"));
    CORRADE_VERIFY(!data.hasAttribute(2, "$LayerName"));
    CORRADE_VERIFY(!data.hasAttribute(2, "NormalTexture"));
    CORRADE_VERIFY(data.hasAttribute(3, "NormalTexture"));

    CORRADE_COMPARE(data.attributeId(0, "DoubleSided"), 1);
    CORRADE_COMPARE(data.attributeId(1, "highlightColor"), 2);
    CORRADE_COMPARE(data.attributeId(1, "$LayerName"), 0);
    CORRADE_COMPARE(data.attributeId(3, "NormalTexture"), 0);

    CORRADE_COMPARE(data.attributeType(0, "DoubleSided"), MaterialAttributeType::Bool);
    CORRADE_COMPARE(data.attributeType(1, "highlightColor"), MaterialAttributeType::Vector4);
    CORRADE_COMPARE(data.attributeType(1, "$LayerName"), MaterialAttributeType::String);
    CORRADE_COMPARE(data.attributeType(3, "NormalTexture"), MaterialAttributeType::UnsignedInt);

    CORRADE_COMPARE(data.attribute<bool>(0, "DoubleSided"), true);
    CORRADE_COMPARE(data.attribute<Color4>(1, "highlightColor"), 0x335566ff_rgbaf);
    CORRADE_COMPARE(data.attribute<Containers::StringView>(1, "$LayerName"), "ClearCoat");
    CORRADE_COMPARE(data.attribute<UnsignedInt>(3, "NormalTexture"), 3);

    CORRADE_COMPARE(*static_cast<const bool*>(data.attribute(0, "DoubleSided")), true);
    CORRADE_COMPARE(*static_cast<const Color4*>(data.attribute(1, "highlightColor")), 0x335566ff_rgbaf);
    CORRADE_COMPARE(static_cast<const char*>(data.attribute(1, "$LayerName")), "ClearCoat"_s);
    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.attribute(3, "NormalTexture")), 3);

    /* Access by layer string and attribute ID */
    CORRADE_COMPARE(data.attributeName("ClearCoat", 1), "AlphaBlend");
    CORRADE_COMPARE(data.attributeName("ClearCoat", 2), "highlightColor");

    CORRADE_COMPARE(data.attributeType("ClearCoat", 1), MaterialAttributeType::Bool);
    CORRADE_COMPARE(data.attributeType("ClearCoat", 2), MaterialAttributeType::Vector4);

    CORRADE_COMPARE(data.attribute<bool>("ClearCoat", 1), true);
    CORRADE_COMPARE(data.attribute<Color4>("ClearCoat", 2), 0x335566ff_rgbaf);

    CORRADE_COMPARE(*static_cast<const bool*>(data.attribute("ClearCoat", 1)), true);
    CORRADE_COMPARE(*static_cast<const Color4*>(data.attribute("ClearCoat", 2)), 0x335566ff_rgbaf);

    /* Access by layer string and attribute name */
    CORRADE_VERIFY(data.hasAttribute("ClearCoat", MaterialAttribute::AlphaBlend));
    CORRADE_VERIFY(data.hasAttribute("ClearCoat", MaterialAttribute::LayerName));

    CORRADE_COMPARE(data.attributeId("ClearCoat", MaterialAttribute::AlphaBlend), 1);
    CORRADE_COMPARE(data.attributeId("ClearCoat", MaterialAttribute::LayerName), 0);

    CORRADE_COMPARE(data.attributeType("ClearCoat", MaterialAttribute::AlphaBlend), MaterialAttributeType::Bool);
    CORRADE_COMPARE(data.attributeType("ClearCoat", MaterialAttribute::LayerName), MaterialAttributeType::String);

    CORRADE_COMPARE(data.attribute<bool>("ClearCoat", MaterialAttribute::AlphaBlend), true);
    CORRADE_COMPARE(data.attribute<Containers::StringView>("ClearCoat", MaterialAttribute::LayerName), "ClearCoat");

    CORRADE_COMPARE(*static_cast<const bool*>(data.attribute("ClearCoat", MaterialAttribute::AlphaBlend)), true);
    CORRADE_COMPARE(static_cast<const char*>(data.attribute("ClearCoat", MaterialAttribute::LayerName)), "ClearCoat"_s);

    /* Access by layer string and attribute string */
    CORRADE_VERIFY(data.hasAttribute("ClearCoat", "highlightColor"));
    CORRADE_VERIFY(data.hasAttribute("ClearCoat", "$LayerName"));

    CORRADE_COMPARE(data.attributeId("ClearCoat", "highlightColor"), 2);
    CORRADE_COMPARE(data.attributeId("ClearCoat", "$LayerName"), 0);

    CORRADE_COMPARE(data.attributeType("ClearCoat", "highlightColor"), MaterialAttributeType::Vector4);
    CORRADE_COMPARE(data.attributeType("ClearCoat", "$LayerName"), MaterialAttributeType::String);

    CORRADE_COMPARE(data.attribute<Color4>("ClearCoat", "highlightColor"), 0x335566ff_rgbaf);
    CORRADE_COMPARE(data.attribute<Containers::StringView>("ClearCoat", "$LayerName"), "ClearCoat");

    CORRADE_COMPARE(*static_cast<const Color4*>(data.attribute("ClearCoat", "highlightColor")), 0x335566ff_rgbaf);
    CORRADE_COMPARE(static_cast<const char*>(data.attribute("ClearCoat", "$LayerName")), "ClearCoat"_s);
}

void MaterialDataTest::constructLayersNotMonotonic() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialData data{MaterialType::Phong, {
        {MaterialAttribute::DoubleSided, true},
        {MaterialAttribute::DiffuseTextureCoordinates, 5u},
        {MaterialAttribute::AlphaBlend, true},
        {MaterialAttribute::LayerName, "ClearCoat"},
        {MaterialAttribute::NormalTexture, 3u}
    }, {2, 5, 4, 5}};
    CORRADE_COMPARE(out.str(), "Trade::MaterialData: invalid range (5, 4) for layer 2 with 5 attributes in total\n");
}

void MaterialDataTest::constructLayersOffsetOutOfBounds() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    MaterialData data{MaterialType::Phong, {
        {MaterialAttribute::DoubleSided, true},
        {MaterialAttribute::DiffuseTextureCoordinates, 5u},
        {MaterialAttribute::AlphaBlend, true},
        {MaterialAttribute::LayerName, "ClearCoat"},
        {MaterialAttribute::NormalTexture, 3u}
    }, {2, 6}};
    CORRADE_COMPARE(out.str(), "Trade::MaterialData: invalid range (2, 6) for layer 1 with 5 attributes in total\n");
}

void MaterialDataTest::constructNonOwned() {
    constexpr MaterialAttributeData attributes[]{
        {"AmbientTextureMatrix"_s, Matrix3{{0.5f, 0.0f, 0.0f},
                                           {0.0f, 1.0f, 0.0f},
                                           {0.0f, 0.0f, 1.0f}}},
        {"DiffuseTextureCoordinates"_s, 5u},
        {"DoubleSided"_s, true},
        {"highlightColor"_s, Vector4{0.2f, 0.6f, 0.4f, 1.0f}}
    };

    int state;
    MaterialData data{MaterialType::Phong, {}, attributes, &state};

    /* Expecting the same output as in construct() */
    CORRADE_COMPARE(data.types(), MaterialType::Phong);
    CORRADE_COMPARE(data.layerCount(), 1);
    CORRADE_VERIFY(!data.layerData());
    CORRADE_COMPARE(data.attributeCount(), 4);
    CORRADE_COMPARE(data.attributeData().size(), 4);
    CORRADE_COMPARE(data.attributeData().data(), attributes);
    CORRADE_COMPARE(data.importerState(), &state);

    /* We sorted the input already */
    CORRADE_COMPARE(data.attributeName(0), "AmbientTextureMatrix");
    CORRADE_COMPARE(data.attributeName(1), "DiffuseTextureCoordinates");
    CORRADE_COMPARE(data.attributeName(2), "DoubleSided");
    CORRADE_COMPARE(data.attributeName(3), "highlightColor");

    /* No need to verify the contents as there's no difference in access in
       owned vs non-owned */
}

void MaterialDataTest::constructNonOwnedLayers() {
    constexpr MaterialAttributeData attributes[]{
        {"DiffuseCoordinateSet"_s, 5u},
        {"DoubleSided"_s, true},

        {"$LayerName"_s, "ClearCoat"_s},
        {"AlphaBlend"_s, true},
        {"highlightColor"_s, Vector4{0.2f, 0.6f, 0.4f, 1.0f}},

        /* Empty layer here */

        /* Unnamed but nonempty layer */
        {"NormalTexture"_s, 3u},
        {"thickness"_s, 0.015f}
    };

    constexpr UnsignedInt layers[]{
        2, 5, 5, 7
    };

    int state;
    MaterialData data{MaterialType::Phong,
        {}, attributes,
        {}, layers, &state};

    /* Expecting the same output as in constructLayers() */
    CORRADE_COMPARE(data.types(), MaterialType::Phong);
    CORRADE_COMPARE(data.importerState(), &state);

    CORRADE_COMPARE(data.layerCount(), 4);
    CORRADE_COMPARE(data.layerData().size(), 4);
    CORRADE_COMPARE(data.layerData().data(), layers);

    CORRADE_COMPARE(data.attributeData().size(), 7);
    CORRADE_COMPARE(data.attributeData().data(), attributes);
    CORRADE_COMPARE(data.attributeCount(0), 2);
    CORRADE_COMPARE(data.attributeCount(1), 3);
    CORRADE_COMPARE(data.attributeCount(2), 0);
    CORRADE_COMPARE(data.attributeCount(3), 2);

    /* Layer access */
    CORRADE_COMPARE(data.layerName(0), "");
    CORRADE_COMPARE(data.layerName(1), "ClearCoat");
    CORRADE_COMPARE(data.layerName(2), "");
    CORRADE_COMPARE(data.layerName(3), "");

    /* We sorted the input already */
    CORRADE_COMPARE(data.attributeName(0, 0), "DiffuseCoordinateSet");
    CORRADE_COMPARE(data.attributeName(0, 1), "DoubleSided");

    CORRADE_COMPARE(data.attributeName(1, 0), "$LayerName");
    CORRADE_COMPARE(data.attributeName(1, 1), "AlphaBlend");
    CORRADE_COMPARE(data.attributeName(1, 2), "highlightColor");

    CORRADE_COMPARE(data.attributeName(3, 0), "NormalTexture");
    CORRADE_COMPARE(data.attributeName(3, 1), "thickness");

    /* No need to verify the contents as there's no difference in access in
       owned vs non-owned */
}

void MaterialDataTest::constructNonOwnedEmptyAttribute() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialAttributeData attributes[]{
        {"DiffuseTexture"_s, 12u},
        MaterialAttributeData{}
    };

    std::ostringstream out;
    Error redirectError{&out};
    /* nullptr to avoid attributes interpreted as importerState */
    MaterialData{{}, {}, attributes, nullptr};
    CORRADE_COMPARE(out.str(), "Trade::MaterialData: attribute 1 doesn't specify anything\n");
}

void MaterialDataTest::constructNonOwnedNotSorted() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialAttributeData attributes[]{
        {"DiffuseTextureCoordinates"_s, 5u},
        {"DiffuseTexture"_s, 12u}
    };

    std::ostringstream out;
    Error redirectError{&out};
    /* nullptr to avoid attributes interpreted as importerState */
    MaterialData{{}, {}, attributes, nullptr};
    CORRADE_COMPARE(out.str(), "Trade::MaterialData: DiffuseTexture has to be sorted before DiffuseTextureCoordinates if passing non-owned data\n");
}

void MaterialDataTest::constructNonOwnedDuplicateAttribute() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialAttributeData attributes[]{
        {"DiffuseTexture"_s, 35u},
        {"DiffuseTextureCoordinates"_s, 5u},
        {"DiffuseTextureCoordinates"_s, 12u}
    };

    std::ostringstream out;
    Error redirectError{&out};
    /* nullptr to avoid attributes interpreted as importerState */
    MaterialData{{}, {}, attributes, nullptr};
    CORRADE_COMPARE(out.str(), "Trade::MaterialData: duplicate attribute DiffuseTextureCoordinates\n");
}

void MaterialDataTest::constructNonOwnedLayersNotMonotonic() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialAttributeData attributes[]{
        {MaterialAttribute::AlphaBlend, true},
        {MaterialAttribute::DiffuseTextureCoordinates, 5u},
        {MaterialAttribute::LayerName, "ClearCoat"},
        {MaterialAttribute::DoubleSided, true},
        {MaterialAttribute::NormalTexture, 3u}
    };

    UnsignedInt layers[]{
        2, 5, 4, 5
    };

    std::ostringstream out;
    Error redirectError{&out};
    MaterialData data{MaterialType::Phong,
        {}, attributes,
        {}, layers};
    CORRADE_COMPARE(out.str(), "Trade::MaterialData: invalid range (5, 4) for layer 2 with 5 attributes in total\n");
}

void MaterialDataTest::constructNonOwnedLayersOffsetOutOfBounds() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialAttributeData attributes[]{
        {MaterialAttribute::AlphaBlend, true},
        {MaterialAttribute::DiffuseTextureCoordinates, 5u},
        {MaterialAttribute::LayerName, "ClearCoat"},
        {MaterialAttribute::DoubleSided, true},
        {MaterialAttribute::NormalTexture, 3u}
    };

    UnsignedInt layers[]{
        2, 6
    };

    std::ostringstream out;
    Error redirectError{&out};
    MaterialData data{MaterialType::Phong,
        {}, attributes,
        {}, layers};
    CORRADE_COMPARE(out.str(), "Trade::MaterialData: invalid range (2, 6) for layer 1 with 5 attributes in total\n");
}

void MaterialDataTest::constructCopy() {
    CORRADE_VERIFY(!(std::is_constructible<MaterialData, const MaterialData&>{}));
    CORRADE_VERIFY(!(std::is_assignable<MaterialData, const MaterialData&>{}));
}

void MaterialDataTest::constructMove() {
    int state;
    MaterialData a{MaterialType::Phong, {
        {MaterialAttribute::DoubleSided, true},
        {MaterialAttribute::AlphaBlend, true},
        {"boredomFactor", 5}
    }, {
        1, 1, 3
    }, &state};

    MaterialData b{std::move(a)};
    CORRADE_COMPARE(a.layerCount(), 1);
    CORRADE_COMPARE(a.attributeCount(), 0);
    CORRADE_COMPARE(b.types(), MaterialType::Phong);
    CORRADE_COMPARE(b.layerCount(), 3);
    CORRADE_COMPARE(b.attributeCount(2), 2);
    CORRADE_COMPARE(b.attributeName(2, 0), "AlphaBlend");
    CORRADE_COMPARE(b.importerState(), &state);

    MaterialData c{MaterialTypes{}, {
        {MaterialAttribute::AlphaMask, 0.5f}
    }, {1}};
    c = std::move(b);
    CORRADE_COMPARE(b.attributeCount(), 1);
    CORRADE_COMPARE(b.layerCount(), 1);
    CORRADE_COMPARE(c.types(), MaterialType::Phong);
    CORRADE_COMPARE(c.layerCount(), 3);
    CORRADE_COMPARE(c.attributeCount(2), 2);
    CORRADE_COMPARE(c.attributeName(2, 0), "AlphaBlend");
    CORRADE_COMPARE(c.importerState(), &state);

    CORRADE_VERIFY(std::is_nothrow_move_constructible<MaterialData>::value);
    CORRADE_VERIFY(std::is_nothrow_move_assignable<MaterialData>::value);
}

void MaterialDataTest::access() {
    MaterialData a{{}, {
        {MaterialAttribute::DoubleSided, false},
        {MaterialAttribute::AlphaBlend, true},
        {MaterialAttribute::AlphaMask, 0.9f}
    }};
    CORRADE_VERIFY(!a.isDoubleSided());
    CORRADE_COMPARE(a.alphaMode(), MaterialAlphaMode::Blend);
    CORRADE_COMPARE(a.alphaMask(), 0.9f);

    MaterialData b{{}, {
        {MaterialAttribute::AlphaBlend, false},
        {MaterialAttribute::AlphaMask, 0.3f}
    }};
    CORRADE_VERIFY(!b.isDoubleSided());
    CORRADE_COMPARE(b.alphaMode(), MaterialAlphaMode::Mask);
    CORRADE_COMPARE(b.alphaMask(), 0.3f);

    MaterialData c{{}, {
        {MaterialAttribute::DoubleSided, true},
    }};
    CORRADE_VERIFY(c.isDoubleSided());
    CORRADE_COMPARE(c.alphaMode(), MaterialAlphaMode::Opaque);
    CORRADE_COMPARE(c.alphaMask(), 0.5f);
}

void MaterialDataTest::accessPointer() {
    const Float a = 3.0f;
    Long b = -4;

    MaterialData data{{}, {
        {"pointer", &a},
        {"mutable", &b}
    }};
    CORRADE_COMPARE(data.attributeType("pointer"), MaterialAttributeType::Pointer);
    CORRADE_COMPARE(data.attributeType("mutable"), MaterialAttributeType::MutablePointer);

    CORRADE_COMPARE(*static_cast<const Float* const*>(data.attribute("pointer")), &a);
    CORRADE_COMPARE(*static_cast<Long* const*>(data.attribute("mutable")), &b);
    CORRADE_COMPARE(data.attribute<const Float*>("pointer"), &a);
    CORRADE_COMPARE(data.attribute<Long*>("mutable"), &b);
}

void MaterialDataTest::accessString() {
    MaterialData data{{}, {
        {"name?", "THIS IS\0WHO I AM!"_s}
    }};
    CORRADE_COMPARE(data.attributeType("name?"), MaterialAttributeType::String);

    /* Pointer access will stop at the first null byte, but typed access won't */
    CORRADE_COMPARE(static_cast<const char*>(data.attribute(0)), "THIS IS"_s);
    CORRADE_COMPARE(data.attribute<Containers::StringView>(0), "THIS IS\0WHO I AM!"_s);
    CORRADE_COMPARE(data.attribute<Containers::StringView>(0).flags(), Containers::StringViewFlag::NullTerminated);
    CORRADE_COMPARE(data.attribute<Containers::StringView>(0)[data.attribute<Containers::StringView>(0).size()], '\0');
}

void MaterialDataTest::accessTextureSwizzle() {
    MaterialData data{{}, {
        {"normalSwizzle", MaterialTextureSwizzle::BA}
    }};
    CORRADE_COMPARE(data.attributeType("normalSwizzle"), MaterialAttributeType::TextureSwizzle);

    /* Pointer access will stop at the first null byte, printing the string
       value */
    CORRADE_COMPARE(static_cast<const char*>(data.attribute(0)), "BA"_s);
    CORRADE_COMPARE(*static_cast<const MaterialTextureSwizzle*>(data.attribute(0)), MaterialTextureSwizzle::BA);
    CORRADE_COMPARE(data.attribute<MaterialTextureSwizzle>(0), MaterialTextureSwizzle::BA);
}

void MaterialDataTest::accessOptional() {
    MaterialData data{{}, {
        {MaterialAttribute::AlphaMask, 0.5f},
        {MaterialAttribute::SpecularTexture, 3u}
    }};

    /* This exists */
    CORRADE_VERIFY(data.tryAttribute("SpecularTexture"));
    CORRADE_VERIFY(data.tryAttribute(MaterialAttribute::SpecularTexture));
    CORRADE_COMPARE(*static_cast<const Int*>(data.tryAttribute("SpecularTexture")), 3);
    CORRADE_COMPARE(*static_cast<const Int*>(data.tryAttribute(MaterialAttribute::SpecularTexture)), 3);
    CORRADE_COMPARE(data.tryAttribute<UnsignedInt>("SpecularTexture"), 3);
    CORRADE_COMPARE(data.tryAttribute<UnsignedInt>(MaterialAttribute::SpecularTexture), 3);
    CORRADE_COMPARE(data.attributeOr("SpecularTexture", 5u), 3);
    CORRADE_COMPARE(data.attributeOr(MaterialAttribute::SpecularTexture, 5u), 3);

    /* This doesn't */
    CORRADE_VERIFY(!data.tryAttribute("DiffuseTexture"));
    CORRADE_VERIFY(!data.tryAttribute(MaterialAttribute::DiffuseTexture));
    CORRADE_VERIFY(!data.tryAttribute<UnsignedInt>("DiffuseTexture"));
    CORRADE_VERIFY(!data.tryAttribute<UnsignedInt>(MaterialAttribute::DiffuseTexture));
    CORRADE_COMPARE(data.attributeOr("DiffuseTexture", 5u), 5);
    CORRADE_COMPARE(data.attributeOr(MaterialAttribute::DiffuseTexture, 5u), 5);
}

void MaterialDataTest::accessOutOfBounds() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {MaterialAttribute::AlphaMask, 0.5f},
        {MaterialAttribute::SpecularTexture, 3u}
    }};

    std::ostringstream out;
    Error redirectError{&out};
    data.attributeName(2);
    data.attributeType(2);
    data.attribute(2);
    data.attribute<Int>(2);
    data.attribute<Containers::StringView>(2);
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attributeName(): index 2 out of range for 2 attributes in layer 0\n"
        "Trade::MaterialData::attributeType(): index 2 out of range for 2 attributes in layer 0\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 attributes in layer 0\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 attributes in layer 0\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 attributes in layer 0\n");
}

void MaterialDataTest::accessNotFound() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {"DiffuseColor", 0xff3366aa_rgbaf}
    }};

    CORRADE_VERIFY(!data.hasAttribute("DiffuseColour"));

    std::ostringstream out;
    Error redirectError{&out};
    data.attributeId("DiffuseColour");
    data.attributeType("DiffuseColour");
    data.attribute("DiffuseColour");
    data.attribute<Color4>("DiffuseColour");
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attributeId(): attribute DiffuseColour not found in layer 0\n"
        "Trade::MaterialData::attributeType(): attribute DiffuseColour not found in layer 0\n"
        "Trade::MaterialData::attribute(): attribute DiffuseColour not found in layer 0\n"
        "Trade::MaterialData::attribute(): attribute DiffuseColour not found in layer 0\n");
}

void MaterialDataTest::accessWrongType() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {"DiffuseColor", 0xff3366aa_rgbaf}
    }};

    std::ostringstream out;
    Error redirectError{&out};
    data.attribute<Color3>(0);
    data.attribute<Color3>(MaterialAttribute::DiffuseColor);
    data.attribute<Color3>("DiffuseColor");
    data.tryAttribute<Color3>(MaterialAttribute::DiffuseColor);
    data.tryAttribute<Color3>("DiffuseColor");
    data.attributeOr(MaterialAttribute::DiffuseColor, Color3{1.0f});
    data.attributeOr("DiffuseColor", Color3{1.0f});
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attribute(): improper type requested for DiffuseColor of Trade::MaterialAttributeType::Vector4\n"
        "Trade::MaterialData::attribute(): improper type requested for DiffuseColor of Trade::MaterialAttributeType::Vector4\n"
        "Trade::MaterialData::attribute(): improper type requested for DiffuseColor of Trade::MaterialAttributeType::Vector4\n"
        /* tryAttribute() and attributeOr() delegate to attribute() so the
           assert is the same */
        "Trade::MaterialData::attribute(): improper type requested for DiffuseColor of Trade::MaterialAttributeType::Vector4\n"
        "Trade::MaterialData::attribute(): improper type requested for DiffuseColor of Trade::MaterialAttributeType::Vector4\n"
        "Trade::MaterialData::attribute(): improper type requested for DiffuseColor of Trade::MaterialAttributeType::Vector4\n"
        "Trade::MaterialData::attribute(): improper type requested for DiffuseColor of Trade::MaterialAttributeType::Vector4\n");
}

void MaterialDataTest::accessWrongPointerType() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    Int a = 3;
    const Double b = 57.0;

    MaterialData data{{}, {
        {"mutablePointer", &a},
        {"pointer", &b}
    }};

    /* These are fine (type is not checked) */
    data.attribute<Byte*>("mutablePointer");
    data.attribute<const Float*>("pointer");

    std::ostringstream out;
    Error redirectError{&out};
    data.attribute<const Int*>("mutablePointer");
    data.attribute<Double*>("pointer");
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attribute(): improper type requested for mutablePointer of Trade::MaterialAttributeType::MutablePointer\n"
        "Trade::MaterialData::attribute(): improper type requested for pointer of Trade::MaterialAttributeType::Pointer\n");
}

void MaterialDataTest::accessWrongTypeString() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {"Shininess", 0.0f}
    }};

    std::ostringstream out;
    Error redirectError{&out};
    data.attribute<Containers::StringView>(0);
    data.attribute<Containers::StringView>(MaterialAttribute::Shininess);
    data.attribute<Containers::StringView>("Shininess");
    data.tryAttribute<Containers::StringView>(MaterialAttribute::Shininess);
    data.tryAttribute<Containers::StringView>("Shininess");
    data.attributeOr(MaterialAttribute::Shininess, Containers::StringView{});
    data.attributeOr("Shininess", Containers::StringView{});
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attribute(): Shininess of Trade::MaterialAttributeType::Float can't be retrieved as a string\n"
        "Trade::MaterialData::attribute(): Shininess of Trade::MaterialAttributeType::Float can't be retrieved as a string\n"
        "Trade::MaterialData::attribute(): Shininess of Trade::MaterialAttributeType::Float can't be retrieved as a string\n"
        /* tryAttribute() and attributeOr() delegate to attribute() so the
           assert is the same */
        "Trade::MaterialData::attribute(): Shininess of Trade::MaterialAttributeType::Float can't be retrieved as a string\n"
        "Trade::MaterialData::attribute(): Shininess of Trade::MaterialAttributeType::Float can't be retrieved as a string\n"
        "Trade::MaterialData::attribute(): Shininess of Trade::MaterialAttributeType::Float can't be retrieved as a string\n"
        "Trade::MaterialData::attribute(): Shininess of Trade::MaterialAttributeType::Float can't be retrieved as a string\n");
}

void MaterialDataTest::accessLayerLayerNameInBaseMaterial() {
    MaterialData data{{}, {
        {MaterialAttribute::Shininess, 50.0f},
        {MaterialAttribute::LayerName, "base material name"}
    }};

    /* To avoid confusing the base material with a layer, LayerName is ignored
       for the base material. */
    CORRADE_COMPARE(data.layerName(0), "");
    CORRADE_VERIFY(!data.hasLayer("base material name"));
}

void MaterialDataTest::accessLayerEmptyLayer() {
    /* If a layer is empty, its contents shouldn't leak into upper layers */
    MaterialData data{{}, {
        {MaterialAttribute::NormalTexture, 3u},
        {MaterialAttribute::LayerName, "crumples"}
    }, {0, 0, 2}};

    CORRADE_COMPARE(data.layerName(0), "");
    CORRADE_COMPARE(data.layerName(1), "");
    CORRADE_COMPARE(data.layerName(2), "crumples");
    CORRADE_COMPARE(data.attributeCount(0), 0);
    CORRADE_COMPARE(data.attributeCount(1), 0);
    CORRADE_COMPARE(data.attributeCount(2), 2);
    CORRADE_COMPARE(data.layerId("crumples"), 2);
    CORRADE_COMPARE(data.attribute<UnsignedInt>("crumples", MaterialAttribute::NormalTexture), 3u);
}

void MaterialDataTest::accessLayerIndexOptional() {
    MaterialData data{{}, {
        {MaterialAttribute::DiffuseColor, 0x335566ff_rgbaf},
        {MaterialAttribute::AlphaMask, 0.5f},
        {MaterialAttribute::SpecularTexture, 3u}
    }, {1, 3}};

    /* This exists */
    CORRADE_VERIFY(data.tryAttribute(1, "SpecularTexture"));
    CORRADE_VERIFY(data.tryAttribute(1, MaterialAttribute::SpecularTexture));
    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.tryAttribute(1, "SpecularTexture")), 3);
    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.tryAttribute(1, MaterialAttribute::SpecularTexture)), 3);
    CORRADE_COMPARE(data.tryAttribute<UnsignedInt>(1, "SpecularTexture"), 3);
    CORRADE_COMPARE(data.tryAttribute<UnsignedInt>(1, MaterialAttribute::SpecularTexture), 3);
    CORRADE_COMPARE(data.attributeOr(1, "SpecularTexture", 5u), 3);
    CORRADE_COMPARE(data.attributeOr(1, MaterialAttribute::SpecularTexture, 5u), 3);

    /* This doesn't */
    CORRADE_VERIFY(!data.tryAttribute(1, "DiffuseTexture"));
    CORRADE_VERIFY(!data.tryAttribute(1, MaterialAttribute::DiffuseTexture));
    CORRADE_VERIFY(!data.tryAttribute<UnsignedInt>(1, "DiffuseTexture"));
    CORRADE_VERIFY(!data.tryAttribute<UnsignedInt>(1, MaterialAttribute::DiffuseTexture));
    CORRADE_COMPARE(data.attributeOr(1, "DiffuseTexture", 5u), 5);
    CORRADE_COMPARE(data.attributeOr(1, MaterialAttribute::DiffuseTexture, 5u), 5);
}

void MaterialDataTest::accessLayerStringOptional() {
    MaterialData data{{}, {
        {MaterialAttribute::DiffuseColor, 0x335566ff_rgbaf},
        {MaterialAttribute::LayerName, "ClearCoat"},
        {MaterialAttribute::AlphaMask, 0.5f},
        {MaterialAttribute::SpecularTexture, 3u}
    }, {1, 4}};

    /* This exists */
    CORRADE_VERIFY(data.tryAttribute("ClearCoat", "SpecularTexture"));
    CORRADE_VERIFY(data.tryAttribute("ClearCoat", MaterialAttribute::SpecularTexture));
    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.tryAttribute("ClearCoat", "SpecularTexture")), 3);
    CORRADE_COMPARE(*static_cast<const UnsignedInt*>(data.tryAttribute("ClearCoat", MaterialAttribute::SpecularTexture)), 3);
    CORRADE_COMPARE(data.tryAttribute<UnsignedInt>("ClearCoat", "SpecularTexture"), 3);
    CORRADE_COMPARE(data.tryAttribute<UnsignedInt>("ClearCoat", MaterialAttribute::SpecularTexture), 3);
    CORRADE_COMPARE(data.attributeOr("ClearCoat", "SpecularTexture", 5u), 3);
    CORRADE_COMPARE(data.attributeOr("ClearCoat", MaterialAttribute::SpecularTexture, 5u), 3);

    /* This doesn't */
    CORRADE_VERIFY(!data.tryAttribute("ClearCoat", "DiffuseTexture"));
    CORRADE_VERIFY(!data.tryAttribute("ClearCoat", MaterialAttribute::DiffuseTexture));
    CORRADE_VERIFY(!data.tryAttribute<UnsignedInt>("ClearCoat", "DiffuseTexture"));
    CORRADE_VERIFY(!data.tryAttribute<UnsignedInt>("ClearCoat", MaterialAttribute::DiffuseTexture));
    CORRADE_COMPARE(data.attributeOr("ClearCoat", "DiffuseTexture", 5u), 5);
    CORRADE_COMPARE(data.attributeOr("ClearCoat", MaterialAttribute::DiffuseTexture, 5u), 5);
}

void MaterialDataTest::accessLayerOutOfBounds() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {MaterialAttribute::AlphaMask, 0.5f},
        {MaterialAttribute::SpecularTexture, 3u}
    }, {0, 2}};

    std::ostringstream out;
    Error redirectError{&out};
    data.layerName(2);
    data.attributeCount(2);
    data.hasAttribute(2, "AlphaMask");
    data.hasAttribute(2, MaterialAttribute::AlphaMask);
    data.attributeId(2, "AlphaMask");
    data.attributeId(2, MaterialAttribute::AlphaMask);
    data.attributeName(2, 0);
    data.attributeType(2, 0);
    data.attributeType(2, "AlphaMask");
    data.attributeType(2, MaterialAttribute::AlphaMask);
    data.attribute(2, 0);
    data.attribute(2, "AlphaMask");
    data.attribute(2, MaterialAttribute::AlphaMask);
    data.attribute<Int>(2, 0);
    data.attribute<Int>(2, "AlphaMask");
    data.attribute<Int>(2, MaterialAttribute::AlphaMask);
    data.attribute<Containers::StringView>(2, 0);
    data.tryAttribute(2, "AlphaMask");
    data.tryAttribute(2, MaterialAttribute::AlphaMask);
    data.tryAttribute<bool>(2, "AlphaMask");
    data.tryAttribute<bool>(2, MaterialAttribute::AlphaMask);
    data.attributeOr(2, "AlphaMask", false);
    data.attributeOr(2, MaterialAttribute::AlphaMask, false);
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::layerName(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attributeCount(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::hasAttribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::hasAttribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attributeId(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attributeId(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attributeName(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attributeType(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attributeType(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attributeType(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::tryAttribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::tryAttribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::tryAttribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::tryAttribute(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attributeOr(): index 2 out of range for 2 layers\n"
        "Trade::MaterialData::attributeOr(): index 2 out of range for 2 layers\n");
}

void MaterialDataTest::accessLayerNotFound() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {MaterialAttribute::LayerName, "clearCoat"},
        {MaterialAttribute::AlphaMask, 0.5f},
    }, {0, 2}};

    std::ostringstream out;
    Error redirectError{&out};
    data.attributeCount("ClearCoat");
    data.hasAttribute("ClearCoat", "AlphaMask");
    data.hasAttribute("ClearCoat", MaterialAttribute::AlphaMask);
    data.attributeId("ClearCoat", "AlphaMask");
    data.attributeId("ClearCoat", MaterialAttribute::AlphaMask);
    data.attributeName("ClearCoat", 0);
    data.attributeType("ClearCoat", 0);
    data.attributeType("ClearCoat", "AlphaMask");
    data.attributeType("ClearCoat", MaterialAttribute::AlphaMask);
    data.attribute("ClearCoat", 0);
    data.attribute("ClearCoat", "AlphaMask");
    data.attribute("ClearCoat", MaterialAttribute::AlphaMask);
    data.attribute<Int>("ClearCoat", 0);
    data.attribute<Int>("ClearCoat", "AlphaMask");
    data.attribute<Int>("ClearCoat", MaterialAttribute::AlphaMask);
    data.attribute<Containers::StringView>("ClearCoat", 0);
    data.tryAttribute("ClearCoat", "AlphaMask");
    data.tryAttribute("ClearCoat", MaterialAttribute::AlphaMask);
    data.tryAttribute<bool>("ClearCoat", "AlphaMask");
    data.tryAttribute<bool>("ClearCoat", MaterialAttribute::AlphaMask);
    data.attributeOr("ClearCoat", "AlphaMask", false);
    data.attributeOr("ClearCoat", MaterialAttribute::AlphaMask, false);
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attributeCount(): layer ClearCoat not found\n"
        "Trade::MaterialData::hasAttribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::hasAttribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::attributeId(): layer ClearCoat not found\n"
        "Trade::MaterialData::attributeId(): layer ClearCoat not found\n"
        "Trade::MaterialData::attributeName(): layer ClearCoat not found\n"
        "Trade::MaterialData::attributeType(): layer ClearCoat not found\n"
        "Trade::MaterialData::attributeType(): layer ClearCoat not found\n"
        "Trade::MaterialData::attributeType(): layer ClearCoat not found\n"
        "Trade::MaterialData::attribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::attribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::attribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::attribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::attribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::attribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::attribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::tryAttribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::tryAttribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::tryAttribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::tryAttribute(): layer ClearCoat not found\n"
        "Trade::MaterialData::attributeOr(): layer ClearCoat not found\n"
        "Trade::MaterialData::attributeOr(): layer ClearCoat not found\n");
}

void MaterialDataTest::accessOutOfBoundsInLayerIndex() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {MaterialAttribute::AlphaMask, 0.5f},
        {MaterialAttribute::SpecularTexture, 3u}
    }, {0, 2}};

    std::ostringstream out;
    Error redirectError{&out};
    data.attributeName(1, 2);
    data.attributeType(1, 2);
    data.attribute(1, 2);
    data.attribute<Int>(1, 2);
    data.attribute<Containers::StringView>(1, 2);
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attributeName(): index 2 out of range for 2 attributes in layer 1\n"
        "Trade::MaterialData::attributeType(): index 2 out of range for 2 attributes in layer 1\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 attributes in layer 1\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 attributes in layer 1\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 attributes in layer 1\n");
}

void MaterialDataTest::accessOutOfBoundsInLayerString() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {MaterialAttribute::LayerName, "ClearCoat"},
        {MaterialAttribute::AlphaMask, 0.5f}
    }, {0, 2}};

    std::ostringstream out;
    Error redirectError{&out};
    data.attributeName("ClearCoat", 2);
    data.attributeType("ClearCoat", 2);
    data.attribute("ClearCoat", 2);
    data.attribute<Int>("ClearCoat", 2);
    data.attribute<Containers::StringView>("ClearCoat", 2);
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attributeName(): index 2 out of range for 2 attributes in layer ClearCoat\n"
        "Trade::MaterialData::attributeType(): index 2 out of range for 2 attributes in layer ClearCoat\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 attributes in layer ClearCoat\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 attributes in layer ClearCoat\n"
        "Trade::MaterialData::attribute(): index 2 out of range for 2 attributes in layer ClearCoat\n");
}

void MaterialDataTest::accessNotFoundInLayerIndex() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {"DiffuseColor", 0xff3366aa_rgbaf}
    }, {0, 1}};

    CORRADE_VERIFY(!data.hasAttribute(1, "DiffuseColour"));

    std::ostringstream out;
    Error redirectError{&out};
    data.attributeId(1, "DiffuseColour");
    data.attributeType(1, "DiffuseColour");
    data.attribute(1, "DiffuseColour");
    data.attribute<Color4>(1, "DiffuseColour");
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attributeId(): attribute DiffuseColour not found in layer 1\n"
        "Trade::MaterialData::attributeType(): attribute DiffuseColour not found in layer 1\n"
        "Trade::MaterialData::attribute(): attribute DiffuseColour not found in layer 1\n"
        "Trade::MaterialData::attribute(): attribute DiffuseColour not found in layer 1\n");
}

void MaterialDataTest::accessNotFoundInLayerString() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {
        {MaterialAttribute::LayerName, "ClearCoat"},
        {"DiffuseColor", 0xff3366aa_rgbaf}
    }, {0, 1}};

    CORRADE_VERIFY(!data.hasAttribute(1, "DiffuseColour"));

    std::ostringstream out;
    Error redirectError{&out};
    data.attributeId("ClearCoat", "DiffuseColour");
    data.attributeType("ClearCoat", "DiffuseColour");
    data.attribute("ClearCoat", "DiffuseColour");
    data.attribute<Color4>("ClearCoat", "DiffuseColour");
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attributeId(): attribute DiffuseColour not found in layer ClearCoat\n"
        "Trade::MaterialData::attributeType(): attribute DiffuseColour not found in layer ClearCoat\n"
        "Trade::MaterialData::attribute(): attribute DiffuseColour not found in layer ClearCoat\n"
        "Trade::MaterialData::attribute(): attribute DiffuseColour not found in layer ClearCoat\n");
}

void MaterialDataTest::accessInvalidAttributeName() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    MaterialData data{{}, {}};

    /* The name should be converted to a string first and foremost and only
       then delegated to another overload. Which means all asserts should
       print the leaf function name. */
    std::ostringstream out;
    Error redirectError{&out};
    data.hasAttribute(0, MaterialAttribute(0x0));
    data.hasAttribute("Layer", MaterialAttribute(0xfefe));
    data.attributeId(0, MaterialAttribute(0x0));
    data.attributeId("Layer", MaterialAttribute(0xfefe));
    data.attributeType(0, MaterialAttribute(0x0));
    data.attributeType("Layer", MaterialAttribute(0xfefe));
    data.attribute(0, MaterialAttribute(0x0));
    data.attribute("Layer", MaterialAttribute(0xfefe));
    data.attribute<Int>(0, MaterialAttribute(0x0));
    data.attribute<Int>("Layer", MaterialAttribute(0xfefe));
    data.tryAttribute(0, MaterialAttribute(0x0));
    data.tryAttribute("Layer", MaterialAttribute(0xfefe));
    data.tryAttribute<Int>(0, MaterialAttribute(0x0));
    data.tryAttribute<Int>("Layer", MaterialAttribute(0xfefe));
    data.attributeOr(0, MaterialAttribute(0x0), 42);
    data.attributeOr("Layer", MaterialAttribute(0xfefe), 42);
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::hasAttribute(): invalid name Trade::MaterialAttribute(0x0)\n"
        "Trade::MaterialData::hasAttribute(): invalid name Trade::MaterialAttribute(0xfefe)\n"
        "Trade::MaterialData::attributeId(): invalid name Trade::MaterialAttribute(0x0)\n"
        "Trade::MaterialData::attributeId(): invalid name Trade::MaterialAttribute(0xfefe)\n"
        "Trade::MaterialData::attributeType(): invalid name Trade::MaterialAttribute(0x0)\n"
        "Trade::MaterialData::attributeType(): invalid name Trade::MaterialAttribute(0xfefe)\n"
        "Trade::MaterialData::attribute(): invalid name Trade::MaterialAttribute(0x0)\n"
        "Trade::MaterialData::attribute(): invalid name Trade::MaterialAttribute(0xfefe)\n"
        "Trade::MaterialData::attribute(): invalid name Trade::MaterialAttribute(0x0)\n"
        "Trade::MaterialData::attribute(): invalid name Trade::MaterialAttribute(0xfefe)\n"
        "Trade::MaterialData::tryAttribute(): invalid name Trade::MaterialAttribute(0x0)\n"
        "Trade::MaterialData::tryAttribute(): invalid name Trade::MaterialAttribute(0xfefe)\n"
        "Trade::MaterialData::tryAttribute(): invalid name Trade::MaterialAttribute(0x0)\n"
        "Trade::MaterialData::tryAttribute(): invalid name Trade::MaterialAttribute(0xfefe)\n"
        "Trade::MaterialData::attributeOr(): invalid name Trade::MaterialAttribute(0x0)\n"
        "Trade::MaterialData::attributeOr(): invalid name Trade::MaterialAttribute(0xfefe)\n");
}

void MaterialDataTest::releaseAttributes() {
    MaterialData data{{}, {
        {"DiffuseColor", 0xff3366aa_rgbaf},
        {MaterialAttribute::NormalTexture, 0u}
    }, {1, 2}};

    const void* pointer = data.attributeData().data();

    Containers::Array<MaterialAttributeData> released = data.releaseAttributeData();
    CORRADE_COMPARE(released.data(), pointer);
    CORRADE_COMPARE(released.size(), 2);
    CORRADE_VERIFY(data.layerData());
    CORRADE_COMPARE(data.layerCount(), 2);
    CORRADE_VERIFY(!data.attributeData());
    /* This is based on the layer offsets, not an actual attribute count, so
       it's inconsistent, yes */
    CORRADE_COMPARE(data.attributeCount(), 1);
}

void MaterialDataTest::releaseLayers() {
    MaterialData data{{}, {
        {"DiffuseColor", 0xff3366aa_rgbaf},
        {MaterialAttribute::NormalTexture, 0u}
    }, {1, 2}};

    const void* pointer = data.layerData().data();

    Containers::Array<UnsignedInt> released = data.releaseLayerData();
    CORRADE_COMPARE(released.data(), pointer);
    CORRADE_COMPARE(released.size(), 2);
    CORRADE_VERIFY(!data.layerData());
    /* Returns always at least 1 (now it sees no layer data and thus thinks
       there's just the implicit base material) */
    CORRADE_COMPARE(data.layerCount(), 1);
    CORRADE_VERIFY(data.attributeData());
    /* No layer offsets anymore, so this is the total attribute count instead
       of the base material attribute count. It's inconsistent, yes. */
    CORRADE_COMPARE(data.attributeCount(), 2);
}

#ifdef MAGNUM_BUILD_DEPRECATED
void MaterialDataTest::constructPhongDeprecated() {
    const int a{};
    CORRADE_IGNORE_DEPRECATED_PUSH
    PhongMaterialData data{PhongMaterialData::Flag::DoubleSided,
        0xccffbb_rgbf, {},
        0xebefbf_rgbf, {},
        0xacabad_rgbf, {}, {}, {},
        MaterialAlphaMode::Mask, 0.3f, 80.0f, &a};
    CORRADE_IGNORE_DEPRECATED_POP

    CORRADE_COMPARE(data.types(), MaterialType::Phong);
    CORRADE_IGNORE_DEPRECATED_PUSH
    CORRADE_COMPARE(data.type(), MaterialType::Phong);
    CORRADE_COMPARE(data.flags(), PhongMaterialData::Flag::DoubleSided);
    CORRADE_IGNORE_DEPRECATED_POP
    CORRADE_COMPARE(data.ambientColor(), 0xccffbb_rgbf);
    CORRADE_COMPARE(data.diffuseColor(), 0xebefbf_rgbf);
    CORRADE_COMPARE(data.specularColor(), 0xacabad_rgbf);
    CORRADE_COMPARE(data.textureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.alphaMode(), MaterialAlphaMode::Mask);
    CORRADE_COMPARE(data.alphaMask(), 0.3f);
    CORRADE_COMPARE(data.shininess(), 80.0f);
    CORRADE_COMPARE(data.importerState(), &a);
}

void MaterialDataTest::constructPhongDeprecatedTextured() {
    const int a{};
    CORRADE_IGNORE_DEPRECATED_PUSH
    PhongMaterialData data{
        PhongMaterialData::Flag::AmbientTexture|PhongMaterialData::Flag::SpecularTexture,
        0x111111_rgbf, 42,
        0xeebbff_rgbf, {},
        0xacabad_rgbf, 17, {}, {},
        MaterialAlphaMode::Blend, 0.37f, 96.0f, &a};
    CORRADE_IGNORE_DEPRECATED_POP

    CORRADE_COMPARE(data.types(), MaterialType::Phong);
    CORRADE_IGNORE_DEPRECATED_PUSH
    CORRADE_COMPARE(data.type(), MaterialType::Phong);
    CORRADE_COMPARE(data.flags(), PhongMaterialData::Flag::AmbientTexture|PhongMaterialData::Flag::SpecularTexture);
    CORRADE_IGNORE_DEPRECATED_POP
    CORRADE_COMPARE(data.ambientColor(), 0x111111_rgbf);
    CORRADE_COMPARE(data.ambientTexture(), 42);
    CORRADE_COMPARE(data.ambientTextureCoordinates(), 0);
    CORRADE_COMPARE(data.diffuseColor(), 0xeebbff_rgbf);
    CORRADE_COMPARE(data.specularColor(), 0xacabad_rgbf);
    CORRADE_COMPARE(data.specularTexture(), 17);
    CORRADE_COMPARE(data.specularTextureCoordinates(), 0);
    CORRADE_COMPARE(data.textureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.alphaMode(), MaterialAlphaMode::Blend);
    CORRADE_COMPARE(data.alphaMask(), 0.37f);
    CORRADE_COMPARE(data.shininess(), 96.0f);
    CORRADE_COMPARE(data.importerState(), &a);
}

void MaterialDataTest::constructPhongDeprecatedTexturedTextureTransform() {
    const int a{};
    CORRADE_IGNORE_DEPRECATED_PUSH
    PhongMaterialData data{
        PhongMaterialData::Flag::DiffuseTexture|PhongMaterialData::Flag::NormalTexture|PhongMaterialData::Flag::TextureTransformation,
        0x111111_rgbf, {},
        0xeebbff_rgbf, 42,
        0xacabad_rgbf, {}, 17,
        Matrix3::rotation(90.0_degf),
        MaterialAlphaMode::Mask, 0.5f, 96.0f, &a};
    CORRADE_IGNORE_DEPRECATED_POP

    CORRADE_COMPARE(data.types(), MaterialType::Phong);
    CORRADE_IGNORE_DEPRECATED_PUSH
    CORRADE_COMPARE(data.type(), MaterialType::Phong);
    CORRADE_COMPARE(data.flags(), PhongMaterialData::Flag::DiffuseTexture|PhongMaterialData::Flag::NormalTexture|PhongMaterialData::Flag::TextureTransformation);
    CORRADE_IGNORE_DEPRECATED_POP
    CORRADE_COMPARE(data.ambientColor(), 0x111111_rgbf);
    CORRADE_COMPARE(data.diffuseColor(), 0xeebbff_rgbf);
    CORRADE_COMPARE(data.diffuseTexture(), 42);
    CORRADE_COMPARE(data.specularColor(), 0xacabad_rgbf);
    CORRADE_COMPARE(data.normalTexture(), 17);
    CORRADE_COMPARE(data.textureMatrix(), Matrix3::rotation(90.0_degf));
    CORRADE_COMPARE(data.alphaMode(), MaterialAlphaMode::Mask);
    CORRADE_COMPARE(data.alphaMask(), 0.5f);
    CORRADE_COMPARE(data.shininess(), 96.0f);
    CORRADE_COMPARE(data.importerState(), &a);
}

void MaterialDataTest::constructPhongDeprecatedTexturedCoordinates() {
    const int a{};
    CORRADE_IGNORE_DEPRECATED_PUSH
    PhongMaterialData data{
        PhongMaterialData::Flag::AmbientTexture|PhongMaterialData::Flag::DiffuseTexture|PhongMaterialData::Flag::SpecularTexture|PhongMaterialData::Flag::NormalTexture|PhongMaterialData::Flag::TextureCoordinates,
        0x111111_rgbf, 42, 3,
        0xeebbff_rgbf, {}, 6,
        0xacabad_rgbf, 17, 1,
        0, 8, {},
        MaterialAlphaMode::Blend, 0.37f, 96.0f, &a};
    CORRADE_IGNORE_DEPRECATED_POP

    CORRADE_COMPARE(data.types(), MaterialType::Phong);
    CORRADE_IGNORE_DEPRECATED_PUSH
    CORRADE_COMPARE(data.type(), MaterialType::Phong);
    CORRADE_COMPARE(data.flags(), PhongMaterialData::Flag::AmbientTexture|PhongMaterialData::Flag::DiffuseTexture|PhongMaterialData::Flag::SpecularTexture|PhongMaterialData::Flag::NormalTexture|PhongMaterialData::Flag::TextureCoordinates);
    CORRADE_IGNORE_DEPRECATED_POP
    CORRADE_COMPARE(data.ambientColor(), 0x111111_rgbf);
    CORRADE_COMPARE(data.ambientTexture(), 42);
    CORRADE_COMPARE(data.ambientTextureCoordinates(), 3);
    CORRADE_COMPARE(data.diffuseColor(), 0xeebbff_rgbf);
    CORRADE_COMPARE(data.diffuseTextureCoordinates(), 6);
    CORRADE_COMPARE(data.specularColor(), 0xacabad_rgbf);
    CORRADE_COMPARE(data.specularTexture(), 17);
    CORRADE_COMPARE(data.specularTextureCoordinates(), 1);
    CORRADE_COMPARE(data.normalTexture(), 0);
    CORRADE_COMPARE(data.normalTextureCoordinates(), 8);
    CORRADE_COMPARE(data.textureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.ambientTextureCoordinates(), 3);
    CORRADE_COMPARE(data.alphaMode(), MaterialAlphaMode::Blend);
    CORRADE_COMPARE(data.alphaMask(), 0.37f);
    CORRADE_COMPARE(data.shininess(), 96.0f);
    CORRADE_COMPARE(data.importerState(), &a);
}

void MaterialDataTest::constructPhongDeprecatedTextureTransformNoTextures() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    CORRADE_IGNORE_DEPRECATED_PUSH
    PhongMaterialData a{PhongMaterialData::Flag::TextureTransformation,
        {}, {},
        {}, {},
        {}, {}, {}, {},
        {}, 0.5f, 80.0f};
    CORRADE_IGNORE_DEPRECATED_POP
    CORRADE_COMPARE(out.str(),
        "Trade::PhongMaterialData: texture transformation enabled but the material has no textures\n");
}

void MaterialDataTest::constructPhongDeprecatedNoTextureTransformationFlag() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    CORRADE_IGNORE_DEPRECATED_PUSH
    PhongMaterialData a{{},
        {}, {},
        {}, {},
        {}, {}, {}, Matrix3::rotation(90.0_degf),
        {}, 0.5f, 80.0f};
    CORRADE_IGNORE_DEPRECATED_POP
    CORRADE_COMPARE(out.str(),
        "PhongMaterialData::PhongMaterialData: non-default texture matrix requires Flag::TextureTransformation to be enabled\n");
}

void MaterialDataTest::constructPhongDeprecatedNoTextureCoordinatesFlag() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    std::ostringstream out;
    Error redirectError{&out};
    CORRADE_IGNORE_DEPRECATED_PUSH
    PhongMaterialData a{{},
        {}, {}, 1,
        {}, {}, 2,
        {}, {}, 3, {}, 4, {},
        {}, 0.5f, 80.0f};
    CORRADE_IGNORE_DEPRECATED_POP
    CORRADE_COMPARE(out.str(),
        "PhongMaterialData::PhongMaterialData: non-zero texture coordinate sets require Flag::TextureCoordinates to be enabled\n");
}
#endif

void MaterialDataTest::phongAccess() {
    MaterialData base{MaterialType::Phong, {
        {MaterialAttribute::AmbientColor, 0xccffbbff_rgbaf},
        {MaterialAttribute::DiffuseColor, 0xebefbfff_rgbaf},
        {MaterialAttribute::SpecularColor, 0xacabadff_rgbaf},
        {MaterialAttribute::Shininess, 96.0f}
    }};

    CORRADE_COMPARE(base.types(), MaterialType::Phong);
    const PhongMaterialData& data = static_cast<const PhongMaterialData&>(base);

    CORRADE_VERIFY(!data.hasTextureTransformation());
    CORRADE_VERIFY(!data.hasTextureCoordinates());
    CORRADE_COMPARE(data.ambientColor(), 0xccffbb_rgbf);
    CORRADE_COMPARE(data.diffuseColor(), 0xebefbf_rgbf);
    CORRADE_COMPARE(data.specularColor(), 0xacabad_rgbf);
    CORRADE_COMPARE(data.shininess(), 96.0f);
}

void MaterialDataTest::phongAccessDefaults() {
    MaterialData base{{}, {}};

    CORRADE_COMPARE(base.types(), MaterialTypes{});
    /* Casting is fine even if the type doesn't include Phong */
    const PhongMaterialData& data = static_cast<const PhongMaterialData&>(base);

    CORRADE_VERIFY(!data.hasTextureTransformation());
    CORRADE_VERIFY(!data.hasTextureCoordinates());
    CORRADE_COMPARE(data.ambientColor(), 0x000000_rgbf);
    CORRADE_COMPARE(data.diffuseColor(), 0xffffff_rgbf);
    CORRADE_COMPARE(data.specularColor(), 0xffffff_rgbf);
    CORRADE_COMPARE(data.textureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.textureCoordinates(), 0);
    CORRADE_COMPARE(data.shininess(), 80.0f);
}

void MaterialDataTest::phongAccessTextured() {
    PhongMaterialData data{{}, {
        {MaterialAttribute::AmbientColor, 0x111111ff_rgbaf},
        {MaterialAttribute::AmbientTexture, 42u},
        {MaterialAttribute::AmbientTextureMatrix, Matrix3::scaling({0.5f, 1.0f})},
        {MaterialAttribute::AmbientTextureCoordinates, 2u},
        {MaterialAttribute::DiffuseTexture, 33u},
        {MaterialAttribute::DiffuseColor, 0xeebbffff_rgbaf},
        {MaterialAttribute::DiffuseTextureMatrix, Matrix3::scaling({0.5f, 0.5f})},
        {MaterialAttribute::DiffuseTextureCoordinates, 3u},
        {MaterialAttribute::SpecularColor, 0xacabadff_rgbaf},
        {MaterialAttribute::SpecularTexture, 17u},
        {MaterialAttribute::SpecularTextureMatrix, Matrix3::scaling({1.0f, 1.0f})},
        {MaterialAttribute::SpecularTextureCoordinates, 4u},
        {MaterialAttribute::NormalTexture, 0u},
        {MaterialAttribute::NormalTextureMatrix, Matrix3::scaling({1.0f, 0.5f})},
        {MaterialAttribute::NormalTextureCoordinates, 5u}
    }};

    CORRADE_VERIFY(data.hasTextureTransformation());
    CORRADE_VERIFY(data.hasTextureCoordinates());
    CORRADE_COMPARE(data.ambientColor(), 0x111111_rgbf);
    CORRADE_COMPARE(data.ambientTexture(), 42);
    CORRADE_COMPARE(data.ambientTextureMatrix(), Matrix3::scaling({0.5f, 1.0f}));
    CORRADE_COMPARE(data.ambientTextureCoordinates(), 2);
    CORRADE_COMPARE(data.diffuseColor(), 0xeebbff_rgbf);
    CORRADE_COMPARE(data.diffuseTexture(), 33);
    CORRADE_COMPARE(data.diffuseTextureMatrix(), Matrix3::scaling({0.5f, 0.5f}));
    CORRADE_COMPARE(data.diffuseTextureCoordinates(), 3);
    CORRADE_COMPARE(data.specularColor(), 0xacabad_rgbf);
    CORRADE_COMPARE(data.specularTexture(), 17);
    CORRADE_COMPARE(data.specularTextureMatrix(), Matrix3::scaling({1.0f, 1.0f}));
    CORRADE_COMPARE(data.specularTextureCoordinates(), 4);
    CORRADE_COMPARE(data.normalTexture(), 0);
    CORRADE_COMPARE(data.normalTextureMatrix(), Matrix3::scaling({1.0f, 0.5f}));
    CORRADE_COMPARE(data.normalTextureCoordinates(), 5);

    CORRADE_COMPARE(data.textureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.textureCoordinates(), 0);
}

void MaterialDataTest::phongAccessTexturedDefaults() {
    PhongMaterialData data{{}, {
        {MaterialAttribute::AmbientTexture, 42u},
        {MaterialAttribute::DiffuseTexture, 33u},
        {MaterialAttribute::SpecularTexture, 17u},
        {MaterialAttribute::NormalTexture, 1u}
    }};

    CORRADE_VERIFY(!data.hasTextureTransformation());
    CORRADE_VERIFY(!data.hasTextureCoordinates());
    CORRADE_COMPARE(data.ambientColor(), 0xffffffff_rgbaf);
    CORRADE_COMPARE(data.ambientTexture(), 42);
    CORRADE_COMPARE(data.ambientTextureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.ambientTextureCoordinates(), 0);
    CORRADE_COMPARE(data.diffuseColor(), 0xffffffff_rgbaf);
    CORRADE_COMPARE(data.diffuseTexture(), 33);
    CORRADE_COMPARE(data.diffuseTextureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.diffuseTextureCoordinates(), 0);
    CORRADE_COMPARE(data.specularColor(), 0xffffffff_rgbaf);
    CORRADE_COMPARE(data.specularTexture(), 17);
    CORRADE_COMPARE(data.specularTextureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.specularTextureCoordinates(), 0);
    CORRADE_COMPARE(data.normalTexture(), 1);
    CORRADE_COMPARE(data.normalTextureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.normalTextureCoordinates(), 0);

    CORRADE_COMPARE(data.textureMatrix(), Matrix3{});
    CORRADE_COMPARE(data.textureCoordinates(), 0);
}

void MaterialDataTest::phongAccessTexturedSingleMatrixCoordinates() {
    PhongMaterialData data{{}, {
        {MaterialAttribute::AmbientTexture, 42u},
        {MaterialAttribute::DiffuseTexture, 33u},
        {MaterialAttribute::SpecularTexture, 17u},
        {MaterialAttribute::NormalTexture, 0u},
        {MaterialAttribute::TextureMatrix, Matrix3::translation({0.5f, 1.0f})},
        {MaterialAttribute::TextureCoordinates, 2u}
    }};

    CORRADE_VERIFY(data.hasTextureTransformation());
    CORRADE_VERIFY(data.hasTextureCoordinates());
    CORRADE_COMPARE(data.ambientTextureMatrix(), Matrix3::translation({0.5f, 1.0f}));
    CORRADE_COMPARE(data.ambientTextureCoordinates(), 2);
    CORRADE_COMPARE(data.diffuseTextureMatrix(), Matrix3::translation({0.5f, 1.0f}));
    CORRADE_COMPARE(data.diffuseTextureCoordinates(), 2);
    CORRADE_COMPARE(data.specularTextureMatrix(), Matrix3::translation({0.5f, 1.0f}));
    CORRADE_COMPARE(data.specularTextureCoordinates(), 2);
    CORRADE_COMPARE(data.normalTextureMatrix(), Matrix3::translation({0.5f, 1.0f}));
    CORRADE_COMPARE(data.normalTextureCoordinates(), 2);

    CORRADE_COMPARE(data.textureMatrix(), Matrix3::translation({0.5f, 1.0f}));
    CORRADE_COMPARE(data.textureCoordinates(), 2);
}

void MaterialDataTest::phongAccessInvalidTextures() {
    #ifdef CORRADE_NO_ASSERT
    CORRADE_SKIP("CORRADE_NO_ASSERT defined, can't test assertions");
    #endif

    PhongMaterialData data{{}, {}};

    std::ostringstream out;
    Error redirectError{&out};
    data.ambientTexture();
    data.ambientTextureMatrix();
    data.ambientTextureCoordinates();
    data.diffuseTexture();
    data.diffuseTextureMatrix();
    data.diffuseTextureCoordinates();
    data.specularTexture();
    data.specularTextureMatrix();
    data.specularTextureCoordinates();
    data.normalTexture();
    data.normalTextureMatrix();
    data.normalTextureCoordinates();
    CORRADE_COMPARE(out.str(),
        "Trade::MaterialData::attribute(): attribute AmbientTexture not found in layer 0\n"
        "Trade::PhongMaterialData::ambientTextureMatrix(): the material doesn't have an ambient texture\n"
        "Trade::PhongMaterialData::ambientTextureCoordinates(): the material doesn't have an ambient texture\n"
        "Trade::MaterialData::attribute(): attribute DiffuseTexture not found in layer 0\n"
        "Trade::PhongMaterialData::diffuseTextureMatrix(): the material doesn't have a diffuse texture\n"
        "Trade::PhongMaterialData::diffuseTextureCoordinates(): the material doesn't have a diffuse texture\n"
        "Trade::MaterialData::attribute(): attribute SpecularTexture not found in layer 0\n"
        "Trade::PhongMaterialData::specularTextureMatrix(): the material doesn't have a specular texture\n"
        "Trade::PhongMaterialData::specularTextureCoordinates(): the material doesn't have a specular texture\n"
        "Trade::MaterialData::attribute(): attribute NormalTexture not found in layer 0\n"
        "Trade::PhongMaterialData::normalTextureMatrix(): the material doesn't have a normal texture\n"
        "Trade::PhongMaterialData::normalTextureCoordinates(): the material doesn't have a normal texture\n");
}

void MaterialDataTest::debugAttribute() {
    std::ostringstream out;

    Debug{&out} << MaterialAttribute::DiffuseTextureCoordinates << MaterialAttribute::LayerName << MaterialAttribute(0xfefe) << MaterialAttribute{};
    CORRADE_COMPARE(out.str(), "Trade::MaterialAttribute::DiffuseTextureCoordinates Trade::MaterialAttribute::LayerName Trade::MaterialAttribute(0xfefe) Trade::MaterialAttribute(0x0)\n");
}

void MaterialDataTest::debugTextureSwizzle() {
    std::ostringstream out;

    /* The swizzle is encoded as a fourCC, so it just prints the numerical
       value as a char. Worst case this will print nothing or four garbage
       letters. Sorry in that case. */
    Debug{&out} << MaterialTextureSwizzle::BA << MaterialTextureSwizzle{};
    CORRADE_COMPARE(out.str(), "Trade::MaterialTextureSwizzle::BA Trade::MaterialTextureSwizzle::\n");
}

void MaterialDataTest::debugAttributeType() {
    std::ostringstream out;

    Debug{&out} << MaterialAttributeType::Matrix3x2 << MaterialAttributeType(0xfe);
    CORRADE_COMPARE(out.str(), "Trade::MaterialAttributeType::Matrix3x2 Trade::MaterialAttributeType(0xfe)\n");
}

void MaterialDataTest::debugType() {
    std::ostringstream out;

    Debug(&out) << MaterialType::Phong << MaterialType(0xbe);
    CORRADE_COMPARE(out.str(), "Trade::MaterialType::Phong Trade::MaterialType(0xbe)\n");
}

void MaterialDataTest::debugTypes() {
    std::ostringstream out;

    Debug{&out} << (MaterialType::Phong|MaterialType(0xe0)) << MaterialTypes{};
    CORRADE_COMPARE(out.str(), "Trade::MaterialType::Phong|Trade::MaterialType(0xe0) Trade::MaterialTypes{}\n");
}

#ifdef MAGNUM_BUILD_DEPRECATED
CORRADE_IGNORE_DEPRECATED_PUSH
void MaterialDataTest::debugFlag() {
    std::ostringstream out;

    Debug{&out} << MaterialData::Flag::DoubleSided << MaterialData::Flag(0xf0);
    CORRADE_COMPARE(out.str(), "Trade::MaterialData::Flag::DoubleSided Trade::MaterialData::Flag(0xf0)\n");
}

void MaterialDataTest::debugFlags() {
    std::ostringstream out;

    Debug{&out} << MaterialData::Flag::DoubleSided << MaterialData::Flags{};
    CORRADE_COMPARE(out.str(), "Trade::MaterialData::Flag::DoubleSided Trade::MaterialData::Flags{}\n");
}
CORRADE_IGNORE_DEPRECATED_POP
#endif

void MaterialDataTest::debugAlphaMode() {
    std::ostringstream out;

    Debug{&out} << MaterialAlphaMode::Opaque << MaterialAlphaMode(0xee);
    CORRADE_COMPARE(out.str(), "Trade::MaterialAlphaMode::Opaque Trade::MaterialAlphaMode(0xee)\n");
}

#ifdef MAGNUM_BUILD_DEPRECATED
CORRADE_IGNORE_DEPRECATED_PUSH
void MaterialDataTest::debugPhongFlag() {
    std::ostringstream out;

    Debug{&out} << PhongMaterialData::Flag::AmbientTexture << PhongMaterialData::Flag(0xf0);
    CORRADE_COMPARE(out.str(), "Trade::PhongMaterialData::Flag::AmbientTexture Trade::PhongMaterialData::Flag(0xf0)\n");
}

void MaterialDataTest::debugPhongFlags() {
    std::ostringstream out;

    Debug{&out} << (PhongMaterialData::Flag::DiffuseTexture|PhongMaterialData::Flag::SpecularTexture) << PhongMaterialData::Flags{};
    CORRADE_COMPARE(out.str(), "Trade::PhongMaterialData::Flag::DiffuseTexture|Trade::PhongMaterialData::Flag::SpecularTexture Trade::PhongMaterialData::Flags{}\n");
}
CORRADE_IGNORE_DEPRECATED_POP
#endif

}}}}

CORRADE_TEST_MAIN(Magnum::Trade::Test::MaterialDataTest)
