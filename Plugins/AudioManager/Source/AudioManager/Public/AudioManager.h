// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AudioActor.h"
#include "ExtendedAudioComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "AudioManager.generated.h"

/**
 * 
 */
UCLASS()
class AUDIOMANAGER_API UAudioManager : public UObject
{
	GENERATED_BODY()
	
public:

	UAudioManager(const FObjectInitializer & ObjectInitializer);

	//	returns AudioComponent's index in array
	int32 PlaySound(USoundBase* soundBase, bool bLooping);

	void Repeat(int32 recordID);

	void Stop(int32 recordID);

	void Pause(int32 recordID);

	void FadeIn(float FadeInDuration);
	void FadeOut(float FadeOutDuration);

	UExtendedAudioComponent* GetAudioComponent(int32 recordID) const;

	bool IsAudioMuted() const;

	float GetVolumeInSettings() const;

	UFUNCTION()
	void AudioVolumeChanged(float NewVolume);

	UFUNCTION()
	void AudioMutedChanged(bool bMuted);


private:

	UPROPERTY(meta = (DisplayName = "Audio Actor"))
	AAudioActor* m_AudioActor;

	void SpawnAudioActor();
	
	//	Volume
	float m_VolumeInSettings;
	float m_VolumeMin;
	float m_VolumeMax;

	bool m_AudioMuted;

	void SetVolume(float newVolume);

	//	Fade in\out
	FTimerHandle m_FadeTimerHandle;

	float m_FadeDuration;
	float m_FadeDeltaTime;
	float m_FadeTimeElapsed;

	//	uses to separate volume settings either process in Fade In\Out or just volume's been changed statically 
	bool m_InFading;
	//	defines process Fade In or Out
	bool m_FadeIn;

	void FadeVolume();


};
