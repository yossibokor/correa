/* ===========================================================================================
 *
 * Generate polygon
 *
 ==============================================================================================*/

#ifndef _POLYGON_H
#define _POLYGON_H

  #include "Types.h"
  #include "Vertex.h"

/* ===========================================================================================
 * Class for polygon
 ==============================================================================================*/

  class Polygon {

	public:
		// constructor
		Polygon() = default;

		// copy constructor
		Polygon(Polygon& polygon);

		std::vector<Vertex> vertices;
		std::vector<double > bdLength0;
		std::vector<double > bdLength;

		std::vector<std::pair<int, int> > edges;

		// area of the polygon
		double area();

		// area of the polygon
		double length();

		// Center and scale the polygon
		void centerScale(double range, int iscale);

		void boundaryLength0();
		void boundaryLength();

		double distorsion();

		void shift(Vector2D center) {
			for(VertexIter v = vertices.begin(); v != vertices.end(); v++) {
				v->position -= center;
			};
			std::cout << "shifting has occured, center was selected as (" << center.x << ", " << center.y << ")." << std::endl;
  		};


		int size() {
			return vertices.size();
		};

  };

/* ===========================================================================================
 * Computes the area inside a curve using the shoelace formula
 ==============================================================================================*/

  double Polygon::area()
  {
	double surface = 0.0;
	Vector2D a,b;

	for(VertexIter v = vertices.begin(); v != vertices.end(); v++) {
		a = v->position;
		b = v->prev->position;
		surface += b.x * a.y - a.x * b.y;
	}

	surface *= 0.5;


	return surface;
  }

/* ===========================================================================================
 * Computes the length of a polygon
 ==============================================================================================*/

  double Polygon::length()
  {
	double l = 0.0;
	Vector2D a, b;

	for(VertexIter v = vertices.begin(); v != vertices.end(); v++) {
		a = v->position;
		b = v->next->position;
		l += (a-b).norm();
	}

	return l;
  }

/* ===========================================================================================
 * Computes the length of boundary edges
 ==============================================================================================*/

  void Polygon::boundaryLength0()
  {
	
	int n = vertices.size();
	bdLength0.clear();
	bdLength0.resize(n);
	Vector2D a, b;

	for(VertexIter v = vertices.begin(); v != vertices.end(); v++) {
		a = v->position;
		b = v->next->position;
		bdLength0[v->index] = (a-b).norm();
	}

  }

/* ===========================================================================================
 * Computes the length of boundary edges
 ==============================================================================================*/

  void Polygon::boundaryLength()
  {
	
	int n = vertices.size();
	bdLength.clear();
	bdLength.resize(n);
	Vector2D a, b;

	for(VertexIter v = vertices.begin(); v != vertices.end(); v++) {
		a = v->position;
		b = v->next->position;
		bdLength[v->index] = (a-b).norm();
	}

  }

/* ===========================================================================================
 * Distorsion in edge lengths
 ==============================================================================================*/

  double Polygon::distorsion()
  {
	int n = vertices.size();
	double err=0;
	double val;
	for(int i = 0; i < n; i++) {
		val = ( (bdLength[i]-bdLength0[i]) /bdLength0[i]);
		err += 100*std::abs(val);
	}
	err = err/n;
	return err;
  }

/* ===========================================================================================
 * Center and scale the polygon
 ==============================================================================================*/

  void Polygon::centerScale(double range, int iscale)
  {
	Vector2D center, a;

	center[0] = 0; center[1] = 0;
	for(VertexIter v = vertices.begin(); v != vertices.end(); v++) {
		center += v->position;
	}
	center /= vertices.size();
	double r=0;

	for(VertexIter v = vertices.begin(); v != vertices.end(); v++) {
		v->position -= center;
//		a = v->position;
//		r = std::max(r, a.norm());
	}

	r = length();
	if(iscale !=0) {
		double scale = range/r;
		for(VertexIter v = vertices.begin(); v != vertices.end(); v++) {
			v->position *= scale;	
		}
	}
  
		void boundaryLength0();
		void boundaryLength();

		double distorsion();

  };


/* ===========================================================================================
 * Constructor
 ==============================================================================================*/


/*********************************************************************************
  Copy Constructor
 *********************************************************************************/

  Polygon::Polygon(Polygon& polygon) {

	// initialize vertices and copy from input polygon
	int nvertex = polygon.vertices.size();
	vertices.reserve(nvertex);
	std::vector<VertexIter> indexToVertex(nvertex);
	int i = 0;
	for (VertexIter v = polygon.vertices.begin(); v != polygon.vertices.end(); v++) {
		VertexIter vNew = vertices.insert(vertices.end(), Vertex());
		vNew->position = v->position;
		vNew->index = v->index;
		indexToVertex[i] = vNew;
		i++;
	}

	VertexIter v;
	int im1 = nvertex-1;
	for(int i = 0; i < nvertex-1; i++) {
		v = indexToVertex[i];
		v->prev = indexToVertex[im1];
		v->next = indexToVertex[i+1];
		im1 = i;
	}
	v = indexToVertex[nvertex-1];
	v->prev = indexToVertex[nvertex-2];
	v->next = indexToVertex[0];

	int nedges = polygon.edges.size();

	for(int i = 0; i < nedges; i++) {
		edges.push_back(polygon.edges[i]);
	}

  }

#endif
