// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GeneContainerComponent.generated.h"


class UGeneDataAsset;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRISPR_API UGeneContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGeneContainerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(VisibleInstanceOnly)
	TArray<UGeneDataAsset*> Genes;
};
