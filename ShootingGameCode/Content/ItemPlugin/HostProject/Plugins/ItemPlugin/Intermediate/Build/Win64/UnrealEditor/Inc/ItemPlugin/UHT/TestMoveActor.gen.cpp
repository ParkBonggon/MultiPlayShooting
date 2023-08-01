// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ItemPlugin/Public/TestMoveActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTestMoveActor() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ITEMPLUGIN_API UClass* Z_Construct_UClass_ATestMoveActor();
	ITEMPLUGIN_API UClass* Z_Construct_UClass_ATestMoveActor_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ItemPlugin();
// End Cross Module References
	void ATestMoveActor::StaticRegisterNativesATestMoveActor()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATestMoveActor);
	UClass* Z_Construct_UClass_ATestMoveActor_NoRegister()
	{
		return ATestMoveActor::StaticClass();
	}
	struct Z_Construct_UClass_ATestMoveActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATestMoveActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ItemPlugin,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestMoveActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "TestMoveActor.h" },
		{ "ModuleRelativePath", "Public/TestMoveActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATestMoveActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATestMoveActor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATestMoveActor_Statics::ClassParams = {
		&ATestMoveActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATestMoveActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATestMoveActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATestMoveActor()
	{
		if (!Z_Registration_Info_UClass_ATestMoveActor.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATestMoveActor.OuterSingleton, Z_Construct_UClass_ATestMoveActor_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATestMoveActor.OuterSingleton;
	}
	template<> ITEMPLUGIN_API UClass* StaticClass<ATestMoveActor>()
	{
		return ATestMoveActor::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATestMoveActor);
	ATestMoveActor::~ATestMoveActor() {}
	struct Z_CompiledInDeferFile_FID_Work_MultiPlayShooting_ShootingGameCode_Content_ItemPlugin_HostProject_Plugins_ItemPlugin_Source_ItemPlugin_Public_TestMoveActor_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_MultiPlayShooting_ShootingGameCode_Content_ItemPlugin_HostProject_Plugins_ItemPlugin_Source_ItemPlugin_Public_TestMoveActor_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATestMoveActor, ATestMoveActor::StaticClass, TEXT("ATestMoveActor"), &Z_Registration_Info_UClass_ATestMoveActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATestMoveActor), 2244999311U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_MultiPlayShooting_ShootingGameCode_Content_ItemPlugin_HostProject_Plugins_ItemPlugin_Source_ItemPlugin_Public_TestMoveActor_h_1020286813(TEXT("/Script/ItemPlugin"),
		Z_CompiledInDeferFile_FID_Work_MultiPlayShooting_ShootingGameCode_Content_ItemPlugin_HostProject_Plugins_ItemPlugin_Source_ItemPlugin_Public_TestMoveActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Work_MultiPlayShooting_ShootingGameCode_Content_ItemPlugin_HostProject_Plugins_ItemPlugin_Source_ItemPlugin_Public_TestMoveActor_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
