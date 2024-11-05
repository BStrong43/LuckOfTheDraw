// Fill out your copyright notice in the Description page of Project Settings.


#include "CowboyCharacter.h"

// Sets default values
ACowboyCharacter::ACowboyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SetCanBeDamaged(true);
    health = MaxHealth;

    //Capsule Init as Root Component
    Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    RootComponent = Collider;  // Set capsule as root component
    Collider->InitCapsuleSize(42.f, 96.f);  // Set Standard UE Mannequin size
    Collider->SetEnableGravity(true);

    //Set Collision Channels
    Collider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);  // Cowboy
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);  // Enemy bullets
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);  // Cowboy bullets
    Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);  // Walls

    //Movement Init
    MovementComponent = CreateDefaultSubobject<UCowboyMovementComponent>(TEXT("Movement Component"));
    MovementComponent->UpdatedComponent = RootComponent;

    //Mag Init
    Mag = CreateDefaultSubobject<UMagazine>(TEXT("Gun Clip"));
    Mag->LoadDefaultCowboyMagazine();

    //Spring Arm Init
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = CameraHeight; // Set camera height
    SpringArm->bDoCollisionTest = false;
    SpringArm->SetAbsolute(false, true, false);//Lock Rotation
    SpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f)); // Top-down view

    // Init camera component
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    Camera->bUsePawnControlRotation = false; // Camera will not rotate with pawn or controller

    //Init Skeleton
    CowboyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeleton"));
    CowboyMesh->SetupAttachment(RootComponent);
    CowboyMesh->SetRelativeLocation(FVector(0, 0, -96));
    CowboyMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CowboyMeshAsset(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
    if (CowboyMeshAsset.Succeeded())
    {
        CowboyMesh->SetSkeletalMesh(CowboyMeshAsset.Object);
    }

    // Animation Init
    static ConstructorHelpers::FObjectFinder<UAnimBlueprint> CowboyAnimBlueprint(TEXT("AnimBlueprint'/Game/Characters/Mannequins/Animations/ABP_Manny.ABP_Manny'"));
    if (CowboyAnimBlueprint.Succeeded())
    {
        CowboyMesh->SetAnimInstanceClass(CowboyAnimBlueprint.Object->GeneratedClass);
    }
}

// Called when the game starts or when spawned
void ACowboyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACowboyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (recoilTime > 0)
    {
        recoilTime -= DeltaTime;
    }
}

UPawnMovementComponent* ACowboyCharacter::GetMovementComponent() const
{
    return MovementComponent;
}

//Character Actions
void ACowboyCharacter::Dodge()
{
    OnDodge();
}

void ACowboyCharacter::Shoot()
{
    if (recoilTime <= 0)
    {
        TSubclassOf<ABullet> Projectile = Mag->ShootChamberedBullet();

        if (Projectile)
        {
            FVector Barrel = GetActorLocation() + (GetActorForwardVector() * 50);
            FRotator BulletDir = GetActorRotation();
            FActorSpawnParameters param = FActorSpawnParameters();
            param.Owner = this;
            param.Instigator = this;
            param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
            param.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

            ABullet* shot = GetWorld()->SpawnActor<ABullet>(Projectile, Barrel, BulletDir, param);
            shot->SetCollisionAsCowboy();
            recoilTime += shot->RecoilTime;
            OnShoot(shot);
        }
    }
    else 
    {
        //Still in recoil
    }
}

void ACowboyCharacter::Look(FVector point)
{
    FVector Direction = point.GetSafeNormal();
    FRotator NewRotation = Direction.Rotation();
    SetActorRotation(NewRotation);
}

void ACowboyCharacter::OnDodge_Implementation()
{

}

void ACowboyCharacter::OnShoot_Implementation(ABullet* shot)
{

}

void ACowboyCharacter::Die()
{
    GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("You Died"));
    //Destroy();
}

float ACowboyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    health -= DamageAmount;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Cowboy Took Damage"));

    if (health <= 0)
    {
        OnDie();
        Die();
    }

    return 0;
}