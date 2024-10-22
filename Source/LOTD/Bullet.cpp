// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;
    distanceCovered = 0;
    eProjectileType = EProjectileType::BULLET;
    eDamageType = EDamageType::PT_Default;

    //Root Collider
    Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
    //Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    RootComponent = Collider;

    // Create the mesh component 
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("'/Game/EngineAssets/Primitives/Shape_Sphere.Shape_Sphere'"));
    if (SphereMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(SphereMeshAsset.Object);
    }
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MeshComponent->SetupAttachment(RootComponent);


    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    ProjectileMovement->UpdatedComponent = RootComponent;
    ProjectileMovement->InitialSpeed = ProjectileSpeed; // Set a default initial speed
    ProjectileMovement->MaxSpeed = ProjectileSpeed; // Set a maximum speed
    ProjectileMovement->bRotationFollowsVelocity = false; // Optional: rotate the bullet with its velocity
    ProjectileMovement->bShouldBounce = false; // Set to true if you want the bullet to bounce
    
    //Align components
    MeshComponent->SetRelativeLocation(FVector(0, 0, -30));
    MeshComponent->SetRelativeScale3D(FVector(.66));

    //Resize Actor To Bullet Size
    SetActorScale3D(FVector(.25));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
    Super::BeginPlay();

    // Set the initial movement direction (for example, forward)
    movementDirection = GetActorForwardVector();

    OnFire();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Move the projectile
    FVector NewLocation = GetActorLocation() + (movementDirection * ProjectileSpeed * DeltaTime);
    FHitResult hit;
    SetActorLocation(NewLocation, true, &hit);

    if (hit.bBlockingHit)
        OnHit(Collider, hit.GetActor(), hit.GetComponent(), hit.ImpactNormal, hit);

    //Distance Control
    if(TrackDistance)
        distanceCovered += (ProjectileSpeed * DeltaTime);

    if (distanceCovered >= ProjectileRange)
    {
        Destroy();
    }
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    
    if (OtherActor && OtherActor != this && OtherComp)
    {
        // Log the actor we hit
        UE_LOG(LogTemp, Warning, TEXT("Bullet hit: %s"), *OtherActor->GetName());

        UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, nullptr);
        
        // Destroy the bullet on hit
        DoExplode(Hit);
        Destroy();
    }
}

void ABullet::SetCollisionAsEnemy()
{
    Collider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel4);  //EnemyBullet
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);  // Cowboy
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);  // Enemy
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Ignore);  // Other enemy bullets
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);  // Walls
}

void ABullet::SetCollisionAsCowboy()
{
    Collider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);  //CowboyBullet
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);  // Enemy
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);  // Cowboy
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Ignore);  // Other cowboy bullets
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);  // Walls
}

void ABullet::OnWallHit(FHitResult hit)
{
    DoExplode(hit);
    Destroy();
}