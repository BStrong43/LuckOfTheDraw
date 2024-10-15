// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the mesh component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1); // Set to your desired channel
    //MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    MeshComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap); // Respond to Pawns

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("'/Game/EngineAssets/Primitives/Shape_Sphere.Shape_Sphere'"));
    if (SphereMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(SphereMeshAsset.Object);
    }

    RootComponent = MeshComponent;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = MeshComponent;
    ProjectileMovement->InitialSpeed = ProjectileSpeed; // Set a default initial speed
    ProjectileMovement->MaxSpeed = ProjectileSpeed; // Set a maximum speed
    ProjectileMovement->bRotationFollowsVelocity = false; // Optional: rotate the bullet with its velocity
    ProjectileMovement->bShouldBounce = false; // Set to true if you want the bullet to bounce


    // Set default values
    ProjectileSpeed = 2000.0f; // Default speed
    ProjectileRange = 1500.0f; // Default range

    distanceCovered = 0;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
    Super::BeginPlay();

    // Set the initial movement direction (for example, forward)
    movementDirection = GetActorForwardVector();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Move the projectile
    FVector NewLocation = GetActorLocation() + (movementDirection * ProjectileSpeed * DeltaTime);
    SetActorLocation(NewLocation, true);

    //Track Distance
    distanceCovered += (ProjectileSpeed * DeltaTime);

    if (distanceCovered >= ProjectileRange)
    {
        Destroy();
    }
}

void ABullet::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    //Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    if (Other && Other != this && Other != Owner) // Ensure you don't hit yourself
    {
        // Implement damage logic or other interactions here
        UE_LOG(LogTemp, Warning, TEXT("Hit detected with: %s"), *Other->GetName());

        // Optionally destroy the bullet after hitting
        Destroy();
    }
}

