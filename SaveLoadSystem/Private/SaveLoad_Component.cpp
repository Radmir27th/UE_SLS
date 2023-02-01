// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoad_Component.h"
#include "GameFramework/Actor.h"
#include "SLSGameInstanceSubsystem.h"
#include "Engine.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components.h"
#include "EngineUtils.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Components/ActorComponent.h"






// Sets default values for this component's properties
USaveLoad_Component::USaveLoad_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USaveLoad_Component::BeginPlay()
{

	
	Super::BeginPlay();
	
	// ...

}

void USaveLoad_Component::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Save();

	Super::EndPlay(EndPlayReason);

	
}


void USaveLoad_Component::ISaveData_Implementation(){
	
	
	
}

void USaveLoad_Component::ILoadData_Implementation(/*FActorSaveData data*/) {

	
	

	
}

void USaveLoad_Component::isDestroy_Implementation() {
	return;
}

void USaveLoad_Component::Load(FActorSaveData& data)
{
	//if (LoadToLvl) TypeLoading == Loading::CUSTOM;

	//UE_LOG(LogTemp, Error, TEXT("Load to LvL: %d"), LoadToLvl);
	//if (TypeLoading == Loading::DEFAULT || (TypeLoading == Loading::CUSTOM && !LoadToLvl))
	{
		condition = Condition::LOAD;
		this->SaveLoadMaterials(data);

		FMemoryReader MemoReader(data.ByteData, true);
		FObjectAndNameAsStringProxyArchive Ar(MemoReader, false);
		Ar.ArIsSaveGame = true;
		GetOwner()->Serialize(Ar);
		GetOwner()->SetActorTransform(data.Transform);
	}
	//if (TypeLoading == Loading::CUSTOM && LoadToLvl)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Load to LvL: %d"), LoadToLvl);
	//	GetOwner()->SetActorTransform(Transform);
	//}

	
}
	

void USaveLoad_Component::Save()
{
	if (Spawned) return;
	AActor* Owner = GetOwner();

	USLSGameInstanceSubsystem* SG = GetWorld()->GetGameInstance()->GetSubsystem< USLSGameInstanceSubsystem>();

	ActorSave.ActorName = Owner->GetFName();
	ActorSave.Transform = Owner->GetActorTransform();
	ActorSave.SpawnActor = Owner->GetClass();

	FMemoryWriter MemWriter(ActorSave.ByteData, true);
	FObjectAndNameAsStringProxyArchive Ar(MemWriter, false);
	Ar.ArIsSaveGame = true;
	GetOwner()->Serialize(Ar);
	
	condition = Condition::SAVE;
	this->SaveLoadMaterials(ActorSave);

	
	
	SG->GetSaveDataFromComp(ActorSave, ActorSave.ActorName, ShouldLoadWithCharacter);
}

void USaveLoad_Component::SaveLoadMaterials(FActorSaveData &data)
{
	TArray<UStaticMeshComponent*> ArComp;
	GetOwner()->GetComponents<UStaticMeshComponent>(ArComp);

	switch (condition) 
	{
	case Condition::SAVE:
		for (auto& Mesh : ArComp) {
			for (auto& mat : Mesh->GetMaterials()) {
				data.Material.Add(mat);
			}
		}
		break;
	case Condition::LOAD:
		if (!data.Material.IsEmpty()) {
			for (auto& Mesh : ArComp) {
				for (int i = 0; i < Mesh->GetNumMaterials(); ++i) {
					Mesh->SetMaterial(i, data.Material[i]);
				}
			}
		}
		break;
	}
		

	

	
}

