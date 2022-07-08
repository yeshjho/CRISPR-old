// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneContainerComponent.h"

#include "ActiveGene.h"
#include "CharacterBase.h"
#include "GeneContainerWidgetBase.h"
#include "GeneDataAsset.h"
#include "PassiveGene.h"
#include "GameFramework/InputSettings.h"

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

	Character = dynamic_cast<ACharacterBase*>(GetOwner());
	
	int i = 0;
	constexpr const char* defaultKeys[] = { "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P" };
	for (const char* c : defaultKeys)
	{
		FString str{ "Activate Slot " };
		str.Append(FString::FromInt(i + 1));
		const FName name{ *str };
		const FKey key{ c };
		if (!UInputSettings::GetInputSettings()->DoesActionExist(name))
		{
			UInputSettings::GetInputSettings()->AddActionMapping({ name, key });
		}
		
		Character->InputComponent->BindAction<FKeyInputDelegate>(name, EInputEvent::IE_Pressed, this, &UGeneContainerComponent::OnKeyInput, i);

	    i++;
	}
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
	gene->Character = Character;
	Genes.Emplace(SlotSize - GeneData->SlotCount, GeneData->SlotCount, gene);
	gene->OnAdded();
	if (SlotSize < GeneData->SlotCount)
	{
		Genes.RemoveAt(0);
		gene->OnRemoved();
	}

	Character->ContainerWidget->SetGenes(Genes);
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

void UGeneContainerComponent::SetSlotSize(const int Size)
{
	if (SlotSize == Size || Size < 0)
	{
		return;
	}

	SlotSize = Size;
	PushAndTruncateGenes(SlotSize);

	Character->ContainerWidget->SetSlotCount(SlotSize);
	Character->ContainerWidget->SetGenes(Genes);
}

void UGeneContainerComponent::PushAndTruncateGenes(int LastGeneStartSlotIndex)
{
	for (int i = Genes.Num() - 1; i >= 0; i--)
	{
		auto& info = Genes[i];
		const int thisGeneEndSlotIndex = info.StartSlotIndex + info.SlotSize - 1;
		const int overlapSize = thisGeneEndSlotIndex - LastGeneStartSlotIndex + 1;
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
		LastGeneStartSlotIndex = info.StartSlotIndex;
	}
}

void UGeneContainerComponent::OnKeyInput(const int SlotIndex)
{
    for (const auto& info : Genes)
    {
        if (info.StartSlotIndex <= SlotIndex && SlotIndex <= info.StartSlotIndex + info.SlotSize - 1)
        {
			if (auto* gene = dynamic_cast<UActiveGene*>(info.Gene.Get()))
			{
				gene->OnActivate();
			}
			break;
        }
    }
}

