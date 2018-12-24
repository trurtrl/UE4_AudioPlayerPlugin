// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AudioManager.h"


class FAudioManagerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	UAudioManager* GetAudioManager() const;

private:

	UPROPERTY(meta = (DisplayName = "Audio Manager"))
	UAudioManager* m_AudioManager;
};
