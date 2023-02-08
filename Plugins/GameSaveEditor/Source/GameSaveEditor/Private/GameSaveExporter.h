// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Exporters/Exporter.h"
#include "GameSaveExporter.generated.h"

/**
 * 
 */
UCLASS()
class UGameSaveExporter : public UExporter
{
	GENERATED_UCLASS_BODY()

	public:
		virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex, uint32 PortFlags) override;

	
};
