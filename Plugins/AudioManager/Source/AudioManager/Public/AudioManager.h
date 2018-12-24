// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AudioActor.h"
#include "ExtendedAudioComponent.h"
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

	UExtendedAudioComponent* GetAudioComponent(int32 id) const;

	bool IsAudioMuted() const;

	float GetVolumeInSettings() const;

	UFUNCTION()
	void AudioVolumeChanged(float NewVolume);

	UFUNCTION()
	void AudioMutedChanged(bool bMuted);


private:

	UPROPERTY(meta = (DisplayName = "Audio Actor"))
	AAudioActor* m_AudioActor;

	void SpawnAudioActor(UWorld* newWorld);
	
	//	Volume
	float m_VolumeInSettings;
	float m_VolumeMin;
	float m_VolumeMax;

	bool m_AudioMuted;

	void SetVolume(float newVolume);



};
