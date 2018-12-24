// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioManager.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
//#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Engine/World.h"


UAudioManager::UAudioManager(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_VolumeInSettings(0.7f)
	, m_VolumeMin(0.001f)
	, m_VolumeMax(1.0f)
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UAudioManager::SpawnAudioActor);
}

int32 UAudioManager::PlaySound(USoundBase* soundBase, bool bLooping)
{
	return m_AudioActor->PlaySound(soundBase, bLooping);
}

UExtendedAudioComponent* UAudioManager::GetAudioComponent(int32 id) const
{
	return m_AudioActor->GetAudioComponent(id);
}

void UAudioManager::SpawnAudioActor(UWorld* newWorld)
{
	FActorSpawnParameters SpawnInfo;
	if (newWorld)
	{
		m_AudioActor = newWorld->SpawnActor<AAudioActor>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		AudioVolumeChanged(m_VolumeInSettings);
	}
}


/**
 *		Volume
 */

bool UAudioManager::IsAudioMuted() const
{
	return m_AudioMuted;
}

void UAudioManager::AudioMutedChanged(bool bMuted)
{
	m_AudioMuted = bMuted;
	float NewVolume = m_AudioMuted ? m_VolumeMin : m_VolumeInSettings;
	SetVolume(NewVolume);
}

void UAudioManager::AudioVolumeChanged(float newVolume)
{
	if (m_AudioMuted)
	{
		SetVolume(0.001f);
		return;
	}

	//if (!bInFading)
	//{
	//	m_VolumeInSettings = newVolume;
	//}

	SetVolume(newVolume);
}

float UAudioManager::GetVolumeInSettings() const
{
	return m_VolumeInSettings;
}

void UAudioManager::SetVolume(float newVolume)
{
	m_AudioActor->SetVolume(newVolume);
}



