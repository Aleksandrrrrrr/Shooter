#include "StatisticSystem/StatisticComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UStatisticComponent::UStatisticComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);

	// ...
}

void UStatisticComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStatisticComponent, CurrentStat);
}


void UStatisticComponent::CalculateStat_Server_Implementation(float ChangedValue)
{
	CalculateStat(ChangedValue);
}

void UStatisticComponent::ChangedStat_Client_Implementation()
{
	if(CurrentStat <= 0)
	{
		OnStatEnded.Broadcast();
	}
	OnStatValueChanged.Broadcast(CurrentStat, MaxStat);
}

// Called when the game starts
void UStatisticComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UStatisticComponent::Init_Implementation()
{
	CurrentStat = MaxStat;
}

void UStatisticComponent::CalculateStat_Implementation(float ChangedValue)
{
	if (ChangedValue + CurrentStat > 0) { CurrentStat = ChangedValue + CurrentStat; }
	else CurrentStat = 0;

	ChangedStat_Client();
}

// Called every frame
void UStatisticComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

