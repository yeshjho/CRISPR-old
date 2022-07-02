// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GeneContainerComponent.generated.h"


class UGeneDataAsset;
class UGene;


USTRUCT()
struct FGeneInfo
{
	GENERATED_BODY()
	FGeneInfo() = default;
	FGeneInfo(int startSlotIndex, unsigned int slotSize, UGene* gene)
	    : StartSlotIndex(startSlotIndex), SlotSize(slotSize), Gene(gene)
	{}

	int StartSlotIndex;
	unsigned int SlotSize;
	UPROPERTY()
	UGene* Gene;
};

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

	UFUNCTION(BlueprintCallable)
	void AddGene(const UGeneDataAsset* GeneData);

	// Temporary for testing
	UFUNCTION(BlueprintCallable)
	void ActivateAllGenes();

	UFUNCTION(BlueprintCallable)
	int GetSlotSize() const { return SlotSize; }

	UFUNCTION(BlueprintCallable)
	void SetSlotSize(int size);

private:
	void PushAndTruncateGenes(int lastGeneStartSlotIndex);


public:
	UPROPERTY(VisibleInstanceOnly)
	TArray<FGeneInfo> Genes;

private:
	int SlotSize = 3;
};
