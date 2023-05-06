/*
 	correa_bindings.h

 	Authors: Patrice Koehl, Department of Computer Science, University of California, Davis
				Yossi Bokor Bleile, Department of Mathematical Sciences, University of Aalborg, Aalborg
 	Date: April 2023
	Version: 1
*/

#ifndef _CORREABINDINGS_H_
#define _CORREABINDINGS_H_

/* ===============================================================================================
   System includes
   =============================================================================================== */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <limits>
#include <assert.h>
#include <algorithm>

/*================================================================================================
 Definitions for multi-threading
================================================================================================== */

#define NUM_THREADS 32

int threadids[NUM_THREADS];
pthread_t threads[NUM_THREADS];

/* ===============================================================================================
   Local includes
   =============================================================================================== */

#include "InOut.h"
#include "PolygonBuilder.h"
#include "Polygon.h"
#include "Ellipse.h"
#include "OT1.h"
#include "PH0.h"
#include "Curvature.h"
#include "Component.h"
#include "hera/wasserstein.h"
#include "Frechet.h"

namespace correa{   

	auto hera_wasserstein_distance(const std::vector<std::pair<double,double>> pd1, const std::vector<std::pair<double,double>> pd2, int q = 2) {
		hera::AuctionParams<double> hera_params;
		hera_params.max_num_phases = 800;
		hera_params.wasserstein_power = q;
		hera_params.internal_p = q;
		const hera::AuctionParams<double> params = hera_params;
		double w_q_dist = hera::wasserstein_dist<std::vector<std::pair<double,double>>>(pd1, pd2, params);
		return w_q_dist;
	};
	// construct a polygon with focal point center of mass of the vertices supplied
	auto initialise_polygon(std::string path_to_vertices) {

		PolygonBuilder pbuilder;
		Polygon polygon;
		INOUT inout; 
		int ndim;
		int npoint;

		double *X;
		X = nullptr;

		inout.read(path_to_vertices, &ndim, &npoint, &X);
		pbuilder.clean_points(&npoint, X);
		pbuilder.buildPolygon(npoint, X, polygon);
		
		// Center polygon
		int iscale = 0;
		double range = 100;
		polygon.centerScale(range,iscale);
		return polygon;
	} 

	auto initialise_polygon(std::string path_to_vertices, std::string path_to_focal_point) {

		PolygonBuilder pbuilder;
		Polygon polygon;
		INOUT inout; 
		int ndim;
		int npoint;

		double *X;
		X = nullptr;

		inout.read(path_to_vertices , &ndim, &npoint, &X);
		pbuilder.clean_points(&npoint, X);
		pbuilder.buildPolygon(npoint, X, polygon);

		// Center polygon
		int iscale = 0;
		double range = 100;
		polygon.centerScale(range,iscale);
		return polygon;
	}


	 auto load_polygon(std::string file_path) {
		Polygon polygon = initialise_polygon(file_path);
		return polygon;
	}

	auto load_polygon(std::string path_to_vertices, std::string path_to_focal) {
		Polygon polygon = initialise_polygon(path_to_vertices, path_to_focal);
		return polygon;
	}

	class PyPolygon{
		using PersistenceDiagram = std::vector<std::pair<double,double>>;
		private:
			std::tuple<double, double, double> ellipse_min_;
			std::tuple<double, double, double> ellipse_max_;
			std::tuple<double, double, double> ellipse_lsq_;
			double willmore_;
			PersistenceDiagram  persistence_diagram_;


		public:
			Polygon polygon;
			PyPolygon(std::string file_path) {
				polygon = load_polygon(file_path);
				Ellipse ellipse;
				Curvature curv;
				double a, b; 
				ellipse.EllipseMin(polygon, &a, &b);
				std::get<0>(ellipse_min_)= a;
				std::get<1>(ellipse_min_) = b;
				std::get<2>(ellipse_min_)= a/b;
				ellipse.EllipseMax(polygon, &a, &b);
				std::get<0>(ellipse_max_)= a;
				std::get<1>(ellipse_max_) = b;
				std::get<2>(ellipse_max_)= a/b;
				ellipse.EllipseLSQ(polygon, &a, &b);
				std::get<0>(ellipse_lsq_)= a;
				std::get<1>(ellipse_lsq_) = b;
				std::get<2>(ellipse_lsq_)= a/b;

				willmore_ = curv.Willmore(polygon);
				PH0 f(polygon.vertices);
				f.Persistence();
				persistence_diagram_ = f.persistence_diagram();
			}

