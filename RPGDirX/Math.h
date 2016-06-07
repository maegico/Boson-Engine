#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include <string.h>

#define FAIL do{ getchar(); exit(EXIT_FAILURE); }while(false)

//will want to put this under a different project
//try to make this a dll

struct vec3{
	float x = 0, y = 0, z = 0;
};

union vec4{
	struct vertex{
		float x = 0, y = 0, z = 0, w = 0;
	};
	struct color{
		float r = 0, g = 0, b = 0, a = 0;
	};
};

class mat4{
	float* data;
	mat4::mat4(){
		data = (float*)calloc(16, sizeof(float));
		if (data = nullptr){
			FAIL;
		}
		//memset(data, 0, sizeof(float) * 16);
	}
	mat4::mat4(float* d){
		data = d;
	}
};