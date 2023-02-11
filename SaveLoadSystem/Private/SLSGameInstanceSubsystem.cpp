// Fill out your copyright notice in the Description page of Project Settings.


#include "SLSGameInstanceSubsystem.h"
#include "SLSInterface.h"
#include "Engine.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components.h"
#include "EngineUtils.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "SaveLoadComponent.h"



void USLSGameInstanceSubsystem::LoadGame(FString SlotName)
{
	if (SlotName.IsEmpty())
		SelectSlot();
	else
		SaveGameSlotName = SlotName;
	ReadSaveGame();
	LoadActorItems();
}


void USLSGameInstanceSubsystem::SaveGame()
{
	WriteSaveGame();
}


void USLSGameInstanceSubsystem::ReadSaveGame()
{
	CurrentSave = Cast<USLSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0));
	if (!CurrentSave)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No saved games found. Trying to save a new one."));
	}
	else
	{
		for (FActorIterator It(GetWorld()); It; ++It)
		{
			AActor* Actor = *It;
			USaveLoadComponent* SL = Actor->FindComponentByClass<USaveLoadComponent>();



			if (!SL)
			{
				continue;
			}

			if (SL->ShouldLoadWithCharacter)
			{
				Actors.Add(Actor);
				continue;
			}

			if (CurrentSave->SavedActors.Contains(Actor->GetFName()))
			{
				SL->Load(CurrentSave->SavedActors[Actor->GetFName()]);
				CurrentSave->SavedActors.Remove(Actor->GetFName());
			}

		}
		// Spawn Actor that were spawned last session

		for (auto& Spawn : CurrentSave->SavedActors)
		{
			auto Actor = GetWorld()->SpawnActor(Spawn.Value.SpawnActor);
			USaveLoadComponent* SL = Actor->FindComponentByClass<USaveLoadComponent>();



			if (!SL)
			{
				continue;
			}

			SL->ShouldLoadWithCharacter = false;

			SL->Load(CurrentSave->SavedActors[Spawn.Value.ActorName]);
		}
		CurrentSave->SavedActors.Empty();
	}
}

void USLSGameInstanceSubsystem::WriteSaveGame()
{
	if (!CurrentSave)
		CurrentSave = Cast<USLSSaveGame>(UGameplayStatics::CreateSaveGameObject(USLSSaveGame::StaticClass()));

	for (FActorIterator It(GetWorld()); It; ++It) {
		AActor* Actor = *It;

		FActorSaveData ActorData;
		USaveLoadComponent* SL = Actor->FindComponentByClass<USaveLoadComponent>();

		if (!SL)
		{
			continue;
		}


		SL->Save();

	}
	UGameplayStatics::SaveGameToSlot(CurrentSave, SaveGameSlotName, 0);
}

void USLSGameInstanceSubsystem::SaveToSlot(FString SlotName)
{
	UGameplayStatics::SaveGameToSlot(CurrentSave, SlotName, 0);
	UGameplayStatics::SaveGameToSlot(CurrentSaveItem, SaveActorItemSlotName, 0);
}

void USLSGameInstanceSubsystem::DeleteSlot(FString SlotName)
{
	UGameplayStatics::DeleteGameInSlot(SlotName, 0);
}

void USLSGameInstanceSubsystem::LoadActorItems()
{
	if (!CurrentSaveItem)
		CurrentSaveItem = Cast<USLSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveActorItemSlotName, 0));
	if (!CurrentSaveItem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No saved Actor Items. Trying to save a new one."));
	}
	else
	{

		if (Actors.Num() != 0)
		{
			for (auto rActor : Actors)
			{
				USaveLoadComponent* SL = rActor->FindComponentByClass<USaveLoadComponent>();

				if (!SL)
				{
					continue;
				}

				if (CurrentSaveItem->SavedActors.Contains(SL->Tag))
				{
					SL->Load(CurrentSaveItem->SavedActors[SL->Tag]);
				}

			}
		}
		else
		{

			for (auto& Items : CurrentSaveItem->SavedActors)
			{
				AActor* Actor = GetWorld()->SpawnActor(Items.Value.SpawnActor);
				USaveLoadComponent* SL = Actor->FindComponentByClass<USaveLoadComponent>();

				if (!SL)
				{
					continue;
				}

				SL->ID = Items.Value.ID;
				SL->Tag = Items.Value.ActorName;
				SL->ShouldLoadWithCharacter = true;
				SL->Load(CurrentSaveItem->SavedActors[Items.Value.ActorName]);

			}

		}
		CurrentSaveItem->SavedActors.Empty();
	}
	Actors.Empty();

}

void USLSGameInstanceSubsystem::GetSaveDataFromComp(FActorSaveData& ActorData, FName ID, bool isNeedToLoad)
{

	if (isNeedToLoad)
	{
		if (!CurrentSaveItem)
		{
			CurrentSaveItem = Cast<USLSSaveGame>(UGameplayStatics::CreateSaveGameObject(USLSSaveGame::StaticClass()));
			CurrentSaveItem->SavedActors.Empty();
		}
		CurrentSaveItem->SavedActors.Add(ID, ActorData);
		return;
	}


	if (!CurrentSave)
	{
		CurrentSave = Cast<USLSSaveGame>(UGameplayStatics::CreateSaveGameObject(USLSSaveGame::StaticClass()));
		CurrentSave->SavedActors.Empty();
	}
	CurrentSave->SavedActors.Add(ID, ActorData);

	

}

void USLSGameInstanceSubsystem::SelectSlot() {

	UWorld* World = GetWorld();


	if (!World) return;

	FString CurrentLevelName = World->GetMapName();

	SaveGameSlotName = CurrentLevelName;

}

void USLSGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

	Super::Initialize(Collection);

}

void USLSGameInstanceSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Error, TEXT("WHEN MTF"));
}
