// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Slider.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/Engine/Classes/Sound/SoundBase.h"
#include "AudioManager/Public/AudioManager.h"
#include "SettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class AUDIOMGR_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	USettingsWidget(const FObjectInitializer & ObjectInitializer);

	virtual bool Initialize() override;

	UFUNCTION()
	void AudioVolumeChanged(float NewVolume);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "SoundBase 1"))
	USoundBase* m_SoundBase1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "SoundBase 2"))
	USoundBase* m_SoundBase2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "SoundBase 3"))
	USoundBase* m_SoundBase3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "SoundBase 4"))
	USoundBase* m_SoundBase4;


private:

	UPROPERTY(meta = (BindWidget), meta = (DisplayName = "Slider Sound"))
	USlider* m_SliderSound;

	UPROPERTY(meta = (BindWidget), meta = (DisplayName = "Button Play"))
	UButton* m_ButtonPlay;

	UPROPERTY(meta = (BindWidget), meta = (DisplayName = "Button Play Background"))
	UButton* m_ButtonPlayBackground;

	UPROPERTY(meta = (BindWidget), meta = (DisplayName = "Button Change"))
	UButton* m_ButtonChange;

	UPROPERTY(meta = (BindWidget), meta = (DisplayName = "Button Change Background"))
	UButton* m_ButtonChangeBackground;

	UPROPERTY(meta = (BindWidget), meta = (DisplayName = "Button Repeat"))
	UButton* m_ButtonRepeat;


	UFUNCTION()
	void ButtonPlayClicked();

	UFUNCTION()
	void ButtonPlayBackgroundClicked();

	UFUNCTION()
	void ButtonChangeClicked();

	UFUNCTION()
	void ButtonChangeBackgroundClicked();

	UFUNCTION()
	void ButtonRepeatClicked();

	UPROPERTY()
	UAudioManager* m_AudioManager;

	int32 m_record1;
	int32 m_record2;

};
