// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneContainerComponent.h"

#include "ActiveGene.h"
#include "GeneDataAsset.h"
#include "PassiveGene.h"

// Sets default values for this component's properties
UGeneContainerComponent::UGeneContainerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UGeneContainerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGeneContainerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGeneContainerComponent::AddGene(const UGeneDataAsset* GeneData)
{
	const auto* activeGene = GeneData->ActiveGeneImpl.Get();
	const auto* passiveGene = GeneData->PassiveGeneImpl.Get();
	check((activeGene != nullptr) ^ (passiveGene != nullptr));

	const UClass* geneClass = activeGene ? activeGene : passiveGene;

	PushAndTruncateGenes(SlotSize - GeneData->SlotCount);

	auto* gene = NewObject<UGene>(this, geneClass);
	gene->DataAsset = GeneData;
	gene->Character = GetOwner();
	Genes.Emplace(SlotSize - GeneData->SlotCount, GeneData->SlotCount, gene);
	gene->OnAdded();
}

void UGeneContainerComponent::ActivateAllGenes()
{
    for (const auto& info : Genes)
    {
		UGene* gene = info.Gene;
        if (auto* activeGene = dynamic_cast<UActiveGene*>(gene))
        {
			activeGene->OnActivate();
        }
    }
}

void UGeneContainerComponent::SetSlotSize(int size)
{
	SlotSize = size;
	PushAndTruncateGenes(SlotSize);
}

void UGeneContainerComponent::PushAndTruncateGenes(int lastGeneStartSlotIndex)
{
	for (int i = Genes.Num() - 1; i >= 0; i--)
	{
		auto& info = Genes[i];
		const int thisGeneEndSlotIndex = info.StartSlotIndex + info.SlotSize - 1;
		const int overlapSize = thisGeneEndSlotIndex - lastGeneStartSlotIndex + 1;
		if (overlapSize <= 0)
		{
			break;
		}
		info.StartSlotIndex -= overlapSize;
		if (info.StartSlotIndex < 0)
		{
			for (int j = 0; j <= i; j++)
			{
				Genes[j].Gene->OnRemoved();
			}
			Genes.RemoveAt(0, i + 1);
			break;
		}
		lastGeneStartSlotIndex = info.StartSlotIndex;
	}
}

