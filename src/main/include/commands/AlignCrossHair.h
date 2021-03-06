/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "Constants.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Limelight.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AlignCrossHair
    : public frc2::CommandHelper<frc2::CommandBase, AlignCrossHair> {
 public:
  AlignCrossHair(Drivetrain* subsystem1, Limelight* subsystem2);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    Drivetrain* drive;
    Limelight* light;
    //frc2::PIDController pid(1.0, 0.0, 0.0);
};
