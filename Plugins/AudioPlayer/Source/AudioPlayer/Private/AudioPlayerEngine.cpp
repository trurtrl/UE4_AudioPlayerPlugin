// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioPlayerEngine.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
//#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Engine/World.h"


UAudioPlayerEngine::UAudioPlayerEngine(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_VolumeInSettings(1.f)
	, m_VolumeMin(0.001f)
	, m_VolumeMax(1.0f)
	, m_FadeDuration(0.f)
	, m_FadeDeltaTime(0.1f)
	, m_FadeTimeElapsed(0.f)
	, m_FadeExecutionDelay(0.f)
	, m_ErrorTolerance(0.05f)
	, m_FadeIn(false)
{

}

int32 UAudioPlayerEngine::PlaySound(USoundBase* soundBase, bool bLooping)
{
	if (!m_AudioActor)
	{
		SpawnAudioActor();
	}
	return m_AudioActor->PlaySound(soundBase, bLooping);
	SetVolume(m_VolumeInSettings);
}

UExtendedAudioComponent* UAudioPlayerEngine::GetAudioComponent(int32 recordID) const
{
	if (m_AudioActor)
	{
		return m_AudioActor->GetAudioComponent(recordID);
	}
	return nullptr;
}

void UAudioPlayerEngine::SpawnAudioActor()
{
	FActorSpawnParameters SpawnInfo;
	m_AudioActor = GetWorld()->SpawnActor<AAudioActor>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	AudioVolumeChanged(m_VolumeInSettings);
}

void UAudioPlayerEngine::Repeat(int32 recordID)
{
	if (m_AudioActor)
	{
		m_AudioActor->Repeat(recordID);
	}
}

void UAudioPlayerEngine::Stop(int32 recordID)
{
	if (m_AudioActor)
	{
		m_AudioActor->Stop(recordID);
	}
}

void UAudioPlayerEngine::Pause(int32 recordID)
{
	if (m_AudioActor)
	{
		m_AudioActor->Pause(recordID);
	}
}


/**
 *		Volume
 */

bool UAudioPlayerEngine::IsAudioMuted() const
{
	return m_AudioMuted;
}

void UAudioPlayerEngine::AudioMutedChanged(bool bMuted)
{
	m_AudioMuted = bMuted;
	float NewVolume = m_AudioMuted ? m_VolumeMin : m_VolumeInSettings;
	SetVolume(NewVolume);
}

void UAudioPlayerEngine::AudioVolumeChanged(float newVolume)
{
	if (m_AudioMuted)
	{
		newVolume = m_VolumeMin;
	}

	SetVolume(newVolume);
}

float UAudioPlayerEngine::GetVolumeInSettings() const
{
	return m_VolumeInSettings;
}

void UAudioPlayerEngine::SetVolume(float newVolume)
{
	if (m_AudioActor)
	{
		m_AudioActor->SetVolume(newVolume);
	}
}

/**
 *		Fade In\Out
 */

void UAudioPlayerEngine::FadeIn(bool bFadeIn, float FadeDuration)
{
	m_FadeIn = bFadeIn;

	m_FadeDuration = FadeDuration;
	m_FadeTimeElapsed = 0;

	if (m_AudioActor)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_FadeTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(m_FadeTimerHandle, this, &UAudioPlayerEngine::FadeVolume, m_FadeDeltaTime, true, m_FadeExecutionDelay);
	}
}

void UAudioPlayerEngine::FadeVolume()
{
	if (m_FadeTimeElapsed < m_FadeDuration || FMath::IsNearlyEqual(m_FadeTimeElapsed, m_FadeDuration, m_ErrorTolerance))
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

void UAudioPlayerEngine::SetVolumeMultiplier(float newMuptiplier)
{
	if (m_AudioActor)
	{
		m_AudioActor->SetVolumeMultiplier(newMuptiplier);
	}
}