// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Gene.generated.h"

class ACharacterBase;
class UGeneDataAsset;
/**
 * 
 */
UCLASS(Abstract, BlueprintType)
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
	TObjectPtr<ACharacterBase> Character;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<const UGeneDataAsset> DataAsset;
};
