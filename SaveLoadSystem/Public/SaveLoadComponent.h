// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SLSInterface.h"
#include "SLSSaveGame.h"
#include "SLSTargetSpawn.h"
#include "SaveLoadComponent.generated.h"

enum class Condition
{
	SAVE,
	LOAD,
	DEFAULT
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SAVELOADSYSTEM_API USaveLoadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USaveLoadComponent();
	UPROPERTY(EditAnywhere)
		bool ShouldLoadWithCharacter = false;
	bool Spawned = false;
	UPROPERTY(EditAnywhere, DisplayName = "ID")
		int32 ID = 0;
	UPROPERTY(EditAnywhere)
		FName Tag = "0";
private:
	FActorSaveData ActorSave;
	Condition condition = Condition::DEFAULT;

	void LoadDefault(FActorSaveData& data);
	void LoadCustom(FActorSaveData& data);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);



public:
	void ISaveData_Implementation();
	void ILoadData_Implementation(/*FActorSaveData data*/);
	void isDestroy_Implementation();

	void Load(FActorSaveData& data);

	void Save();
	void SaveLoadMaterials(FActorSaveData& data);

	


};
