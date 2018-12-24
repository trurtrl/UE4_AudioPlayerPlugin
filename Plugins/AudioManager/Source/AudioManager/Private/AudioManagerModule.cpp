// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AudioManagerModule.h"



#define LOCTEXT_NAMESPACE "FAudioManagerModule"

void FAudioManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module	

	m_AudioManager = NewObject<UAudioManager>();
}

void FAudioManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

UAudioManager* FAudioManagerModule::GetAudioManager() const
{
	return m_AudioManager;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAudioManagerModule, AudioManager)