// sat_to_mat.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include "vec.h"
#include "LineStream.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef vec3g<double> vec3;

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		return 0;
	}

	string off_file = argv[1];
	string moff_file = argv[2];

	ifstream moff_input(moff_file.c_str());
	LineInputStream moff_in(moff_input);
	ifstream off_input(off_file.c_str());
	LineInputStream off_in(off_input);
	ofstream ma_out(argv[3]);

	std::vector<vec3> vertices ;
	std::vector<double> radiuses;
	std::vector<vec3> off_vertices;

	std::vector<unsigned> vertice_index;
	std::vector<Face> face_struct_vector;
	std::set<pair<unsigned, unsigned>> edge_pair_set;
	
	if(!moff_in.ok())
		return 0;

	// handle the moff file
	moff_in.get_line();
	std::string keyword ;
	moff_in >> keyword ;
	if(keyword == "MOFF") {
		unsigned ver_number = 0, face_number = 0;
		double scale_factor;

		moff_in >> ver_number >> face_number >> scale_factor;

		for (unsigned i = 0; i < ver_number; i++)
		{
			if(!moff_in.eof()) {
				moff_in.get_line() ;
				vec3 p ;
				moff_in >> p ;
				vertices.push_back(p);
				
				double radius;
				moff_in >> radius;
				radiuses.push_back(radius / scale_factor);
			}
		}
	}
	
	// handle the off file
	if(!off_in.ok())
		return 0;

	off_in.get_line();
	off_in >> keyword ;
	if(keyword == "OFF") {
		unsigned vertice_number = 0, face_number = 0;
		off_in >> vertice_number;
		off_in >> face_number;

		for (unsigned i = 0; i < vertice_number; i++)
		{
			if(!off_in.eof()) {
				off_in.get_line() ;
				vec3 p ;
				off_in >> p ;
				off_vertices.push_back(p);

				vector<vec3>::iterator it = vertices.begin();
				for (; it != vertices.end(); it++)
				{
					if (std::abs((*it).x - p.x) < x_error_metric && std::abs((*it).y - p.y) < y_error_metric && std::abs((*it).z - p.z) < z_error_metric)
					{
						vertice_index.push_back(it - vertices.begin());
						break;
					}
				}

				if (it == vertices.end())
				{
					vertice_index.push_back(-1);
				}
			}
		}
				
		// store the edge and face information
		for (unsigned i = 0; i < face_number; i++)
		{
			unsigned temp, x, y, z;
			if(!off_in.eof()) {
				off_in.get_line() ;
				off_in >> temp >> x >> y >> z ;

				edge_pair_set.insert(pair<unsigned, unsigned>(x, y));
				edge_pair_set.insert(pair<unsigned, unsigned>(y, z));
				edge_pair_set.insert(pair<unsigned, unsigned>(x, z));

				Face face_index = {x, y, z};
				face_struct_vector.push_back(face_index);
			}
		}		
		
		ma_out << vertice_number << " " << edge_pair_set.size() << " " << face_number << endl;

		// store the vertice information
		for (unsigned i = 0; i < vertice_number; i++)
		{
			unsigned index = vertice_index[i];
			if (index != -1)
			{
				ma_out << "v " << off_vertices[i].x << " " << off_vertices[i].y << " " << off_vertices[i].z << " " << radiuses[index] << endl;
			}
			else
			{
				ma_out << "v " << off_vertices[i].x << " " << off_vertices[i].y << " " << off_vertices[i].z << " " << 0 << endl;
			}
		}

		// output the information of the edge
		for (set<pair<unsigned, unsigned>>::iterator pt = edge_pair_set.begin(); pt != edge_pair_set.end(); pt++)
		{
			ma_out << "e " << (*pt).first << " " << (*pt).second << endl;
		}

		// output the information of the face
		for (vector<Face>::iterator it = face_struct_vector.begin(); it != face_struct_vector.end(); it++)
		{
			ma_out << "f " << it->x << " " << it->y << " " << it->z << endl;
		}

	}
	
	// close the stream
	ma_out.close();
	moff_input.close();
	off_input.close();

	return 0;
}

