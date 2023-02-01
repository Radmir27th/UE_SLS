// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SLSSaveGame.h"
#include "SLSInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USLSInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAVELOADSYSTEM_API ISLSInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:



	UFUNCTION(BlueprintImplementableEvent)
	void ISaveData();
	UFUNCTION(BlueprintImplementableEvent)
	void ILoadData(/*FActorSaveData data*/);
	UFUNCTION(BlueprintImplementableEvent)
	void isDestroy();

};
