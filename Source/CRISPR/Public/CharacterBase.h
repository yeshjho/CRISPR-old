// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UGeneDataAsset;
class UGeneContainerWidgetBase;
UCLASS(Blueprintable)
class CRISPR_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	void OnDead(const UGeneDataAsset* GeneData);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InnerOnDead();

	UFUNCTION(BlueprintCallable)
	void RemoveComponentByClass(TSubclassOf<UActorComponent> ComponentClass);

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGeneContainerWidgetBase> ContainerWidget;
};
