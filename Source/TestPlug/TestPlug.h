// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class TESTPLUG_API FTestPlugModule : public IModuleInterface
{
public:
	static inline  FTestPlugModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FTestPlugModule>("TestPlug");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("TestPlug");
	}

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};