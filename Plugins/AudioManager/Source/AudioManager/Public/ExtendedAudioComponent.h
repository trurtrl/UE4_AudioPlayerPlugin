// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "ExtendedAudioComponent.generated.h"


/** called when we finish playing audio, either because it played to completion or because a Stop() call turned it off early */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExtendedAudioFinished);

/**
 * 
 */
UCLASS()
class UExtendedAudioComponent : public UAudioComponent
{
	GENERATED_BODY()
	
public:

	UExtendedAudioComponent(const FObjectInitializer & ObjectInitializer);

	virtual void InitializeComponent() override;

	//UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")
	virtual void Play(float StartTime = 0.f) override;

	UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")
	void SetLoop(bool bLoop);

	UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")
	bool IsInPause();

	UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")
	void SetVolume(float newVolume);

	UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")
	void Pause();

	UPROPERTY(BlueprintAssignable)
	FOnExtendedAudioFinished OnExtendedAudioFinished;

protected:

	bool m_Loop;

	bool m_InPause;

	UFUNCTION()
	void PlayInLoop();

	float m_CurrentVolume;
};
