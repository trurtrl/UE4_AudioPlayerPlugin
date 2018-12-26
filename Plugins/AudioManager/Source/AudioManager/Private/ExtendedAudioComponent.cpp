// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedAudioComponent.h"


UExtendedAudioComponent::UExtendedAudioComponent(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_Loop(false)
{
	bWantsInitializeComponent = true;
}

void UExtendedAudioComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OnAudioFinished.AddDynamic(this, &UExtendedAudioComponent::PlayInLoop);
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