			//std::vector<std::vector<double>> vertices();

			//auto polygon() {
			//	return polygon;
			//}
			auto persistence_diagram() {
				
				return persistence_diagram_;
			}
			int size() {
				return polygon.size();
			}

			double length() {
				return polygon.length();
			}

			double area() {
				return polygon.area();
			}

			auto vertices() {
				//std::cerr << "there are " << polygon.vertices.size() << " vertices in this polygon" << std::endl;
				std::vector<std::vector<double>> vertices;
				for (int i = 0; i < polygon.vertices.size(); i++) {
					std::vector<double> vert_i;
					vert_i.push_back(polygon.vertices[i].position.x);
					vert_i.push_back(polygon.vertices[i].position.y);
					vertices.push_back(vert_i);
				}
				return vertices;
			}

			auto ellipse_max() {
				//std::cerr << "ellipse_min_ is: (" << ellipse_min_[0] << ", " << ellipse_min_[1] << ", " << ellipse_min_[2] << ")." << std::endl;
				return ellipse_max_;
			}

			auto ellipse_max_a() {
				//std::cerr << "ellipse_max_ is: (" << ellipse_max_[0] << ", " << ellipse_max_[1] << ", " << ellipse_max_[2] << ")." << std::endl;
				return std::get<0>(ellipse_max_);
			}
			auto ellipse_max_b() {
				//std::cerr << "ellipse_max_ is: (" << ellipse_max_[0] << ", " << ellipse_max_[1] << ", " << ellipse_max_[2] << ")." << std::endl;
				return std::get<1>(ellipse_max_);
			}
			auto ellipse_max_ratio() {
				//std::cerr << "ellipse_max_ is: (" << ellipse_max_[0] << ", " << ellipse_max_[1] << ", " << ellipse_max_[2] << ")." << std::endl;
				return std::get<2>(ellipse_max_);
			}
		   
		   auto ellipse_min() {
				//std::cerr << "ellipse_min_ is: (" << ellipse_min_[0] << ", " << ellipse_min_[1] << ", " << ellipse_min_[2] << ")." << std::endl;
				return ellipse_min_;
			}

			auto ellipse_min_a() {
				//std::cerr << "ellipse_max_ is: (" << ellipse_max_[0] << ", " << ellipse_max_[1] << ", " << ellipse_max_[2] << ")." << std::endl;
				return std::get<0>(ellipse_min_);
			}
			auto ellipse_min_b() {
				//std::cerr << "ellipse_max_ is: (" << ellipse_max_[0] << ", " << ellipse_max_[1] << ", " << ellipse_max_[2] << ")." << std::endl;
				return std::get<1>(ellipse_min_);
			}
			auto ellipse_min_ratio() {
				//std::cerr << "ellipse_max_ is: (" << ellipse_max_[0] << ", " << ellipse_max_[1] << ", " << ellipse_max_[2] << ")." << std::endl;
				return std::get<2>(ellipse_min_);
			}

			auto ellipse_lsq() {
				//std::cerr << "ellipse_min_ is: (" << ellipse_min_[0] << ", " << ellipse_min_[1] << ", " << ellipse_min_[2] << ")." << std::endl;
				return ellipse_lsq_;
			}

			auto ellipse_lsq_a() {
				//std::cerr << "ellipse_max_ is: (" << ellipse_max_[0] << ", " << ellipse_max_[1] << ", " << ellipse_max_[2] << ")." << std::endl;
				return std::get<0>(ellipse_lsq_);
			};
			auto ellipse_lsq_b() {
				//std::cerr << "ellipse_max_ is: (" << ellipse_max_[0] << ", " << ellipse_max_[1] << ", " << ellipse_max_[2] << ")." << std::endl;
				return std::get<1>(ellipse_lsq_);
			};
			auto ellipse_lsq_ratio() {
				//std::cerr << "ellipse_max_ is: (" << ellipse_max_[0] << ", " << ellipse_max_[1] << ", " << ellipse_max_[2] << ")." << std::endl;
				return std::get<2>(ellipse_lsq_);
			};

			auto willmore() {
				//std::cerr << "willmore enegery is: " << willmore_ << "." << std::endl;
				return willmore_;
			};

