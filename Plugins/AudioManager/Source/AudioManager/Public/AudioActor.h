// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtendedAudioComponent.h"
#include "Runtime/Engine/Classes/Sound/SoundBase.h"
#include "AudioActor.generated.h"



UCLASS()
class AAudioActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioActor();

	//	returns AudioComponent's index in array
	int32 PlaySound(USoundBase* soundBase, bool bLooping);

	void Repeat(int32 id);

	void Stop(int32 id);

	UExtendedAudioComponent* GetAudioComponent(int32 id) const;

	void SetVolume(float newVolume);

protected:
	//// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	UPROPERTY(meta = (DisplayName = "Components Array"))
	TArray<UExtendedAudioComponent*> m_ComponentsArray;

	int32 GetFreeComponentNumber();

	float m_CurrentVolume;

public:	
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;
		
	
};
