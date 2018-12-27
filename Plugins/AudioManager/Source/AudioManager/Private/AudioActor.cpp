// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioActor.h"


// Sets default values
AAudioActor::AAudioActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

//// Called when the game starts or when spawned
//void AAudioActor::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void AAudioActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

int32 AAudioActor::PlaySound(USoundBase* soundBase, bool bLooping)
{
	int32 ComponentNumber = GetFreeComponentNumber();

	m_ComponentsArray[ComponentNumber]->SetLoop(bLooping);
	m_ComponentsArray[ComponentNumber]->SetSound(soundBase);
	m_ComponentsArray[ComponentNumber]->Play();

	return ComponentNumber;
}

int32 AAudioActor::GetFreeComponentNumber()
{
	int32 Num = -1;

	for (int32 i = 0; i < m_ComponentsArray.Num(); ++i)
	{
		if (!m_ComponentsArray[i]->IsPlaying())
		{
			Num = i;
			break;
		}
	}

	//	If there is NO free component create new one
	if (Num == -1)
	{
		UExtendedAudioComponent* ExtendedAudioComponent = NewObject<UExtendedAudioComponent>(this);
		if (ExtendedAudioComponent)
		{
			ExtendedAudioComponent->RegisterComponent();
			ExtendedAudioComponent->SetVolume(m_CurrentVolume);

			if (GetRootComponent())
			{
				ExtendedAudioComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
			}
			else
			{
				RootComponent = ExtendedAudioComponent;
			}

			m_ComponentsArray.Add(ExtendedAudioComponent);
			Num = m_ComponentsArray.Num() - 1;
		}
	}

	return Num;
}

UExtendedAudioComponent* AAudioActor::GetAudioComponent(int32 recordID) const
{
	UExtendedAudioComponent* AudioComponent = nullptr;

	if (m_ComponentsArray.IsValidIndex(recordID))
	{
		AudioComponent = m_ComponentsArray[recordID];
	}
	return AudioComponent;
}

void AAudioActor::SetVolume(float newVolume)
{
	m_CurrentVolume = newVolume;

	for (UExtendedAudioComponent* AudioComponent : m_ComponentsArray)
	{
		AudioComponent->SetVolume(newVolume);
	}
}

void AAudioActor::Repeat(int32 recordID)
{
	if (m_ComponentsArray.IsValidIndex(recordID))
	{
		m_ComponentsArray[recordID]->Stop();
		m_ComponentsArray[recordID]->Play();
		//m_ComponentsArray[recordID]->SetVolume(m_CurrentVolume);
	}
}

void AAudioActor::Stop(int32 recordID)
{
	if (m_ComponentsArray.IsValidIndex(recordID))
	{
		m_ComponentsArray[recordID]->Stop();
	}
}

void AAudioActor::Pause(int32 recordID)
{
	if (m_ComponentsArray.IsValidIndex(recordID))
	{
		m_ComponentsArray[recordID]->SetPaused(!m_ComponentsArray[recordID]->IsInPause());
	}
}
