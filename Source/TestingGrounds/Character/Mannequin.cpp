// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "../Weapons/Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->RelativeLocation = FVector(1.44f, 1.75f, 64.f); // Position the camera
	FPCamera->bUsePawnControlRotation = true;
	
	/*CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);

	TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPCamera"));
	TPCamera->SetupAttachment(CameraBoom);
	TPCamera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera*/

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FPArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArms"));
	FPArms->SetOnlyOwnerSee(true);
	FPArms->SetupAttachment(FPCamera);
	FPArms->bCastDynamicShadow = false;
	FPArms->CastShadow = false;
	FPArms->RelativeLocation = FVector(-0.5f, -4.4f, -159.7f);
	FPArms->RelativeRotation = FRotator(1.9f, -19.19f, -19.2f);
}

void AMannequin::PullTrigger()
{
	Gun->OnFire();
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	if (GunBlueprint == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Gun Blueprint Missing"));
		return;
	}
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	Gun->AttachToComponent(FPArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	Gun->AnimInstance = GetMesh()->GetAnimInstance();
	
	// If Player
	if (InputComponent != NULL) {
		InputComponent->BindAction("Fire", IE_Pressed, Gun, &AGun::OnFire);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
 void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
} 

