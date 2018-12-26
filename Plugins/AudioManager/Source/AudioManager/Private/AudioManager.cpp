// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioManager.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
//#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Engine/World.h"


UAudioManager::UAudioManager(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_VolumeInSettings(1.f)
	, m_VolumeMin(0.001f)
	, m_VolumeMax(1.0f)
	, m_FadeDuration(0.f)
	, m_FadeDeltaTime(0.2f)
	, m_FadeTimeElapsed(0.f)
	, m_InFading(false)
	, m_FadeIn(false)
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

UExtendedAudioComponent* UAudioManager::GetAudioComponent(int32 recordID) const
{
	if (m_AudioActor)
	{
		return m_AudioActor->GetAudioComponent(recordID);
	}
	return nullptr;
}

void UAudioManager::SpawnAudioActor()
{
	FActorSpawnParameters SpawnInfo;
	m_AudioActor = GetWorld()->SpawnActor<AAudioActor>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	AudioVolumeChanged(m_VolumeInSettings);
}

void UAudioManager::Repeat(int32 recordID)
{
	if (m_AudioActor)
	{
		m_AudioActor->Repeat(recordID);
	}
}

void UAudioManager::Stop(int32 recordID)
{
	if (m_AudioActor)
	{
		m_AudioActor->Stop(recordID);
	}
}

void UAudioManager::Pause(int32 recordID)
{
	if (m_AudioActor)
	{
		m_AudioActor->Pause(recordID);
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

	if (!m_InFading)
	{
		m_VolumeInSettings = newVolume;
	}

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

/**
 *		Fade In\Out
 */

void UAudioManager::FadeIn(float FadeInDuration)
{
	m_FadeIn = true;
	m_InFading = true;
	m_FadeDuration = FadeInDuration;

	if (m_AudioActor)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_FadeTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(m_FadeTimerHandle, this, &UAudioManager::FadeVolume, m_FadeDeltaTime, true, 0.f);
	}
}

void UAudioManager::FadeOut(float FadeOutDuration)
{
	m_FadeIn = false;
	m_InFading = true;
	m_FadeDuration = FadeOutDuration;

	if (m_AudioActor)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_FadeTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(m_FadeTimerHandle, this, &UAudioManager::FadeVolume, m_FadeDeltaTime, true, 0.f);
	}
}

void UAudioManager::FadeVolume()
{
	if (m_FadeTimeElapsed < m_FadeDuration || FMath::IsNearlyEqual(m_FadeTimeElapsed, m_FadeDuration, 0.05f))
	{
		float FadeDelta = m_FadeIn ? m_FadeTimeElapsed : (m_FadeDuration - m_FadeTimeElapsed);
		float NewVolume = m_VolumeInSettings * (FadeDelta / m_FadeDuration);
		AudioVolumeChanged(NewVolume);
		m_FadeTimeElapsed += m_FadeDeltaTime;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(m_FadeTimerHandle);
		m_InFading = false;
	}
}