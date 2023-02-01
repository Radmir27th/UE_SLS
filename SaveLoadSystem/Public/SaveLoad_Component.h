// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SLSInterface.h"
#include "SLSSaveGame.h"
#include "SaveLoad_Component.generated.h"

enum class Condition{
	SAVE,
	LOAD,
	DEFAULT
};

UENUM(BlueprintType)
enum class Loading : uint8
{
	DEFAULT UMETA(DisplayName = "Default"),
	CUSTOM UMETA(DisplayName = "Custom"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAVELOADSYSTEM_API USaveLoad_Component : public UActorComponent, public ISLSInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USaveLoad_Component();
	UPROPERTY(EditAnywhere, Category = "Custom Setting")
		bool ShouldLoadWithCharacter = false;
	UPROPERTY(VisibleAnywhere, Category = "Custom Setting")
		bool Spawned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Custom Setting")
		TArray<Loading> TypeLoading;
	UPROPERTY(EditAnywhere, Category = "Custom Setting")
		TArray<FTransform> Transform;
	UPROPERTY(EditAnywhere, Category = "Custom Setting")
		TArray<UMaterialInterface*> Material;;

private:
	FActorSaveData ActorSave;
	Condition condition = Condition::DEFAULT;

	

public:
	
	void ISaveData_Implementation();
	void ILoadData_Implementation(/*FActorSaveData data*/);
	void isDestroy_Implementation() ;

	void Load(FActorSaveData &data);
	void Save();
	void SaveLoadMaterials(FActorSaveData &data);
protected:
	
	virtual void BeginPlay() override;		


	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
};
