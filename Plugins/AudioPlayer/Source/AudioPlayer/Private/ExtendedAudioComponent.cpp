// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedAudioComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "AudioActor.h"



UExtendedAudioComponent::UExtendedAudioComponent(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_Loop(false)
	, m_CurrentVolume(0.f)
	, m_AutoDestroyDelay(10.f)
	, m_AdjustVolumeDelay(0.f)
{
	bWantsInitializeComponent = true;
}

void UExtendedAudioComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OnAudioFinished.AddDynamic(this, &UExtendedAudioComponent::PlayInLoop);
}

void UExtendedAudioComponent::Play(float StartTime)
{
	Super::Play(StartTime);
	AdjustVolume(m_AdjustVolumeDelay, m_CurrentVolume);

	GetWorld()->GetTimerManager().ClearTimer(m_TimerHandle);
}

void UExtendedAudioComponent::PlayInLoop()
{
	if (m_Loop)
	{
		Play();
	}
	else
	{
		if (OnExtendedAudioFinished.IsBound())
		{
			OnExtendedAudioFinished.Broadcast();
		}

		GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &UExtendedAudioComponent::DestroyItself, m_AutoDestroyDelay, false, m_AutoDestroyDelay);
	}
}

void UExtendedAudioComponent::SetLoop(bool bLoop)
{
	m_Loop = bLoop;
}

bool UExtendedAudioComponent::IsInPause()
{
	return m_InPause;
}

void UExtendedAudioComponent::SetVolume(float newVolume)
{
	m_CurrentVolume = newVolume;

	AdjustVolume(m_AdjustVolumeDelay, newVolume);
}

void UExtendedAudioComponent::Pause()
{
	m_InPause = !m_InPause;
	SetPaused(m_InPause);
}

void UExtendedAudioComponent::DestroyItself()
{
	UE_LOG(LogTemp, Warning, TEXT("Delete component"))
	AAudioActor* AudioActor = Cast<AAudioActor>(GetOwner());
	if (AudioActor)
	{
		AudioActor->DeleteComponent(this);
	}
}