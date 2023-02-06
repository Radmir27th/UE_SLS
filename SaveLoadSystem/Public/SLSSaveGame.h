// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "SLSSaveGame.generated.h"

/**
 * 
 */

USTRUCT()
struct FActorSaveData
{
	GENERATED_USTRUCT_BODY()

public:


	UPROPERTY()
		TSubclassOf<AActor> SpawnActor;
	/* Identifier for which Actor this belongs to */
	UPROPERTY()
		FName ActorName;
	/* For movable Actors, keep location,rotation,scale. */
	UPROPERTY()
		FTransform Transform;
	UPROPERTY()
		TArray<UMaterialInterface*> Material;
	/* Contains all 'SaveGame' marked variables of the Actor */
	UPROPERTY()
		TArray<uint8> ByteData;
	UPROPERTY()
		TArray<uint8> ByteDataComp;
	UPROPERTY()
		int32 ID;


};

UCLASS()
class SAVELOADSYSTEM_API USLSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	/* Actors stored from a level (currently does not support a specific level and just assumes the demo map) */
	UPROPERTY()
		TMap<FName ,FActorSaveData> SavedActors;
	
};
