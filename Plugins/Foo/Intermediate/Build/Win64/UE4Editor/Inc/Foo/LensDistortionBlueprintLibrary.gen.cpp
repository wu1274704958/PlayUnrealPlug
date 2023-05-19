// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Foo/Classes/LensDistortionBlueprintLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLensDistortionBlueprintLibrary() {}
// Cross Module References
	FOO_API UClass* Z_Construct_UClass_UFooBlueprintLibrary_NoRegister();
	FOO_API UClass* Z_Construct_UClass_UFooBlueprintLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_Foo();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	FOO_API UScriptStruct* Z_Construct_UScriptStruct_FFooCameraModel();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UFooBlueprintLibrary::execNotEqual_CompareLensDistortionModels)
	{
		P_GET_STRUCT_REF(FFooCameraModel,Z_Param_Out_A);
		P_GET_STRUCT_REF(FFooCameraModel,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UFooBlueprintLibrary::NotEqual_CompareLensDistortionModels(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFooBlueprintLibrary::execEqualEqual_CompareLensDistortionModels)
	{
		P_GET_STRUCT_REF(FFooCameraModel,Z_Param_Out_A);
		P_GET_STRUCT_REF(FFooCameraModel,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UFooBlueprintLibrary::EqualEqual_CompareLensDistortionModels(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFooBlueprintLibrary::execDrawUVDisplacementToRenderTarget)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_STRUCT_REF(FFooCameraModel,Z_Param_Out_CameraModel);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DistortedHorizontalFOV);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DistortedAspectRatio);
		P_GET_PROPERTY(FFloatProperty,Z_Param_UndistortOverscanFactor);
		P_GET_OBJECT(UTextureRenderTarget2D,Z_Param_OutputRenderTarget);
		P_GET_PROPERTY(FFloatProperty,Z_Param_OutputMultiply);
		P_GET_PROPERTY(FFloatProperty,Z_Param_OutputAdd);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFooBlueprintLibrary::DrawUVDisplacementToRenderTarget(Z_Param_WorldContextObject,Z_Param_Out_CameraModel,Z_Param_DistortedHorizontalFOV,Z_Param_DistortedAspectRatio,Z_Param_UndistortOverscanFactor,Z_Param_OutputRenderTarget,Z_Param_OutputMultiply,Z_Param_OutputAdd);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFooBlueprintLibrary::execGetUndistortOverscanFactor)
	{
		P_GET_STRUCT_REF(FFooCameraModel,Z_Param_Out_CameraModel);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DistortedHorizontalFOV);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DistortedAspectRatio);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_UndistortOverscanFactor);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFooBlueprintLibrary::GetUndistortOverscanFactor(Z_Param_Out_CameraModel,Z_Param_DistortedHorizontalFOV,Z_Param_DistortedAspectRatio,Z_Param_Out_UndistortOverscanFactor);
		P_NATIVE_END;
	}
	void UFooBlueprintLibrary::StaticRegisterNativesUFooBlueprintLibrary()
	{
		UClass* Class = UFooBlueprintLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DrawUVDisplacementToRenderTarget", &UFooBlueprintLibrary::execDrawUVDisplacementToRenderTarget },
			{ "EqualEqual_CompareLensDistortionModels", &UFooBlueprintLibrary::execEqualEqual_CompareLensDistortionModels },
			{ "GetUndistortOverscanFactor", &UFooBlueprintLibrary::execGetUndistortOverscanFactor },
			{ "NotEqual_CompareLensDistortionModels", &UFooBlueprintLibrary::execNotEqual_CompareLensDistortionModels },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics
	{
		struct FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms
		{
			const UObject* WorldContextObject;
			FFooCameraModel CameraModel;
			float DistortedHorizontalFOV;
			float DistortedAspectRatio;
			float UndistortOverscanFactor;
			UTextureRenderTarget2D* OutputRenderTarget;
			float OutputMultiply;
			float OutputAdd;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraModel_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CameraModel;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DistortedHorizontalFOV;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DistortedAspectRatio;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_UndistortOverscanFactor;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OutputRenderTarget;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_OutputMultiply;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_OutputAdd;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_WorldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_WorldContextObject_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_WorldContextObject_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_CameraModel_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_CameraModel = { "CameraModel", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms, CameraModel), Z_Construct_UScriptStruct_FFooCameraModel, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_CameraModel_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_CameraModel_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_DistortedHorizontalFOV = { "DistortedHorizontalFOV", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms, DistortedHorizontalFOV), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_DistortedAspectRatio = { "DistortedAspectRatio", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms, DistortedAspectRatio), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_UndistortOverscanFactor = { "UndistortOverscanFactor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms, UndistortOverscanFactor), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_OutputRenderTarget = { "OutputRenderTarget", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms, OutputRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_OutputMultiply = { "OutputMultiply", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms, OutputMultiply), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_OutputAdd = { "OutputAdd", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms, OutputAdd), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_CameraModel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_DistortedHorizontalFOV,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_DistortedAspectRatio,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_UndistortOverscanFactor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_OutputRenderTarget,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_OutputMultiply,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::NewProp_OutputAdd,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::Function_MetaDataParams[] = {
		{ "Category", "Foo | Lens Distortion" },
		{ "Comment", "/** Draws UV displacement map within the output render target.\n\x09 * - Red & green channels hold the distortion displacement;\n\x09 * - Blue & alpha channels hold the undistortion displacement.\n\x09 * @param DistortedHorizontalFOV The desired horizontal FOV in the distorted render.\n\x09 * @param DistortedAspectRatio The desired aspect ratio of the distorted render.\n\x09 * @param UndistortOverscanFactor The factor of the overscan for the undistorted render.\n\x09 * @param OutputRenderTarget The render target to draw to. Don't necessarily need to have same resolution or aspect ratio as distorted render.\n\x09 * @param OutputMultiply The multiplication factor applied on the displacement.\n\x09 * @param OutputAdd Value added to the multiplied displacement before storing into the output render target.\n\x09 */" },
		{ "CPP_Default_OutputAdd", "0.500000" },
		{ "CPP_Default_OutputMultiply", "0.500000" },
		{ "ModuleRelativePath", "Classes/LensDistortionBlueprintLibrary.h" },
		{ "ToolTip", "Draws UV displacement map within the output render target.\n- Red & green channels hold the distortion displacement;\n- Blue & alpha channels hold the undistortion displacement.\n@param DistortedHorizontalFOV The desired horizontal FOV in the distorted render.\n@param DistortedAspectRatio The desired aspect ratio of the distorted render.\n@param UndistortOverscanFactor The factor of the overscan for the undistorted render.\n@param OutputRenderTarget The render target to draw to. Don't necessarily need to have same resolution or aspect ratio as distorted render.\n@param OutputMultiply The multiplication factor applied on the displacement.\n@param OutputAdd Value added to the multiplied displacement before storing into the output render target." },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFooBlueprintLibrary, nullptr, "DrawUVDisplacementToRenderTarget", nullptr, nullptr, sizeof(FooBlueprintLibrary_eventDrawUVDisplacementToRenderTarget_Parms), Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics
	{
		struct FooBlueprintLibrary_eventEqualEqual_CompareLensDistortionModels_Parms
		{
			FFooCameraModel A;
			FFooCameraModel B;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventEqualEqual_CompareLensDistortionModels_Parms, A), Z_Construct_UScriptStruct_FFooCameraModel, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventEqualEqual_CompareLensDistortionModels_Parms, B), Z_Construct_UScriptStruct_FFooCameraModel, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_B_MetaData)) };
	void Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((FooBlueprintLibrary_eventEqualEqual_CompareLensDistortionModels_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FooBlueprintLibrary_eventEqualEqual_CompareLensDistortionModels_Parms), &Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::Function_MetaDataParams[] = {
		{ "Category", "Foo | Lens Distortion" },
		{ "Comment", "/* Returns true if A is equal to B (A == B) */" },
		{ "CompactNodeTitle", "==" },
		{ "DisplayName", "Equal (LensDistortionCameraModel)" },
		{ "Keywords", "== equal" },
		{ "ModuleRelativePath", "Classes/LensDistortionBlueprintLibrary.h" },
		{ "ToolTip", "Returns true if A is equal to B (A == B)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFooBlueprintLibrary, nullptr, "EqualEqual_CompareLensDistortionModels", nullptr, nullptr, sizeof(FooBlueprintLibrary_eventEqualEqual_CompareLensDistortionModels_Parms), Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics
	{
		struct FooBlueprintLibrary_eventGetUndistortOverscanFactor_Parms
		{
			FFooCameraModel CameraModel;
			float DistortedHorizontalFOV;
			float DistortedAspectRatio;
			float UndistortOverscanFactor;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraModel_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CameraModel;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DistortedHorizontalFOV;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DistortedAspectRatio;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_UndistortOverscanFactor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_CameraModel_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_CameraModel = { "CameraModel", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventGetUndistortOverscanFactor_Parms, CameraModel), Z_Construct_UScriptStruct_FFooCameraModel, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_CameraModel_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_CameraModel_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_DistortedHorizontalFOV = { "DistortedHorizontalFOV", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventGetUndistortOverscanFactor_Parms, DistortedHorizontalFOV), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_DistortedAspectRatio = { "DistortedAspectRatio", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventGetUndistortOverscanFactor_Parms, DistortedAspectRatio), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_UndistortOverscanFactor = { "UndistortOverscanFactor", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventGetUndistortOverscanFactor_Parms, UndistortOverscanFactor), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_CameraModel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_DistortedHorizontalFOV,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_DistortedAspectRatio,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::NewProp_UndistortOverscanFactor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::Function_MetaDataParams[] = {
		{ "Category", "Foo | Lens Distortion" },
		{ "Comment", "/** Returns the overscan factor required for the undistort rendering to avoid unrendered distorted pixels. */" },
		{ "ModuleRelativePath", "Classes/LensDistortionBlueprintLibrary.h" },
		{ "ToolTip", "Returns the overscan factor required for the undistort rendering to avoid unrendered distorted pixels." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFooBlueprintLibrary, nullptr, "GetUndistortOverscanFactor", nullptr, nullptr, sizeof(FooBlueprintLibrary_eventGetUndistortOverscanFactor_Parms), Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics
	{
		struct FooBlueprintLibrary_eventNotEqual_CompareLensDistortionModels_Parms
		{
			FFooCameraModel A;
			FFooCameraModel B;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventNotEqual_CompareLensDistortionModels_Parms, A), Z_Construct_UScriptStruct_FFooCameraModel, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FooBlueprintLibrary_eventNotEqual_CompareLensDistortionModels_Parms, B), Z_Construct_UScriptStruct_FFooCameraModel, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_B_MetaData)) };
	void Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((FooBlueprintLibrary_eventNotEqual_CompareLensDistortionModels_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FooBlueprintLibrary_eventNotEqual_CompareLensDistortionModels_Parms), &Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::Function_MetaDataParams[] = {
		{ "Category", "Foo | Lens Distortion" },
		{ "Comment", "/* Returns true if A is not equal to B (A != B) */" },
		{ "CompactNodeTitle", "!=" },
		{ "DisplayName", "NotEqual (LensDistortionCameraModel)" },
		{ "Keywords", "!= not equal" },
		{ "ModuleRelativePath", "Classes/LensDistortionBlueprintLibrary.h" },
		{ "ToolTip", "Returns true if A is not equal to B (A != B)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFooBlueprintLibrary, nullptr, "NotEqual_CompareLensDistortionModels", nullptr, nullptr, sizeof(FooBlueprintLibrary_eventNotEqual_CompareLensDistortionModels_Parms), Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UFooBlueprintLibrary_NoRegister()
	{
		return UFooBlueprintLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UFooBlueprintLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFooBlueprintLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_Foo,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFooBlueprintLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFooBlueprintLibrary_DrawUVDisplacementToRenderTarget, "DrawUVDisplacementToRenderTarget" }, // 3618024597
		{ &Z_Construct_UFunction_UFooBlueprintLibrary_EqualEqual_CompareLensDistortionModels, "EqualEqual_CompareLensDistortionModels" }, // 859929474
		{ &Z_Construct_UFunction_UFooBlueprintLibrary_GetUndistortOverscanFactor, "GetUndistortOverscanFactor" }, // 1516373053
		{ &Z_Construct_UFunction_UFooBlueprintLibrary_NotEqual_CompareLensDistortionModels, "NotEqual_CompareLensDistortionModels" }, // 974605531
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFooBlueprintLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "LensDistortionBlueprintLibrary.h" },
		{ "ModuleRelativePath", "Classes/LensDistortionBlueprintLibrary.h" },
		{ "ScriptName", "LensDistortionLibrary" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFooBlueprintLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFooBlueprintLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFooBlueprintLibrary_Statics::ClassParams = {
		&UFooBlueprintLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x000800A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFooBlueprintLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFooBlueprintLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFooBlueprintLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFooBlueprintLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFooBlueprintLibrary, 2816995606);
	template<> FOO_API UClass* StaticClass<UFooBlueprintLibrary>()
	{
		return UFooBlueprintLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFooBlueprintLibrary(Z_Construct_UClass_UFooBlueprintLibrary, &UFooBlueprintLibrary::StaticClass, TEXT("/Script/Foo"), TEXT("UFooBlueprintLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFooBlueprintLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
