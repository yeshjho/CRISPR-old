// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Gene.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CRISPR_API UGene : public UObject
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnAdded();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRemoved();
};
