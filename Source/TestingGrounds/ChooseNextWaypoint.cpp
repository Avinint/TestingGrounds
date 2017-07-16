// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory)
{
	//Super::ExecuteTask(OwnerComp, NodeMemory);

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto AIController = OwnerComp.GetAIOwner();
	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index)
	//SetPatrolPoints(OwnerComp);
	//SetNextWaypoint(OwnerComp);
	//CycleIndexes(OwnerComp);
	return EBTNodeResult::Succeeded; 
}

void UChooseNextWaypoint::SetPatrolPoints(UBehaviorTreeComponent& OwnerComp)
{
	auto Character = Cast<APatrollingGuard>(OwnerComp.GetOwner());
	PatrolPoints = Character->PatrolPointsCPP;
}

void UChooseNextWaypoint::SetNextWaypoint(UBehaviorTreeComponent& OwnerComp)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto NextWaypoint = PatrolPoints[Index];
	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, NextWaypoint);
}

void UChooseNextWaypoint::CycleIndexes(UBehaviorTreeComponent& OwnerComp)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
}

