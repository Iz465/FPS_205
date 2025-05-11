// Fill out your copyright notice in the Description page of Project Settings.


#include "GunCameraShake.h"

UGunCameraShake::UGunCameraShake()
{
	OscillationDuration = 0.4f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.2f;

	RotOscillation.Pitch.Amplitude = 1.f;
	RotOscillation.Pitch.Frequency = 50;

	RotOscillation.Yaw.Amplitude = 1.f;
	RotOscillation.Yaw.Frequency = 50.f;

	RotOscillation.Roll.Amplitude = 1.f;
	RotOscillation.Roll.Frequency = 50.f;



}
