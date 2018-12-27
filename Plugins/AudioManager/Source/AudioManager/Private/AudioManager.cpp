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
	, m_FadeDeltaTime(0.1f)
	, m_FadeTimeElapsed(0.f)
	, m_FadeIn(false)
{

}

int32 UAudioManager::PlaySound(USoundBase* soundBase, bool bLooping)
{
	if (!m_AudioActor)
	{
		SpawnAudioActor();
	}
	return m_AudioActor->PlaySound(soundBase, bLooping);
	SetVolume(m_VolumeInSettings);
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
		newVolume = 0.001f;
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
	FadeExec(true, FadeInDuration);
}

void UAudioManager::FadeOut(float FadeOutDuration)
{
	FadeExec(false, FadeOutDuration);
}

void UAudioManager::FadeExec(bool bFadeIn, float FadeDuration)
{
	m_FadeIn = bFadeIn;

	m_FadeDuration = FadeDuration;
	m_FadeTimeElapsed = 0;

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
		SetVolumeMultiplier(NewVolume);
		m_FadeTimeElapsed += m_FadeDeltaTime;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(m_FadeTimerHandle);
	}
}

void UAudioManager::SetVolumeMultiplier(float newMuptiplier)
{
	if (m_AudioActor)
	{
		m_AudioActor->SetVolumeMultiplier(newMuptiplier);
	}
}