/***************************************************************************

    file                 : collide.cpp
    created              : Sun Mar 19 00:06:19 CET 2000
    copyright            : (C) 2000 by Eric Espie
    email                : torcs@free.fr
    version              : $Id$

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "sim.h"

#define ROAD_DAMMAGE	5
#define BARRIER_DAMMAGE	5
#define CAR_DAMMAGE	0.1

void
SimCarCollideZ(tCar *car)
{
    int 	i;
    t3Dd	normal;
    tdble	dotProd;
    
    for (i = 0; i < 4; i++) {
	if (car->wheel[i].state & SIM_SUSP_COMP) {
	    car->DynGCg.pos.z += car->wheel[i].susp.x - car->wheel[i].rideHeight;
	    if ((car->DynGCg.vel.ax * car->wheel[i].staticPos.y) < 0) {
		car->DynGCg.vel.ax = 0;
	    }
	    if ((car->DynGCg.vel.ay * car->wheel[i].staticPos.x) < 0) { 
		car->DynGCg.vel.ay = 0;
	    }
	    RtTrackSurfaceNormalL(&(car->trkPos), &normal);
	    dotProd = car->DynGCg.vel.x * normal.x + car->DynGCg.vel.y * normal.y + car->DynGCg.vel.z * normal.z;
	    if (dotProd < 0) {
		car->DynGCg.vel.x -= normal.x * dotProd;
		car->DynGCg.vel.y -= normal.y * dotProd;
		car->DynGCg.vel.z -= normal.z * dotProd;
		car->dammage += ROAD_DAMMAGE * fabs(dotProd);
	    }
	}
    }
}

const tdble BorderFriction = 0.00;

void
SimCarCollideXYScene(tCar *car)
{
    tTrackSeg	*seg = car->trkPos.seg;
    tTrkLocPos	trkpos;
    int		i, j;
    tDynPt	*corner;
    t3Dd	normal;
    tdble	dotProd, nx, ny;
    tWheel	*wheel;
    
    corner = &(car->corner[0]);
    for (i = 0; i < 4; i++, corner++) {
	seg = car->trkPos.seg;
	RtTrackGlobal2Local(seg, corner->pos.ax, corner->pos.ay, &trkpos, TR_LPOS_TRACK);
	seg = trkpos.seg;
	if (trkpos.toRight < 0.0) {
	    /* collision with right border */
	    if (seg->rside != NULL) {
		seg = seg->rside;
	    }
	    RtTrackSideNormalG(seg, corner->pos.ax, corner->pos.ay, TR_RGT, &normal);
	    car->DynGCg.pos.x -= normal.x * trkpos.toRight;
	    car->DynGCg.pos.y -= normal.y * trkpos.toRight;	    
	} else if (trkpos.toLeft < 0.0) {
	    /* collision with left border */
	    if (seg->lside != NULL) {
		seg = seg->lside;
	    }
	    RtTrackSideNormalG(seg, corner->pos.ax, corner->pos.ay, TR_LFT, &normal);
	    car->DynGCg.pos.x -= normal.x * trkpos.toLeft;
	    car->DynGCg.pos.y -= normal.y * trkpos.toLeft;	    
	} else {
	    continue;
	}
	car->blocked = 1;
	/* friction */
	car->collision |= 1;
	nx = normal.x;
	ny = normal.y;
	dotProd = (nx * car->DynGCg.vel.y + ny * car->DynGCg.vel.x) * BorderFriction;
	car->DynGCg.vel.x -= ny * dotProd;
	car->DynGCg.vel.y -= nx * dotProd;
	
	/* rebound */
	dotProd = normal.x * corner->vel.x + normal.y * corner->vel.y;
	car->dammage += BARRIER_DAMMAGE * fabs(dotProd);

	if (dotProd < 0) {
	    car->collision |= 2;
	    car->normal = normal;
	    car->collpos.x = corner->pos.ax;
	    car->collpos.y = corner->pos.ay;
	    
	    /* collision detected */
	    dotProd = nx * car->DynGCg.vel.x + ny * car->DynGCg.vel.y;

	    car->DynGCg.vel.x -= nx * dotProd * 1.1;
	    car->DynGCg.vel.y -= ny * dotProd * 1.1;
	    car->DynGCg.vel.az = -car->DynGCg.vel.az / 2.0;
	}
	for (j = 0; j < 4; j++) {
	    wheel = &(car->wheel[j]);
	    wheel->presx = wheel->sx;
	    wheel->preSpinVel = wheel->spinVel;
	}
    }
}

