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

}

int32 UAudioManager::PlaySound(USoundBase* soundBase, bool bLooping)
{
	if (!m_AudioActor)
	{
		SpawnAudioActor();
	}
	SetVolume(m_VolumeInSettings);
	return m_AudioActor->PlaySound(soundBase, bLooping);
}

UExtendedAudioComponent* UAudioManager::GetAudioComponent(int32 id) const
{
	if (m_AudioActor)
	{
		return m_AudioActor->GetAudioComponent(id);
	}
	return nullptr;
}

void UAudioManager::SpawnAudioActor()
{
	FActorSpawnParameters SpawnInfo;
	m_AudioActor = GetWorld()->SpawnActor<AAudioActor>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	AudioVolumeChanged(m_VolumeInSettings);
}

void UAudioManager::Repeat(int32 index)
{
	if (m_AudioActor)
	{
		m_AudioActor->Repeat(index);
	}
}

void UAudioManager::Stop(int32 index)
{
	if (m_AudioActor)
	{
		m_AudioActor->Stop(index);
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
	if (m_AudioActor)
	{
		m_AudioActor->SetVolume(newVolume);
	}
}



