/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Button.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Constants.h"
#include "commands/AlignCrossHair.h"
#include "commands/ClimbManual.h"
#include "commands/DefaultDrive.h"
#include "commands/Feed.h"
#include "commands/ReverseFeed.h"
#include "commands/LogDataToDashboard.h"
#include "commands/HalfSpeedDrive.h"
#include "commands/Shoot.h"
#include "commands/MoveTrain.h"

#include "RobotContainer.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  
  frc::SmartDashboard::PutNumber("Top Motor RPM", 0.0);
  frc::SmartDashboard::PutNumber("Bottom Motor RPM", 0.0);
  frc::SmartDashboard::PutNumber("Kicker RPM", 0.0);
  frc::SmartDashboard::PutNumber("Hopper Speed", 0.0);
  frc::SmartDashboard::PutNumber("Train Speed", 0.0);

  // Configure the button bindings
  ConfigureButtonBindings();

  // Set up default drive command
  drive.SetDefaultCommand(DefaultDrive(
       &drive,
       [this] { return driver_controller.GetRawAxis(ConXBOXController::RIGHT_TRIGGER_ID) - driver_controller.GetRawAxis(ConXBOXController::LEFT_TRIGGER_ID); },
       [this] { return driver_controller.GetRawAxis(ConXBOXController::LEFT_JOYSTICK_X); }));
    

}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  
  // Commence Half Speed driving when RB is pressed
  frc2::Button([this] { return driver_controller.GetRawButton(ConXBOXController::RIGHT_BUMPER); }).WhenHeld(new HalfSpeedDrive(&drive));
  frc2::Button([this] { return driver_controller.GetRawButton(ConXBOXController::LEFT_BUMPER); }).WhenHeld(new HalfSpeedDrive(&drive));

  frc2::Button([this] { return driver_controller.GetRawButton(ConXBOXController::Y); }).WhenPressed(new AlignCrossHair(&drive, &light));
  // frc2::JoystickButton(&driver_controller, ConXBOXController::RIGHT_BUMPER)
  //     .WhenHeld(new HalfSpeedDrive(&drive));

  frc2::Button([this] { return codriver_controller.GetRawButton(ConCoDriverController::Switch::RED); }).WhenHeld(new Shoot(&shoot));
  frc2::Button([this] {return codriver_controller.GetRawButton(ConCoDriverController::Button::RED); }).WhenHeld(new Feed(&shoot));
  frc2::Button([this] {return codriver_controller.GetRawButton(ConCoDriverController::Button::BLUE); }).WhenHeld(new ReverseFeed(&shoot));
  frc2::Button([this] {return codriver_controller.GetRawButton(ConCoDriverController::Button::YELLOW); }).WhenHeld(new MoveTrain(&shoot));
  //Climb command
  frc2::Button([this] {return codriver_controller.GetRawButton(ConCoDriverController::Button::WHITE); }).WhenHeld(new ClimbManual(&climb, &codriver_controller));
  
  frc2::Button([this] {return true;}).WhileHeld(new LogDataToDashboard(&shoot, &light, &drive));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &simple_auto;
}
