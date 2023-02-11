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
		void LoadGame(FString SlotName);
	UFUNCTION(BlueprintCallable, Category = "Saving")
		void SaveGame();
	UFUNCTION(BlueprintCallable, Category = "Saving")
		void SaveToSlot(FString SlotName);
	UFUNCTION(BlueprintCallable, Category = "Saving")
		void DeleteSlot(FString SlotName);

	void ReadSaveGame();
	void WriteSaveGame();

	void SaveActorItems();
	void LoadActorItems();

	void SelectSlot();

	TArray<AActor*> Actors;
private: 

public:

	

	void GetSaveDataFromComp(FActorSaveData &ActorData, FName ID, bool isNeedToLoad);

	void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize();



	
};
