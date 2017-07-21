// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto Character = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = Character->FindComponentByClass<UPatrolRouteComponent>();
	if (!PatrolRoute) { return EBTNodeResult::Failed; }

	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() > 0) {
		auto BlackboardComp = OwnerComp.GetBlackboardComponent();
		auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
		BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
		auto NextIndex = (Index + 1) % PatrolPoints.Num();
		BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	}
	return EBTNodeResult::Succeeded;
}
