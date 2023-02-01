// Fill out your copyright notice in the Description page of Project Settings.


#include "SLSTargetSpawn.h"

// Sets default values
ASLSTargetSpawn::ASLSTargetSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

}

