#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parameter.h"

int read_param(const char * filename, struct parameter * parameters, int * nparam) {

	FILE * file;
	file=fopen(filename,"r");
	if(file==0) {
	printf("Could not find file %s\n", filename);
	return 1;
	}


	*nparam=0;
	/* define parameters */
	/* filenames */
	strcpy(parameters[*nparam].name,"inputFile");
	strcpy(parameters[*nparam].group," ");
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = STRING;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"galacticusOutputFile");
	strcpy(parameters[*nparam].group," ");
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = STRING;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"makeEnvironmentArrays");
	strcpy(parameters[*nparam].group," ");
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	// cosmology group
	strcpy(parameters[*nparam].name,"HubbleParam");
	strcpy(parameters[*nparam].group,"/cosmology");
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"Omega0");
	strcpy(parameters[*nparam].group,"/cosmology");
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"OmegaLambda");
	strcpy(parameters[*nparam].group,"/cosmology");
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"OmegaBaryon");
	strcpy(parameters[*nparam].group,"/cosmology");
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"powerSpectrumIndex");
	strcpy(parameters[*nparam].group,"/cosmology");
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"sigma_8");
	strcpy(parameters[*nparam].group,"/cosmology");
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"transferFunction");
	strcpy(parameters[*nparam].group,"/cosmology");
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = STRING;
	*nparam+=1;

	/* group finder group */
	strcpy(parameters[*nparam].name,"groupFinderCode");
	strcpy(parameters[*nparam].group,"/groupFinder")  ;
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = STRING;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"linkingLength");
	strcpy(parameters[*nparam].group,"/groupFinder")  ;
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = STRING;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"minimumParticleNumber");
	strcpy(parameters[*nparam].group,"/groupFinder")  ;
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	/* simulation group */
	strcpy(parameters[*nparam].name,"errTolIntAccuracy");
	strcpy(parameters[*nparam].group,"/simulation")  ;
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"typeOfTimestepCriterion");
	strcpy(parameters[*nparam].group,"/simulation")  ;
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"boxSize");
	strcpy(parameters[*nparam].group,"/simulation")  ;
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"simulationCode");
	strcpy(parameters[*nparam].group,"/simulation")  ;
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = STRING;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"simulationICs");
	strcpy(parameters[*nparam].group,"/simulation")  ;
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = STRING;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"softeningKernel");
	strcpy(parameters[*nparam].group,"/simulation")  ;
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = STRING;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"softeningPlummerEquivalent");
	strcpy(parameters[*nparam].group,"/simulation")  ;
	parameters[*nparam].required = 0;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"startRedshift");
	strcpy(parameters[*nparam].group,"/simulation")  ;
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;


	/* units group */
	strcpy(parameters[*nparam].name,"lengthUnitsInSI");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;
	strcpy(parameters[*nparam].name,"lengthHubbleExponent");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;
	strcpy(parameters[*nparam].name,"lengthScaleFactorExponent");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"massUnitsInSI");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;
	strcpy(parameters[*nparam].name,"massHubbleExponent");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;
	strcpy(parameters[*nparam].name,"massScaleFactorExponent");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"timeUnitsInSI");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;
	strcpy(parameters[*nparam].name,"timeHubbleExponent");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;
	strcpy(parameters[*nparam].name,"timeScaleFactorExponent");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"velocityUnitsInSI");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = DOUBLE;
	*nparam+=1;
	strcpy(parameters[*nparam].name,"velocityHubbleExponent");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;
	strcpy(parameters[*nparam].name,"velocityScaleFactorExponent");
	strcpy(parameters[*nparam].group,"/units" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;


	/* halo trees group */
	strcpy(parameters[*nparam].name,"haloMassesIncludeSubhalos");
	strcpy(parameters[*nparam].group,"/haloTrees" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"treesAreSelfContained");
	strcpy(parameters[*nparam].group,"/haloTrees" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"treesHaveSubhalos");
	strcpy(parameters[*nparam].group,"/haloTrees" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	strcpy(parameters[*nparam].name,"velocitiesIncludeHubbleFlow");
	strcpy(parameters[*nparam].group,"/haloTrees" );
	parameters[*nparam].required = 1;
	parameters[*nparam].dtype = INT;
	*nparam+=1;

	int i;
	for(i=0;i<*nparam;i++) {
		parameters[i].found = 0;
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
		for(i=0; i<*nparam; i++) {
			if(strcmp(buf1,parameters[i].name) == 0) {
				if(parameters[i].dtype == DOUBLE) 
					parameters[i].d_val = atof(buf3);
				if(parameters[i].dtype == INT)
					parameters[i].i_val = atoi(buf3);
				if(parameters[i].dtype == STRING)
					strcpy(&(parameters[i].s_val[0]),buf3);
				parameters[i].found+=1;
				lineErrorFlag+=1; 
			}
		}
		if(lineErrorFlag==0) {
			printf("Error in read_param.c: did not find matching parameter for line:\n%s\n",buf);
			return 1;
		}
	}

	for(i=0;i<*nparam;i++) {
		if(parameters[i].found>1) {
			printf("Error in read_param.c: Multiple definition of parameter:\n%s\n",parameters[i].name);
			return 1;
		}
		if(parameters[i].found==0 && parameters[i].required==1) {
			printf("Error in read_param.c: Parameter %s not specified\n",parameters[i].name);
			return 1;     
		}
	}

	/* Output the values in the struct */
	printf("Values read from the parameter file:\n");
	printf("\n");
	for(i=0;i<*nparam;i++) {
		if(parameters[i].found==1) {

			if(parameters[i].dtype == DOUBLE) 
				printf(" %s\t %g\n",parameters[i].name,parameters[i].d_val);
			if(parameters[i].dtype == INT)
				printf(" %s\t %i\n",parameters[i].name,parameters[i].i_val);
			if(parameters[i].dtype == STRING)
				printf(" %s\t %s\n",parameters[i].name,parameters[i].s_val);
		}
	}

	printf("finished reading the parameter file.\n");

	fclose(file);

	return 0;
}
