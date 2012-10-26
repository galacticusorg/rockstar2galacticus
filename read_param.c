#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parameter.h"

int read_param(const char * filename, struct inputParameters * param) {

  FILE * file;
  file=fopen(filename,"r");
  if(file==0) {
    printf("Could not find file %s\n", filename);
    return 1;
  }
 
  const int maxpars = 100;
  char pname[maxpars][50];  /* vector of the parameter names */
  void *addr[maxpars];	    /* pointer to where parameter should be stored */
  enum parameterType {INT, DOUBLE, STRING};
  enum parameterType dtype[maxpars];  /* vector with the type of the parameter*/

  int nparam=0;
  /* define parameters */
  /* filenames */
  strcpy(pname[nparam], "inputFile");
  addr[nparam] = (*param).inputFile;
  dtype[nparam++] = STRING;

  strcpy(pname[nparam], "galacticusOutputFile");
  addr[nparam] = (*param).galacticusOutputFile;
  dtype[nparam++] = STRING;

  strcpy(pname[nparam], "makeEnvironmentArrays");
  addr[nparam] = &(*param).makeEnvironmentArrays;
  dtype[nparam++] = INT;  

  /* cosmology group */
  strcpy(pname[nparam], "H");
  addr[nparam] = (void*)(&(*param).H);
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "Omega0");
  addr[nparam] = &(*param).Omega0;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "OmegaLambda");
  addr[nparam] = &(*param).OmegaLambda;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "OmegaBaryon");
  addr[nparam] = &(*param).OmegaBaryon;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "powerSpectrumIndex");
  addr[nparam] = &(*param).powerSpectrumIndex;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "sigma_8");
  addr[nparam] = &(*param).sigma_8;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "transferFunction");
  addr[nparam] = (*param).transferFunction;
  dtype[nparam++] = STRING;

  /* group finder group */
  strcpy(pname[nparam], "groupFinderCode");
  addr[nparam] = (*param).groupFinderCode;
  dtype[nparam++] = STRING;

  strcpy(pname[nparam], "linkingLength");
  addr[nparam] = &(*param).linkingLength;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "minimumParticleNumber");
  addr[nparam] = &(*param).minimumParticleNumber;
  dtype[nparam++] = INT;

  /* simulation group */
  strcpy(pname[nparam], "errTolIntAccuracy");
  addr[nparam] = &(*param).errTolIntAccuracy;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "typeOfTimestepCriterion");
  addr[nparam] = &(*param).typeOfTimestepCriterion;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "boxSize");
  addr[nparam] = &(*param).boxSize;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "simulationCode");
  addr[nparam] = (*param).simulationCode;
  dtype[nparam++] = STRING;

  strcpy(pname[nparam], "simulationICs");
  addr[nparam] = (*param).simulationICs;
  dtype[nparam++] = STRING;

  strcpy(pname[nparam], "softeningKernel");
  addr[nparam] = (*param).softeningKernel;
  dtype[nparam++] = STRING;

  strcpy(pname[nparam], "softeningPlummerEquivalent");
  addr[nparam] = &(*param).softeningPlummerEquivalent;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "startRedshift");
  addr[nparam] = &(*param).startRedshift;
  dtype[nparam++] = DOUBLE;

  /* units group */
  strcpy(pname[nparam], "lengthUnitsInSI");
  addr[nparam] = &(*param).lengthUnitsInSI;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "lengthHubbleExponent");
  addr[nparam] = &(*param).lengthHubbleExponent;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "lengthScaleFactorExponent");
  addr[nparam] = &(*param).lengthScaleFactorExponent;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "massUnitsInSI");
  addr[nparam] = &(*param).massUnitsInSI;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "massHubbleExponent");
  addr[nparam] = &(*param).massHubbleExponent;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "massScaleFactorExponent");
  addr[nparam] = &(*param).massScaleFactorExponent;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "timeUnitsInSI");
  addr[nparam] = &(*param).timeUnitsInSI;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "timeHubbleExponent");
  addr[nparam] = &(*param).timeHubbleExponent;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "timeScaleFactorExponent");
  addr[nparam] = &(*param).timeScaleFactorExponent;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "velocityUnitsInSI");
  addr[nparam] = &(*param).velocityUnitsInSI;
  dtype[nparam++] = DOUBLE;

  strcpy(pname[nparam], "velocityHubbleExponent");
  addr[nparam] = &(*param).velocityHubbleExponent;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "velocityScaleFactorExponent");
  addr[nparam] = &(*param).velocityScaleFactorExponent;
  dtype[nparam++] = INT;

  /* halo trees group */
  strcpy(pname[nparam], "haloMassesIncludeSubhalos");
  addr[nparam] = &(*param).haloMassesIncludeSubhalos;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "treesAreSelfContained");
  addr[nparam] = &(*param).treesAreSelfContained;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "treesHaveSubhalos");
  addr[nparam] = &(*param).treesHaveSubhalos;
  dtype[nparam++] = INT;

  strcpy(pname[nparam], "velocitiesIncludeHubbleFlow");
  addr[nparam] = &(*param).velocitiesIncludeHubbleFlow;
  dtype[nparam++] = INT;


  int i;
  int foundFlag[nparam];
  for(i=0;i<nparam;i++) {
    foundFlag[i]=0;
  }
  printf("Starting to read the parameter file\n");  
  /* read in lines of parameter file */
  while(!feof(file)) {
    char buf[200];
    char buf1[200], buf2[200], buf3[200];
    fgets(buf,200,file);
    /* check whether line starts with #, space or newline */
    if(buf[0]=='#' || buf[0]==' ' || buf[0]=='\n')
      continue;
    /* if not, find the right parameter value and copy what we find */
    /* extract the name and the value from the line */
    sscanf(buf,"%s%s%s\n", buf1,buf2, buf3);
    int lineErrorFlag = 0;
    for(i=0; i<nparam; i++) {
      if(strcmp(buf1,pname[i]) == 0) {
	if(dtype[i] == DOUBLE) 
	  *((double *) addr[i]) = atof(buf3);
	if(dtype[i] == INT)
	   *((int *) addr[i]) = atoi(buf3);
	if(dtype[i] == STRING)
	  strcpy(addr[i],buf3);
	foundFlag[i]+=1;
	lineErrorFlag+=1; 
      }
    }
    if(lineErrorFlag==0) {
      printf("Error in read_param.c: did not find matching parameter for line:\n%s\n",buf);
      return 1;
    }
  }
  for(i=0;i<nparam;i++) {
    if(foundFlag[i]>1) {
      printf("Error in read_param.c: Multiple definition of parameter:\n%s\n",pname[i]);
      return 1;
    }
    if(foundFlag[i]==0) {
      printf("Error in read_param.c: Parameter %s not specified\n",pname[i]);
    }
  }

  /* Output the values in the struct */
  printf("Values read from the parameter file:\n");
  printf("\n");
  printf("Cosmology group\n");
  printf("H: %g\n",(*param).H);
  printf("Omega0: %g\n",(*param).Omega0);
  printf("OmegaLambda: %g\n",(*param).OmegaLambda);
  printf("OmegaBaryon: %g\n",(*param).OmegaBaryon);
  printf("powerSpectrumIndex: %g\n",(*param).powerSpectrumIndex);
  printf("sigma_8: %g\n",(*param).sigma_8);
  printf("\ngroup finder group\n");
  printf("transferFunction: %s\n",(*param).transferFunction);
  printf("groupFinderCode: %s\n",(*param).groupFinderCode);
  printf("linkingLength: %g\n",(*param).linkingLength);
  printf("linkingLength: %i\n",(*param).minimumParticleNumber);
  printf("\nsimulation group\n");
  printf("errTolIntAccuracy: %g\n",(*param).errTolIntAccuracy);
  printf("typeOfTimestepCriterion: %i\n",(*param).typeOfTimestepCriterion);
  printf("boxSize: %g\n",(*param).boxSize);
  printf("simulationCode: %s\n",(*param).simulationCode);
  printf("simulationICs: %s\n",(*param).simulationICs);
  printf("softeningKernel: %s\n",(*param).softeningKernel);
  printf("softeningPlummerEquivalent: %g\n",(*param).softeningPlummerEquivalent);
  printf("startRedshift: %g\n",(*param).startRedshift);
  printf("\nunits group\n");
  printf("lengthUnitsInSI: %g\n",(*param).lengthUnitsInSI);
  printf("lengthHubbleExponent: %i\n",(*param).lengthHubbleExponent);
  printf("lengthScaleFactorExponent: %i\n",(*param).lengthScaleFactorExponent);
  printf("massUnitsInSI: %g\n",(*param).massUnitsInSI);
  printf("massHubbleExponent: %i\n",(*param).massHubbleExponent);
  printf("massScaleFactorExponent: %i\n",(*param).massScaleFactorExponent);
  printf("timeUnitsInSI: %g\n",(*param).timeUnitsInSI);
  printf("timeHubbleExponent: %i\n",(*param).timeHubbleExponent);
  printf("timeScaleFactorExponent: %i\n",(*param).timeScaleFactorExponent);
  printf("velocityUnitsInSI: %g\n",(*param).velocityUnitsInSI);
  printf("velocityHubbleExponent: %i\n",(*param).velocityHubbleExponent);
  printf("velocityScaleFactorExponent: %i\n",(*param).velocityScaleFactorExponent);
  printf("\nhalo trees group\n");
  printf("haloMassesIncludeSubhalos: %i\n",(*param).haloMassesIncludeSubhalos);
  printf("treesAreSelfContained: %i\n",(*param).treesAreSelfContained);
  printf("treesHaveSubhalos: %i\n",(*param).treesHaveSubhalos);
  printf("velocitiesIncludeHubbleFlow: %i\n",(*param).velocitiesIncludeHubbleFlow);
  printf("makeEnvironmentArrays: %i\n",(*param).makeEnvironmentArrays);
  printf("\ninput and output files\n");
  printf("inputFile: %s\n",(*param).inputFile);
  printf("outputFile: %s\n",(*param).galacticusOutputFile);

  printf("finished reading the parameter file.\n");

  fclose(file);

  return 0;
}
