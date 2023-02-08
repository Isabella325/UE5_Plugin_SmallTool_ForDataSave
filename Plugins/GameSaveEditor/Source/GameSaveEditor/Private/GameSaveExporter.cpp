// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaveExporter.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/BufferArchive.h"

UGameSaveExporter::UGameSaveExporter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = USaveGame::StaticClass();
	PreferredFormatIndex = 0;
	FormatExtension.Add(TEXT("sav"));
	FormatDescription.Add(TEXT("Game Save File"));
}

bool UGameSaveExporter::ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex, uint32 PortFlags)
{
	USaveGame* Asset = CastChecked<USaveGame>(Object);
	FBufferArchive Data;
	if (UGameplayStatics::SaveGameToMemory(Asset,Data)&& Data.Num() > 0)
	{
		Ar.Serialize(Data.GetData(),Data.Num());
		return true;
	}
	return false;
}