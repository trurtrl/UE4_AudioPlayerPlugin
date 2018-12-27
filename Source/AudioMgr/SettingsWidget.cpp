// Fill out your copyright notice in the Description page of Project Settings.

#include "SettingsWidget.h"


USettingsWidget::USettingsWidget(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_record1(-1)
	, m_record2(-1)
	, m_VolumeLevel(0.5f)
{

}

bool USettingsWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (m_ButtonPlay && !m_ButtonPlay->OnReleased.IsBound())
	{
		m_ButtonPlay->OnReleased.AddDynamic(this, &USettingsWidget::ButtonPlayClicked);
	}

	if (m_ButtonPlayBackground && !m_ButtonPlayBackground->OnReleased.IsBound())
	{
		m_ButtonPlayBackground->OnReleased.AddDynamic(this, &USettingsWidget::ButtonPlayBackgroundClicked);
	}

	if (m_ButtonChange && !m_ButtonChange->OnReleased.IsBound())
	{
		m_ButtonChange->OnReleased.AddDynamic(this, &USettingsWidget::ButtonChangeClicked);
	}

	if (m_ButtonChangeBackground && !m_ButtonChangeBackground->OnReleased.IsBound())
	{
		m_ButtonChangeBackground->OnReleased.AddDynamic(this, &USettingsWidget::ButtonChangeBackgroundClicked);
	}

	if (m_ButtonRepeat && !m_ButtonRepeat->OnReleased.IsBound())
	{
		m_ButtonRepeat->OnReleased.AddDynamic(this, &USettingsWidget::ButtonRepeatClicked);
	}

	if (m_ButtonFadeIn && !m_ButtonFadeIn->OnReleased.IsBound())
	{
		m_ButtonFadeIn->OnReleased.AddDynamic(this, &USettingsWidget::ButtonFadeInClicked);
	}

	if (m_ButtonFadeOut && !m_ButtonFadeOut->OnReleased.IsBound())
	{
		m_ButtonFadeOut->OnReleased.AddDynamic(this, &USettingsWidget::ButtonFadeOutClicked);
	}

	if (m_SliderSound)
	{
		m_SliderSound->OnValueChanged.AddDynamic(this, &USettingsWidget::AudioVolumeChanged);
		m_SliderSound->SetValue(m_VolumeLevel);
	}

	m_AudioManager = NewObject<UAudioPlayer>(this, FName(TEXT("Audio Mgr")));

	AudioVolumeChanged(m_VolumeLevel);

	return true;
}

void USettingsWidget::AudioVolumeChanged(float NewVolume)
{
	m_AudioManager->AudioVolumeChanged(NewVolume);
}

void USettingsWidget::ButtonPlayClicked()
{
	m_AudioManager->Stop(m_record1);
	m_record1 = m_AudioManager->PlaySound(m_SoundBase1, 0);
}

void USettingsWidget::ButtonPlayBackgroundClicked()
{
	m_AudioManager->Stop(m_record2);
	m_record2 = m_AudioManager->PlaySound(m_SoundBase2, 1);
}

void USettingsWidget::ButtonChangeClicked()
{
	m_AudioManager->Stop(m_record1);
	m_record1 = m_AudioManager->PlaySound(m_SoundBase3, 0);
}

void USettingsWidget::ButtonChangeBackgroundClicked()
{
	m_AudioManager->Stop(m_record2);
	m_record2 = m_AudioManager->PlaySound(m_SoundBase4, 1);
}

void USettingsWidget::ButtonRepeatClicked()
{
	m_AudioManager->Repeat(m_record1);
}

void USettingsWidget::ButtonFadeInClicked()
{
	m_AudioManager->FadeIn(1.5f);
}

void USettingsWidget::ButtonFadeOutClicked()
{
	m_AudioManager->FadeOut(1.5f);
}

UAudioPlayer* USettingsWidget::GetAudioManager() const
{
	return m_AudioManager;
}