// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FFooCameraModel;
class UObject;
class UTextureRenderTarget2D;
#ifdef FOO_LensDistortionBlueprintLibrary_generated_h
#error "LensDistortionBlueprintLibrary.generated.h already included, missing '#pragma once' in LensDistortionBlueprintLibrary.h"
#endif
#define FOO_LensDistortionBlueprintLibrary_generated_h

#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_SPARSE_DATA
#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execNotEqual_CompareLensDistortionModels); \
	DECLARE_FUNCTION(execEqualEqual_CompareLensDistortionModels); \
	DECLARE_FUNCTION(execDrawUVDisplacementToRenderTarget); \
	DECLARE_FUNCTION(execGetUndistortOverscanFactor);


#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execNotEqual_CompareLensDistortionModels); \
	DECLARE_FUNCTION(execEqualEqual_CompareLensDistortionModels); \
	DECLARE_FUNCTION(execDrawUVDisplacementToRenderTarget); \
	DECLARE_FUNCTION(execGetUndistortOverscanFactor);


#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFooBlueprintLibrary(); \
	friend struct Z_Construct_UClass_UFooBlueprintLibrary_Statics; \
public: \
	DECLARE_CLASS(UFooBlueprintLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Foo"), FOO_API) \
	DECLARE_SERIALIZER(UFooBlueprintLibrary)


#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUFooBlueprintLibrary(); \
	friend struct Z_Construct_UClass_UFooBlueprintLibrary_Statics; \
public: \
	DECLARE_CLASS(UFooBlueprintLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Foo"), FOO_API) \
	DECLARE_SERIALIZER(UFooBlueprintLibrary)


#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	FOO_API UFooBlueprintLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFooBlueprintLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(FOO_API, UFooBlueprintLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFooBlueprintLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	FOO_API UFooBlueprintLibrary(UFooBlueprintLibrary&&); \
	FOO_API UFooBlueprintLibrary(const UFooBlueprintLibrary&); \
public:


#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	FOO_API UFooBlueprintLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	FOO_API UFooBlueprintLibrary(UFooBlueprintLibrary&&); \
	FOO_API UFooBlueprintLibrary(const UFooBlueprintLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(FOO_API, UFooBlueprintLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFooBlueprintLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFooBlueprintLibrary)


#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_PRIVATE_PROPERTY_OFFSET
#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_12_PROLOG
#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_PRIVATE_PROPERTY_OFFSET \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_SPARSE_DATA \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_RPC_WRAPPERS \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_INCLASS \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_PRIVATE_PROPERTY_OFFSET \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_SPARSE_DATA \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_INCLASS_NO_PURE_DECLS \
	TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h_15_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class FooBlueprintLibrary."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FOO_API UClass* StaticClass<class UFooBlueprintLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TestPlug_Plugins_Foo_Source_Foo_Classes_LensDistortionBlueprintLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
