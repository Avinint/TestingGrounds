// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector IndexKey;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector Waypoint;

	void SetPatrolPoints(UBehaviorTreeComponent & OwnerComp);
	void SetNextWaypoint(UBehaviorTreeComponent& OwnerComp);
	void CycleIndexes(UBehaviorTreeComponent & OwnerComp);

private:
	UBehaviorTreeComponent OwnerComponent;
	TArray<AActor*>PatrolPoints;
};
