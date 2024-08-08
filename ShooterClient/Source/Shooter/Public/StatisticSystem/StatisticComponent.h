// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatisticComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatValueChanged, float, CurrentStat, float, MaxStat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatEnded);


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UStatisticComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatisticComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(BlueprintAssignable, Category = Statistics)
	FOnStatValueChanged OnStatValueChanged;

	UPROPERTY(BlueprintAssignable, Category = Statistics)
	FOnStatEnded OnStatEnded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	FText StatName;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	float CurrentStat;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	float MaxStat;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void CalculateStat_Server(float ChangedValue);

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ChangedStat_Client();

	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = Internal)
	void Init();
	virtual void Init_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = Internal)
	void CalculateStat(float ChangedValue);
	virtual void CalculateStat_Implementation(float ChangedValue);
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
