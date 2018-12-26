// Fill out your copyright notice in the Description page of Project Settings.

#include "SettingsWidget.h"


USettingsWidget::USettingsWidget(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_record1(-1)
	, m_record2(-1)
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

	if (m_SliderSound)
	{
		m_SliderSound->OnValueChanged.AddDynamic(this, &USettingsWidget::AudioVolumeChanged);
	}

	m_AudioManager = NewObject<UAudioManager>(this, FName(TEXT("Audio Mgr")));

	AudioVolumeChanged(0.2f);

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
