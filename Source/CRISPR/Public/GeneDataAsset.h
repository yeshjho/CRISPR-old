// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GeneDataAsset.generated.h"

class UPassiveGene;
class UActiveGene;
/**
 * 
 */
UCLASS(BlueprintType)
class CRISPR_API UGeneDataAsset final : public UDataAsset
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int SlotCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UActiveGene> ActiveGeneImpl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPassiveGene> PassiveGeneImpl;
};
