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

/*------------------------------------------------------------------------
 *   Read Hessian from files  
 *  ----------------------------------------------------------------------*/

#include "fd.h"

void readhess(int nx, int ny, int nz, float ***  hess1, float ***  hess2, float ***hess3){

	extern int NX, NY, NZ, NXG, NYG, NZG, POS[4];
	extern FILE *FP;
float vp0=1240.0, vs0=730.0, rho0=1820.0;
		
	/* local variables */
	float rhov, vp, vs; /*qp, qs;*/
	int i, j, k, ii, jj, kk;
	FILE *fp_vs, *fp_vp, *fp_rho;
	char filename[STRING_SIZE];

	/* choose data format: ASCII: format=2, BINARY: format=3*/
	const int format=3; 
	

		

	   fprintf(FP,"\n...reading hess information from hess-files...\n");

	   sprintf(filename,"hess/hess.vp");
	   fp_vp=fopen(filename,"r");
	   if (fp_vp==NULL) err(" Could not open hess.vp ! ");

	   sprintf(filename,"hess/hess.vs");
	   fp_vs=fopen(filename,"r");
	   if (fp_vs==NULL) err(" Could not open  hess.vs! ");

	   sprintf(filename,"hess/hess.rho");
	   fp_rho=fopen(filename,"r");
	   if (fp_rho==NULL) err(" Could not open hess.rho ! ");
	   

	/* loop over global grid */
		 for (j=1;j<=NYG;j++){
			for (i=1;i<=NXG;i++){
				for (k=1;k<=NZG;k++){
				vp=readdsk(fp_vp, format);
				vs=readdsk(fp_vs, format);
				rhov=readdsk(fp_rho , format);
	
				/* only the PE which belongs to the current global gridpoint 
				is saving model parameters in his local arrays */
				if ((POS[1]==((i-1)/NX)) && 
				    (POS[2]==((j-1)/NY)) && 
				    (POS[3]==((k-1)/NZ))){
					ii=i-POS[1]*NX;
					jj=j-POS[2]*NY;
					kk=k-POS[3]*NZ;
					
					/*hess1[jj][ii][kk]=vp;
					hess2[jj][ii][kk]=vs;
					hess3[jj][ii][kk]=rhov;*/
					
					
					hess1[jj][ii][kk]=vp*pow(vp0,2);
					hess2[jj][ii][kk]=vs*pow(vs0,2);
					hess3[jj][ii][kk]=rhov*pow(rho0,2);
					
			
				}
				}
			}
		}

	fclose(fp_vp);
	fclose(fp_vs);
	fclose(fp_rho);	
	

}




