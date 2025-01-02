// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIC.h"

#include "Enemy_Parent.h"

AEnemy_AIC::AEnemy_AIC(FObjectInitializer const& ObjectInitializer)
{
}

void AEnemy_AIC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AEnemy_Parent* const npc = Cast<AEnemy_Parent>(InPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree())
		{
			UBlackboardComponent* bb;
			UseBlackboard(tree->BlackboardAsset, bb);
			Blackboard = bb;
			RunBehaviorTree(tree);
		}
	}
}
