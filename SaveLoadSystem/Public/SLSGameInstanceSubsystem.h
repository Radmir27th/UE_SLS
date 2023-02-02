// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Components/ActorComponent.h"
#include "SLSSaveGame.h"
#include "SLSGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS(meta = (Displayname = "SaveLoad System"))
class SAVELOADSYSTEM_API USLSGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnyWhere, Category = "Saving")
		USLSSaveGame* CurrentSave;
	UPROPERTY(EditAnyWhere, Category = "Saving")
		USLSSaveGame* CurrentSaveItem;
	UPROPERTY(BlueprintReadOnly, Category = "Saving")
		FString SaveGameSlotName;
	
	UPROPERTY(BlueprintReadOnly, Category = "Saving")
		FString SaveActorItemSlotName = "SaveItem";

private:
	UFUNCTION(BlueprintCallable, Category = "Saving")
		void LoadGame();
	UFUNCTION(BlueprintCallable, Category = "Saving")
		void SaveGame();

	void SelectSlot();

	void ReadSaveGame();
	void WriteSaveGame();

	void SaveActorItems();
	void LoadActorItems();

	TArray<AActor*> Actors;
	
public:

	

	void GetSaveDataFromComp(FActorSaveData &ActorData, FName ID, bool isNeedToLoad);

	void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize();



	
};