static void
SimCarCollideResponse(void * /*dummy*/, DtObjectRef obj1, DtObjectRef obj2, const DtCollData *collData)
{
    tCar	*car1 = (tCar*)obj1;
    tCar	*car2 = (tCar*)obj2;
    tCarElt	*carElt;


    sgVec2	n, p1, p2;
    sgVec2	v1ap, v1bp, v1ab;
    sgVec2	rap, rbp;
    sgVec2	v2a, v2b;
    sgVec2	tmpv;
    sgVec3	pa, pb, pab ;

    float	j;		/* impulse */
    float	rapn, rbpn;
    float	distpab;

    float	e = 0.5;	/* energy restitution */
    
    /* vector conversion from double to float */
    p1[0] = (float)collData->point1[0];
    p1[1] = (float)collData->point1[1];
    p2[0] = (float)collData->point2[0];
    p2[1] = (float)collData->point2[1];
    n[0]  = (float)collData->normal[0];
    n[1]  = (float)collData->normal[1];

    sgNormalizeVec2(n);
    
/*     printf("Coll %d <> %d : (%f, %f) - (%f, %f) - (%f, %f)    ", */
/* 	   car1->carElt->index, car2->carElt->index, */
/* 	   p1[0], p1[1], */
/* 	   p2[0], p2[1], */
/* 	   n[0], n[1]); */

    /* vector GP */
    sgSubVec2(rap, p1, (const float*)&(car1->statGC));
    sgSubVec2(rbp, p2, (const float*)&(car2->statGC));
    
    /* speed of collision points */
    v1ap[0] = car1->DynGCg.vel.x - car1->DynGCg.vel.az * rap[1];
    v1ap[1] = car1->DynGCg.vel.y + car1->DynGCg.vel.az * rap[0];
    v1bp[0] = car2->DynGCg.vel.x - car2->DynGCg.vel.az * rbp[1];
    v1bp[1] = car2->DynGCg.vel.y + car2->DynGCg.vel.az * rbp[0];
    
    /* relative speed */
    sgSubVec2(v1ab, v1ap, v1bp);
/*     printf("Coll %d <> %d : vab = %f\n", car1->carElt->index, car2->carElt->index, sgLengthVec2(v1ab)); */

    /* try to separate the cars */
    sgCopyVec2(pa, rap);
    sgCopyVec2(pb, rbp);
    pa[2] = pb[2] = 0;
    sgFullXformPnt3(pa, car1->carElt->_posMat);
    sgFullXformPnt3(pb, car2->carElt->_posMat);
    sgSubVec2(pab, pb, pa);
    distpab = sgLengthVec2(pab);
/*     printf("Coll %d <> %d : (%f, %f) - (%f, %f) dist = %f\n", */
/* 	   car1->carElt->index, car2->carElt->index, */
/* 	   pa[0], pa[1], pb[0], pb[1], */
/* 	   distpab); */
/*     printf("Coll %d <> %d : dist = %f\n", car1->carElt->index, car2->carElt->index, distpab); */
/*     if (distpab > 1.0) { */
/* 	return; */
/*     } */
    
    if ((car1->blocked == 0) && (car2->blocked == 0)) {
	/* move the 2 cars */
	sgScaleVec2(tmpv, n, MIN(distpab, 0.05));
	sgAddVec2((float*)&(car1->DynGCg.pos), tmpv);
	sgSubVec2((float*)&(car2->DynGCg.pos), tmpv);
	car1->blocked = 1;
	car2->blocked = 1;
    } else if (car1->blocked == 0) {
	sgScaleVec2(tmpv, n, MIN(distpab, 0.05));	
	sgAddVec2((float*)&(car1->DynGCg.pos), tmpv);
	car1->blocked = 1;
    } else if (car2->blocked == 0) {
	sgScaleVec2(tmpv, n, MIN(distpab, 0.05));	
	sgSubVec2((float*)&(car2->DynGCg.pos), tmpv);
	car2->blocked = 1;
    }

    if (sgScalarProductVec2(v1ab, n) > 0) {
	return;
    }
    
    /* impulse */
    rapn = sgScalarProductVec2(rap, n);
    rbpn = sgScalarProductVec2(rbp, n);
    
    
    j = -(1 + e) * sgScalarProductVec2(v1ab, n) /
	((car1->Minv + car2->Minv) +
	 rapn * rapn * car1->Iinv.z + rbpn * rbpn * car2->Iinv.z);

    car1->dammage += CAR_DAMMAGE * fabs(j);
    car2->dammage += CAR_DAMMAGE * fabs(j);

/*     if (j < 0) { */
/* 	return; */
/*     } */
    
    
/*     printf("Coll %d <> %d : j = %f\n", car1->carElt->index, car2->carElt->index, j); */

#define ROT_K	0.5

    sgScaleVec2(tmpv, n, j * car1->Minv);
    if (car1->collision & 4) {
	sgAddVec2(v2a, (const float*)&(car1->VelColl.x), tmpv);
	car1->VelColl.az = car1->VelColl.az + j * rapn * car1->Iinv.z * ROT_K;
    } else {
	sgAddVec2(v2a, (const float*)&(car1->DynGCg.vel), tmpv);
	car1->VelColl.az = car1->DynGCg.vel.az + j * rapn * car1->Iinv.z * ROT_K;
    }
    if (fabs(car1->VelColl.az) > 3.0) {
	car1->VelColl.az = SIGN(car1->VelColl.az) * 3.0;
    }
    
    sgCopyVec2((float*)&(car1->VelColl.x), v2a);

    /* Move the car for the collision lib */
    carElt = car1->carElt;
    sgMakeCoordMat4(carElt->pub->posMat, car1->DynGCg.pos.x, car1->DynGCg.pos.y, car1->DynGCg.pos.z - carElt->_statGC_z,
		    RAD2DEG(carElt->_yaw), RAD2DEG(carElt->_roll), RAD2DEG(carElt->_pitch));
    dtSelectObject(car1);
    dtLoadIdentity();
    dtTranslate(-carElt->_statGC_x, -carElt->_statGC_y, 0);
    dtMultMatrixf((const float *)(carElt->_posMat));

/*     printf("Vel %d : %f (%f, %f, %f) -> ", car2->carElt->index, j, */
/* 	   car2->DynGCg.vel.x, car2->DynGCg.vel.y, car2->DynGCg.vel.az); */
    
    sgScaleVec2(tmpv, n, -j * car2->Minv);
    if (car2->collision & 4) {
	sgAddVec2(v2b, (const float*)&(car2->VelColl), tmpv);
	car2->VelColl.az = car2->VelColl.az - j * rbpn * car1->Iinv.z * ROT_K;
    } else {
	sgAddVec2(v2b, (const float*)&(car2->DynGCg.vel), tmpv);
	car2->VelColl.az = car2->DynGCg.vel.az - j * rbpn * car1->Iinv.z * ROT_K;
    }
    if (fabs(car2->VelColl.az) > 3.0) {
	car2->VelColl.az = SIGN(car2->VelColl.az) * 3.0;
    }
    sgCopyVec2((float*)&(car2->VelColl), v2b);

    /* Move the car for the collision lib */
    carElt = car2->carElt;
    sgMakeCoordMat4(carElt->pub->posMat, car2->DynGCg.pos.x, car2->DynGCg.pos.y, car2->DynGCg.pos.z - carElt->_statGC_z,
		    RAD2DEG(carElt->_yaw), RAD2DEG(carElt->_roll), RAD2DEG(carElt->_pitch));
    dtSelectObject(car2);
    dtLoadIdentity();
    dtTranslate(-carElt->_statGC_x, -carElt->_statGC_y, 0);
    dtMultMatrixf((const float *)(carElt->_posMat));


/*     printf("(%f, %f, %f)\n", car2->DynGCg.vel.x, car2->DynGCg.vel.y, car2->DynGCg.vel.az); */
    
    car1->collision |= 4;
    car2->collision |= 4;

}