			friend ostream &operator<<( ostream &out, PyPolygon &P ) { 
				out <<  "====================================\n";
				out << "Displaying Polygon Information:     \n";
				out << "Number of vertices:                 " << P.size() << "\n";
				out << "Length:                             " << P.length() << "\n";
				out << "Area:                               " << P.area() << "\n";
				out << "Sphericity (4*Pi*Area/L^2):         " <<  4*M_PI*P.area()/(P.length()*P.length()) << "\n";
				out << "Maximum volume inscribed ellipse:   a: " << P.ellipse_max_a() << " b: " << P.ellipse_max_b() << " ratio: " << P.ellipse_max_ratio()<< "\n";
				out << "Minimum volume inscribing ellipse:  a: " << P.ellipse_min_a() << " b: " << P.ellipse_min_b() << " ratio: " << P.ellipse_min_ratio() << "\n";
				out << "Least square ellipse:               a: " << P.ellipse_lsq_a() << " b: " << P.ellipse_lsq_b() << " ratio: " << P.ellipse_lsq_ratio() << "\n";
				out << "Wilmore energy:                     " << P.willmore() << "\n";
				out << "Persistence diagram: number of points:     " << P.persistence_diagram().size() << "\n";
				for (int i = 0; i < P.persistence_diagram().size(); i++) {
					out << "( " << P.persistence_diagram()[i].first << ", " << P.persistence_diagram()[i].second << ")" << std::endl;
				}
				return out;            
			};
	};  

 
/*!
* wrapper to compare pairs of polygons.
* 
* Has a variety of methods to calculate the distances between a pair of polygons. 
*/
	auto compare_polygons(PyPolygon poly1, PyPolygon poly2){ //}, int q=2, bool verbose=false) {
		bool verbose = true;
		int q =2;
		Frechet frechet;
		Ellipse ellipse;
		Curvature curv;
		const std::vector<std::pair<double,double>> pd1 = poly1.persistence_diagram();
		const std::vector<std::pair<double,double>> pd2 = poly2.persistence_diagram();
		double dWasserstein = hera_wasserstein_distance(pd1, pd2, q=q);
		double dFrechet = frechet.dFD(poly1.polygon, poly2.polygon);
		double a1_M, b1_M, a2_M, b2_M;
		double dMax = ellipse.dEllipseMax(poly1.polygon, poly2.polygon, &a1_M, &b1_M, &a2_M, &b2_M);
		double a1_m, b1_m, a2_m, b2_m;
		double dMin = ellipse.dEllipseMin(poly1.polygon, poly2.polygon, &a1_m, &b1_m, &a2_m, &b2_m);
		double a1_lsq, b1_lsq, a2_lsq, b2_lsq;
		double dLSQ = ellipse.dEllipseLSQ(poly1.polygon, poly2.polygon, &a1_lsq, &b1_lsq, &a2_lsq, &b2_lsq);
		double dWillmore = std::abs(curv.Willmore(poly1.polygon) - curv.Willmore(poly2.polygon));
		double dCurvOT = curv.curvOT(poly1.polygon, poly2.polygon);
		if (verbose) {
			std::cerr << "The two polygons are:" << std::endl;
			std::cerr << "Polygon 1:" << std::endl;
			std::cerr << poly1 << std::endl;
			std::cerr << "Polygon 2:" << std::endl;
			std::cerr << poly2 << std::endl;
			std::cerr << " and the distances between them are:" << std::endl;
			std::cerr << "Wasserstein distance (q="<<q<<"):	" << std::setw(7) << std::fixed  << dWasserstein << std::endl;
			std::cerr << "Frechet distance:					"  << std::setw(7) << std::fixed << dFrechet << std::endl;
			std::cerr << "Max Ellipse distance:	"  << std::setw(7) << std::fixed << dMax << std::endl;
			std::cerr << "Min Ellipse distance:	"  << std::setw(7) << std::fixed << dMin << std::endl;
			std::cerr << "LSQ Ellipse distance:	"  << std::setw(7) << std::fixed << dLSQ << std::endl;
			std::cerr << "Willmore distance:	"  << std::setw(7) << std::fixed << dWillmore << std::endl;
			std::cerr << "Curve OT distance:	"  << std::setw(7) << std::fixed << dCurvOT << std::endl;
		}
		return 0;// dWasserstein, dFrechet, dMax, dMin, dLSQ, dWillmore, dCurvOT;
	};		



	void print_polygon(PyPolygon P) {
		std::cerr << P << std::endl;
	}
}


#endif