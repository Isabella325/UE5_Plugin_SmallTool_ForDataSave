// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaveFactory.h"
#include "GameFramework/SaveGame.h"
#include <Runtime/Core/Public/Misc/FileHelper.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

UGameSaveFactory::UGameSaveFactory(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("sav;")));
	SupportedClass = USaveGame::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}

bool UGameSaveFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	if (Obj)
	{
		return DoesSupportClass(Obj->GetClass());
	}
	return false;
}

EReimportResult::Type UGameSaveFactory::Reimport(UObject* Obj)
{
	if (IsValid(Obj))
	{
		USaveGame* Asset = Cast<USaveGame>(Obj);
		bool OutCancel = false;
		UObject* NewObj = ImportObject(Obj->GetClass(), Obj->GetOuter(), Obj->GetFName(), Obj->GetFlags(), PreferredReimportPath, nullptr, OutCancel);
		if (NewObj && !OutCancel)
		{
			return EReimportResult::Succeeded;
		}
	}
	return EReimportResult::Failed;
}

bool UGameSaveFactory::DoesSupportClass(UClass* Class)
{
	return Class->IsChildOf<USaveGame>();
}


UObject* UGameSaveFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Pams, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	TArray<uint8> Bytes;
	USaveGame* SaveGame = nullptr;


	if (FFileHelper::LoadFileToArray(Bytes, *Filename))
	{
		USaveGame* Temp = UGameplayStatics::LoadGameFromMemory(Bytes);
		if (Temp)
		{
			SaveGame = DuplicateObject(Temp, InParent, InName);
			SaveGame->SetFlags(Flags);
		}
	}
	bOutOperationCanceled = !SaveGame;

	return SaveGame;
}