void 
SimCarCollideConfig(tCar *car)
{
    tCarElt *carElt;
    
    carElt = car->carElt;
    // The current car shape is a box...
    car->shape = dtBox(carElt->_dimension_x, carElt->_dimension_y, carElt->_dimension_z);
    dtCreateObject(car, car->shape);

    dtSetDefaultResponse(SimCarCollideResponse, DT_SMART_RESPONSE, NULL);
}


void
SimCarCollideCars(tSituation *s)
{
    tCar	*car;
    tCarElt	*carElt;
    int		i;
    
    for (i = 0; i < s->_ncars; i++) {
	carElt = s->cars[i];
	car = &(SimCarTable[carElt->index]);
	dtSelectObject(car);
	dtLoadIdentity();
	dtTranslate(-carElt->_statGC_x, -carElt->_statGC_y, 0);
	dtMultMatrixf((const float *)(carElt->_posMat));
	memset(&(car->VelColl), 0, sizeof(tPosd));
    }
    
/*     for (i = 0; i < 5; i++) { */
	if (dtTest() == 0) {
	    dtProceed();
/* 	    break; */
	}
/*     } */

    for (i = 0; i < s->_ncars; i++) {
	carElt = s->cars[i];
	car = &(SimCarTable[carElt->index]);
	if (car->collision & 4) {
	    car->DynGCg.vel.x = car->VelColl.x;
	    car->DynGCg.vel.y = car->VelColl.y;
	    car->DynGCg.vel.az = car->VelColl.az;
	}
    }
}

