// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "GeneContainerComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UE::Math::TVector<double> location = Transform.GetLocation();
	location.Y = 0;

	SetActorLocation(location);
}

void ACharacterBase::OnDead(const UGeneDataAsset* GeneData)
{
	static_cast<UGeneContainerComponent*>(GetComponentByClass(UGeneContainerComponent::StaticClass()))->AddGene(GeneData);
	InnerOnDead();
}

