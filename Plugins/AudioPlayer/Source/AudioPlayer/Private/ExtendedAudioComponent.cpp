// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedAudioComponent.h"



UExtendedAudioComponent::UExtendedAudioComponent(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_Loop(false)
	, m_CurrentVolume(0.f)
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
	AdjustVolume(0.f, m_CurrentVolume);
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
	//	0.f - Adjust volume immediately
	AdjustVolume(0.f, newVolume);
}

void UExtendedAudioComponent::Pause()
{
	m_InPause = !m_InPause;
	SetPaused(m_InPause);
}
