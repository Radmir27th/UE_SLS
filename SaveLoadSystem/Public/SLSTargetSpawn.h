// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLSTargetSpawn.generated.h"


UCLASS()
class SAVELOADSYSTEM_API ASLSTargetSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASLSTargetSpawn();

	UPROPERTY(VisibleAnywhere)
	UBillboardComponent *BillBoard;

	UPROPERTY(EditAnywhere, DisplayName = "ID", Category = "SLS Settings")
		int32 ID;


};
