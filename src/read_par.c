/*------------------------------------------------------------------------
 * Copyright (C) 2015 For the list of authors, see file AUTHORS.
 *
 * This file is part of IFOS3D.
 * 
 * IFOS3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.0 of the License only.
 * 
 * IFOS3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with IFOS3D. See file COPYING and/or 
 * <http://www.gnu.org/licenses/gpl-2.0.html>.
--------------------------------------------------------------------------*/

/*---------------------------------------------------------------
 * Reading FD-Parameters from input-file                           
 ----------------------------------------------------------------*/

#include "fd.h"

int read_par(FILE *fp_in){


	/* declaration of extern variables */
	extern int   NX, NY, NZ, SOURCE_SHAPE, SOURCE_TYPE, SNAP, SNAP_FORMAT, SNAP_PLANE;
	extern int DRX, DRY, L, SRCREC, FDORDER, FW, FDCOEFF;
	extern float DX, DY, DZ, TIME, DT, TS, *FL, TAU, PLANE_WAVE_DEPTH, PHI;
	extern float XREC1, XREC2, YREC1, YREC2, ZREC1, ZREC2, ALPHA, BETA;
	extern float REC_ARRAY_DEPTH, REC_ARRAY_DIST;
	extern int SEISMO, NDT, NDTSHIFT, NGEOPH, SEIS_FORMAT[6], FREE_SURF, READMOD, MOD_FORMAT[6], READREC, RUN_MULTIPLE_SHOTS;
	extern int BOUNDARY, REC_ARRAY, LOG, IDX, IDY, IDZ, ABS_TYPE;
	extern float TSNAP1, TSNAP2, TSNAPINC, REFREC[4], DAMPING, FPML, VPPML;
	extern char  MFILE[STRING_SIZE], SIGNAL_FILE[STRING_SIZE];
	extern char SNAP_FILE[STRING_SIZE], SOURCE_FILE[STRING_SIZE], REC_FILE[STRING_SIZE];
	extern char SEIS_FILE[STRING_SIZE],GRAD_FILE[STRING_SIZE], SEIS_OBS_FILE[STRING_SIZE],INV_FILE[STRING_SIZE];
	extern int NPROCX,NPROCY,NPROCZ;
	extern int ASCIIEBCDIC,LITTLEBIG,IEEEIBM;
	
	extern float FC,AMP, REFSRC[3], SRC_DT, SRCTSHIFT;
	extern int SRC_MF, SIGNAL_FORMAT[6], SRCOUT_PAR[6], FSRC, JSRC, LSRC;
	extern char SRCOUT_FILE[STRING_SIZE];
	extern char MOD_OUT_FILE[STRING_SIZE], HESS_FILE[STRING_SIZE];
	extern int METHOD;
	extern int ITMIN, ITMAX, FILT, NFMAX, TAST, NSHOTS_STEP, DAMPTYPE, HESS, READ_HESS, REC_HESS,EXTOBS,LBFGS;
	/*extern float F_INV;*/
	extern float TESTSTEP, WATER_HESS[3], WEIGHT[3], VP0, VS0, RHO0;
	extern int BFGSNUM, NUMPAR;
	
	/* definition of local variables */
	char s[256], cline[256]="";
	int  lineno=0, l, nvarin=0;
	
	
	if (fp_in==NULL) err(" Could not open input parameter file (ifos3d.inp)! ");

		while (fgets(cline,255,fp_in)){ /* leaves via break */
			/* If there are more than 255 characters in one line, this does not work. */
			if (cline[0]!='#'){      /* no comment line */
				lineno++;
				/* fprintf(stderr,"Reading Linenumber %i\n",lineno); */
				switch (lineno){
				case 1 :
					sscanf(cline,"%s =%i",s,&NPROCX);
					break;
				case 2 :
					sscanf(cline,"%s =%i",s,&NPROCZ); 
					/*not that internally "y" is used for the vertical coordinate,
					for usability reasons, we switch the "y" and "z" coordinate 
					so that "z" - as commonly used - denotes the depth (vertical direction)*/
					break;
				case 3 :
					sscanf(cline,"%s =%i",s,&NPROCY); 
					break;
				case 4 :
					sscanf(cline,"%s =%i",s,&NX);
					break;
				case 5 :
					sscanf(cline,"%s =%i",s,&NZ);
					break;
				case 6 :
					sscanf(cline,"%s =%i",s,&NY);
					break;
				case 7 :
					sscanf(cline,"%s =%f",s,&DX);
					break;
                                case 8 :
					sscanf(cline,"%s =%f",s,&DZ);
					break;
				case 9 :
					sscanf(cline,"%s =%f",s,&DY);
					break;
				case 10 :
					sscanf(cline,"%s =%i",s,&FDORDER);
					break;
				case 11 :
					sscanf(cline,"%s =%i",s,&FDCOEFF);
					break;	
				case 12 :
					sscanf(cline,"%s =%f",s,&TIME);
					break;
				case 13 :
					sscanf(cline,"%s =%f",s,&DT);
					break;					
				case 14 :
					nvarin=sscanf(cline,"%s =%i , %f , %f",s,&SOURCE_SHAPE,&FC,&AMP);
					switch(nvarin){
						case 0: 
						case 1: SOURCE_SHAPE=0;
							/* fprintf(stderr," Caution: SOURCE_SHAPE set to %d.\n",SOURCE_SHAPE); */
						case 2: FC=0.0; 
							/* fprintf(stderr," FC set to %d.\n",FC); */
						case 3: AMP=1.0;
							/* fprintf(stderr," AMP set to %d.\n",AMP); */
						/* case 4: break;
						default: fprintf(stderr,"This line of read_par.c should never be reached! [1]\n"); */
					}
					break;
				case 15 :
					sscanf(cline,"%s =%i",s,&SOURCE_TYPE);
					break;
				case 16 :
					sscanf(cline,"%s =%f",s,&ALPHA);		
					break;
				case 17 :
					sscanf(cline,"%s =%f",s,&BETA);
					break;
				case 18 :
					sscanf(cline,"%s =%f",s,&PLANE_WAVE_DEPTH);
					break;
				case 19 :
					sscanf(cline,"%s =%f",s,&PHI);
					break;
				case 20 :
					/* TS has to remain for the plane wave excitation*/
					nvarin=sscanf(cline,"%s =%f , %f",s,&TS,&SRC_DT);
					switch(nvarin){
						case 0: 
						case 1: TS=0; /* to be determined from input data */
						case 2: SRC_DT=DT;
					}					
					break;
				case 21 :
					nvarin=sscanf(cline,"%s =%s , %i , %i , %i , %i , %i , %i",s,SIGNAL_FILE,&SIGNAL_FORMAT[0],&SIGNAL_FORMAT[1],&SIGNAL_FORMAT[2],&SIGNAL_FORMAT[3],&SIGNAL_FORMAT[4],&SIGNAL_FORMAT[5]);
					switch(nvarin){
						case 0: 
						case 1: strcpy(SIGNAL_FILE,"\0");
						case 2: SIGNAL_FORMAT[0]=0;
						case 3: SIGNAL_FORMAT[1]=0;
						case 4: SIGNAL_FORMAT[2]=0;
						case 5: SIGNAL_FORMAT[3]=0;
						case 6: SIGNAL_FORMAT[4]=0;
						case 7: SIGNAL_FORMAT[5]=0;
						/* case 8: break;
						default: fprintf(stderr,"This line of read_par.c should never be reached! [2]\n");*/
					}
					break;
				
				case 22 :
					nvarin=sscanf(cline,"%s =%i , %i , %f , %f , %f",s,&SRCREC,&SRC_MF,&REFSRC[0],&REFSRC[1],&REFSRC[2]);
					switch(nvarin){
						case 0: 
						case 1: SRCREC=0; /* default: do not read source positions from file */
						case 2: SRC_MF=0; /* source positions in meter */
						case 3: REFSRC[0]=0.0; /* Reference x-coordinate */
						case 4: REFSRC[1]=0.0; /* Reference y-coordinate */
						case 5: REFSRC[2]=0.0; /* Reference z-coordinate (vertical!)*/
					}
					break;
				case 23 :
					nvarin=sscanf(cline,"%s =%s , %s , %i , %i , %i , %i , %i , %i",s,SOURCE_FILE,SRCOUT_FILE,&SRCOUT_PAR[0],&SRCOUT_PAR[1],&SRCOUT_PAR[2],&SRCOUT_PAR[3],&SRCOUT_PAR[4],&SRCOUT_PAR[5]);	
					switch(nvarin){
						case 0:
						case 1: strcpy(SOURCE_FILE,"\0");
						case 2: strcpy(SRCOUT_FILE,"\0");
						case 3: SRCOUT_PAR[0]=0;
						case 4: SRCOUT_PAR[1]=0;
						case 5: SRCOUT_PAR[2]=0;
						case 6: SRCOUT_PAR[3]=0;
						case 7: SRCOUT_PAR[4]=0;
						case 8: SRCOUT_PAR[5]=0;
					}
					break;
				case 24 :
					nvarin=sscanf(cline,"%s =%i , %f , %i , %i , %i",s,&RUN_MULTIPLE_SHOTS,&SRCTSHIFT,&FSRC,&JSRC,&LSRC);
					switch(nvarin){
						case 0:
						case 1: RUN_MULTIPLE_SHOTS=1;
						case 2: SRCTSHIFT=0.0;
						case 3: FSRC=0;
						case 4: JSRC=1;
						case 5: LSRC=2147483647; /* max int */
					}
					break;
				case 25 :
					nvarin=sscanf(cline,"%s =%i , %i , %i , %i , %i , %i , %i",s,&READMOD,&MOD_FORMAT[0],&MOD_FORMAT[1],&MOD_FORMAT[2],&MOD_FORMAT[3],&MOD_FORMAT[4],&MOD_FORMAT[5]);
					switch(nvarin){
						case 0:
						case 1: READMOD=0;
						case 2: MOD_FORMAT[0]=0;
						case 3: MOD_FORMAT[1]=0;
						case 4: MOD_FORMAT[2]=0;
						case 5: MOD_FORMAT[3]=0;
						case 6: MOD_FORMAT[4]=0;
						case 7: MOD_FORMAT[5]=0;							
					}
					break;
				case 26 :
					sscanf(cline,"%s =%s",s,MFILE);
					break;
				case 27 :
					sscanf(cline,"%s =%i",s,&L);
					FL=vector(1,L);
					break;
				case 28 :
					sscanf(cline,"%s =%f",s,&FL[1]);
					for (l=2;l<=L;l++) sscanf(cline,"%f",&FL[l]);
					break;
				case 29 :
					sscanf(cline,"%s =%f",s,&TAU);
					break;
				case 30 :
					sscanf(cline,"%s =%i",s,&FREE_SURF);
					break;
				case 31 :
					sscanf(cline,"%s =%i",s,&ABS_TYPE);
					break;	
				case 32 :
					sscanf(cline,"%s =%i",s,&FW);
					if (FW<0) FW=0;
					break;				
				case 33 :
					sscanf(cline,"%s =%f",s,&DAMPING);
					break;
				case 34 :
					sscanf(cline,"%s =%f",s,&FPML);
					break;

				case 35 :
					sscanf(cline,"%s =%f",s,&VPPML);
					break;	
				case 36:
					sscanf(cline,"%s =%i",s,&BOUNDARY);
					break;
				case 37 :
					sscanf(cline,"%s =%i",s,&SNAP);
					break;
				case 38 :
					sscanf(cline,"%s =%f",s,&TSNAP1);
					break;
				case 39 :
					sscanf(cline,"%s =%f",s,&TSNAP2);
					break;
				case 40 :
					sscanf(cline,"%s =%f",s,&TSNAPINC);
					break;
				case 41 :
					sscanf(cline,"%s =%i",s,&IDX);
					break;
				case 42 :
					sscanf(cline,"%s =%i",s,&IDZ);
					/*not that internally "y" is used for the vertical coordinate,
					for usability reasons, we switch the "y" and "z" coordinate 
					so that "z" - as commonly used - denotes the depth (vertical direction)*/
					break;
				case 43 :
					sscanf(cline,"%s =%i",s,&IDY);
					break;
				case 44 :
					sscanf(cline,"%s =%i",s,&SNAP_FORMAT);
					break;
				case 45 :
					sscanf(cline,"%s =%s",s,SNAP_FILE);
					break;
				case 46 :
					sscanf(cline,"%s =%i",s,&SNAP_PLANE);
					break;	
				case 47 :
					sscanf(cline,"%s =%i",s,&SEISMO);
					break;
				case 48 :
					sscanf(cline,"%s =%i",s,&READREC);
					break;
				case 49 :
					sscanf(cline,"%s =%s",s,REC_FILE);
					break;
				case 50 :
					sscanf(cline,"%s =%f ,%f , %f",s,&REFREC[1],&REFREC[3],&REFREC[2]);
					break;
				case 51 :
					sscanf(cline,"%s =%f ,%f ,%f",s,&XREC1,&ZREC1,&YREC1);
					break;
				case 52 :
					sscanf(cline,"%s =%f ,%f ,%f",s,&XREC2,&ZREC2,&YREC2);
					break;
				case 53 :
					sscanf(cline,"%s =%i",s,&NGEOPH);
					break;
				case 54 :
					sscanf(cline,"%s =%i",s,&REC_ARRAY);
					break;
				case 55 :
					sscanf(cline,"%s =%f",s,&REC_ARRAY_DEPTH);
					break;
				case 56 :
					sscanf(cline,"%s =%f",s,&REC_ARRAY_DIST);
					break;
				case 57 :
					sscanf(cline,"%s =%i",s,&DRX);
					break;
				case 58 :
					sscanf(cline,"%s =%i",s,&DRY);
					break;
				case 59 :
					nvarin=sscanf(cline,"%s =%i , %i",s,&NDT,&NDTSHIFT);
					switch(nvarin){ /* missing input values may be read as zero or lead to reduced nvarin */
						case 0: ;
						case 1: NDT=1;
							/* fprintf(stderr," NDT set to %d.\n",NDT); */
						case 2: NDTSHIFT=0;
							/* fprintf(stderr," NDTSHIFT set to %d.\n",NDTSHIFT); */
					}
					break;
				case 60 :
					nvarin=sscanf(cline,"%s =%i ,%i ,%i ,%i ,%i ,%i",
						s,&SEIS_FORMAT[0],&SEIS_FORMAT[1],&SEIS_FORMAT[2],&SEIS_FORMAT[3],&SEIS_FORMAT[4],&SEIS_FORMAT[5]);
					/* fprintf (stderr,"%d values read to SEIS_FORMAT.\n",nvarin-1); */
					switch(nvarin){
						case 0: ;
						case 1: SEIS_FORMAT[0]=0; /* seimogram data format */
						        /* fprintf(stderr," SEIS_FORMAT[0] set to %d.\n",SEIS_FORMAT[0]); */
						case 2: SEIS_FORMAT[1]=0; /* ASCII- / EBCDIC- output*/
						        /* fprintf(stderr," SEIS_FORMAT[1] set to %d.\n",SEIS_FORMAT[1]); */
						case 3: SEIS_FORMAT[2]=0; /* little / big endian output */
						        /* fprintf(stderr," SEIS_FORMAT[2] set to %d.\n",SEIS_FORMAT[2]); */
						case 4: SEIS_FORMAT[3]=0; /* ieee / ibm float output */
						        /* fprintf(stderr," SEIS_FORMAT[3] set to %d.\n",SEIS_FORMAT[3]); */
						case 5: SEIS_FORMAT[4]=0; /* output in meter / feet */
						        /* fprintf(stderr," SEIS_FORMAT[4] set to %d.\n",SEIS_FORMAT[4]); */
						case 6: SEIS_FORMAT[5]=0; /* maximum trace length */
						        /* fprintf(stderr," SEIS_FORMAT[5] set to %d.\n",SEIS_FORMAT[5]); */
					}
					if (SEIS_FORMAT[0]==4) {
						SEIS_FORMAT[0]=0;
						/* fprintf(stderr," SEIS_FORMAT[1] set to %d.\n",SEIS_FORMAT[1]); */
					}
					if (SEIS_FORMAT[0]==5) {
						SEIS_FORMAT[0]=0;
						SEIS_FORMAT[1]=1;
						/* fprintf(stderr," SEIS_FORMAT[1] set to %d.\n",SEIS_FORMAT[1]); */
						SEIS_FORMAT[2]=1;
						/* fprintf(stderr," SEIS_FORMAT[2] set to %d.\n",SEIS_FORMAT[2]); */
						SEIS_FORMAT[3]=1;
						/* fprintf(stderr," SEIS_FORMAT[3] set to %d.\n",SEIS_FORMAT[3]); */
						SEIS_FORMAT[4]=0;
						SEIS_FORMAT[5]=0;					
					}
					break;
				case 61 :
					sscanf(cline,"%s =%s",s,SEIS_FILE);
					break;
				case 62:
					sscanf(cline,"%s =%i",s,&METHOD);
	    				break;
				case 63 :
					sscanf(cline,"%s =%s",s,GRAD_FILE);
					break;
				case 64 :
					sscanf(cline,"%s =%s",s,MOD_OUT_FILE);
					break;	
				/*case 69 :
					sscanf(cline,"%s =%f",s,&F_INV);
					break;	*/
				case 65 :
					sscanf(cline,"%s =%s",s,SEIS_OBS_FILE);
					break;	
				case 66:
					sscanf(cline,"%s =%i",s,&EXTOBS);
	    				break;
				case 67 :
					sscanf(cline,"%s =%s",s,INV_FILE);
					break;
				case 68 :
					sscanf(cline,"%s =%s",s,HESS_FILE);
					break;	
				case 69 :	
					sscanf(cline,"%s =%i , %i",s,&ITMIN,&ITMAX);
					if(!METHOD) ITMAX=1;
					break;						
				case 70 :
					sscanf(cline,"%s =%i",s,&FILT);
					break;
				case 71 :
					sscanf(cline,"%s =%i",s,&NFMAX);
					break;	
				case 72 :
					sscanf(cline,"%s =%i",s,&TAST);
					break;	
				case 73:
					sscanf(cline,"%s =%f, %f, %f",s,&VP0,&VS0,&RHO0);
					break;	
				case 74 :
					sscanf(cline,"%s =%f, %f, %f",s,&WEIGHT[0],&WEIGHT[1],&WEIGHT[2]);	
					break;	
					
				case 75 :
					sscanf(cline,"%s =%i",s,&NSHOTS_STEP);
					break;	
				case 76 :
					sscanf(cline,"%s =%f",s,&TESTSTEP);
					break;
				case 77 :
					sscanf(cline,"%s =%i",s,&DAMPTYPE);
					break;
				case 78 :
					sscanf(cline,"%s =%i",s,&HESS);
					break;	
				case 79 :
					sscanf(cline,"%s =%i",s,&READ_HESS);
					break;	
				case 80 :
					sscanf(cline,"%s =%i",s,&REC_HESS);
					break;	
				case 81 :
					sscanf(cline,"%s =%f, %f, %f",s,&WATER_HESS[0],&WATER_HESS[1],&WATER_HESS[2]);
					break;	
				case 82 :
					sscanf(cline,"%s =%i",s,&LBFGS);
					break;
				case 83 :
					sscanf(cline,"%s =%i",s,&NUMPAR);
					break;	
				case 84 :
					sscanf(cline,"%s =%i",s,&BFGSNUM);
					break;	
				case 85 :
	    				nvarin=sscanf(cline,"%s =%i ,%i ,%i",s,&ASCIIEBCDIC,&LITTLEBIG,&IEEEIBM);
					switch(nvarin){
						case 0: ;
						case 1: ASCIIEBCDIC=0;
						case 2: LITTLEBIG=0;
						case 3: IEEEIBM=0;
					}					
	    				break;						    			
 				default:
					break;
				}		
			}
		}
		LOG=0;
		if(lineno<85) fprintf(stderr," Warning: only %d non-commentary lines of input parameters read (expected 83).\n",lineno);
		/* else if (lineno>71) fprintf(stderr," Warning: %d non-commentary lines of input parameters read \n \t(expected and interpreted: 67).\n",lineno); */
		/* else  fprintf(stderr," %d non-commentary lines of input parameters read.\n",lineno); */
		fclose(fp_in);
	return (lineno);
}

