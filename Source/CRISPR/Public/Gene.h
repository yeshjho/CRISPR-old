// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Gene.generated.h"

class UGeneDataAsset;
/**
 * 
 */
UCLASS(Abstract)
class CRISPR_API UGene : public UObject
{
	GENERATED_BODY()

		
public:
	friend class UGeneContainerComponent;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnAdded();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRemoved();


public:
	UPROPERTY(BlueprintReadOnly)
	AActor* Character;

private:
	const UGeneDataAsset* DataAsset;
};
