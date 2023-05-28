// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestPlug.h"
#include "Modules/ModuleManager.h"


IMPLEMENT_GAME_MODULE( FTestPlugModule, TestPlug);


void FTestPlugModule::StartupModule()
{
	IModuleInterface::StartupModule();
	const auto ShaderDir = FPaths::Combine(FPaths::ProjectDir(),TEXT("Shaders/Private"));
	AddShaderSourceDirectoryMapping("/Shaders",ShaderDir);
}

void FTestPlugModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}
