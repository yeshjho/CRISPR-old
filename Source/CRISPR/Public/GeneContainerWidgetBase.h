// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneContainerComponent.h"
#include "Blueprint/UserWidget.h"
#include "GeneContainerWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CRISPR_API UGeneContainerWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetSlotCount(int Count);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetGenes(const TArray<FGeneInfo>& GeneInfos);
};
