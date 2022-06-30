// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gene.h"
#include "ActiveGene.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CRISPR_API UActiveGene : public UGene
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnActivate();
};
