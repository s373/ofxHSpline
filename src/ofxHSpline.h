
// ofxHSpline - André Sier 2005, 2010
// hermite spline interpolation
//————————————————————————————————————————————————————————————————
//hspline - andré sier 2005
//
//using hermite splines (less elaborate than b-splines) on a bunch
//of equally spaced ctrl input points (the stride parameter of the 
//equation)
//
//smooth out path making






#pragma once


#include "ofMain.h"



class ofxHSpline {	
public:
	/// each spline
	ofPoint loc, ploc;
	float   alpha;
	
	bool go, end;
	
	float   stride, counter;
	int		whichPoint, numPoints;
	vector <ofPoint> pathPoints;	
	
	int maxPoint;
	bool done;
	
	
	vector <ofPoint> trailPts;
	int				numTrailPts;

	
	ofxHSpline(){ 
		done = false; go = true; end = false; whichPoint = 0; 
		pathPoints.clear();
		maxPoint = numPoints = 0;
		stride = 0.0001f;
		counter = 0.00f;
		loc.set(ofRandom(-1e5,1e5),ofRandom(-1e5,1e5),ofRandom(-1e5,1e5) );
		ploc.set(loc);
		alpha = 0.5f;
		numTrailPts = 1000;
	}
	
	
	
	
	
	
	void setup(vector <ofPoint> *pts, float strid = 0.0001, float alph = 0.5){
				
		ofPoint p;
		p = pts->at(0);
		loc.set(p);
		ploc = loc;
		
		alpha = alph;
		stride = strid; 
		counter = 0.0f;
		
		whichPoint = 1;
		numPoints = (int) pts->size();						
		maxPoint = numPoints-1;
		
		trailPts.clear();		
		pathPoints.clear();
		for(int i=0; i<numPoints; i++){						
			ofPoint p ( pts->at(i) );
			pathPoints.push_back(p);
		}
		
		go = true;
		end = true;
	}
	
				
	
	
	void update(float av = 1){
		
		if(!go)
			return;
		
		
		ofPoint a,b,c,d;
		
		float step2, step3, m0[3], m1[3], block[4];
		int pt = whichPoint;
		float step = counter - whichPoint;
		
		
		/// set pts, 3 cases
		
		if( pt == 0 ){
			a = pathPoints[0] ;
			b = pathPoints[0] ;
			c = pathPoints[1] ;
			d = pathPoints[3] ;
		} else if ( pt == (numPoints-2) ) {		
			a = pathPoints[(pt-1)] ;
			b = pathPoints[(pt+0)] ;
			c = pathPoints[(pt+1)] ;
			d = pathPoints[(pt+1)] ;			
		} else {
			a = pathPoints[(pt-1)] ;
			b = pathPoints[(pt+0)] ;
			c = pathPoints[(pt+1)] ;
			d = pathPoints[(pt+2)] ;
		}
		
		// hermite spline's method
		// p(t) = (2t^3 - 3t^2 + 1)p0 + (t^3 -2t^2+t)m0 + (t^3-t^2)m1 + (-2t^3 + 3t^2)p1
		// m_i = ((1-å)/2) ((p_i - p_i-1)+(p_i+1 - p_i)) 
		
		step2 = step*step;
		step3 = step2*step;
		
		// eq multiplier blocks
		block[0] = 2*step3 - 3*step2 + 1;
		block[1] = step3 - 2*step2 + step;
		block[2] = step3 - step2;
		block[3] = -2*step3 + 3*step2;
		
		m0[0] = ((1.0-alpha) * 0.5) * ((b.x - a.x) + (c.x - b.x)); 
		m1[0] = ((1.0-alpha) * 0.5) * ((c.x - b.x) + (d.x - c.x)); 
		
		m0[1] = ((1.0-alpha) * 0.5) * ((b.y - a.y) + (c.y - b.y)); 
		m1[1] = ((1.0-alpha) * 0.5) * ((c.y - b.y) + (d.y - c.y)); 
		
		m0[2] = ((1.0-alpha) * 0.5) * ((b.z - a.z) + (c.z - b.z)); 
		m1[2] = ((1.0-alpha) * 0.5) * ((c.z - b.z) + (d.z - c.z)); 
							
		ploc = loc; // guardar a pos anterior para direcção
		
		loc.x = block[0]*b.x + block[1]*m0[0] + block[2]*m1[0] + block[3]*c.x;
		loc.y = block[0]*b.y + block[1]*m0[1] + block[2]*m1[1] + block[3]*c.y;
		loc.z = block[0]*b.z + block[1]*m0[2] + block[2]*m1[2] + block[3]*c.z;		
		
		// advance stride		
		counter += stride * av;
				
		if(counter >= maxPoint){
			counter = 0.0f;		
			done = true;
		}
		if(counter < 0){
			counter = maxPoint;		
		}
		
		whichPoint = (int) counter;
		
		
		trailPts.push_back(loc);
		if(trailPts.size()>numTrailPts){
			trailPts.erase(trailPts.begin());
		}
		
	}
	
	
	void draw(){
		glPushMatrix();
		glTranslatef(loc.x, loc.y, loc.z);		
		ofCircle(0,0, 25);
		glPopMatrix();
	}
	
	void drawPath(){
		for(int j=0; j<pathPoints.size()-1;j++){
			ofPoint &o  = pathPoints[j];
			ofPoint &p  = pathPoints[j+1];			
			ofLine(o,p);
		}
		
	}
	void drawTrails(){
		for(int j=0; j<trailPts.size()-1;j++){
			ofPoint &o  = trailPts[j];
			ofPoint &p  = trailPts[j+1];			
			ofLine(o,p);
		}
		
	}
	
	
};