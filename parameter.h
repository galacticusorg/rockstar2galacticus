#ifndef PARAMETER_H
#define PARAMETER_H

struct inputParameters {
  /* filenames */
  char inputFile[200];
  char galacticusOutputFile[200];
  int  makeEnvironmentArrays;

  /* cosmology group */
  double H;
  double Omega0;
  double OmegaLambda;
  double OmegaBaryon;
  double powerSpectrumIndex;
  double sigma_8;
  char transferFunction[200];
  /* group finder group */
  char groupFinderCode[200];
  double linkingLength;
  int minimumParticleNumber;
  /* simulation group */
  double errTolIntAccuracy;
  int typeOfTimestepCriterion;
  double boxSize;
  char simulationCode[200];
  char simulationICs[200];
  char softeningKernel[200];
  double softeningPlummerEquivalent;
  double startRedshift;
  /* units group */
  double lengthUnitsInSI;
  int    lengthHubbleExponent;
  int    lengthScaleFactorExponent;
  double massUnitsInSI;
  int    massHubbleExponent;
  int    massScaleFactorExponent;
  double timeUnitsInSI;
  int    timeHubbleExponent;
  int    timeScaleFactorExponent;
  double velocityUnitsInSI;
  int    velocityHubbleExponent;
  int    velocityScaleFactorExponent;
  /* halo trees group */
  int    haloMassesIncludeSubhalos;
  int    treesAreSelfContained;
  int    treesHaveSubhalos;
  int    velocitiesIncludeHubbleFlow;
};

#endif
