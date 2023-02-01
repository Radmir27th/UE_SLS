// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadComponent.h"
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
USaveLoadComponent::USaveLoadComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}




// Called when the game starts
void USaveLoadComponent::BeginPlay()
{


	Super::BeginPlay();

	// ...

}

void USaveLoadComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Save();

	Super::EndPlay(EndPlayReason);


}


void USaveLoadComponent::ISaveData_Implementation() {



}

void USaveLoadComponent::ILoadData_Implementation(/*FActorSaveData data*/) {





}

void USaveLoadComponent::isDestroy_Implementation() {
	return;
}

void USaveLoadComponent::Load(FActorSaveData& data)
{


	LoadDefault(data);


}

void USaveLoadComponent::LoadDefault(FActorSaveData& data)
{

	condition = Condition::LOAD;
	this->SaveLoadMaterials(data);
	FMemoryReader MemoReader(data.ByteData, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoReader, false);
	Ar.ArNoDelta = true;
	Ar.ArIsSaveGame = true;
	GetOwner()->Serialize(Ar);
	if (data.ID != 0)
	{
		TArray<AActor*> TempActors;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASLSTargetSpawn::StaticClass(), TempActors);



		for (auto Actor : TempActors)
		{
			ASLSTargetSpawn* target = Cast<ASLSTargetSpawn>(Actor);


			if (target->ID == data.ID)
			{

				GetOwner()->SetActorTransform(target->GetActorTransform());
			}
		}
		return;
	}

	GetOwner()->SetActorTransform(data.Transform);

}

void USaveLoadComponent::LoadCustom(FActorSaveData& data)
{
	TArray<AActor*> TempActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASLSTargetSpawn::StaticClass(), TempActors);



	for (auto Actor : TempActors)
	{
		ASLSTargetSpawn* target = Cast<ASLSTargetSpawn>(Actor);


		if (target->ID == data.ID)
		{

			GetOwner()->SetActorTransform(target->GetActorTransform());
		}
	}
}

void USaveLoadComponent::Save()
{

	AActor* Owner = GetOwner();

	USLSGameInstanceSubsystem* SG = GetWorld()->GetGameInstance()->GetSubsystem< USLSGameInstanceSubsystem>();

	ActorSave.ActorName = Owner->GetFName();
	ActorSave.Transform = Owner->GetActorTransform();
	ActorSave.SpawnActor = GetOwner()->GetClass();
	ActorSave.ID = ID;

	FMemoryWriter MemWriter(ActorSave.ByteData, true);
	FObjectAndNameAsStringProxyArchive Ar(MemWriter, false);
	Ar.ArNoDelta = true;
	Ar.ArIsSaveGame = true;
	GetOwner()->Serialize(Ar);

	condition = Condition::SAVE;
	this->SaveLoadMaterials(ActorSave);

	if (ShouldLoadWithCharacter)
	{
		ActorSave.ActorName = Tag;
	}

	SG->GetSaveDataFromComp(ActorSave, ActorSave.ActorName, ShouldLoadWithCharacter);
}

void USaveLoadComponent::SaveLoadMaterials(FActorSaveData& data)
{
	TArray<UStaticMeshComponent*> ArComp;
	GetOwner()->GetComponents<UStaticMeshComponent>(ArComp);

	switch (condition) {
	case Condition::SAVE:
		for (auto& Mesh : ArComp) {
			for (auto& mat : Mesh->GetMaterials()) {
				data.Material.Add(mat);
			}
		}
	case Condition::LOAD:
		if (data.Material.Num() != 0)
		{
			for (auto& Mesh : ArComp) {
				for (int i = 0; i < Mesh->GetNumMaterials(); ++i) {
					Mesh->SetMaterial(i, data.Material[i]);
				}
			}
		}
	}





}

