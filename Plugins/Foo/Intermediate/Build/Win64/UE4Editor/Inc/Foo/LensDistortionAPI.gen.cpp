// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Foo/Classes/LensDistortionAPI.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLensDistortionAPI() {}
// Cross Module References
	FOO_API UScriptStruct* Z_Construct_UScriptStruct_FFooCameraModel();
	UPackage* Z_Construct_UPackage__Script_Foo();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
// End Cross Module References
class UScriptStruct* FFooCameraModel::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FOO_API uint32 Get_Z_Construct_UScriptStruct_FFooCameraModel_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFooCameraModel, Z_Construct_UPackage__Script_Foo(), TEXT("FooCameraModel"), sizeof(FFooCameraModel), Get_Z_Construct_UScriptStruct_FFooCameraModel_Hash());
	}
	return Singleton;
}
template<> FOO_API UScriptStruct* StaticStruct<FFooCameraModel>()
{
	return FFooCameraModel::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFooCameraModel(FFooCameraModel::StaticStruct, TEXT("/Script/Foo"), TEXT("FooCameraModel"), false, nullptr, nullptr);
static struct FScriptStruct_Foo_StaticRegisterNativesFFooCameraModel
{
	FScriptStruct_Foo_StaticRegisterNativesFFooCameraModel()
	{
		UScriptStruct::DeferCppStructOps<FFooCameraModel>(FName(TEXT("FooCameraModel")));
	}
} ScriptStruct_Foo_StaticRegisterNativesFFooCameraModel;
	struct Z_Construct_UScriptStruct_FFooCameraModel_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_K1_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_K1;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_K2_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_K2;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_K3_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_K3;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_P1_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_P1;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_P2_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_P2;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_F_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_F;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_C_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_C;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFooCameraModel_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Mathematic camera model for lens distortion/undistortion.\n *\n * Camera matrix =\n *  | F.X  0  C.x |\n *  |  0  F.Y C.Y |\n *  |  0   0   1  |\n */" },
		{ "ModuleRelativePath", "Classes/LensDistortionAPI.h" },
		{ "ToolTip", "Mathematic camera model for lens distortion/undistortion.\n\nCamera matrix =\n| F.X  0  C.x |\n|  0  F.Y C.Y |\n|  0   0   1  |" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFooCameraModel>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K1_MetaData[] = {
		{ "Category", "Lens Distortion|Camera Model" },
		{ "Comment", "/** Radial parameter #1. */" },
		{ "ModuleRelativePath", "Classes/LensDistortionAPI.h" },
		{ "ToolTip", "Radial parameter #1." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K1 = { "K1", nullptr, (EPropertyFlags)0x0010000200000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFooCameraModel, K1), METADATA_PARAMS(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K1_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K1_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K2_MetaData[] = {
		{ "Category", "Lens Distortion|Camera Model" },
		{ "Comment", "/** Radial parameter #2. */" },
		{ "ModuleRelativePath", "Classes/LensDistortionAPI.h" },
		{ "ToolTip", "Radial parameter #2." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K2 = { "K2", nullptr, (EPropertyFlags)0x0010000200000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFooCameraModel, K2), METADATA_PARAMS(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K2_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K2_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K3_MetaData[] = {
		{ "Category", "Lens Distortion|Camera Model" },
		{ "Comment", "/** Radial parameter #3. */" },
		{ "ModuleRelativePath", "Classes/LensDistortionAPI.h" },
		{ "ToolTip", "Radial parameter #3." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K3 = { "K3", nullptr, (EPropertyFlags)0x0010000200000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFooCameraModel, K3), METADATA_PARAMS(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K3_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K3_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P1_MetaData[] = {
		{ "Category", "Lens Distortion|Camera Model" },
		{ "Comment", "/** Tangential parameter #1. */" },
		{ "ModuleRelativePath", "Classes/LensDistortionAPI.h" },
		{ "ToolTip", "Tangential parameter #1." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P1 = { "P1", nullptr, (EPropertyFlags)0x0010000200000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFooCameraModel, P1), METADATA_PARAMS(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P1_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P1_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P2_MetaData[] = {
		{ "Category", "Lens Distortion|Camera Model" },
		{ "Comment", "/** Tangential parameter #2. */" },
		{ "ModuleRelativePath", "Classes/LensDistortionAPI.h" },
		{ "ToolTip", "Tangential parameter #2." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P2 = { "P2", nullptr, (EPropertyFlags)0x0010000200000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFooCameraModel, P2), METADATA_PARAMS(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P2_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P2_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_F_MetaData[] = {
		{ "Category", "Lens Distortion|Camera Model" },
		{ "Comment", "/** Camera matrix's Fx and Fy. */" },
		{ "ModuleRelativePath", "Classes/LensDistortionAPI.h" },
		{ "ToolTip", "Camera matrix's Fx and Fy." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_F = { "F", nullptr, (EPropertyFlags)0x0010000200000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFooCameraModel, F), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_F_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_F_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_C_MetaData[] = {
		{ "Category", "Lens Distortion|Camera Model" },
		{ "Comment", "/** Camera matrix's Cx and Cy. */" },
		{ "ModuleRelativePath", "Classes/LensDistortionAPI.h" },
		{ "ToolTip", "Camera matrix's Cx and Cy." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_C = { "C", nullptr, (EPropertyFlags)0x0010000200000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFooCameraModel, C), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_C_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_C_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFooCameraModel_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K1,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K2,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_K3,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P1,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_P2,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_F,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFooCameraModel_Statics::NewProp_C,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFooCameraModel_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Foo,
		nullptr,
		&NewStructOps,
		"FooCameraModel",
		sizeof(FFooCameraModel),
		alignof(FFooCameraModel),
		Z_Construct_UScriptStruct_FFooCameraModel_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFooCameraModel_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFooCameraModel_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFooCameraModel_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFooCameraModel()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFooCameraModel_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_Foo();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FooCameraModel"), sizeof(FFooCameraModel), Get_Z_Construct_UScriptStruct_FFooCameraModel_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFooCameraModel_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFooCameraModel_Hash() { return 1471602108U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
