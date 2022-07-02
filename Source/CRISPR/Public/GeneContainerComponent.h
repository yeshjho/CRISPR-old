// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GeneContainerComponent.generated.h"


class ACharacterBase;
class UGeneDataAsset;
class UGene;


USTRUCT(BlueprintType)
struct FGeneInfo
{
	GENERATED_BODY()
	FGeneInfo() = default;
	FGeneInfo(int startSlotIndex, unsigned int slotSize, UGene* gene)
	    : StartSlotIndex(startSlotIndex), SlotSize(slotSize), Gene(gene)
	{}

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int StartSlotIndex;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int SlotSize;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
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
	void SetSlotSize(int Size);

private:
	void PushAndTruncateGenes(int lastGeneStartSlotIndex);


public:
	UPROPERTY(VisibleInstanceOnly)
	TArray<FGeneInfo> Genes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int SlotSize = 3;

	UPROPERTY(BlueprintReadOnly)
	ACharacterBase* Character;
};
