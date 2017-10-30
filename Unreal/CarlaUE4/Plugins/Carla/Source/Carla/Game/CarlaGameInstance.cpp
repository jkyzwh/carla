// CARLA, Copyright (C) 2017 Computer Vision Center (CVC)

#include "Carla.h"
#include "CarlaGameInstance.h"

#include "CarlaGameController.h"
#include "MockGameController.h"
#include "Settings/CarlaSettings.h"

UCarlaGameInstance::UCarlaGameInstance() {
  CarlaSettings = CreateDefaultSubobject<UCarlaSettings>(TEXT("CarlaSettings"));
  check(CarlaSettings != nullptr);
  CarlaSettings->LoadSettings();
  CarlaSettings->LogSettings();
}

UCarlaGameInstance::~UCarlaGameInstance() {}

void UCarlaGameInstance::InitializeGameControllerIfNotPresent(
    const FMockGameControllerSettings &MockControllerSettings)
{
  if (GameController == nullptr) {
    if (CarlaSettings->bUseNetworking) {
      GameController = MakeUnique<CarlaGameController>();
    } else {
      GameController = MakeUnique<MockGameController>(MockControllerSettings);
      UE_LOG(LogCarla, Log, TEXT("Using mock CARLA controller"));
    }
  }
}