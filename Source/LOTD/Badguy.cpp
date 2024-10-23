#include "Badguy.h"

// Sets default values
ABadguy::ABadguy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    health = MaxHealth;

    //Set Up AIController
    static ConstructorHelpers::FClassFinder<AController> AIControllerBPClass(TEXT("/Game/Blueprints/BadguyController_BP"));  // Replace with your actual Blueprint path
    if (AIControllerBPClass.Class)
    {
        AIControllerClass = AIControllerBPClass.Class;
    }
    else 
    {
        AIControllerClass = ABadguyController::StaticClass();
    }
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    RootComponent = Collider;  // Set capsule as root component
    Collider->InitCapsuleSize(42.f, 96.f);  // Set Standard UE Mannequin size
    Collider->SetEnableGravity(true);

	//Set Collision Channels
	Collider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);  // Enemy
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);  // Cowboy bullets
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Ignore);  // Enemy bullets
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);  // Walls

    //Mag Init
    Mag = CreateDefaultSubobject<UMagazine>(TEXT("Gun Clip"));
    Mag->LoadDefaultEnemyMagazine();

    //Init Skeleton
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeleton"));
    Mesh->SetupAttachment(RootComponent);
    Mesh->SetRelativeLocation(FVector(0, 0, -96));
    Mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CowboyMeshAsset(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
    if (CowboyMeshAsset.Succeeded())
    {
        Mesh->SetSkeletalMesh(CowboyMeshAsset.Object);
    }

    // Animation Init
    static ConstructorHelpers::FObjectFinder<UAnimBlueprint> CowboyAnimBlueprint(TEXT("AnimBlueprint'/Game/Characters/Mannequins/Animations/ABP_Manny.ABP_Manny'"));
    if (CowboyAnimBlueprint.Succeeded())
    {
        Mesh->SetAnimInstanceClass(CowboyAnimBlueprint.Object->GeneratedClass);
    }

    MovementComponent = CreateDefaultSubobject<UCowboyMovementComponent>(TEXT("Movement"));
    MovementComponent->MoveSpeed = RunSpeed;
    MovementComponent->SetUpdatedComponent(RootComponent);
}

// Called when the game starts or when spawned
void ABadguy::BeginPlay()
{
	Super::BeginPlay();
}

void ABadguy::Heal(int healAmount)
{
    health += healAmount;

    if (health > MaxHealth)
        health = MaxHealth;
}

// Called every frame
void ABadguy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UPawnMovementComponent* ABadguy::GetMovementComponent() const
{
    return MovementComponent;
}

void ABadguy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Enemy Hit"));

}

float ABadguy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

    health -= DamageAmount;

    if (health <= 0)
    {
        Die();
    }

	return health;
}

void ABadguy::Die()
{
    OnDie();
    Destroy();
}