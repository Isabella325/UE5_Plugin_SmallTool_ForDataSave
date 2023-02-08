// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EditorReimportHandler.h"
#include "GameSaveFactory.generated.h"

/**
 *
 */
UCLASS()
class UGameSaveFactory : public UFactory, public FReimportHandler
{
	GENERATED_UCLASS_BODY()
public:
	virtual bool DoesSupportClass(UClass* Class) override;

	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override {};
	virtual EReimportResult::Type Reimport(UObject* Obj) override;

	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParentm,
		FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Pams,
		FFeedbackContext* Warn, bool& bOutOperationCanceled) override;

};
